/*
  This is free and unencumbered software released into the public domain.
  Author: pavel.hromada@gmail.com
*/

#include <QNetworkProxyFactory>
#include <QQmlContext>
#include <QNetworkAccessManager>
#include <QJsonObject>

#include "lavalampapplication.h"
#include "configuration.h"

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

    Configuration config;
    config.load(); // let it load config file from default locations

    auto buildInfoProviders = loadBuildInfoProviders( config.builds(),
                                                      config.teamCityServerBaseUrl() );

    auto mainWindow = engine_.rootObjects().at( 0 );

    if (buildInfoProviders.empty())
        mainWindow->setProperty( "configurationError", true );

    mainWindow->setProperty( "buildInfoColumns", config.countOfColumns() );

    buildsModel_.setBuildsProviders( std::move( buildInfoProviders ));

    return app_.exec();
}

BuildInfoProviderContainer LavaLampApplication::loadBuildInfoProviders( const QJsonArray& builds,
                                                                        const QUrl& serverUrl ) const
{
    BuildInfoProviderContainer infoProviders;
    auto nam = std::make_shared<QNetworkAccessManager>();

    infoProviders.reserve( static_cast<BuildInfoProviderContainer::size_type>( builds.size() ));

    for (const auto& buildConfig : builds)
        infoProviders.emplace_back( new BuildInfoProvider( serverUrl, nam, buildConfig.toObject() ));

    return infoProviders;
}
