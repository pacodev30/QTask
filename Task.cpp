#include "Task.h"

#include <QInputDialog>
#include <QJsonDocument>

Task::Task(QWidget *parent)
    : QWidget(parent)
{
    initialize();
    manageLayouts();
    manageConnects();
}

// MANAGE
void Task::initialize()
{
    setWindowTitle("Tasks");
    _tasksJsonArray = new QJsonArray();
    _updateForm = new TaskForm(this);

    _updateBtn = new QPushButton(tr("Update task"), this);
    _deleteBtn = new QPushButton(tr("Delete task"), this);

    _taskTable = new QTableWidget(this);
    _taskTable->setFixedWidth(640);
    _taskTable->setColumnCount(3);
    _taskTable->setColumnWidth(0, 150);
    _taskTable->setColumnWidth(1, 300);
    _taskTable->setColumnWidth(2, 150);
    _taskTable->setHorizontalHeaderLabels({tr("Title"), tr("Description"), tr("Status")});
}

void Task::manageLayouts()
{
    _layoutVBox = new QVBoxLayout(this);
    _layoutVBox->addWidget(_taskTable);
    _layoutVBox->addWidget(_updateBtn);
    _layoutVBox->addWidget(_deleteBtn);
}

void Task::manageConnects()
{
    connect(_updateBtn, SIGNAL(clicked(bool)), this, SLOT(onUpdateBtn_clicked()));
    connect(_deleteBtn, SIGNAL(clicked(bool)), this, SLOT(onDeleteBtn_clicked()));
}

// EVENTS
void Task::onUpdateBtn_clicked()
{
    int row = _taskTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, tr("Update Error"), tr("Please select a task to update."));
        return;
    }

    QString currentTitle = _taskTable->item(row, 0)->text();
    QString currentDescription = _taskTable->item(row, 1)->text();

    _updateForm->titleLine()->setText(currentTitle);
    _updateForm->descriptionText()->setPlainText(currentDescription);
    _updateForm->alertTitleLabel()->hide();
    _updateForm->exec();

    _taskTable->removeRow(row);
    _taskTable->insertRow(row);
    _taskTable->setItem(row, 0, new QTableWidgetItem(_updateForm->dataTitle()));
    _taskTable->setItem(row, 1, new QTableWidgetItem(_updateForm->dataDescription()));
    _taskTable->setItem(row, 2, new QTableWidgetItem(_updateForm->dataStatus()));
}

void Task::onDeleteBtn_clicked()
{

    int row = _taskTable->currentRow();
    int deletedConfirmation = QMessageBox::question(
        this,
        tr("Deleted confirmation"),
        tr("Are you really sure to delete this task ?"),
        QMessageBox::Yes | QMessageBox::No
    );

    if(deletedConfirmation == QMessageBox::No)
    {
        return;
    }

    if(row >=0)
    {
        _taskTable->removeRow(row);
    }

}

// GETTERS AND SETTERS
QTableWidget *Task::taskTable() const
{
    return _taskTable;
}

void Task::setTaskTable(QTableWidget *newTaskTable)
{
    _taskTable = newTaskTable;
}



