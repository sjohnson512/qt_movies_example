#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect to sqlite database
    m_dbInterface = DBInterface();

    // Populate genre combo box with possible values selected from database
    QStringList genreNames = m_dbInterface.getGenres();
    foreach(QString name, genreNames)
        ui->comboGenre->addItem(name);
}

MainWindow::~MainWindow()
{
    delete ui;
}
