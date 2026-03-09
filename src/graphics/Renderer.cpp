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

    m_program->release();
}

void Renderer::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void Renderer::paintGL()
{
    m_program->bind();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    m_program->setUniformValue(m_matrixUniform, cam.getMatrix());

    std::vector<GLfloat> vertices;
    std::vector<GLfloat> colors;
    std::vector<GLfloat> normals;

    drawCircle(0.0f, 0.5f, vertices, colors, normals);

    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, vertices.data());
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors.data());
    glVertexAttribPointer(m_normAttr, 3, GL_FLOAT, GL_FALSE, 0, normals.data());

    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_colAttr);
    glEnableVertexAttribArray(m_normAttr);

    glDrawArrays(GL_TRIANGLES, 0, vertices.size()/3);

    glDisableVertexAttribArray(m_normAttr);
    glDisableVertexAttribArray(m_colAttr);
    glDisableVertexAttribArray(m_posAttr);

    m_program->release();
}

struct Point {
    float x;
    float y;
    float z;
};

Point evalSphere(float u, float v, float r) {
    Point p;
    p.x = cos(u)*sin(v)*r;
    p.y = cos(v)*r;
    p.z = sin(u)*sin(v)*r;

    return p;
}

void drawCircle(float center, float radius, std::vector<GLfloat>& pos,
                                            std::vector<GLfloat>& col, 
                                            std::vector<GLfloat>& normals) {
    auto addVertex = [&](Point p) {
        pos.push_back(p.x);
        pos.push_back(p.y);
        pos.push_back(p.z);

        col.push_back(0.14);
        col.push_back(0.43);
        col.push_back(0.12);

        normals.push_back(p.x / radius);
        normals.push_back(p.y / radius);
        normals.push_back(p.z / radius);
    };
    
    int uRes = 32;
    int vRes = 32;

    float uEnd = 2 * M_PI;
    float vEnd = M_PI;
    float uStep = (uEnd) / uRes;
    float vStep = (vEnd) / vRes;

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

            addVertex(p1);
            addVertex(p2);
            addVertex(p3);
        }
    }
}