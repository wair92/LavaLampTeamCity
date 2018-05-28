/*
  This is free and unencumbered software released into the public domain.
  Author: pavel.hromada@gmail.com
*/

#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QUrl>

#include "buildprovidersloader.h"

QJsonObject configJsonObject()
{
    QString configFilePath;
    auto appArgs = QCoreApplication::arguments();

    if (appArgs.size() == 2) // executable name + config file name
        configFilePath = appArgs.at( 1 );
    else
        configFilePath = QCoreApplication::applicationDirPath() + QDir::separator() + "config.json";

    QFile configFile( configFilePath );

    if (!configFile.open( QIODevice::ReadOnly | QIODevice::Text )) {
        qWarning( "Cannot open config file %s", qPrintable( configFilePath ));
        return QJsonObject();
    }

    return QJsonDocument::fromJson( configFile.readAll() ).object();
}

BuildInfoProviderContainer BuildProvidersLoader::loadBuildInfoProviders()
{
    const auto config = configJsonObject();

    if (config.isEmpty()) {
        qWarning( "Empty config json file" );
        return BuildInfoProviderContainer();
    }

    auto nam = std::make_shared<QNetworkAccessManager>();
    BuildInfoProviderContainer infoProviders;

    QUrl baseUrl{ config[ "teamCityBaseUrl" ].toString() };

    const auto buildsConfig = config[ "builds" ].toArray();
    infoProviders.reserve( static_cast<BuildInfoProviderContainer::size_type>( buildsConfig.size() ));

    for (const auto& buildConfig : buildsConfig)
        infoProviders.emplace_back( new BuildInfoProvider( baseUrl, nam, buildConfig.toObject() ));

    return infoProviders;
}

