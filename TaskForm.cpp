#include "TaskForm.h"

TaskForm::TaskForm(QWidget *parent)
    : QDialog{parent}
{
    // INIT
    _formLayout = new QFormLayout(this);
    _titleLine = new QLineEdit(this);
    _alertTitleLabel = new QLabel(tr("Title is require ;)"), this);
        _alertTitleLabel->setStyleSheet("QLabel {color : brown;}");
    _confTitleLabel = new QLabel(tr(":)"), this);
        _confTitleLabel->setStyleSheet("QLabel {color : green;}");
        _confTitleLabel->hide();
    _descriptionText = new QTextEdit(this);
    _statusList = {
        tr("Pending"),
        tr("In progress"),
        tr("Completed")
    };
    _submitBtn = new QPushButton(tr("Submit"), this);

    // LAYOUT
    setLayout(_formLayout);
        _formLayout->addRow(tr("title"), _titleLine);
        _formLayout->addWidget(_alertTitleLabel);
        _formLayout->addWidget(_confTitleLabel);
        _formLayout->addRow(tr("Description"), _descriptionText);
        _formLayout->addRow(tr("Status"), addQRadios(_statusList));
        _formLayout->addWidget(_submitBtn);

    // CONNECT
    connect(_titleLine, SIGNAL(textEdited(QString)), this, SLOT(onTitleLine_changed()));
    connect(_submitBtn, SIGNAL(clicked(bool)), this, SLOT(onSubmitBtn_clicked()));
}

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

void TaskForm::onSubmitBtn_clicked()
{
    if(!_titleLine->text().isEmpty())
    {
        _dataTitle = _titleLine->text();
        _dataDescription = _descriptionText->toPlainText();
        _dataStatus = _buttonGroupStatus->checkedButton()->text();
        this->close();
    }

    qDebug() << _dataTitle << _dataDescription << _dataStatus;
}

void TaskForm::onTitleLine_changed()
{
    if(_titleLine->text().isEmpty())
    {
        _alertTitleLabel->show();
        _confTitleLabel->hide();
    } else
    {
        _alertTitleLabel->hide();
        _confTitleLabel->show();
    }
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



