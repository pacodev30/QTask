#include "Task.h"

#include <QInputDialog>
#include <QJsonDocument>

Task::Task(QWidget *parent)
    : QWidget(parent)
{
    // INIT
    setWindowTitle("TaskManager");
    _tasksJsonArray = new QJsonArray();
    _fileNane = "tasks.json";

    _taskTable = new QTableWidget(this);
    _taskTable->setFixedWidth(480);
        _taskTable->setColumnCount(3);
        _taskTable->setHorizontalHeaderLabels({tr("Title"), tr("Description"), tr("Status")});

    _addBtn = new QPushButton(tr("Add task"), this);
    _deleteBtn = new QPushButton(tr("Delete task"), this);
    _loadBtn = new QPushButton(tr("Load"), this);
    _saveBtn = new QPushButton(tr("Save"), this);

    // LAYOUT
    _layoutVBox = new QVBoxLayout(this);
        _layoutVBox->addWidget(_taskTable);
        _layoutVBox->addWidget(_addBtn);
        _layoutVBox->addWidget(_deleteBtn);
        _layoutVBox->addWidget(_loadBtn);
        _layoutVBox->addWidget(_saveBtn);

    // CONNECT
    connect(_addBtn, SIGNAL(clicked(bool)), this, SLOT(onAddBtn_clicked()));
    connect(_deleteBtn, SIGNAL(clicked(bool)), this, SLOT(onDeleteBtn_clicked()));
    connect(_loadBtn, SIGNAL(clicked(bool)), this, SLOT(onLoadBtn_clicked()));
    connect(_saveBtn, SIGNAL(clicked(bool)), this, SLOT(onSaveBtn_clicked()));
}

void Task::onAddBtn_clicked()
{
    bool ok;
    QString title = QInputDialog::getText(this, tr("Input text"), tr("Title : "), QLineEdit::Normal, QString(), &ok);
    QString description = QInputDialog::getText(this, tr("Input description"), tr("Description"), QLineEdit::Normal, QString(), &ok);
    QStringList statusList = {
        tr("Not started"),
        tr("In progress"),
        tr("Complete")
    };
    QString status = QInputDialog::getItem(this, tr("Input status"), tr("Status : "), statusList, 0, false, &ok);

    int row = _taskTable->rowCount();

    if(ok && !title.isEmpty() && !description.isEmpty() && !status.isEmpty())
    {
        _taskTable->insertRow(row);
        _taskTable->setItem(row, 0, new QTableWidgetItem(title));
        _taskTable->setItem(row, 1, new QTableWidgetItem(description));
        _taskTable->setItem(row, 2, new QTableWidgetItem(status));
    }
}

void Task::onDeleteBtn_clicked()
{
    int row = _taskTable->currentRow();
    if(row >=0)
    {
        _taskTable->removeRow(row);
    }
}

void Task::onSaveBtn_clicked()
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
}

void Task::onLoadBtn_clicked()
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
