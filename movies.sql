-- Create a new movie database and populate it with sample data
-- Usage: sqlite3 movies.db < movies.sql

CREATE TABLE movie(
   id            INTEGER PRIMARY KEY NOT NULL,
   genre_id      INTEGER,
   title         CHAR(75),
   year          INTEGER,
   rating        REAL,
   actors		 CHAR(200),
   FOREIGN KEY(genre_id) REFERENCES genre(id)
);

CREATE TABLE genre(
   id   INTEGER PRIMARY KEY NOT NULL,
   name CHAR(25)
);

INSERT INTO genre(name)
VALUES
    ('Action'),
    ('Drama'),
    ('Comedy'),
    ('Documentary'),
    ('Horror'),
    ('SciFi');
	
INSERT INTO movie (genre_id, title, year, rating, actors)
VALUES	
	(2, 'My Madeup Movie', 2018, 4.7, 'Some Actor, Another Actor, An Actress'),
	(3, 'A Really Good Movie', 2017, 3.0, 'Some Actor, Another Actor, An Actress'),
	(4, 'Another Movie', 2012, 3.0, 'Actress 2, Actress 3, Actor 4'),
	(3, 'Yet Another Movie', 2012, 4.9, 'Actor 3, Acress 2, Actress 3');
