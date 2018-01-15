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
    void             updateMovie(int movieId, const QString &title, int genreId, int year, double rating);
    int              insertMovie(const QString& title, int genreID, int year, double rating);

private:
    QSqlDatabase m_database;


};

#endif // DBINTERFACE_H

