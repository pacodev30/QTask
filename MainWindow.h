#pragma once

#include <QMainWindow>
#include <Task.h>
#include <QMenuBar>
#include <QToolBar>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QApplication>
#include <TaskForm.h>
#include <QFile>
#include <QTableWidget>
#include <QJsonDocument>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onNewAction_triggered();
    void onOpenAction_triggered();
    void onSaveAction_triggered();

private:
    void initialize();
    void manageLayout();
    void manageAction();
    void manageMenu();
    void manageToolbar();
    void manageConnect();

    void newTask(
        const QString &title,
        const QString &description,
        const QString &status,
        QTableWidget *taskTable
    );
    void openJsonfile(const QString &fileName, QTableWidget *taskTable);
    void saveJsonFile(const QString &fileName, QTableWidget *taskTable);

private:
    QMdiArea    *_centralArea;
    Task        *_task;
    TaskForm    *_taskForm;
    QMenu       *_fileMenu;
    QToolBar    *_toolBar;
    QAction     *_newAction, *_deleteAction, *_openAction, *_saveAction, *_quitAction;
};
