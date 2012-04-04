#include "glwidget.h"

#include <material.h>

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    n = 0;
    slide = 0;

    toggled = false;
}

GLWidget::~GLWidget()
{
}

void GLWidget::initializeGL(){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    //glShadeModel(GL_FLAT);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    //glEnable(GL_POLYGON_OFFSET_FILL);
    //glPolygonOffset(1.0,1.0);

    glEnable(GL_LIGHTING);
    //glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    //glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);

    float lspecular[] = {0.3,0.3,0.3,1.0};
    float lambient[] = {0.5,0.5,0.5,1.0};
    float ldiffuse[] = {0.5,0.5,0.5,1.0};
    float lposition[] = {0,0,1,1.0};

    glLightfv(GL_LIGHT0, GL_SPECULAR, lspecular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, ldiffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, lposition);

    Material mat;

    mat.gl();

    /*
    float mspecular[] = {0.5,1,0.5,1.0};
    float memission[] = {0,0,0,1.0};
    float mdiffuse[] = {1,0.5,0.5,1.0};
    float mshininess[] = {1};
    */

    /*
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mspecular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mshininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mdiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, memission);
    */

    //glDisable(GL_LIGHTING);
    glEnable(GL_LIGHTING);

    //object->makeObject();
}

void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    float spacing = 0.1;

    /*if(n==1){
        glTranslated(-spacing, 0.0, 0);
    }else if(n==2){
        glTranslated(spacing, 0.0, 0);
    }*/
    int xRot = 0,yRot = 0,zRot = 0;
    glRotated(xRot, 1.0, 0.0, 0.0);
    glRotated(yRot, 0.0, 1.0, 0.0);
    glRotated(zRot, 0.0, 0.0, 1.0);
    //glCallList(object->object);

    glViewport((w - side) / 2, (h - side) / 2, side/2, side);
    drawScene(-spacing);
    glViewport((w) / 2, (h - side) / 2, side/2, side);
    drawScene(spacing);
    n+=1;
}

void GLWidget::resizeGL(int w, int h){
    side = qMax(w, h);
    this->w = w;
    this->h = h;
    //glViewport((w - side) / 2, (h - side) / 2, side, side);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //int zoom = 1;
    //glOrtho(-250/zoom,250/zoom,-250/zoom,250/zoom,1000/zoom,-1000/zoom);
    glFrustum(-1,1,-1,1,1,1000);
    glMatrixMode(GL_MODELVIEW);
}

#include <cmath>

#include <iostream>
using namespace std;

#define SPC << " " <<

void GLWidget::drawFigure(){
    for(int o=0;o<scenario.objectlist.size();o++){
        scenario.objectlist[o].material.gl();
        glPushMatrix();
        glTranslatef(scenario.objectlist.at(o).posx,scenario.objectlist.at(o).posy,scenario.objectlist.at(o).posz);
        glRotatef(scenario.objectlist.at(o).rotx,1,0,0);
        glRotatef(scenario.objectlist.at(o).roty,0,1,0);
        glRotatef(scenario.objectlist.at(o).rotz,0,0,1);
        for(int f=0;f<scenario.objectlist.at(o).facelist.size();f++){
            //Face *fa = (Face*)&obj.facelist.at(f);

            Vert normal = scenario.objectlist.at(o).facelist.at(f).normal;
            glNormal3f(normal.x, normal.y, normal.z);

            glBegin(GL_POLYGON);
            //glBegin(GL_POINTS);
            //glBegin(GL_LINE_STRIP);
            for(int v=0;v<scenario.objectlist.at(o).facelist.at(f).vert.size();v++){
                int vnum = scenario.objectlist.at(o).facelist.at(f).vert.at(v);
                Vert ve;
                ve = scenario.objectlist.at(o).vertlist.at( vnum-1 );
                //glNormal3f(obj.facelist.at(f).normal.x,obj.facelist.at(f).normal.y,obj.facelist.at(f).normal.z);
                //cout << obj.facelist.at(f).normal.x SPC obj.facelist.at(f).normal.y SPC obj.facelist.at(f).normal.z << endl;
                float c = (float)f/(float)(scenario.objectlist.at(o).facelist.size()-1);
                glColor3f(c,c,c);
                glVertex3f(ve.x,ve.y,ve.z);
            }
            glEnd();

            //Print normals;
            /*
            for(int v=0;v<scenario.objectlist.at(o).facelist.at(f).vert.size();v++){
                int vnum = scenario.objectlist.at(o).facelist.at(f).vert.at(v);
                Vert ve, norm;
                ve = scenario.objectlist.at(o).vertlist.at( vnum-1 );
                norm = scenario.objectlist.at(o).facelist.at(f).normal;
                norm = norm + ve;
                glBegin(GL_LINES);
                    glColor3f(1,0,0);
                    glVertex3f(ve.x,ve.y,ve.z);
                    glVertex3f(norm.x,norm.y,norm.z);
                glEnd();
            }//*/
            //end print normals;
        }
        glPopMatrix();
        scenario.objectlist[o].update();
    }
}

void GLWidget::toggle()
{
    if(toggled){
        glDisable(GL_LIGHTING);
    }else{
        glDisable(GL_LIGHTING);
    }
    toggled = !toggled;

}

void GLWidget::drawScene(float offset){
    glPushMatrix();

    glTranslatef(offset,0,0);

    drawFigure();

    glPopMatrix();
}

void GLWidget::drawStereo()
{
    /*GLubyte colors[3];
    glReadPixels(0,0,1,1,GL_RGB,GL_UNSIGNED_BYTE,(void*)colors);
    cout << (int)colors[0] << (int)colors[1] << (int)colors[2] << endl;
    //glDrawPixels(1,1,GL_RGB,GL_FLOAT,&colors);*/
}
