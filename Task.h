#pragma once

#include <QTableWidget>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>

class Task : public QWidget
{
    Q_OBJECT
public:
    explicit Task(QWidget *parent = nullptr);

private slots:
    /**
     * @brief onAddBtn_clicked
     */
    void onAddBtn_clicked();

    /**
     * @brief onDeleteBtn_clicked
     */
    void onDeleteBtn_clicked();

    /**
     * @brief onSaveBtn_clicked
     */
    void onSaveBtn_clicked();

    /**
     * @brief onLoadBtn_clicked
     */
    void onLoadBtn_clicked();

private:
    QVBoxLayout *_layoutVBox;
    QPushButton *_addBtn, *_deleteBtn,*_loadBtn, *_saveBtn;
    QTableWidget *_taskTable;
    QJsonArray *_tasksJsonArray;
    QString _fileNane;
};
