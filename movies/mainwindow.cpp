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

    // Set up the movie TreeWidget
    ui->treeMovies->setColumnCount(5);
    ui->treeMovies->setHeaderLabels(QStringList() << "Title" << "Year" << "Genre" << "Rating" << "Actors");

    // Update movie treeWidget
    updateMovies();

    // Update actor listWidget
    int movie_id = 1;
    updateActors(movie_id);
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

void MainWindow::updateActors(int movieID)
{
    ui->listActors->clear();
    QStringList actorList = m_dbInterface.getActorsForMovie(movieID);

    foreach(QString name, actorList)
    {
        ui->listActors->addItem(name);
    }
}

void MainWindow::updateMovies()
{
    QList<MovieData> movieList = m_dbInterface.getMovies();

    foreach(MovieData movieData, movieList)
    {
        QTreeWidgetItem *movieItem = new QTreeWidgetItem(ui->treeMovies);
        movieItem->setText(0, movieData.title);
        movieItem->setText(1, QString::number(movieData.year));
        movieItem->setText(2, movieData.genre);
        movieItem->setText(3, QString::number(movieData.rating));

        int movieId= movieData.id;
        QStringList actorList = m_dbInterface.getActorsForMovie(movieId);
        QString actors = actorList.join(", ");
        movieItem->setText(4, actors);

    }
}
