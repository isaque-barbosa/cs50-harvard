SELECT p2.name
FROM people p1
INNER JOIN stars s1 ON s1.person_id = p1.id
INNER JOIN movies m ON s1.movie_id = m.id
INNER JOIN stars s2 ON s2.movie_id = m.id
INNER JOIN people p2 ON s2.person_id = p2.id
WHERE p1.name = 'Kevin Bacon' AND p1.birth = 1958 AND p2.name != 'Kevin Bacon';
