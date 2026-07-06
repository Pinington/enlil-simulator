#ifndef RENDERER_H
#define RENDERER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>

#include <vector>

#include "graphics/Camera.h"
#include "graphics/MeshMaker.h"

#include "const.h"
#include "utils.h"

class Renderer : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
public:
    explicit Renderer(QWidget *parent = nullptr);
    void instantiateSphere(float x, float y, float z);
    void updatePositions(const std::vector<float>&);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    Camera cam;

    GLuint m_matrixUniform;
    GLuint VAO, VBO, offsetVBO, EBO;

    SphereMaker sm;
    int sphereCount { 0 };
    std::vector<float> positions;

    QOpenGLShaderProgram *m_program;
    virtual void keyPressEvent(QKeyEvent *event);
};

#endif 