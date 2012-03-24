#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "glwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;

    GLWidget *g1;//, *g2;

    void resizeEvent(QResizeEvent *);

private slots:
    void timedUpdate();
    void updateSlide();
};

#endif // MAINWINDOW_H