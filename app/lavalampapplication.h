/*
  This is free and unencumbered software released into the public domain.
  Author: pavel.hromada@gmail.com
*/

#ifndef LAVALAMPAPPLICATION_H
#define LAVALAMPAPPLICATION_H

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "buildsinfomodel.h"
#include "buildinfoprovider.h"

class LavaLampApplication
{
public:
    LavaLampApplication( int& argc, char** argv );
    ~LavaLampApplication();

    int run();

private:
    BuildInfoProviderContainer loadBuildInfoProviders( const QJsonArray& builds,
                                                       const QUrl& serverUrl ) const;

    QGuiApplication         app_;
    QQmlApplicationEngine   engine_;
    BuildsInfoModel         buildsModel_;
};

#endif // LAVALAMPAPPLICATION_H
