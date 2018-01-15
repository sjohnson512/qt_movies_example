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
    QStringList nameList;
    QSqlQuery query("SELECT * FROM genre");
    int idName = query.record().indexOf("name");
    while (query.next())
    {
       QString name = query.value(idName).toString();
       nameList << name;
    }

    return nameList;
}
