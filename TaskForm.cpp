#include "TaskForm.h"

TaskForm::TaskForm(QWidget *parent)
    : QDialog{parent}
{
    initialize();
    manageLayouts();
    manageConnects();
}

// MANAGE
void TaskForm::initialize()
{
    _formLayout = new QFormLayout(this);
    _titleLine = new QLineEdit(this);

    _alertTitleLabel = new QLabel(tr("Title is required :-("), this);
        _alertTitleLabel->setStyleSheet("QLabel {color : brown;}");
    _confirmTitleLabel = new QLabel(":-)", this);
        _confirmTitleLabel->setStyleSheet("QLabel {color : green;}");
        _confirmTitleLabel->hide();
    _descriptionText = new QTextEdit(this);
    _statusList = {
        tr("Pending"),
        tr("In progress"),
        tr("Completed")
    };
    _submitBtn = new QPushButton(tr("Submit"), this);
}

void TaskForm::manageLayouts()
{
    setLayout(_formLayout);
        _formLayout->addRow(tr("title"), _titleLine);
        _formLayout->addWidget(_alertTitleLabel);
        _formLayout->addWidget(_confirmTitleLabel);
        _formLayout->addRow(tr("Description"), _descriptionText);
        _formLayout->addRow(tr("Status"), addQRadios(_statusList));
        _formLayout->addWidget(_submitBtn);
}

void TaskForm::manageConnects()
{
    connect(_titleLine, SIGNAL(textEdited(QString)), this, SLOT(onTitleLine_changed()));
    connect(_submitBtn, SIGNAL(clicked(bool)), this, SLOT(onSubmitBtn_clicked()));
}

// EVENTS
void TaskForm::onSubmitBtn_clicked()
{
    if(!_titleLine->text().isEmpty())
    {
        _dataTitle = _titleLine->text();
        _dataDescription = _descriptionText->toPlainText();
        _dataStatus = _buttonGroupStatus->checkedButton()->text();
        this->close();
    }
}

void TaskForm::onTitleLine_changed()
{
    if(_titleLine->text().isEmpty())
    {
        _alertTitleLabel->show();
        _confirmTitleLabel->hide();
    } else
    {
        _alertTitleLabel->hide();
        _confirmTitleLabel->show();
    }
}

// FUNCTIONS
QWidget* TaskForm::addQRadios(QStringList &values)
{
    _containerStatus = new QWidget(this);
    _vBoxStatus = new QVBoxLayout(_containerStatus);
    _buttonGroupStatus = new QButtonGroup(_containerStatus);

    for(int i = 0; i < values.size(); i++)
    {
        QRadioButton *radio = new QRadioButton(values.at(i), _containerStatus);
        _buttonGroupStatus->addButton(radio);
        _vBoxStatus->addWidget(radio);
        if(radio->text() == values.at(0))
            radio->setChecked(true);
    }

    return _containerStatus;
}

// GETTERS AND SETTERS
QButtonGroup *TaskForm::buttonGroupStatus() const
{
    return _buttonGroupStatus;
}

QTextEdit *TaskForm::descriptionText() const
{
    return _descriptionText;
}

QLineEdit *TaskForm::titleLine() const
{
    return _titleLine;
}

QLabel *TaskForm::alertTitleLabel() const
{
    return _alertTitleLabel;
}

QString TaskForm::dataTitle() const
{
    return _dataTitle;
}

QString TaskForm::dataDescription() const
{
    return _dataDescription;
}

QString TaskForm::dataStatus() const
{
    return _dataStatus;
}



