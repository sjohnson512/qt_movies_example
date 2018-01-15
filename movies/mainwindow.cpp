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
    connect(ui->treeMovies,SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
            this, SLOT(updateMovieDetails(QTreeWidgetItem*,QTreeWidgetItem*)));

    // Populate genre combo box with possible values selected from database
    QStringList genreNames = m_dbInterface.getGenres();
    foreach(QString name, genreNames)
        ui->comboGenre->addItem(name); 

    // Set up the movie TreeWidget
    ui->treeMovies->setColumnCount(6);
    ui->treeMovies->hideColumn(5);
    ui->treeMovies->setHeaderLabels(QStringList() << "Title" << "Year" << "Genre" << "Rating" << "Actors");

    // Set the MainWindow size and position
    QSettings settings;
    this->restoreGeometry(settings.value(MAINWINDOW_GEOMETRY,"").toByteArray());

    // Set TreeWidget column widths
    ui->treeMovies->setColumnWidth(0, settings.value(TREE_WIDTH_0,"144").toInt());
    ui->treeMovies->setColumnWidth(1, settings.value(TREE_WIDTH_1,"45").toInt());
    ui->treeMovies->setColumnWidth(2, settings.value(TREE_WIDTH_2,"61").toInt());
    ui->treeMovies->setColumnWidth(3, settings.value(TREE_WIDTH_3,"50").toInt());
    ui->treeMovies->setColumnWidth(4, settings.value(TREE_WIDTH_4,"300").toInt());

    // Set Splitter position
    ui->splitter->restoreState(settings.value(SPLITTER_POSITION,"").toByteArray());

    // Update movie treeWidget
    updateMovies();
}

MainWindow::~MainWindow()
{
    // Save window size and position
    QSettings settings;
    settings.setValue(MAINWINDOW_GEOMETRY, this->saveGeometry());

    // Save TreeWidget column widths
    settings.setValue(TREE_WIDTH_0,ui->treeMovies->columnWidth(0));
    settings.setValue(TREE_WIDTH_1,ui->treeMovies->columnWidth(1));
    settings.setValue(TREE_WIDTH_2,ui->treeMovies->columnWidth(2));
    settings.setValue(TREE_WIDTH_3,ui->treeMovies->columnWidth(3));
    settings.setValue(TREE_WIDTH_4,ui->treeMovies->columnWidth(4));

    // Save splitter position
    settings.setValue(SPLITTER_POSITION, ui->splitter->saveState());

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
        movieItem->setText(MOVIE_ID_COL, QString::number(movieData.id));
        movieItem->setText(MOVIE_TITLE_COL, movieData.title);
        movieItem->setText(MOVIE_YEAR_COL, QString::number(movieData.year));
        movieItem->setText(MOVIE_GENRE_COL, movieData.genre);
        movieItem->setText(MOVIE_RATING_COL, QString::number(movieData.rating));

        int movieId= movieData.id;
        QStringList actorList = m_dbInterface.getActorsForMovie(movieId);
        QString actors = actorList.join(", ");
        movieItem->setText(4, actors);

    }
}

void MainWindow::updateMovieDetails(QTreeWidgetItem* currentItem, QTreeWidgetItem* previousItem)
{
    ui->lineTitle->clear();
    ui->spinboxYear->clear();
    ui->doubleSpinRating->clear();

    ui->lineTitle->setText(currentItem->data(MOVIE_TITLE_COL, Qt::DisplayRole).toString());
    ui->comboGenre->setCurrentText(currentItem->data(MOVIE_GENRE_COL, Qt::DisplayRole).toString());
    ui->spinboxYear->setValue(currentItem->data(MOVIE_YEAR_COL, Qt::DisplayRole).toInt());
    ui->doubleSpinRating->setValue(currentItem->data(MOVIE_RATING_COL, Qt::DisplayRole).toDouble());

    int movieId = currentItem->data(MOVIE_ID_COL, Qt::DisplayRole).toInt();
    updateActors(movieId);
}
