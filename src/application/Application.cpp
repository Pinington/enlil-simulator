#include "application/Application.h"

#if TESTING
#include "core/Particles.h"
#endif

inline void newFrame(Engine& e, ParticleSystem& ps, Renderer* r) {
    /*
     The architecture might suck ass because I need to independently work on the particles and
     renderer so the user kinda has to know that or use this function
    */
    e.applyGravity();
    ps.updateSystem();
    r->updatePositions(ps.getPositions());
}

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
    // Creating particles manually for test
    float x = 0.f; float y = 0.f; float z = 0.f;
    SphereParticle s ( {x, y, z}, 1.0f );
    particles.addParticles(s);
    renderer->instantiateSphere(x, y, z);

    renderer->updatePositions(std::vector<float> {0.f, 1.f, 0.f});

#endif

    QTimer* simulationTimer = new QTimer();

    QObject::connect(simulationTimer, &QTimer::timeout, [&]() {
        newFrame(engine, particles, renderer);
    });

    simulationTimer->start(DELTA_T);

    return app.exec();
}