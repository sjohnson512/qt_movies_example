#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <dbinterface.h>
#include <QTreeWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    // Screen updates
    void refreshMovies();
    void refreshMovieDetails();

    // Edit data
    void addMovie();
    void updateMovie();
    void deleteMovie();

    // Search
    void searchPrevious();
    void searchNext();

private:
    Ui::MainWindow *ui;

    DBInterface    m_dbInterface;
    int            m_currentMovieID;

    const int MOVIE_TITLE_COL  = 0;
    const int MOVIE_YEAR_COL   = 1;
    const int MOVIE_GENRE_COL  = 2;
    const int MOVIE_RATING_COL = 3;
    const int MOVIE_ACTORS_COL = 4;
    const int MOVIE_ID_COL     = 5;

    const QString TREE_WIDTH_0 = "tree_width_0";
    const QString TREE_WIDTH_1 = "tree_width_1";
    const QString TREE_WIDTH_2 = "tree_width_2";
    const QString TREE_WIDTH_3 = "tree_width_3";
    const QString TREE_WIDTH_4 = "tree_width_4";

    const QString SPLITTER_POSITION = "splitter_position";
    const QString MAINWINDOW_GEOMETRY = "mainwindow_geometry";

    void search(bool searchDown);
    QTreeWidgetItem* getNextItem(QTreeWidgetItem* currentItem, bool searchDown);
};

#endif // MAINWINDOW_H
