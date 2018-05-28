/*
  This is free and unencumbered software released into the public domain.
  Author: pavel.hromada@gmail.com
*/

#include <QCoreApplication>
#include "lavalampapplication.h"

int main( int argc, char* argv[] )
{
    QCoreApplication::setAttribute( Qt::AA_EnableHighDpiScaling );

    LavaLampApplication app( argc, argv );
    return app.run();
}
