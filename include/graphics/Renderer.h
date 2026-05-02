#ifndef RENDERER_H
#define RENDERER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include "graphics/Camera.h"
#include "graphics/MeshMaker.h"

#define MAX_SPHERES 64

class Renderer : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
public:
    explicit Renderer(QWidget *parent = nullptr);
    void instantiateSphere(float x, float y, float z);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    Camera cam;

    GLuint m_matrixUniform;
    GLuint VAO, VBO, offsetVBO, EBO;

    SphereMaker sm;
    int sphereCount = 0;

    QOpenGLShaderProgram *m_program;
    virtual void keyPressEvent(QKeyEvent *event);
};

#endif 