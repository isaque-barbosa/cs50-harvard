SELECT p.name
FROM people p
LEFT JOIN stars s ON s.person_id = p.id
LEFT JOIN movies m ON s.movie_id = m.id
WHERE m.title = 'Toy Story'
