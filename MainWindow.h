#pragma once

#include <QMainWindow>
#include <Task.h>
#include <QMenuBar>
#include <QToolBar>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QApplication>



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
    QMdiArea *_centralArea;
    Task *_task;
    QMenu *_fileMenu;
    QToolBar *_toolBar;
    QAction *_newAction, *_deleteAction, *_openAction, *_saveAction, *_quitAction;
};
