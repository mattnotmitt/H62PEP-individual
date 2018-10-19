#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QStatusBar>
#include "edititemdialog.h"
#include "stockitemlistmodel.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

	public:
    	explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

    public slots:
        void handleAddButton();
        void handleEditButton();
        void handleRemoveButton();

    private:
        Ui::MainWindow *ui;
        StockItemListModel stockList;


    signals:
        void statusUpdateMessage( const QString & message, int timeout );
};

#endif // MAINWINDOW_H
