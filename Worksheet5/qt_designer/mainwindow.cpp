#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stockitem.h"
#include "edititemdialog.h"
#include "stockitemlistmodel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->listView->setModel( &stockList );
    ui->listView->setSelectionBehavior( QAbstractItemView::SelectItems );

    connect( ui->addButton, &QPushButton::released, this, &MainWindow::handleAddButton );
    connect( ui->editButton, &QPushButton::released, this, &MainWindow::handleEditButton );
    connect( ui->removeButton, &QPushButton::released, this, &MainWindow::handleRemoveButton );
    connect( ui->actionSave, &QAction::triggered, this, &MainWindow::handleSaveAction );

    connect( this, &MainWindow::statusUpdateMessage, ui->statusBar, &QStatusBar::showMessage );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleAddButton() {
	StockItem item;
    QModelIndexList selectedList;
    selectedList = ui->listView->selectionModel()->selectedIndexes();
    if( selectedList.length() == 0 ) {
        emit statusUpdateMessage( QString::number(selectedList[0].row()), 0 );
        stockList.insertItem( item, selectedList[0] );
    } else {
        stockList.addItem( item );
    }
}

void MainWindow::handleEditButton() {
    EditItemDialog dialog( this );
    QModelIndexList selectedList;
    selectedList = ui->listView->selectionModel()->selectedIndexes();
    if( selectedList.length() == 1 ) {
        // selectedList is a list of all selected items in the listView. Since we set its
        // behaviour to single selection, were only interested in the first selecteded item.
        StockItem item = stockList.getItem( selectedList[0] );
        if( dialog.runDialog( item ) ) {
            // user clicked ok, need to update item in list...
            stockList.setItem( item, selectedList[0] );
        }
    } else {
        emit statusUpdateMessage( QString("No item selected to edit!"), 0 );
    }
}

void MainWindow::handleRemoveButton() {
    StockItem item;
    QModelIndexList selectedList;
    selectedList = ui->listView->selectionModel()->selectedIndexes();
    if( selectedList.length() == 1 ) {
        emit statusUpdateMessage( QString("Removed selected item."), 0 );
        stockList.removeItem( selectedList[0] );
    } else {
        emit statusUpdateMessage( QString("No item selected to remove!"), 0 );
    }
}

void MainWindow::handleSaveAction() {
    if (stockList.rowCount() > 0) {
        QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save Items"), "",
            tr("Comma-seperated Values (*.csv);;All Files (*)"));
        if (fileName.isEmpty()) {
            emit statusUpdateMessage( QString("Empty filename."), 0 );
            return;
        } else {
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                emit statusUpdateMessage( QString("Unable to open file"), 0);
                return;
            }
            stockList.outputToCSV(file);
        }
    } else {
        emit statusUpdateMessage( QString("Stock list is empty"), 0);
    }
}