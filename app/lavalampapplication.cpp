/*
  This is free and unencumbered software released into the public domain.
  Author: pavel.hromada@gmail.com
*/

#include <QNetworkProxyFactory>
#include "lavalampapplication.h"

LavaLampApplication::LavaLampApplication( int& argc, char** argv )
    : app_( argc, argv )
{
    QNetworkProxyFactory::setUseSystemConfiguration( true );
    // TODO load config
}

int LavaLampApplication::run()
{
    engine_.load( QUrl( QStringLiteral( "qrc:/qml/main.qml" )));
    if (engine_.rootObjects().isEmpty())
        return -1;

    return app_.exec();
}
