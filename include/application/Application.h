#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>

#include "application/UI.h"
#include "graphics/Renderer.h"

#include "physics/Engine.h"

class Application
{
public:
    int run(int argc, char *argv[]);
};

#endif