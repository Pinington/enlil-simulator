#include "graphics/Renderer.h"
#include "graphics/Camera.h"

void Renderer::initializeGL()
{
    makeCurrent();
    initializeOpenGLFunctions();
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/src/graphics/shaders/vertex.glsl");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/src/graphics/shaders/fragment.glsl");
    m_program->link();
    m_posAttr = m_program->attributeLocation("posAttr");
    m_colAttr = m_program->attributeLocation("colAttr");
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

    glClear(GL_COLOR_BUFFER_BIT);

    Camera* cam = new Camera(float(width()) / float(height()));

    m_program->setUniformValue(m_matrixUniform, cam->getMatrix());

    GLfloat vertices[] = {
        0.0f, 0.5f, 0.0f,
        -0.6f, -0.5f, 0.0f,
        0.6f, -0.5f, 0.0f,
        0.0f, -0.8f, 0.5f
    };

    GLfloat colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.f, 1.f, 1.f
    };

    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors);

    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_colAttr);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glDisableVertexAttribArray(m_colAttr);
    glDisableVertexAttribArray(m_posAttr);

    m_program->release();
}