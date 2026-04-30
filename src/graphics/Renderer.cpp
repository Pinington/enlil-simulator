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

    glBindBuffer(GL_ARRAY_BUFFER, offsetVBO);
    glBufferData(GL_ARRAY_BUFFER, 64 * sizeof(float) * 3, nullptr, GL_DYNAMIC_DRAW); // 64 = MaxSpheres

    drawSphere(0.5f);

    glBindBuffer(GL_ARRAY_BUFFER, offsetVBO);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(3);
    glVertexAttribDivisor(3, 1); // Per instance instead of per vertex

    instantiateSphere(0.f, -1.f, 0.f);
    instantiateSphere(0.f, 1.f, 0.f);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
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

    m_program->setUniformValue(m_matrixUniform, cam.getMatrix());
    glBindVertexArray(this->VAO);
    glDrawElementsInstanced(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, 0, sphereCount);

    m_program->release();
}

void Renderer::drawSphere(float radius) {
    
    auto evalSphere = [](float u, float v, float r) {
        Point p;
        p.x = cos(u)*sin(v)*r;
        p.y = cos(v)*r;
        p.z = sin(u)*sin(v)*r;

        return p;
    };

    auto addVertex = [&](Point p) {
        // Coordinates
        arr.push_back(p.x);
        arr.push_back(p.y);
        arr.push_back(p.z);

        // Colors
        arr.push_back(0.14);
        arr.push_back(0.43);
        arr.push_back(0.12);

        // Normals are normalized in the fragment shader
        arr.push_back(p.x);
        arr.push_back(p.y);
        arr.push_back(p.z);
    };
    
    int uRes = 32;
    int vRes = 32;

    float uEnd = 2 * M_PI;
    float vEnd = M_PI;
    float uStep = (uEnd) / uRes;
    float vStep = (vEnd) / vRes;

    int c = arr.size() / 9; 
    for (int u = 0; u < uRes; u++) {
        for (int v = 0; v < vRes; v++) {
            float lng = u * uStep;
            float lat = v * vStep;

            float lngN = (u + 1 == uRes) ? uEnd : (u + 1) * uStep;
            float latN = (v + 1 == vRes) ? vEnd : (v + 1) * vStep;

            Point p0 = evalSphere(lng, lat, radius);
            Point p1 = evalSphere(lng, latN, radius);
            Point p2 = evalSphere(lngN, lat, radius);
            Point p3 = evalSphere(lngN, latN, radius);

            addVertex(p0);
            addVertex(p1);
            addVertex(p2);
            addVertex(p3);
            
            idx.push_back(c + 0);
            idx.push_back(c + 1);
            idx.push_back(c + 2);

            idx.push_back(c + 1);
            idx.push_back(c + 2);
            idx.push_back(c + 3);
            c += 4;
        }
    }

    vertexCount = idx.size();

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * arr.size(), arr.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, idx.size() * sizeof(GLuint), idx.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*) (3 * sizeof(GLfloat)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*) (6 * sizeof(GLfloat)));
}

void Renderer::instantiateSphere(float x, float y, float z) {
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
    repaint();
}