/*
  This is free and unencumbered software released into the public domain.
  Author: pavel.hromada@gmail.com
*/

#include <QCoreApplication>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include "configuration.h"

Configuration::Configuration() = default;

bool Configuration::load( const QString& filePath )
{
    QString configFilePath = filePath.isEmpty() ? defaultConfigFilePath() : filePath;

    if (configFilePath.isEmpty())
        return false;

    QFile configFile( configFilePath );

    if (!configFile.open( QIODevice::ReadOnly | QIODevice::Text )) {
        qWarning( "Cannot open config file %s", qPrintable( configFilePath ));
        return false;
    }

    auto config = QJsonDocument::fromJson( configFile.readAll() ).object();

    buildsConfig_           = config[ "builds" ].toArray();
    serverUrl_              = config[ "teamCityBaseUrl" ].toString();
    buildsUiColumnsCount_   = config[ "buildInfoUiColumns" ].toInt();

    return true;
}

QJsonArray Configuration::builds() const
{
    return buildsConfig_;
}

QUrl Configuration::teamCityServerBaseUrl() const
{
    return serverUrl_;
}

int Configuration::countOfColumns() const
{
    return buildsUiColumnsCount_;
}

QString Configuration::defaultConfigFilePath() const
{
    QString configFilePath;
    auto appArgs = QCoreApplication::arguments();

    if (appArgs.size() == 2) // executable name + config file name
        configFilePath = appArgs.at( 1 );
    else
        configFilePath = QCoreApplication::applicationDirPath() + QDir::separator() + "config.json";

    return QFile::exists( configFilePath ) ? configFilePath : QString();
}
