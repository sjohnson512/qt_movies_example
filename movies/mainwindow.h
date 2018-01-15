#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <dbinterface.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;

    DBInterface    m_dbInterface;
    int            m_currentMovieID;


private slots:
    void addMovie();
    void updateMovies();
    void updateActors(int movieID);


};

#endif // MAINWINDOW_H
