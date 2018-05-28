/*
  This is free and unencumbered software released into the public domain.
  Author: pavel.hromada@gmail.com
*/

#ifndef BUILDINFOPROVIDER_H
#define BUILDINFOPROVIDER_H

#include <QObject>

class BuildInfoProvider : public QObject
{
    Q_OBJECT
public:
    explicit BuildInfoProvider( QObject* parent = nullptr );

signals:

public slots:
};

#endif // BUILDINFOPROVIDER_H
