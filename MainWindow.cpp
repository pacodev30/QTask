#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    // INIT
    _task = new Task(this);
    _taskForm = new TaskForm(this);
    setWindowIcon(QIcon(":/img/logos/logo.png"));
    setWindowTitle(tr("QTask"));

    // LAYOUT
    setCentralWidget(_task);

    // ACTION
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

    // MENU
    _fileMenu = menuBar()->addMenu(tr("&File"));
        _fileMenu->addAction(_newAction);
        _fileMenu->addSeparator();
        _fileMenu->addAction(_openAction);
        _fileMenu->addAction(_saveAction);
        _fileMenu->addSeparator();
        _fileMenu->addAction(_quitAction);

    // TOOLBAR
    _toolBar = addToolBar(tr("File"));
        _toolBar->addAction(_newAction);
        _toolBar->addSeparator();
        _toolBar->addAction(_openAction);
        _toolBar->addAction(_saveAction);
        _toolBar->addSeparator();
        _toolBar->addAction(_quitAction);

    // CONNECT
    connect(_newAction, SIGNAL(triggered(bool)), this, SLOT(onNewAction_triggered()));
    connect(_openAction, SIGNAL(triggered(bool)), this, SLOT(onOpenAction_triggered()));
    connect(_saveAction, SIGNAL(triggered(bool)), this, SLOT(onSaveAction_triggered()));
    connect(_quitAction, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
}

void MainWindow::onNewAction_triggered()
{
    _taskForm->exec();

    _task->addTask(
        _taskForm->dataTitle(),
        _taskForm->dataDescription(),
        _taskForm->dataStatus()
    );
}

void MainWindow::onOpenAction_triggered()
{
    _task->openTaskFile();
}

void MainWindow::onSaveAction_triggered()
{
    _task->saveTaskFile();
}
