#pragma once
#include <QTableWidget>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QMessageBox>
#include <TaskForm.h>

class Task : public QWidget
{
    Q_OBJECT
public:
    explicit Task(QWidget *parent = nullptr);

    /**
     * @brief taskTable
     * @return
     */
    QTableWidget *taskTable() const;

    /**
     * @brief setTaskTable
     * @param newTaskTable
     */
    void setTaskTable(QTableWidget *newTaskTable);

private:
    /**
     * @brief initialize
     */
    void initialize();

    /**
     * @brief manageLayouts
     */
    void manageLayouts();

    /**
     * @brief manageConnects
     */
    void manageConnects();

private slots:
    /**
     * @brief onUpdateBtn_clicked
     */
    void onUpdateBtn_clicked();

    /**
     * @brief onDeleteBtn_clicked
     */
    void onDeleteBtn_clicked();

private:
    QVBoxLayout     *_layoutVBox;
    QPushButton     *_updateBtn, *_deleteBtn;
    QTableWidget    *_taskTable;
    QJsonArray      *_tasksJsonArray;
    TaskForm        *_updateForm;
};

