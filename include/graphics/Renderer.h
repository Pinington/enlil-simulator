#ifndef RENDERER_H
#define RENDERER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include "graphics/Camera.h"


void drawCircle(float center, float radius, std::vector<GLfloat>& pos, std::vector<GLfloat>& col, std::vector<GLfloat>& normals);

class Renderer : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    explicit Renderer(QWidget *parent = nullptr) : QOpenGLWidget(parent), cam(float(800)/float(600)) {};

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    Camera cam;
    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_normAttr;
    GLuint m_matrixUniform;
    QOpenGLShaderProgram *m_program;
};

#endif 