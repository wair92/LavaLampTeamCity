/*
  This is free and unencumbered software released into the public domain.
  Author: pavel.hromada@gmail.com
*/

#ifndef LAVALAMPAPPLICATION_H
#define LAVALAMPAPPLICATION_H

#include <QGuiApplication>
#include <QQmlApplicationEngine>

class LavaLampApplication
{
public:
    LavaLampApplication( int& argc, char** argv );

    int run();

private:
    QGuiApplication       app_;
    QQmlApplicationEngine engine_;
};

#endif // LAVALAMPAPPLICATION_H
