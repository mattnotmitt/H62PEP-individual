#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect( ui->addButton, &QPushButton::released, this, &MainWindow::handleAddButton );
    connect( ui->editButton, &QPushButton::released, this, &MainWindow::handleEditButton );
    connect( ui->removeButton, &QPushButton::released, this, &MainWindow::handleRemoveButton );

    connect( this, &MainWindow::statusUpdateMessage, ui->statusBar, &QStatusBar::showMessage );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleAddButton() {
	QMessageBox msgBox;
	msgBox.setText("Add button was clicked");
	msgBox.exec();
}

void MainWindow::handleEditButton() {
        QMessageBox msgBox;
        msgBox.setText("Edit button was clicked");
        msgBox.exec();
}

void MainWindow::handleRemoveButton() {
        QMessageBox msgBox;
        msgBox.setText("Remove button was clicked");
        msgBox.exec();
}
