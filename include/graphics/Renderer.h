#ifndef RENDERER_H
#define RENDERER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QElapsedTimer>
#include <QTimer>
#include "graphics/Camera.h"

struct Point {
    float x;
    float y;
    float z;
};

class Renderer : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
public:
    explicit Renderer(QWidget *parent = nullptr);
    void drawSphere(Point center, float radius);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    std::vector<GLfloat> arr;
    std::vector<unsigned int> idx;
    Camera cam;
    GLuint m_matrixUniform;
    GLuint VAO, VBO, EBO;
    GLuint colorUniform;
    QElapsedTimer tm;
    int vertexCount = 0;
    QOpenGLShaderProgram *m_program;
};

#endif 