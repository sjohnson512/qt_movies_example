This project creates a Qt application that stores movie data in a sqlite database.

Build Instructions
1) Install Qt (tested 5.9.3 on Windows10, 5.9.4 on Mac)
2) Install sqlite3 (tested 3.21.0 on Windows10, 3.19.3 on Mac)
3) Create a database file: sqlite3 movies.db < movies.sql
4) Open movies.pro in QtCreator
5) Configure the project withe desired kits
6) Build->Build All

Project contents:
movies.sql: sql file used to create database with sample data
movies/dbinterface.h/cpp: contains the sqlite3 wrapper the application uses to interface with the database
movies/main.cpp: contains the main() method that starts the QApplication
movies/mainwindow.h/cpp: contains MainWindow class that defines the gui and its functionality
movies/mainwindow.ui: XML file created by QtCreator that defines ui elements
