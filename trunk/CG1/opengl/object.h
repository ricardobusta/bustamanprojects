#ifndef OBJECT_H
#define OBJECT_H

#include <QString>
#include <QVector>
#include <QVector2D>
#include <QVector3D>

#include "model.h"

class Animation;

class Object
{
public:
  Object();
  ~Object();

  static Object *create(QString object_name,QString model_name);

  void setModel(QString model_name);

  void draw() const;
  void drawArtifacts() const;

  void step();

  void setEulerRotation(float x, float y, float z);
  void setPosition(QVector3D pos);

  void setOverrideTexture(QString s);

  Object operator=(Object o);

  QString name() const;

  void addAnimation(Animation *animation);
private:
  void transform() const;

  QString name_;

  bool valid_;
  QString material_;

  QString override_texture_;

  QVector3D position_;
  QVector3D euler_rotation_;

  Model *model_;

  QList<Animation*> animation_;
};

#endif // OBJECT_H
