#pragma once

enum class EHeaders
{
    Title,
    Description,
    Status
};

enum class EStatus
{
    Pending,
    InProgress,
    Completed
};

qDebug() << Q_ENUM(EHeaders::Title);
