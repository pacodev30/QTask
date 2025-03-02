#pragma once

#include <QMainWindow>
#include <QMdiArea>
#include <Task.h>
#include <QMenuBar>
#include <QAction>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onNewBtn_triggered();

private:
    void addTask();

private:
    QAction *_newAction, *_quitAction;
    QMdiArea *_centralArea;
};
