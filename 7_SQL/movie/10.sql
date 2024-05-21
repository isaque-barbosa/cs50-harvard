SELECT DISTINCT(p.name)
FROM people p
INNER JOIN directors d ON d.person_id = p.id
INNER JOIN movies m ON d.movie_id = m.id
INNER JOIN ratings r ON r.movie_id = m.id
WHERE r.rating >= 9.0
