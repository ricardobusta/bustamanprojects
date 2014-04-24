#include "sceneobject.h"

//#include <QtOpenGL>
#ifdef _WIN32
#include <Windows.h>
#endif

#include <GL/gl.h>
#include <limits>

#include "scene/triangleface.h"
#include "scene/openglauxfunctions.h"
#include "scene/objloader.h"

const float kMaxFloat = std::numeric_limits<float>::max();
const float kMinFloat = -kMaxFloat;

SceneObject::SceneObject()
  : bounding_worthy_(false)
{
}

SceneObject::SceneObject(const SceneObject *object, const Ric::Matrix4x4 *transform)
  : bounding_worthy_(false)
{
  foreach(TriangleFace f,object->faces_){
    this->faces_.push_back(TriangleFace(f,transform));
  }
  for(int i=0;i<object->child_objects_.size();i++){
    child_objects_.push_back(SceneObject(&object->child_objects_[i],transform));
  }
}

SceneObject::~SceneObject()
{

}

void SceneObject::move(Ric::Vector m)
{
  for(int i=0;i<faces_.size();i++) {
    faces_[i].move(m);
  }
  for(int i=0;i<child_objects_.size();i++){
    child_objects_[i].move(m);
  }
  GenerateBoundingVolumeRec();
}

void SceneObject::scale(double s)
{
  for(int i=0;i<faces_.size();i++) {
    faces_[i].scale(s);
  }
  for(int i=0;i<child_objects_.size();i++){
    child_objects_[i].scale(s);
  }
  GenerateBoundingVolumeRec();
}

void SceneObject::GlDraw(bool lighting,bool draw_bounding_box)
{
  glPushAttrib(GL_ALL_ATTRIB_BITS);

  if(draw_bounding_box){
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glDisable(GL_LIGHTING);
    foreach(TriangleFace f,bounding_volume_){
      f.material().GlSet();
      glBegin(GL_TRIANGLES);
      Gl::Normal3f( f.n() );
      //      qDebug() << f.vt0();
      //      qDebug() << f.vn0();
      Gl::TexCoord( f.vt0() );
      //      Gl::Normal3f( f.vn0() );
      Gl::Vertex3f( f.v0() );
      Gl::TexCoord( f.vt1() );
      //      Gl::Normal3f( f.vn1() );
      Gl::Vertex3f( f.v1() );
      Gl::TexCoord( f.vt2() );
      //      Gl::Normal3f( f.vn2() );
      Gl::Vertex3f( f.v2() );
      glEnd();
    }
  }

  if(child_objects_.isEmpty()){
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    if(lighting){
      glEnable(GL_LIGHTING);
    }
    foreach(TriangleFace f,faces_){
      f.material().GlSet();
      glBegin(GL_TRIANGLES);
      Gl::Normal3f( f.n() );
      //      qDebug() << f.vt0();
      //      qDebug() << f.vn0();
      Gl::TexCoord( f.vt0() );
      //      Gl::Normal3f( f.vn0() );
      Gl::Vertex3f( f.v0() );
      Gl::TexCoord( f.vt1() );
      //      Gl::Normal3f( f.vn1() );
      Gl::Vertex3f( f.v1() );
      Gl::TexCoord( f.vt2() );
      //      Gl::Normal3f( f.vn2() );
      Gl::Vertex3f( f.v2() );
      glEnd();
    }
  }else{
    for(int i=0;i<child_objects_.size();i++){
      child_objects_[i].GlDraw(lighting,draw_bounding_box);
    }
  }
  glPopAttrib();
}

void SceneObject::GenerateBoundingVolumeRec()
{
  QVector3D max_v = QVector3D(kMinFloat,kMinFloat,kMinFloat);
  QVector3D min_v = QVector3D(kMaxFloat,kMaxFloat,kMaxFloat);

  if(child_objects_.isEmpty()){
    foreach(TriangleFace f, faces_){
      ObjLoader::UpdateMaxAndMin(max_v,min_v,f.v0());
      ObjLoader::UpdateMaxAndMin(max_v,min_v,f.v1());
      ObjLoader::UpdateMaxAndMin(max_v,min_v,f.v2());
    }

    bounding_volume_.clear();
    bounding_volume_ += ObjLoader::CreateBoundingBox(min_v,max_v);
    qDebug() << bounding_volume_.size();
  }else{
    for(int i=0;i<child_objects_.size();i++){
      child_objects_[i].GenerateBoundingVolumeRec();
      foreach(TriangleFace f, child_objects_[i].bounding_volume_){
        ObjLoader::UpdateMaxAndMin(max_v,min_v,f.v0());
        ObjLoader::UpdateMaxAndMin(max_v,min_v,f.v1());
        ObjLoader::UpdateMaxAndMin(max_v,min_v,f.v2());
      }
    }
    bounding_volume_.clear();
    bounding_volume_ += ObjLoader::CreateBoundingBox(min_v,max_v);
    qDebug() << bounding_volume_.size();
  }

  bounding_worthy_ = !(child_objects_.isEmpty() && bounding_volume_.size()>faces_.size());
}