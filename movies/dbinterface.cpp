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
        qDebug() << "Sql error:" << query.lastError().text();
    }

    qDebug() << "actorList: "  << nameList;

    return nameList;
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
