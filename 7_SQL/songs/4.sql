SELECT s.name
FROM songs s
WHERE s.valence > 0.75
and s.energy > 0.75
and s.danceability > 0.75
