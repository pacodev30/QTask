#include "MainWindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    initialize();
    manageLayout();
    manageAction();
    manageMenu();
    manageToolbar();
    manageConnect();
}

// MANAGE
void MainWindow::initialize()
{
    _task = new Task(this);
    _taskForm = new TaskForm(this);
    setWindowIcon(QIcon(":/img/logos/logo.png"));
    setWindowTitle(tr("QTask"));
}

void MainWindow::manageLayout()
{
    setCentralWidget(_task);
}

void MainWindow::manageConnect()
{
    connect(_newAction, SIGNAL(triggered(bool)), this, SLOT(onNewAction_triggered()));
    connect(_openAction, SIGNAL(triggered(bool)), this, SLOT(onOpenAction_triggered()));
    connect(_saveAction, SIGNAL(triggered(bool)), this, SLOT(onSaveAction_triggered()));
    connect(_quitAction, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
}

void MainWindow::manageAction()
{
    _newAction = new QAction(tr("New task"), this);
        _newAction->setIcon(QIcon(":/img/logos/newFile.png"));
        _newAction->setShortcut(QKeySequence("Ctrl+N"));
    _openAction = new QAction(tr("Open"), this);
        _openAction->setIcon(QIcon(":/img/logos/openFile.png"));
        _openAction->setShortcut(QKeySequence("Ctrl+O"));
    _saveAction = new QAction(tr("Save"), this);
        _saveAction->setIcon(QIcon(":/img/logos/download.png"));
        _saveAction->setShortcut(QKeySequence("Ctrl+S"));
    _quitAction = new QAction(tr("Quit"), this);
        _quitAction->setIcon(QIcon(":/img/logos/quit.png"));
        _quitAction->setShortcut(QKeySequence("Ctrl+Q"));
}

void MainWindow::manageMenu()
{
    _fileMenu = menuBar()->addMenu(tr("&File"));
        _fileMenu->addAction(_newAction);
        _fileMenu->addSeparator();
        _fileMenu->addAction(_openAction);
        _fileMenu->addAction(_saveAction);
     _fileMenu->addSeparator();
        _fileMenu->addAction(_quitAction);
}

void MainWindow::manageToolbar()
{
    _toolBar = addToolBar(tr("File"));
        _toolBar->addAction(_newAction);
        _toolBar->addSeparator();
        _toolBar->addAction(_openAction);
        _toolBar->addAction(_saveAction);
        _toolBar->addSeparator();
        _toolBar->addAction(_quitAction);
}

// EVENTS
void MainWindow::onNewAction_triggered()
{
    _taskForm->exec();

    newTask(
        _taskForm->dataTitle(),
        _taskForm->dataDescription(),
        _taskForm->dataStatus(),
        _task->taskTable()
    );
}

void MainWindow::onOpenAction_triggered()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open JSON file"), QString(), "JSON file (*.json)");
    if(!file.isEmpty())
        openJsonfile(file, _task->taskTable());
}

void MainWindow::onSaveAction_triggered()
{
    QString file = QFileDialog::getSaveFileName(this, "Save JSON file", QDir::homePath() + "/tasks.json", "JSON file (*.json)");

    saveJsonFile(file, _task->taskTable());
}

// FUNCTIONS
void MainWindow::newTask(const QString &title, const QString &description, const QString &status,  QTableWidget *taskTable)
{
    int row = taskTable->rowCount();
    if(!title.isEmpty())
    {
        taskTable->insertRow(row);
        taskTable->setItem(row, 0, new QTableWidgetItem(title));
        taskTable->setItem(row, 1, new QTableWidgetItem(description));
        taskTable->setItem(row, 2, new QTableWidgetItem(status));
    }
}

void MainWindow::openJsonfile(const QString &fileName, QTableWidget *taskTable)
{
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        file.close();
        taskTable->setRowCount(0);
        QJsonArray taskArray = doc.array();
        for (const QJsonValue &value : std::as_const(taskArray))
        {
            QJsonObject taskObject = value.toObject();
            int row = taskTable->rowCount();
            taskTable->insertRow(row);
            taskTable->setItem(row, 0, new QTableWidgetItem(taskObject["title"].toString()));
            taskTable->setItem(row, 1, new QTableWidgetItem(taskObject["description"].toString()));
            taskTable->setItem(row, 2, new QTableWidgetItem(taskObject["status"].toString()));
        }
    }
}

void MainWindow::saveJsonFile(const QString &fileName, QTableWidget *taskTable)
{
    QJsonArray taskArray;
    for (int i = 0; i < taskTable->rowCount(); ++i) {
        QJsonObject taskObject;
        taskObject["title"] = taskTable->item(i, 0)->text();
        taskObject["description"] = taskTable->item(i, 1)->text();
        taskObject["status"] = taskTable->item(i, 2)->text();
        taskArray.append(taskObject);
    }

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(taskArray).toJson());
        file.close();
    }
    QMessageBox::information(this, tr("Saved confirmation"), tr("File is saved succesfully :)"));

}

