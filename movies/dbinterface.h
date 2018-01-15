#ifndef DBINTERFACE_H
#define DBINTERFACE_H

#include <QtSql>


class DBInterface
{
public:
    DBInterface();

    QStringList getGenres();
private:
    QSqlDatabase m_database;


};

#endif // DBINTERFACE_H

