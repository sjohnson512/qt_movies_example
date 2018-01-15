#include "dbinterface.h"

DBInterface::DBInterface()
{
   m_database = QSqlDatabase::addDatabase("QSQLITE");
   QString applicationDir = QCoreApplication::applicationDirPath();
   QString dbPath = QDir::cleanPath(applicationDir + "../../../movies.db");
   qDebug() << "database path: " + dbPath;

   m_database.setDatabaseName(dbPath);

   if (!m_database.open())
   {
      qDebug() << "Error: failed to connecti with database";
   }
   else
   {
      qDebug() << "Database: connection ok";
   }
}

QStringList DBInterface::getGenres()
{
    QSqlQuery query("SELECT * FROM genre");
    int idName = query.record().indexOf("name");

    QStringList nameList;
    while (query.next())
    {
       QString name = query.value(idName).toString();
       nameList << name;
    }

    return nameList;
}

QStringList DBInterface::getActorsForMovie(int movieID)
{
    QSqlQuery query;
    query.prepare("SELECT actor.name as name "
                   "FROM actor "
                   "INNER JOIN cast_member ON cast_member.actor_id = actor.id "
                   "WHERE cast_member.movie_id = :movieID");
    query.bindValue(":movieID", movieID);

    QStringList nameList;
    if (query.exec())
    {
        int idName = query.record().indexOf("name");
        while (query.next())
        {
           QString name = query.value(idName).toString();
           nameList << name;
        }
    }
    else
    {
        qDebug() << "Sql error in getActorsForMovie:" << query.lastError().text();
    }

    return nameList;
}

QList<MovieData> DBInterface::getMovies()
{
    QSqlQuery query("SELECT movie.id as id, genre.name as genre, genre_id, title, year, rating "
                    "FROM movie "
                    "INNER JOIN genre ON movie.genre_id = genre.id");

    QList<MovieData> movieList;
    if (query.exec())
    {
        int idId = query.record().indexOf("id");
        int idGenre = query.record().indexOf("genre");
        int idGenreId = query.record().indexOf("genre_id");
        int idTitle = query.record().indexOf("title");
        int idYear = query.record().indexOf("year");
        int idRating = query.record().indexOf("rating");
        while (query.next())
        {
           MovieData movieData;
           movieData.id = query.value(idId).toInt();
           movieData.genre = query.value(idGenre).toString();
           movieData.genreId = query.value(idGenreId).toInt();
           movieData.title = query.value(idTitle).toString();
           movieData.year = query.value(idYear).toInt();
           movieData.rating = query.value(idRating).toDouble();
           movieList << movieData;
        }
    }
    else
    {
        qDebug() << "Sql error in getMovies:" << query.lastError().text();
    }

    return movieList;
}

int DBInterface::insertMovie(const QString& title, int actorListID, int genreID, int year, double rating)
{
    QSqlQuery query("INSERT INTO movie(title, actor_list_id, genre_id, year, rating) "
                    "values(:title,:actor_list_id,:genre_id,:year,:rating");
    query.bindValue(":title", title);
    query.bindValue(":actor_list_id", actorListID);
    query.bindValue(":genre_id", genreID);
    query.bindValue(":year", year);
    query.bindValue(":rating", rating);
    query.exec();

    return query.lastInsertId().toInt();
}
