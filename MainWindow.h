#pragma once

#include <QMainWindow>
#include <Task.h>
#include <QMenuBar>
#include <QToolBar>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QApplication>
#include <TaskForm.h>



class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    /**
     * @brief onNewAction_triggered
     */
    void onNewAction_triggered();

    /**
     * @brief onOpenAction_triggered
     */
    void onOpenAction_triggered();

    /**
     * @brief onSaveAction_triggered
     */
    void onSaveAction_triggered();

private:
    QMdiArea *_centralArea;
    Task *_task;
    TaskForm *_taskForm;
    QMenu *_fileMenu;
    QToolBar *_toolBar;
    QAction *_newAction, *_deleteAction, *_openAction, *_saveAction, *_quitAction;
};
