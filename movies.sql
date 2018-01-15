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
    ('Cale Blanchett'),
    ('Jennifer Lawrence');
	
INSERT INTO cast_member(movie_id, actor_id)
VALUES
	(0,0),
	(0,2),
	(0,6);

INSERT INTO movie (genre_id, title, year, rating)
VALUES	
	(2, 'My Madeup Movie', 2018, 4.7);
