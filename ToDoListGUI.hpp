// A graphical view of a to do list using our LinkedPriortyist as the model
// Programmers Rick Mercer and YOUR NAME
// Modified Nov-2022
//
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListView>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QInputDialog>
#include "mymodel.h"
#include <iostream>

class ToDoListGUI : public QWidget {

private:
  MyModel myModel;
  QGroupBox *horizontalGroupBox;
  QListView *listView = new QListView();
  QPushButton *buttonAdd = new QPushButton{"Add before"};
  QPushButton *buttonLower = new QPushButton{"Lower priority"};
    
  // TODO: Add four more button data members


public:
  ToDoListGUI() {
   horizontalGroupBox = new QGroupBox; // avoid a clang tidy warning
    layoutWidgets();
    registerListeners();
  }

private:
  void layoutWidgets() {
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(buttonAdd);
    layout->addWidget(buttonLower);
      
    // TODO: Add four more buttons to the same layout


    // Add the QListView horizontally, below the buttons
    layout->addWidget(listView);
    horizontalGroupBox->setLayout(layout);

    // Synchronize the listView to display myModel that
    // has a LinkedPriorityList<QString> data member
    listView->setModel(&myModel);

    // Modify listView to be wider with no line wrapping (a scrollbar would appear)
    listView->setFixedWidth(800);
    listView->setWordWrap(false);

    // Change the font shown in the QListView
    QFont font("Times New Roman");
    font.setPointSize(16);
    listView->setFont(font);

    // Make it so row 0 is selected at startup
    QModelIndex index = myModel.index(0, 0);
    listView->setCurrentIndex(index);

    // Add both the horizontal button and the listView below the buttons in a QVBoxLayout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(horizontalGroupBox);
    mainLayout->addWidget(listView);

    // ToDoListGUI extends QWidget so we don't really need this-> here, but it helps clarify
    this->setLayout(mainLayout);
    this->setWindowTitle("To Do List");
  }

  void registerListeners() {
    QObject::connect(buttonAdd, &QPushButton::clicked,
                     this, &ToDoListGUI::addToDo);
    QObject::connect(buttonLower, &QPushButton::clicked,
                     this, &ToDoListGUI::lower);
      
    // TODO: Add four more connections

  }

  void addToDo() {
    // Ask the user for a string.  This is the only place we need QInputDialog.
    QString text = QInputDialog::getText(0, "New TODO",
                                         "Enter new TODO item",
                                         QLineEdit::Normal,
                                         "");
    // Get index of the selected row in QListView
    QModelIndex index = listView->currentIndex();
    auto list = myModel.getList();
    if (index.row() == 0)
      list->insertElementAt(0, text);
    else
      list->insertElementAt(index.row(), text);
    // This message must be sent at the end of all 6 slots (functions like lower below)
    myModel.listChanged();
  }

  void lower() {
    QModelIndex index = listView->currentIndex();
    // Need the following message in every slot that changes the list because
    // getList emits dataChanged so the QListView gets refreshed to show any change.
    auto list = myModel.getList();
    int row = index.row();
    if (row < list->size() - 1 and row >= 0) {
      list->lowerPriorityOf(index.row());
      QModelIndex currentIndex = myModel.index(index.row() + 1);
      listView->setCurrentIndex(currentIndex);
      myModel.listChanged();
    }
  }

  // TODO: Add four more slots as void functions inside this class

};
