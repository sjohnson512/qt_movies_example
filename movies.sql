CREATE TABLE movie(
   id            INTEGER PRIMARY KEY NOT NULL,
   genre_id      INTEGER,
   actor_list_id INTEGER,
   title         CHAR(75),
   year          INTEGER,
   rating        REAL,
   FOREIGN KEY(actor_list_id) REFERENCES actor_list(id),
   FOREIGN KEY(genre_id) REFERENCES genre(id)
);

CREATE TABLE actor_list(
   id       INTEGER PRIMARY KEY NOT NULL,
   actor_id INTEGER,
   FOREIGN KEY(actor_id) REFERENCES actor(id)
);

CREATE TABLE actor(
   id   INTEGER PRIMARY KEY NOT NULL,
   name CHAR(75)
);

CREATE TABLE genre(
   id   INTEGER PRIMARY KEY NOT NULL,
   name CHAR(25)
);

INSERT INTO genre (name)
VALUES
    ('Action'),
    ('Drama'),
    ('Comedy'),
    ('Documentary'),
    ('Horror'),
    ('SciFi')
