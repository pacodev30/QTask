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

    void addTask(const QString &title, const QString &description, const QString &status);
    void saveTaskFile();
    void openTaskFile();

private:
    void initialize();
    void manageLayouts();
    void manageConnects();

private slots:
    void onUpdateBtn_clicked();
    void onDeleteBtn_clicked();


private:
    QVBoxLayout     *_layoutVBox;
    QPushButton     *_updateBtn, *_deleteBtn;
    QTableWidget    *_taskTable;
    QJsonArray      *_tasksJsonArray;
    TaskForm        *_updateForm;
    QString         _fileNane;
};
