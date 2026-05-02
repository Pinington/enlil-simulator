#include "graphics/Renderer.h"
#include "graphics/Camera.h"
#include <QTimer>
#include <string>
#include <sstream>
#include <QFile>
        
Renderer::Renderer(QWidget *parent): QOpenGLWidget(parent), cam(float(800) / float(600)) {
    /* Constructor for regular FPS refresh
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&Renderer::update));
    timer->start(16); 
    */
}


void Renderer::initializeGL()
{
    makeCurrent();  
    setFocusPolicy(Qt::StrongFocus);
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/src/graphics/shaders/vertex.glsl");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/src/graphics/shaders/fragment.glsl");
    m_program->link();

    m_matrixUniform = m_program->uniformLocation("matrix");
    cam = Camera(float(width()) / float(height()));

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &offsetVBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // Initalize Meshes
    SphereData dat = sm.createSphere(0.5f);

    std::vector<GLfloat> sphere_arr = dat.arr;
    std::vector<unsigned int> sphere_idx = dat.idx;


    // Pass data to VBOs and EBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * sphere_arr.size(), sphere_arr.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, offsetVBO);
    glBufferData(GL_ARRAY_BUFFER, MAX_SPHERES * sizeof(float) * 3, nullptr, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphere_idx.size() * sizeof(GLuint), sphere_idx.data(), GL_STATIC_DRAW);


    // Pass info to VAO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*) (3 * sizeof(GLfloat)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*) (6 * sizeof(GLfloat)));

    glBindBuffer(GL_ARRAY_BUFFER, offsetVBO);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glVertexAttribDivisor(3, 1); // Per instance instead of per vertex

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    // Simulate user input (testing)
    instantiateSphere(0.f, -1.f, 0.f);
    instantiateSphere(0.f, 1.f, 0.f);

    m_program->release();
}

void Renderer::resizeGL(int w, int h)
{
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    cam.chPerspective(float(w) / float(h));
}

void Renderer::paintGL()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    m_program->bind();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(VAO);
    m_program->setUniformValue(m_matrixUniform, cam.getMatrix());
    glDrawElementsInstanced(GL_TRIANGLES, sm.getvertexCount(), GL_UNSIGNED_INT, 0, sphereCount);

    m_program->release();
}

void Renderer::instantiateSphere(float x, float y, float z) {
    if (sphereCount >= MAX_SPHERES) return;
    glBindBuffer(GL_ARRAY_BUFFER, offsetVBO);
    float data[3] = { x, y, z };
    glBufferSubData(GL_ARRAY_BUFFER,
                    sphereCount * sizeof(float) * 3, // offset in buffer
                    sizeof(data),
                    data);
    sphereCount++;
}

void Renderer::keyPressEvent(QKeyEvent *event) {
    int k = event->key();
    switch (k) {
        case Qt::Key_W: cam.move(0, 0, cam.speed); break;
        case Qt::Key_S: cam.move(0, 0, -cam.speed); break;
        case Qt::Key_A: cam.rotate(0, 1, 0, 2); break;
        case Qt::Key_D: cam.rotate(0, 1, 0, -2); break;
    }
    update();
}