#include "scene_bonfire.h"

#include <QLabel>
#include <QVBoxLayout>

SceneBonfire::SceneBonfire(QObject *parent):
  Scene(parent)
{
}

SceneBonfire::~SceneBonfire()
{
}

void SceneBonfire::setup_spec()
{
  QStringList objects = Model::load(":/model/campfire.obj");
  for(int i=0;i<objects.size();i++){
    Object *obj = Object::create(objects[i],objects[i]);
    objects_.push_back(obj);
  }
}

void SceneBonfire::buildControlWidget()
{
  if(control_widget_ == NULL) return;

  control_widget_->setLayout(new QVBoxLayout);
  control_widget_->layout()->addWidget(new QLabel("Bonfire"));
}
