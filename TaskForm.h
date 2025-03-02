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

    /**
     * @brief dataTitle
     * @return
     */
    QString dataTitle() const;

    /**
     * @brief dataDescription
     * @return
     */
    QString dataDescription() const;

    /**
     * @brief dataStatus
     * @return
     */
    QString dataStatus() const;

private:
    /**
     * @brief addQRadios
     * @param values
     * @return
     */
    QWidget* addQRadios(QStringList &values);

private slots:
    /**
     * @brief onSubmitBtn_clicked
     */
    void onSubmitBtn_clicked();

    /**
     * @brief onTitleLine_changed
     */
    void onTitleLine_changed();

private:
    QFormLayout *_formLayout;
    QVBoxLayout *_vBoxStatus;
    QButtonGroup *_buttonGroupStatus;
    QLineEdit *_titleLine;
    QLabel *_alertTitleLabel, *_confTitleLabel;
    QTextEdit *_descriptionText;
    QStringList  _statusList;
    QPushButton *_submitBtn;
    QListWidget *_statusListWidget;
    QWidget *_containerStatus;
    QString _dataTitle, _dataDescription, _dataStatus;
};
