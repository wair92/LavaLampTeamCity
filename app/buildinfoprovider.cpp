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
    buildStatusUrl_ = teamCityBaseUrl.url()
        + QStringLiteral("guestAuth/app/rest/builds?locator=buildType(id:%1),count:1,running:any" )
              .arg( config[ "buildTypeId" ].toString() );

    qDebug( "URL for %s: %s", qPrintable( name_ ), qPrintable( buildStatusUrl_.url() ));

    lastCommiteeUrl_ = teamCityBaseUrl.url()
        + QStringLiteral("guestAuth/app/rest/changes?locator=buildType(id:%1),count:1" )
            .arg( config[ "buildTypeId" ].toString() );

    qDebug( "URL for %s: %s", qPrintable( name_ ), qPrintable( lastCommiteeUrl_.url() ));

    requestStatus();
    requestLastCommitee();
}

BuildStatus BuildInfoProvider::status() const
{
    return status_;
}

QString BuildInfoProvider::name() const
{
    return name_;
}

QString BuildInfoProvider::lastCommitee() const
{
    return lastCommitee_;
}

QString BuildInfoProvider::formatedLastCommitee() const
{
    QString name {""};
    QString surname {""};
    auto signIndex = lastCommitee_.indexOf("<");
    if( signIndex == -1 ){
        int dotIntex = lastCommitee_.indexOf(".");
        int atIndex = lastCommitee_.indexOf("@");
        if(dotIntex < 0 || atIndex < 0)
            return lastCommitee_;
        surname = lastCommitee_.mid( 0, dotIntex );
        name = lastCommitee_.mid( dotIntex + 1, atIndex - dotIntex -1 );
        return name + " " + surname;
    }
    else{
        int spaceIndex = lastCommitee_.indexOf(" ");
        surname = lastCommitee_.mid( 0, spaceIndex );
        name = lastCommitee_.mid( spaceIndex + 1, signIndex - spaceIndex -1 );
        return name + " " + surname;
    }
}

void BuildInfoProvider::requestStatus()
{
    QNetworkRequest request;
    request.setUrl( buildStatusUrl_ );
    request.setRawHeader( "Accept", "application/json" );

    responseStatus_ = nam_->get( request );
    connect( responseStatus_, &QNetworkReply::finished, this, &BuildInfoProvider::processStatusResponse );


}

void BuildInfoProvider::requestLastCommitee()
{
    QNetworkRequest request;
    request.setUrl( lastCommiteeUrl_ );
    request.setRawHeader( "Accept", "application/json" );

    responseLastCommitee_ = nam_->get( request );
    connect( responseLastCommitee_, &QNetworkReply::finished, this, &BuildInfoProvider::processLastCommiteeResponse );
}

void BuildInfoProvider::processStatusResponse()
{
    if (!responseStatus_ || responseStatus_->error() != QNetworkReply::NoError) {
        qWarning( "Error during %s status update", qPrintable( name_ ));
        qWarning( "Error message: %s", qPrintable( responseStatus_->errorString() ));
        QTimer::singleShot( 30000, this, &BuildInfoProvider::requestStatus );
        return;
    }

    BuildStatus newStatus = BuildStatus::Failed;
    auto json = QJsonDocument::fromJson( responseStatus_->readAll() ).object();
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

    responseStatus_->deleteLater();
    responseStatus_ = nullptr;

    QTimer::singleShot( 30000, this, &BuildInfoProvider::requestStatus );
}

void BuildInfoProvider::processLastCommiteeResponse()
{
    if (!responseLastCommitee_ || responseLastCommitee_->error() != QNetworkReply::NoError) {
        qWarning( "Error during %s Last commitee update", qPrintable( name_ ));
        qWarning( "Error message: %s", qPrintable( responseStatus_->errorString() ));
        return;
    }

    auto json = QJsonDocument::fromJson( responseLastCommitee_->readAll() ).object();
    auto buildInfo = json["change"].toArray().at( 0 ).toObject();
    QString newUserName = buildInfo[ "username" ].toString();

    if (newUserName != lastCommitee_) {
        lastCommitee_ = newUserName;
        emit lastCommiteeChanged();
    }

    responseLastCommitee_->deleteLater();
    responseLastCommitee_ = nullptr;

    QTimer::singleShot( 30000, this, &BuildInfoProvider::requestLastCommitee );
}
