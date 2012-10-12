#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include "scene/scene.h"

#include <QGLShaderProgram>
#include <QTimer>

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();

private:
    Scene *scene;

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

    QPoint mousexy;
    int mouseButton;

#ifdef SHADERS_ENABLED
    QGLShaderProgram shaderProgram;
#endif

signals:
    
};

#endif // GLWIDGET_H