-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT * FROM crime_scene_reports;
SELECT * FROM crime_scene_reports c WHERE c.month = 7 and c.day = 28;
SELECT * FROM interviews c WHERE c.month = 7 and c.day = 28 and c.year = 2020;
SELECT * FROM flights c WHERE c.month = 7 and c.day = 29 and c.year = 2020;
SELECT c.*, a.full_name FROM flights c INNER JOIN airports a ON a.id = c.origin_airport_id WHERE c.month = 7 and c.day = 29 and c.year = 2020;
SELECT c.*, a.full_name FROM flights c INNER JOIN airports a ON a.id = c.destination_airport_id WHERE c.month = 7 and c.day = 29 and c.year = 2020;
SELECT p.name, c.* FROM atm_transactions c INNER JOIN bank_accounts b ON b.account_number = c.account_number INNER JOIN people p ON p.id = b.person_id WHERE c.month = 7 and c.day = 29 and c.year = 2020;
SELECT p.name, c.* FROM atm_transactions c INNER JOIN bank_accounts b ON b.account_number = c.account_number INNER JOIN people p ON p.id = b.person_id WHERE c.month = 7 and c.day = 29 and c.year = 2020 and c.atm_location = 'Fifer Street';
SELECT * FROM courthouse_security_logs c WHERE c.month = 7 and c.day = 29 and c.year = 2020;
SELECT * FROM flights c INNER JOIN passengers p ON p.flight_id = c.id INNER JOIN people pe ON pe.passport_number = p.passport_number WHERE c.month = 7 and c.day = 29 and c.year = 2020 and pe.name LIKE 'Stephanie%';
SELECT * FROM flights c INNER JOIN passengers p ON p.flight_id = c.id INNER JOIN people pe ON pe.passport_number = p.passport_number WHERE c.month = 7 and c.day = 29 and c.year = 2020 and pe.name LIKE 'Tyler%';
SELECT c.*, p.name FROM courthouse_security_logs c INNER JOIN people p ON p.license_plate = c.license_plate WHERE c.month = 7 and c.day = 29 and c.year = 2020;
SELECT p.name, c.* FROM atm_transactions c INNER JOIN bank_accounts b ON b.account_number = c.account_number INNER JOIN people p ON p.id = b.person_id WHERE p.id in (SELECT p.id FROM courthouse_security_logs c INNER JOIN people p ON p.license_plate = c.license_plate WHERE c.month = 7 and c.day = 29 and c.year = 2020);
select * from phone_calls pc where pc.month = 7 and pc.day = 28 and pc.year = 2020;
SELECT DISTINCT(p.name), f.*, c.hour, c.minute, ai.full_name, ai.city
FROM people p
INNER JOIN bank_accounts b ON b.person_id = p.id
INNER JOIN atm_transactions a ON a.account_number = b.account_number
INNER JOIN courthouse_security_logs c ON c.license_plate = p.license_plate
INNER JOIN passengers pa ON pa.passport_number = p.passport_number
INNER JOIN flights f ON f.id = pa.flight_id
INNER JOIN airports ai ON ai.id = f.destination_airport_id
INNER JOIN phone_calls pc ON pc.caller = p.phone_number
WHERE c.month = 7 and c.day = 28 and c.year = 2020 and c.activity = 'exit'
and a.month = 7 and a.day = 28 and a.year = 2020 and a.atm_location = 'Fifer Street'
and pc.month = 7 and pc.day = 28 and pc.year = 2020 and pc.duration <= 60
and f.month = 7 and f.day = 29 and f.year = 2020
ORDER BY f.year, f.month, f.day, f.hour, f.minute;
SELECT p.name, c.* FROM atm_transactions c INNER JOIN bank_accounts b ON b.account_number = c.account_number INNER JOIN people p ON p.id = b.person_id WHERE c.month = 7 and c.day = 28 and c.year = 2020 and c.atm_location = 'Fifer Street';
SELECT c.*, p.name FROM courthouse_security_logs c INNER JOIN people p ON p.license_plate = c.license_plate WHERE c.month = 7 and c.day = 28 and c.year = 2020 and p.name = 'Eugene';
SELECT p.name, c.* FROM atm_transactions c INNER JOIN bank_accounts b ON b.account_number = c.account_number INNER JOIN people p ON p.id = b.person_id WHERE c.transaction_type = 'withdraw' and c.month = 7 and c.day = 28 and c.year = 2020 and c.atm_location = 'Fifer Street';
