#include "stockitemlistmodel.h"

// function allows listview to determine the number of items in list
int StockItemListModel::rowCount( const QModelIndex & parent ) const {
    return stockItems.size();
}

// function allows the listView to request data at index
// QVariant is just Qt's way of defining a variable that could be any
// basic type (int, float, double, string, ... )
QVariant StockItemListModel::data( const QModelIndex & index, int role ) const {
    // Check that the index is valid
    if( !index.isValid() ) return QVariant();
    if( index.row() >= stockItems.size() || index.row() < 0 ) return QVariant();
    // Return item name as display variable
    if( role == Qt::DisplayRole ) {
        return QVariant( stockItems[index.row()].getName() );
    } else {
        return QVariant();
    }
}

// To allow modifying stored list
void StockItemListModel::addItem( const StockItem & s ) {
    // This emits a signal to warn the listView that extra rows will be added
    emit beginInsertRows( QModelIndex(), stockItems.size()-1, stockItems.size()-1 );
    // Add the extra item to the list
    stockItems.push_back( s );
    // Emits a signal to say rows have been added.
    emit endInsertRows();
}

void StockItemListModel::insertItem( const StockItem &s, const QModelIndex & index ) {
    // This emits a signal to warn the listView that extra rows will be added
    emit beginInsertRows( QModelIndex(), index.row()+1, index.row()+1 );
    // Add the extra item to the list
    stockItems.insert( stockItems.begin() + index.row() + 1, s );
    // Emits a signal to say rows have been added.
    emit endInsertRows();
}

void StockItemListModel::setItem( const StockItem &s, const QModelIndex & index ) {
    if( index.isValid() && index.row() >= 0 && index.row() < stockItems.size() ) {
        stockItems[index.row()] = s;
        emit dataChanged( index, index );
    }
}
void StockItemListModel::removeItem( const QModelIndex & index ) {
    // This emits a signal to warn the listView that extra rows will be added
    emit beginRemoveRows( QModelIndex(), index.row(), index.row() );
    // Add the extra item to the list
    stockItems.erase( stockItems.begin() + index.row());
    // Emits a signal to say rows have been added.
    emit endRemoveRows();
}

// to allow accessing stored list item properties
StockItem StockItemListModel::getItem( const QModelIndex & index ) const {
    if( index.isValid() && index.row() >= 0 && index.row() < stockItems.size() )
        return stockItems[index.row()];
    return StockItem();
}

void StockItemListModel::outputToCSV( QFile & file) {
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_5);
    for ( auto i = stockItems.begin(); i != stockItems.end(); i++ ) {
        out << qPrintable(i->getName()) << ";" << qPrintable(i->getUnitCost()) << ";" << qPrintable(i->getStockLevel()) << ";" << qPrintable(i->getReorder());
    }
}