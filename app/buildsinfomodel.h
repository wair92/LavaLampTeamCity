/*
  This is free and unencumbered software released into the public domain.
  Author: pavel.hromada@gmail.com
*/

#ifndef BUILDSINFOMODEL_H
#define BUILDSINFOMODEL_H

#include <QAbstractListModel>

class BuildsInfoModel : public QAbstractListModel
{
public:
    BuildsInfoModel( QObject* parent = nullptr );
};

#endif // BUILDSINFOMODEL_H
