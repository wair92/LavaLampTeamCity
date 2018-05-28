/*
  This is free and unencumbered software released into the public domain.
  Author: pavel.hromada@gmail.com
*/

#include <functional>

#include "buildsinfomodel.h"

BuildsInfoModel::BuildsInfoModel()
{}

void BuildsInfoModel::setBuildsProviders( BuildInfoProviderContainer&& providers )
{
    beginResetModel();
    buildInfoProviders_ = std::move( providers );
    connectBuildInfoProviders();
    endResetModel();
}

int BuildsInfoModel::rowCount( const QModelIndex& /*parent*/ ) const
{
    return static_cast<int>( buildInfoProviders_.size() );
}

QVariant BuildsInfoModel::data( const QModelIndex& index, int role ) const
{
    if (index.row() >= rowCount() || role < Qt::UserRole)
        return {};

    const auto& buildInfo = buildInfoProviders_[ static_cast<quint32>( index.row() )];

    if ( role == Name )
        return buildInfo->name();
    else
        return buildStatusToString( buildInfo->status() );
}

QHash<int, QByteArray> BuildsInfoModel::roleNames() const
{
    static QHash<int, QByteArray> roles {
        { Name,     QByteArrayLiteral("Name")   },
        { Status,   QByteArrayLiteral("Status") }
    };

    return roles;
}

void BuildsInfoModel::connectBuildInfoProviders()
{
    using std::placeholders::_1;

    for (quint32 i = 0; i < buildInfoProviders_.size(); ++i)
        connect( buildInfoProviders_[ i ].get(), &BuildInfoProvider::statusChanged,
                 std::bind( &BuildsInfoModel::onBuildInfoChanged, this, _1 ));
}

QString BuildsInfoModel::buildStatusToString(BuildStatus status) const
{
    if (status == BuildStatus::Success)
        return QStringLiteral( "success" );
    else if (status == BuildStatus::Running)
        return QStringLiteral( "running" );
    else
        return QStringLiteral( "failed" );
}

void BuildsInfoModel::onBuildInfoChanged( quint32 idx )
{
    emit dataChanged( index( static_cast<int>( idx )),
                      index( static_cast<int>( idx )));
}
