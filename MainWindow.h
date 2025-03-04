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
    /**
     * @brief initialize
     */
    void initialize();

    /**
     * @brief manageLayout
     */
    void manageLayout();

    /**
     * @brief manageAction
     */
    void manageAction();

    /**
     * @brief manageMenu
     */
    void manageMenu();

    /**
     * @brief manageToolbar
     */
    void manageToolbar();

    /**
     * @brief manageConnect
     */
    void manageConnect();

    /**
     * @brief newTask
     * @param title
     * @param description
     * @param status
     * @param taskTable
     */
    void newTask(const QString &title, const QString &description, const QString &status, QTableWidget *taskTable);

    /**
     * @brief openJsonfile
     * @param fileName
     * @param taskTable
     */
    void openJsonfile(const QString &fileName, QTableWidget *taskTable);

    /**
     * @brief saveJsonFile
     * @param fileName
     * @param taskTable
     */
    void saveJsonFile(const QString &fileName, QTableWidget *taskTable);

private:
    QMdiArea    *_centralArea;
    Task        *_task;
    TaskForm    *_taskForm;
    QMenu       *_fileMenu;
    QToolBar    *_toolBar;
    QAction     *_newAction, *_deleteAction, *_openAction, *_saveAction, *_quitAction;
};
