SELECT AVG(rating)
FROM ratings r
INNER JOIN movies m ON m.id = r.movie_id
WHERE m.year = 2012
