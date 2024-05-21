import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime
import locale

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    app.logger.debug('A value for debugging')
    quotes = db.execute("SELECT symbol, name, price, SUM(quantity) as quantity, SUM(quantity * price) as total FROM transactions t WHERE user_id=? GROUP BY symbol, price", session["user_id"])
    app.logger.debug(quotes)
    user = db.execute("SELECT cash FROM users WHERE id=? LIMIT 1", session["user_id"])
    currentMoney = user[0]['cash'] - sum([quote['total'] for quote in quotes])
    userDto = {'quotes': quotes, 'currentMoney': currentMoney, 'originalMoney': user[0]['cash']}
    return render_template("index.html", user=userDto)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
            if request.form.get("symbol") and request.form.get("shares") is not None and request.form.get("shares").isdigit():
                quote = lookup(request.form.get("symbol"))
                if quote is not None:
                    user_cash = db.execute("SELECT cash FROM users WHERE id=? LIMIT 1", session["user_id"])[0]['cash']
                    quantity = int(request.form.get("shares"))
                    if user_cash > quote["price"] * quantity:
                        db.execute("INSERT INTO transactions(user_id, symbol, name, type, price, quantity, createdAt)VALUES(?, ?, ?, ?, ?, ?, ?)",
                                    session["user_id"], quote["symbol"], quote["name"], "BUY", quote["price"], quantity, datetime.now())
                        return redirect("/")
                    return apology("you do not have enough money to buy these quotes", 400)
            return apology("you did not send a valid symbol or correct number of shares", 400)
    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    if session["user_id"]:
        transactions = db.execute("SELECT symbol, quantity, price, createdAt FROM transactions WHERE user_id=?", session["user_id"])
        app.logger.debug(transactions)
        locale.setlocale(locale.LC_ALL, 'en_US.UTF-8')
        for transaction in transactions:
            transaction['price'] = locale.currency(transaction['price'], grouping=True)
        return render_template("history.html", transactions=transactions)
    return apology("you do not have permission, you need to login again.", 403)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        if request.form.get("symbol"):
            quote = lookup(request.form.get("symbol"))
            if quote is not None:
                locale.setlocale(locale.LC_ALL, 'en_US.UTF-8')
                quoteDto = { "name": quote["name"], "symbol": quote["symbol"], "price": locale.currency(quote["price"], grouping=True) }
                return render_template("quote.html", quote=quoteDto)
        return apology("you did not send a valid symbol", 400)
    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        if request.form.get("username") and request.form.get("password") and request.form.get("confirmation"):
            if(request.form.get("password") == request.form.get("confirmation")):
                user_id = db.execute("SELECT id FROM users WHERE username=? LIMIT 1", request.form.get("username"))
                app.logger.debug(user_id)
                if len(user_id) == 0:
                    user_id = db.execute("INSERT INTO users(username, hash)VALUES(?, ?)", request.form.get("username"), generate_password_hash(request.form.get("password")))
                    session["user_id"] = user_id
                    return redirect("/")
                return apology("the username is invalid", 400)
            return apology("the password and the confirm password needs to be equals", 400)
        return apology("the username, the password or the confirm password is invalid", 400)
    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        if request.form.get("symbol") and request.form.get("shares") is not None and request.form.get("shares").isdigit():
            quote = lookup(request.form.get("symbol"))
            quantities = int(request.form.get("shares"))
            if quote is not None:
                quotes = db.execute("SELECT 1 FROM transactions WHERE user_id=? and symbol=? GROUP BY symbol HAVING SUM(quantity) >= ?", session["user_id"], request.form.get("symbol"), quantities)
                if len(quotes) > 0:
                    db.execute("INSERT INTO transactions(user_id, symbol, name, type, price, quantity, createdAt)VALUES(?, ?, ?, ?, ?, ?, ?)",
                                session["user_id"], quote["symbol"], quote["name"], "SELL", quote["price"], quantities * -1, datetime.now())
                    return redirect("/")
                return apology("you do not have enough quotes to sell", 400)
        return apology("the symbol or the shares is incorrect.", 400)
    quotes = db.execute("SELECT symbol FROM transactions WHERE user_id=? GROUP BY symbol HAVING SUM(quantity) > 0", session["user_id"])
    if len(quotes) > 0:
        return render_template("sell.html", quotes=quotes)
    return apology("you do not have quotes to sell", 400)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
