//
// Created by Richard H. Mercer on 4/20/22.
//

#include "mymodel.h"
#include <QAbstractTableModel>
// mymodel.cpp

MyModel::MyModel(QObject *parent)
        : QAbstractListModel(parent) {

  // Populate the list with three TODOs to show at startup
  list.insertElementAt(0, "Complete my new CSC 382 Assignment.");
  list.insertElementAt(1,
                       "Go grocery shopping. We need milk, bread, orange juice, and anything else that looks tasty.");
  list.insertElementAt(2, "Wash the dishes.");
}

int MyModel::rowCount(const QModelIndex & /*parent*/) const {
  return list.size();
}

int MyModel::columnCount(const QModelIndex & /*parent*/) const {
  return 1;
}

QVariant MyModel::data(const QModelIndex &index, int role) const {
  if (role == Qt::DisplayRole)
    return QString(list.getElementAt(index.row()));
  return QVariant();
}

// Return the current version of our priority list
LinkedPriorityList<QString> * MyModel::getList() {
  return &list;
}

// This function must be called when any change is made to the LinkedPriorityList
// In other words, from every slot that responds to a button click to add, remove lower, ...
void MyModel::listChanged() {
  // Identify the top left cell.
  // createIndex is defined in the super class QAbstractListModel
  QModelIndex topLeft = createIndex(0,0);
  // emit a signal to make the view reread identified data
  emit dataChanged(topLeft, topLeft, {Qt::DisplayRole});
}



