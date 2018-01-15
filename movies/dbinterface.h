#ifndef DBINTERFACE_H
#define DBINTERFACE_H

#include <QtSql>

struct MovieData
{
    int     id;
    QString genre;
    int     genreId;
    QString title;
    int     year;
    double  rating;
};

class DBInterface
{
public:
    DBInterface();

    QStringList      getGenres();
    QStringList      getActorsForMovie(int movieID);
    QList<MovieData> getMovies();
    int              insertMovie(const QString& title, int actorListID, int genreID, int year, double rating);

private:
    QSqlDatabase m_database;


};

#endif // DBINTERFACE_H

