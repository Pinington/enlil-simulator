#include "graphics/Renderer.h"
#include "graphics/Camera.h"

void Renderer::initializeGL()
{
    makeCurrent();  
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    
    cam = Camera(float(width()) / float(height()));
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/src/graphics/shaders/vertex.glsl");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/src/graphics/shaders/fragment.glsl");
    m_program->link();
    
    m_posAttr = m_program->attributeLocation("posAttr");
    m_colAttr = m_program->attributeLocation("colAttr");
    m_normAttr = m_program->attributeLocation("normalAttr");
    m_matrixUniform = m_program->uniformLocation("matrix");

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);

    Point center = {-0.5f, 0.0f, 0.0f};
    drawSphere(center, 0.5f);

    Point center2 = {0.5f, 0.0f, -0.2f};
    drawSphere(center2, 0.3f);

    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(m_posAttr);
    
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(m_colAttr);
    
    glVertexAttribPointer(m_normAttr, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*) (6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(m_normAttr);

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
    m_program->bind();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_program->setUniformValue(m_matrixUniform, cam.getMatrix());

    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, idx.size(), GL_UNSIGNED_INT, 0);

    m_program->release();
}

Point evalSphere(float u, float v, float r) {
    Point p;
    p.x = cos(u)*sin(v)*r;
    p.y = cos(v)*r;
    p.z = sin(u)*sin(v)*r;

    return p;
}

void Renderer::drawSphere(Point center, float radius) {
    
    auto addVertex = [&](Point p) {
        // Coordinates
        arr.push_back(p.x + center.x);
        arr.push_back(p.y + center.y);
        arr.push_back(p.z + center.z);

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
            
            this->idx.push_back(c + 0);
            this->idx.push_back(c + 1);
            this->idx.push_back(c + 2);

            this->idx.push_back(c + 1);
            this->idx.push_back(c + 2);
            this->idx.push_back(c + 3);
            c += 4;
        }
    }

    this->vertexCount = arr.size() / 9;

    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * arr.size(), arr.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, idx.size() * sizeof(GLuint), idx.data(), GL_STATIC_DRAW);
}