#ifndef DBINTERFACE_H
#define DBINTERFACE_H

#include <QtSql>


class DBInterface
{
public:
    DBInterface();

    QStringList getGenres();
    QStringList getActorsForMovie(int movieID);
    int         insertMovie(const QString& title, int actorListID, int genreID, int year, double rating);

private:
    QSqlDatabase m_database;


};

#endif // DBINTERFACE_H

