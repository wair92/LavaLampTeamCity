/*
  This is free and unencumbered software released into the public domain.
  Author: pavel.hromada@gmail.com
*/

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QString>
#include <QJsonArray>
#include <QUrl>

class Configuration
{
public:
    Configuration();

    bool load( const QString& filePath = QString() );

    QJsonArray builds() const;
    QUrl teamCityServerBaseUrl() const;
    int countOfColumns() const;

private:
    QString defaultConfigFilePath() const;

    QJsonArray  buildsConfig_;
    QUrl        serverUrl_;
    int         buildsUiColumnsCount_ = 0;
};

#endif // CONFIGURATION_H
