/*
  This is free and unencumbered software released into the public domain.
  Author: pavel.hromada@gmail.com
*/

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTimer>

#include "buildinfoprovider.h"

BuildInfoProvider::BuildInfoProvider( const QUrl& teamCityBaseUrl,
                                      std::shared_ptr<QNetworkAccessManager>& nam,
                                      const QJsonObject& config )
    : nam_( nam )
{
    name_ = config[ "buildName" ].toString();
    url_ = teamCityBaseUrl.url()
        + QStringLiteral("/guestAuth/app/rest/builds?locator=buildType(id:%1),count:1,running:any" )
              .arg( config[ "buildTypeId" ].toString() );

    qDebug( "URL for %s: %s", qPrintable( name_ ), qPrintable( url_.url() ));

    requestStatus();
}

BuildStatus BuildInfoProvider::status() const
{
    return status_;
}

QString BuildInfoProvider::name() const
{
    return name_;
}

void BuildInfoProvider::requestStatus()
{
    QNetworkRequest request;
    request.setUrl( url_ );
    request.setRawHeader( "Accept", "application/json" );

    auto response_ = nam_->get( request );

    connect( response_, &QNetworkReply::finished, this, &BuildInfoProvider::processResponse );
}

void BuildInfoProvider::processResponse()
{
    if (!response_ || response_->error() != QNetworkReply::NoError) {
        qWarning( "Error during %s status update", qPrintable( name_ ));
        QTimer::singleShot( 30000, this, &BuildInfoProvider::requestStatus );
        return;
    }

    BuildStatus newStatus = BuildStatus::Failed;
    auto json = QJsonDocument::fromJson( response_->readAll() ).object();
    auto buildInfo = json["build"].toArray().at( 0 ).toObject();

    if (buildInfo[ "state" ].toString() == "running")
        newStatus = BuildStatus::Running;
    else if (buildInfo[ "status" ].toString() == "SUCCESS")
        newStatus = BuildStatus::Success;
    else
        newStatus = BuildStatus::Failed;

    if (newStatus != status_) {
        status_ = newStatus;
        emit statusChanged();
    }

    response_->deleteLater();
    response_ = nullptr;

    QTimer::singleShot( 30000, this, &BuildInfoProvider::requestStatus );
}
