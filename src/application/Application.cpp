#include "application/Application.h"
#include "graphics/Renderer.h"

int Application::run(int argc, char *argv[])
{
    // Create QT app
    QApplication app(argc, argv);

    // Start a window
    QMainWindow window;
    window.resize(800, 600);
    window.setWindowTitle("Enlil Simulator");

    // Start physics renderer and add to window
    Renderer* renderer = new Renderer();
    window.setCentralWidget(renderer);
    
    // Show window
    window.show();

    return app.exec();
}