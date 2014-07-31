#ifndef OBJECT_H
#define OBJECT_H

#include <QString>
#include <QVector>
#include <QVector2D>
#include <QVector3D>

#include "material.h"

class Object
{
public:
  Object();

  static QVector<Object> load(QString file_name);

  void draw();

  Object operator=(Object o);

private:
  struct Face{
    int v[3];
    int n[3];
    int t[3];

    Face operator=(Face f){
      for(int i=0;i<3;i++){
        v[i] = f.v[i];
        n[i] = f.n[i];
        t[i] = f.t[i];
      }
      return *this;
    }
  };

  bool valid_;
  Material material_;

  QVector<QVector3D> vertex_;
  QVector<QVector3D> normal_;
  QVector<QVector2D> texture_;
  QVector<struct Face> face_;
};

#endif // OBJECT_H