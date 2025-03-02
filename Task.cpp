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

void Task::addTask(const QString &title, const QString &description, const QString &status)
{
    int row = _taskTable->rowCount();
    if(!title.isEmpty())
    {
        _taskTable->insertRow(row);
        _taskTable->setItem(row, 0, new QTableWidgetItem(title));
        _taskTable->setItem(row, 1, new QTableWidgetItem(description));
        _taskTable->setItem(row, 2, new QTableWidgetItem(status));
    }
}

void Task::onUpdateBtn_clicked()
{
    int row = _taskTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, tr("Update Error"), tr("Please select a task to update."));
        return;
    }

    // Get curent values
    QString currentTitle = _taskTable->item(row, 0)->text();
    QString currentDescription = _taskTable->item(row, 1)->text();
    QString currentStatus = _taskTable->item(row, 2)->text();

    // Get new values
    QString newTitle = QInputDialog::getText(this, tr("Update Title"), tr("New Title:"), QLineEdit::Normal, currentTitle);
    if (newTitle.isEmpty()) return;

    QString newDescription = QInputDialog::getText(this, tr("Update Description"), tr("New Description:"), QLineEdit::Normal, currentDescription);
    if (newDescription.isEmpty()) return;

    QString newStatus = QInputDialog::getText(this, tr("Update Status"), tr("New Status:"), QLineEdit::Normal, currentStatus);
    if (newStatus.isEmpty()) return;

    // Update  table
    _taskTable->setItem(row, 0, new QTableWidgetItem(newTitle));
    _taskTable->setItem(row, 1, new QTableWidgetItem(newDescription));
    _taskTable->setItem(row, 2, new QTableWidgetItem(newStatus));
}

void Task::saveTaskFile()
{
    QJsonArray taskArray;
    for (int i = 0; i < _taskTable->rowCount(); ++i) {
        QJsonObject taskObject;
        taskObject["title"] = _taskTable->item(i, 0)->text();
        taskObject["description"] = _taskTable->item(i, 1)->text();
        taskObject["status"] = _taskTable->item(i, 2)->text();
        taskArray.append(taskObject);
    }

    QFile file(_fileNane);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(taskArray).toJson());
        file.close();
    }
    QMessageBox::information(this, tr("Saved confirmation"), tr("File is saved succesfully :)"));

}

void Task::openTaskFile()
{
    QFile file(_fileNane);
    if (file.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        file.close();
        _taskTable->setRowCount(0);
        QJsonArray taskArray = doc.array();
        for (const QJsonValue &value : std::as_const(taskArray))
        {
            QJsonObject taskObject = value.toObject();
            int row = _taskTable->rowCount();
            _taskTable->insertRow(row);
            _taskTable->setItem(row, 0, new QTableWidgetItem(taskObject["title"].toString()));
            _taskTable->setItem(row, 1, new QTableWidgetItem(taskObject["description"].toString()));
            _taskTable->setItem(row, 2, new QTableWidgetItem(taskObject["status"].toString()));
        }
    }
}

void Task::onDeleteBtn_clicked()
{

    int row = _taskTable->currentRow();
    int deletedConfirmation = QMessageBox::question(
        this,
        tr("Deleted confismation"),
        tr(":o  Are you really sure to delete this task ?"),
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

void Task::initialize()
{
    setWindowTitle("Tasks");
    _tasksJsonArray = new QJsonArray();
    _fileNane = "tasks.json";
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
