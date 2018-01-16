-- Create a new movie database and populate it with sample data
-- Usage: sqlite3 movies.db < movies.sql

CREATE TABLE movie(
   id            INTEGER PRIMARY KEY NOT NULL,
   genre_id      INTEGER,
   title         CHAR(75),
   year          INTEGER,
   rating        REAL,
   FOREIGN KEY(genre_id) REFERENCES genre(id)
);

CREATE TABLE cast_member(
   movie_id INTEGER NOT NULL,
   actor_id INTEGER NOT NULL,
   FOREIGN KEY(actor_id) REFERENCES actor(id),
   FOREIGN KEY(movie_id) REFERENCES movie(id)
);

CREATE TABLE actor(
   id   INTEGER PRIMARY KEY NOT NULL,
   name CHAR(75)
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
	
INSERT INTO actor(name)
VALUES
    ('Casey Affleck'),
    ('Leonardo DiCaprio'),
    ('Eddie Redmayne'),
    ('Matthew McConaughey'),
    ('Daniel Day-Lewis'),
    ('Emma Stone'),
    ('Brie Larson'),
    ('Julianne Moore'),
    ('Cate Blanchett'),
    ('Jennifer Lawrence');
	
INSERT INTO cast_member(movie_id, actor_id)
VALUES
	(1,1),
	(1,2),
	(1,6),
	(2,5),
	(2,3),
	(3,4),
	(3,7),
	(3,8),
	(3,9),
	(4,1),
	(4,9);

INSERT INTO movie (genre_id, title, year, rating)
VALUES	
	(2, 'My Madeup Movie', 2018, 4.7),
	(3, 'A Really Good Movie', 2017, 3.0),
	(4, 'Another Movie', 2012, 3.0),
	(3, 'Yet Another Movie', 2012, 4.9);
