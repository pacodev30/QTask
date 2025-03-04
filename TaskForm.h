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

    /**
     * @brief titleLine
     * @return
     */
    QLineEdit *titleLine() const;

    /**
     * @brief alertTitleLabel
     * @return
     */
    QLabel *alertTitleLabel() const;

    /**
     * @brief descriptionText
     * @return
     */
    QTextEdit *descriptionText() const;

    /**
     * @brief buttonGroupStatus
     * @return
     */
    QButtonGroup *buttonGroupStatus() const;


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

    /**
     * @brief addQRadios
     * @param values
     * @return
     */
    QWidget* addQRadios(QStringList &values);

private slots:
    void onSubmitBtn_clicked();
    void onTitleLine_changed();

private:
    QFormLayout     *_formLayout;
    QVBoxLayout     *_vBoxStatus;
    QButtonGroup    *_buttonGroupStatus;
    QLineEdit       *_titleLine;
    QLabel          *_alertTitleLabel, *_confirmTitleLabel;
    QTextEdit       *_descriptionText;
    QPushButton     *_submitBtn;
    QListWidget     *_statusListWidget;
    QWidget         *_containerStatus;
    QStringList     _statusList;
    QString         _dataTitle, _dataDescription, _dataStatus;
};
