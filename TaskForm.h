#pragma once

#include <QWidget>
#include <QDialog>
#include <QFormLayout>
#include <QButtonGroup>
#include <QLineEdit>
#include <QLabel>
#include <QTextEdit>
#include <QRadioButton>
#include <QPushButton>
#include <QListWidget>
#include <QMap>


class TaskForm : public QDialog
{
    Q_OBJECT
public:
    explicit TaskForm(QWidget *parent = nullptr);

    QString dataTitle() const;
    QString dataDescription() const;
    QString dataStatus() const;



    QLineEdit *titleLine() const;
    QLabel *alertTitleLabel() const;
    QTextEdit *descriptionText() const;

    QButtonGroup *buttonGroupStatus() const;


private:
    QWidget* addQRadios(QStringList &values);

private slots:
    void onSubmitBtn_clicked();
    void onTitleLine_changed();

private:
    QFormLayout     *_formLayout;
    QVBoxLayout     *_vBoxStatus;
    QButtonGroup    *_buttonGroupStatus;
    QLineEdit       *_titleLine;
    QLabel          *_alertTitleLabel, *_confTitleLabel;
    QTextEdit       *_descriptionText;
    QPushButton     *_submitBtn;
    QListWidget     *_statusListWidget;
    QWidget         *_containerStatus;
    QStringList     _statusList;
    QString         _dataTitle, _dataDescription, _dataStatus;
};
