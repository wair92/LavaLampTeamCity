/*
  This is free and unencumbered software released into the public domain.
  Author: pavel.hromada@gmail.com
*/

#include <QNetworkProxyFactory>
#include <QQmlContext>

#include "lavalampapplication.h"
#include "buildprovidersloader.h"

LavaLampApplication::LavaLampApplication( int& argc, char** argv )
    : app_( argc, argv )
{
    QNetworkProxyFactory::setUseSystemConfiguration( true );
}

LavaLampApplication::~LavaLampApplication() = default;

int LavaLampApplication::run()
{
    auto qmlContext = engine_.rootContext();
    qmlContext->setContextProperty( QStringLiteral("buildsModel"), &buildsModel_ );

    engine_.load( QUrl( QStringLiteral( "qrc:/qml/main.qml" )));
    if (engine_.rootObjects().isEmpty())
        return -1;

    auto buildInfoProviders = BuildProvidersLoader::loadBuildInfoProviders();

    if (buildInfoProviders.empty())
        engine_.rootObjects().at( 0 )->setProperty( "configurationError", true );

    return app_.exec();
}
