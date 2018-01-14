CREATE TABLE movie(
   id            INT PRIMARY KEY NOT NULL,
   genre         INT,
   actor_list_id INT,
   title         CHAR(75),
   year          INT,
   rating        REAL
   
   FOREIGN KEY(actor_list_id) REFERENCES actor_list(id)
);

CREATE TABLE actor_list(
   id       INT PRIMARY KEY NOT NULL,
   actor_id INT
   FOREIGN KEY(actor_id) REFERENCES actor(id)
);

CREATE TABLE actor(
   id         INT PRIMARY KEY NOT NULL,
   first_name CHAR(50),
   last_name  CHAR(50)
);