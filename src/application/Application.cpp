#include "application/Application.h"

#if TESTING
#include "core/Particles.h"
#endif

int Application::run(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow window;
    window.resize(800, 600);
    window.setWindowTitle("Enlil Simulator");

    // Container for the app, no margin no padding
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

    ParticleSystem particles;
    Engine engine(particles);

    
#if TESTING
    Sphere s ( {0.f, 0.f, 0.f}, 1.0f );
    particles.addParticles(s);
#endif

    return app.exec();
}