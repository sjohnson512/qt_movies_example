#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect to sqlite database
    m_dbInterface = DBInterface();

    // Connect control signals to slots
    connect(ui->btnNew,SIGNAL(clicked()), this, SLOT(addMovie()));

    // Populate genre combo box with possible values selected from database
    QStringList genreNames = m_dbInterface.getGenres();
    foreach(QString name, genreNames)
        ui->comboGenre->addItem(name);

    // Update actor list
    int movie_id = 1;
    updateActorList(movie_id);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addMovie()
{
    QString title = ui->lineTitle->text();
    int actorListID = 1;
    int genreID = 1;
    int year = ui->spinboxYear->value();
    double rating = ui->doubleSpinRating->value();

    m_dbInterface.insertMovie(title,actorListID, genreID, year, rating);
}

void MainWindow::updateActorList(int movieID)
{
    ui->listActors->clear();
    QStringList actorList = m_dbInterface.getActorsForMovie(movieID);

    foreach(QString name, actorList)
    {
        ui->listActors->addItem(name);
    }
}
