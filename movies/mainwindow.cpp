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
    connect(ui->btnNew, SIGNAL(clicked()), this, SLOT(addMovie()));
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(addMovie()));
    connect(ui->btnDelete, SIGNAL(clicked()), this, SLOT(deleteMovie()));
    connect(ui->actionDelete, SIGNAL(triggered()), this, SLOT(deleteMovie()));
    connect(ui->btnSearchPrevious, SIGNAL(clicked()), this, SLOT(searchPrevious()));
    connect(ui->btnSearchNext, SIGNAL(clicked()), this, SLOT(searchNext()));
    connect(ui->treeMovies, SIGNAL(itemSelectionChanged()), this, SLOT(refreshMovieDetails()));
    connect(ui->lineTitle, SIGNAL(editingFinished()), this, SLOT(updateMovie()));
    connect(ui->comboGenre, SIGNAL(currentTextChanged(QString)), this, SLOT(updateMovie()));
    connect(ui->spinboxYear, SIGNAL(editingFinished()), this, SLOT(updateMovie()));
    connect(ui->doubleSpinRating, SIGNAL(editingFinished()), this, SLOT(updateMovie()));
    connect(ui->lineActors, SIGNAL(editingFinished()), this, SLOT(updateMovie()));

    // Populate genre combo box with possible values selected from database
    QStringList genreNames = m_dbInterface.getGenres();
    foreach(QString name, genreNames)
        ui->comboGenre->addItem(name); 

    // Populate search field combo box with possible values
    // Note: these values must be added in numerical order
    ui->comboSearchField->addItem("Title");  // MOVIE_TITLE_COL  = 0
    ui->comboSearchField->addItem("Year");   // MOVIE_YEAR_COL   = 1
    ui->comboSearchField->addItem("Genre");  // MOVIE_GENRE_COL  = 2
    ui->comboSearchField->addItem("Rating"); // MOVIE_RATING_COL = 3
    ui->comboSearchField->addItem("Actors"); // MOVIE_ACTORS_COL = 4

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
    refreshMovies();

    // Select the first move in the tree widget
    ui->treeMovies->setCurrentItem(ui->treeMovies->topLevelItem(0));
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
    // Default data for the new movie
    QString title("NewMovie");
    int year = 2018;
    int genreId = 1;
    QString genre("Action");
    double rating = 2.5;

    // Insert a new movie record in the database
    int movieId = m_dbInterface.insertMovie(title, genreId, year, rating);

    // Add the new movie to the movie tree view
    QTreeWidgetItem *movieItem = new QTreeWidgetItem(ui->treeMovies);
    movieItem->setText(MOVIE_ID_COL, QString::number(movieId));
    movieItem->setText(MOVIE_TITLE_COL, title);
    movieItem->setText(MOVIE_YEAR_COL, QString::number(year));
    movieItem->setText(MOVIE_GENRE_COL, genre);
    movieItem->setText(MOVIE_RATING_COL, QString::number(rating));

    // Select the newly created movie in the tree view so the user can edit it
    int numItems = ui->treeMovies->topLevelItemCount();
    ui->treeMovies->setCurrentItem(ui->treeMovies->topLevelItem(numItems-1));
}

void MainWindow::refreshMovies()
{
    // Clear the movies tree widget
    ui->treeMovies->clear();

    // Fetch movie details and populate the tree widget
    QList<MovieData> movieList = m_dbInterface.getMovies();
    foreach(MovieData movieData, movieList)
    {
        QTreeWidgetItem *movieItem = new QTreeWidgetItem(ui->treeMovies);
        movieItem->setText(MOVIE_ID_COL, QString::number(movieData.id));
        movieItem->setText(MOVIE_TITLE_COL, movieData.title);
        movieItem->setText(MOVIE_YEAR_COL, QString::number(movieData.year));
        movieItem->setText(MOVIE_GENRE_COL, movieData.genre);
        movieItem->setText(MOVIE_RATING_COL, QString::number(movieData.rating));
        movieItem->setText(MOVIE_ACTORS_COL, movieData.actors);
    }
}

void MainWindow::refreshMovieDetails()
{
    // Get the current item
    QTreeWidgetItem* currentItem = ui->treeMovies->currentItem();

    // Clear detail controls
    ui->lineTitle->clear();
    ui->spinboxYear->clear();
    ui->doubleSpinRating->clear();
    ui->lineActors->clear();

    if (currentItem == NULL)
        return;

    // Populate detail controls
    ui->lineTitle->setText(currentItem->data(MOVIE_TITLE_COL, Qt::DisplayRole).toString());
    ui->comboGenre->blockSignals(true);
    ui->comboGenre->setCurrentText(currentItem->data(MOVIE_GENRE_COL, Qt::DisplayRole).toString());
    ui->comboGenre->blockSignals(false);
    ui->spinboxYear->setValue(currentItem->data(MOVIE_YEAR_COL, Qt::DisplayRole).toInt());
    ui->doubleSpinRating->setValue(currentItem->data(MOVIE_RATING_COL, Qt::DisplayRole).toDouble());
    ui->lineActors->setText(currentItem->data(MOVIE_ACTORS_COL, Qt::DisplayRole).toString());


}

void MainWindow::updateMovie()
{
    // Get the current movie ID
    QTreeWidgetItem *currentMovieItem = ui->treeMovies->currentItem();
    if (currentMovieItem==NULL)
        return;
    int movieId = currentMovieItem->data(MOVIE_ID_COL, Qt::DisplayRole).toInt();

    // Get new values
    QString title = ui->lineTitle->text();
    int genreId = ui->comboGenre->currentIndex()+1;
    QString genre = ui->comboGenre->currentText();
    int year = ui->spinboxYear->value();
    double rating = ui->doubleSpinRating->value();
    QString actors = ui->lineActors->text();

    // Update the database
    m_dbInterface.updateMovie(movieId, title, genreId, year, rating, actors);

    // Update the movie tree model
    currentMovieItem->setData(MOVIE_TITLE_COL,Qt::DisplayRole, title);
    currentMovieItem->setData(MOVIE_GENRE_COL,Qt::DisplayRole, genre);
    currentMovieItem->setData(MOVIE_YEAR_COL,Qt::DisplayRole, year);
    currentMovieItem->setData(MOVIE_RATING_COL,Qt::DisplayRole, rating);
    currentMovieItem->setData(MOVIE_ACTORS_COL,Qt::DisplayRole, actors);
}

void MainWindow::deleteMovie()
{
    // Get the current movie ID
    QTreeWidgetItem *currentMovieItem = ui->treeMovies->currentItem();
    if (currentMovieItem==NULL)
        return;
    int movieId = currentMovieItem->data(MOVIE_ID_COL, Qt::DisplayRole).toInt();

    // Delete the movie from the database
    m_dbInterface.deleteMovie(movieId);

    // Remove the tree item widget from the movie tree
    delete currentMovieItem;
}


void MainWindow::searchPrevious()
{
    // Search up the widget
    bool searchDown = false;
    search(searchDown);
}

void MainWindow::searchNext()
{
    // Search down the widget
    bool searchDown = true;
    search(searchDown);

}

void MainWindow::search(bool searchDown)
{
    // Get starting values
    QString searchTerm = ui->lineSearchTerm->text();
    QTreeWidgetItem *currentItem = ui->treeMovies->currentItem();
    QTreeWidgetItem *startItem = currentItem;
    currentItem = getNextItem(currentItem, searchDown);
    int columnNumber = ui->comboSearchField->currentIndex();

    // Walk the widget until we find an item that meets the search criteria
    bool itemFound = false;
    while(!itemFound && currentItem != startItem)
    {
        QString fieldContents = currentItem->data(columnNumber, Qt::DisplayRole).toString();
        if (fieldContents.contains(searchTerm))
        {
            itemFound = true;
        }
        if (!itemFound)
        {
            currentItem = getNextItem(currentItem, searchDown);
        }
    }

    // If we found an item, select it
    if (itemFound)
    {
        ui->treeMovies->setCurrentItem(currentItem);
    }
}

QTreeWidgetItem* MainWindow::getNextItem(QTreeWidgetItem* currentItem, bool searchDown)
{
    QTreeWidgetItem *nextItem = NULL;
    if (searchDown)
    {
        nextItem = ui->treeMovies->itemBelow(currentItem);
        if (nextItem == NULL)
        {
            // wrap around to the top of the list
            nextItem = ui->treeMovies->topLevelItem(0);
        }
    }
    else
    {
        nextItem = ui->treeMovies->itemAbove(currentItem);
        if (nextItem == NULL)
        {
            // wrap around to the bottom of the list
            int numItems = ui->treeMovies->topLevelItemCount();
            nextItem = ui->treeMovies->topLevelItem(numItems-1);
        }
    }

    return nextItem;
}

