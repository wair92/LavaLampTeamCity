/*
  This is free and unencumbered software released into the public domain.
  Author: pavel.hromada@gmail.com
*/

#ifndef BUILDSINFOMODEL_H
#define BUILDSINFOMODEL_H

#include <QAbstractListModel>
#include "buildinfoprovider.h"

class BuildsInfoModel : public QAbstractListModel
{
public:
    enum Role {
        Name = Qt::UserRole + 1,
        Status
    };

    BuildsInfoModel();

    void setBuildsProviders( BuildInfoProviderContainer&& providers );

    int rowCount( const QModelIndex& parent = QModelIndex() ) const override;
    QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    void connectBuildInfoProviders();
    QString buildStatusToString( BuildStatus status ) const;
    void onBuildInfoChanged( quint32 index );

    BuildInfoProviderContainer buildInfoProviders_;
};

#endif // BUILDSINFOMODEL_H
