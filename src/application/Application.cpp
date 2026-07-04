#include "application/Application.h"
#include "application/UI.h"
#include "graphics/Renderer.h"

int Application::run(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow window;
    window.resize(800, 600);
    window.setWindowTitle("Enlil Simulator");

    // Container fot the app, no margin no padding
    QWidget* container = new QWidget();
    QVBoxLayout* mainLayout = new QVBoxLayout(container);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Renderer & UI
    Renderer* renderer = new Renderer();
    UI* menuBar = new UI();

    // Add widgets to layout
    mainLayout->addWidget(menuBar);
    mainLayout->addWidget(renderer);

    window.setCentralWidget(container);
    window.show();


    /*
    =================
    === Main Loop ===
    =================
    */ 



    return app.exec();
}