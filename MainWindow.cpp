#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("Dashboard"));

    // WINDOW LAYOUTS
    _centralArea = new QMdiArea(this);
        setCentralWidget(_centralArea);

    // MENU
    _newAction = new QAction(tr("&New task"), this);
    _quitAction = new QAction(tr("&Quit"), this);

    QMenu *_fileMenu = menuBar()->addMenu(tr("&File"));
        _fileMenu->addAction(_newAction);
        _fileMenu->addAction(_quitAction);

    // CONNECT
        connect(_newAction, SIGNAL(triggered(bool)), this, SLOT(onNewBtn_triggered()));

}

MainWindow::~MainWindow() {}

void MainWindow::onNewBtn_triggered()
{
    Task *newTask = new Task(this);
    _centralArea->addSubWindow(newTask);
    newTask->show();
}

void MainWindow::addTask()
{

}
