#include "scenechquickhull.h"

SceneCHQuickHull::SceneCHQuickHull(const QString &name, const QString &owner, const double &spread, const QString &color):
  SceneObject(name,owner,spread,color,true)
{
  step_count_ = 0;
}

SceneCHQuickHull::~SceneCHQuickHull()
{
}

void SceneCHQuickHull::DrawObject(const float &spread, const float &shrink, const bool user_color, const unsigned int current_frame) const
{
  if(points_.size() <= 0) return;

  glPushAttrib(GL_ALL_ATTRIB_BITS);


  glDisable(GL_LIGHTING);
  //glPointSize(6-5*shrink);
  if(user_color){
    glColor3f(color_.redF(),color_.greenF(),color_.blueF());
  }
  glPointSize(6);
  glBegin(GL_POINTS);
  foreach(QVector3D point, points_){
    Vertex(point+(point*spread));
  }
  glEnd();

  glColor3f(1,0,0);
  glPointSize(10);
  glBegin(GL_POINTS);
  foreach(int index, v_max){
    Vertex( points_[index]+(points_[index]*spread) );
  }
  glEnd();

  glColor3f(0,0,1);
  glPointSize(14);
  glBegin(GL_POINTS);
  foreach(int index, v_3_sel){
    Vertex( points_[index]+(points_[index]*spread) );
  }
  glEnd();

  glEnable(GL_LIGHTING);


  foreach(QHPoly poly, todo_poly_list){
    glColor3f(1,1,1);
    Normal( poly.n_ );
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0; i<poly.face_v_.size(); i++){
      Vertex( points_[poly.face_v_[i]]+(poly.c_*spread) );
    }
    glEnd();
    Normal( -poly.n_ );
    glBegin(GL_TRIANGLE_FAN);
    for(int i=poly.face_v_.size()-1; i>=0; i--){
      Vertex( points_[poly.face_v_[i]]+(poly.c_*spread) );
    }
    glEnd();
    glColor3f(1,0,0);
    glBegin(GL_LINES);
    Vertex( poly.c_ );
    Vertex( poly.c_+poly.n_ );
    glEnd();
  }

  foreach(QHPoly poly, poly_){
    if(user_color){
      glColor3f(color_.redF(),color_.greenF(),color_.blueF());
    }
    Normal( poly.n_ );
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0; i<poly.face_v_.size(); i++){
      Vertex( points_[poly.face_v_[i]]+(poly.c_*spread) );
    }
    glEnd();
    Normal( -poly.n_ );
    glBegin(GL_TRIANGLE_FAN);
    for(int i=poly.face_v_.size()-1; i>=0; i--){
      Vertex( points_[poly.face_v_[i]]+(poly.c_*spread) );
    }
    glEnd();
    glColor3f(1,0,0);
    glBegin(GL_LINES);
    Vertex( poly.c_ );
    Vertex( poly.c_+poly.n_ );
    glEnd();
  }

  glPopAttrib();
}

void SceneCHQuickHull::Clear()
{
  points_.clear();
}

void SceneCHQuickHull::Colorize()
{
}

void SceneCHQuickHull::Delete()
{
  deleted_ = true;
  Clear();
}

void SceneCHQuickHull::RunAlgorithm()
{
  //  while(StepAlgorithm()){
  if(StepAlgorithm()){
    qDebug() << step_count_;
  }
  //  }
  //  if(points_.size()<1){
  //    return;
  //  }

  //  triangles_.resize(points_.size());
  //  //  triangles_.clear();

  //  int v_max[6] = {0,0,0,0,0,0};

  //  for(int i = 0; i<points_.size(); i++){
  //    // Min X
  //    if( points_[i].x() < points_[v_max[0]].x() ){
  //      v_max[0] = i;
  //    }

  //    // Max X
  //    if( points_[i].x() > points_[v_max[1]].x() ){
  //      v_max[1] = i;
  //    }

  //    // Min X
  //    if( points_[i].y() < points_[v_max[2]].y() ){
  //      v_max[2] = i;
  //    }

  //    // Max X
  //    if( points_[i].y() > points_[v_max[3]].y() ){
  //      v_max[3] = i;
  //    }

  //    // Min X
  //    if( points_[i].z() < points_[v_max[4]].z() ){
  //      v_max[4] = i;
  //    }

  //    // Max X
  //    if( points_[i].z() > points_[v_max[5]].z() ){
  //      v_max[5] = i;
  //    }
  //  }

  //  double max_dist;

  //  v_s.resize(3);

  //  // Of the 6 extreme points, two points with the biggest distance.
  //  max_dist = 0;
  //  int max_i = 0, max_j = 0;
  //  for(int i=0;i<6;i++){
  //    for(int j=i+1;j<6;j++){
  //      double new_dist = points_[v_max[i]].distanceToPoint(points_[v_max[j]]);
  //      if( new_dist > max_dist ){
  //        max_dist = new_dist;
  //        max_i = i;
  //        max_j = j;
  //      }
  //    }
  //  }

  //  v_s[0] = v_max[max_i];
  //  v_s[1] = v_max[max_j];

  //  // Get the 3rd point to generate the two first triangles.
  //  max_dist = 0;
  //  int max_k = 0;
  //  for(int k=0;k<6;k++){
  //    if(k!=max_i && k!=max_j){
  //      double new_dist = points_[v_max[k]].distanceToLine(points_[v_s[0]],points_[v_s[1]]-points_[v_s[0]]);
  //      if( new_dist > max_dist ){
  //        max_dist = new_dist;
  //        max_k = k;
  //      }
  //    }
  //  }
  //  v_s[2] = v_max[max_k];

  //  t_list.push_back(QHPoly(v_s[0],v_s[1],v_s[2],points_,NULL));
  //  t_list.push_back(QHPoly(v_s[0],v_s[2],v_s[1],points_,NULL));
  //  //  triangles_[0].push_back(QHTriangle(v_s[0],v_s[2],v_s[1],points_));


  //  // Now, for each triangle on the list, verify if it contains any point on it's "todo" list.
  //  while(!t_list.empty()){
  //    qDebug() << t_list.first().v_index.size();
  //    if(t_list.first().v_index.size() <= 0){
  //      triangles_[0].push_back(QHPoly(t_list.first().v_[0],t_list.first().v_[1],t_list.first().v_[2],points_,&t_list.first()));
  //    }else{
  //      // If does, build the next 3 iteration triangles and remove self.
  //      double max_dist = 0;
  //      int max_i = 0;
  //      for(int i=0;i<t_list.first().v_index.size();i++){
  //        double new_dist = (points_[t_list.first().v_index[i]].distanceToPlane(points_[t_list.first().v_[0]],points_[t_list.first().v_[1]],points_[t_list.first().v_[2]]));
  //        if(new_dist > max_dist){
  //          max_dist = new_dist;
  //          max_i = i;
  //        }
  //      }
  //      //      triangles_[0].push_back(QHTriangle(t_list.first().v0_,t_list.first().v1_,t_list.first().v_index[max_i],points_));
  //      //      triangles_[0].push_back(QHTriangle(t_list.first().v1_,t_list.first().v2_,t_list.first().v_index[max_i],points_));
  //      //      triangles_[0].push_back(QHTriangle(t_list.first().v2_,t_list.first().v0_,t_list.first().v_index[max_i],points_));
  //      //            t_list.push_back(QHTriangle(t_list.first().v1_,t_list.first().v0_,t_list.first().v_index[max_i],points_));
  //      //            t_list.push_back(QHTriangle(t_list.first().v1_,t_list.first().v2_,t_list.first().v_index[max_i],points_));
  //      //            t_list.push_back(QHTriangle(t_list.first().v2_,t_list.first().v0_,t_list.first().v_index[max_i],points_));
  //      for(int i=0;i<t_list.first().v_.size();i++){
  //        t_list.push_back(QHPoly(t_list.first().v_[i],t_list.first().v_[(i+1)%t_list.first().v_.size()],t_list.first().v_index[max_i],points_,&t_list.first()));
  //      }
  //      //      t_list.push_back(QHTriangle(t_list.first().v0_,t_list.first().v1_,t_list.first().v2_,points_));
  //    }
  //    t_list.pop_front();
  //  }
}

bool SceneCHQuickHull::StepAlgorithm()
{
  // case 1
  double max_dist;
  int max_i, max_j, max_k;
  // case 2
  QHPoly *pcw, *pccw;

  switch(step_count_){
  case 0:
    // build the 6 min and max points
    if(points_.size()<1){
      return false;
    }

    v_max.fill(0,6);

    for(int i = 0; i<points_.size(); i++){
      // Min X
      if( points_[i].x() < points_[v_max[0]].x() ){
        v_max[0] = i;
      }

      // Max X
      if( points_[i].x() > points_[v_max[1]].x() ){
        v_max[1] = i;
      }

      // Min X
      if( points_[i].y() < points_[v_max[2]].y() ){
        v_max[2] = i;
      }

      // Max X
      if( points_[i].y() > points_[v_max[3]].y() ){
        v_max[3] = i;
      }

      // Min X
      if( points_[i].z() < points_[v_max[4]].z() ){
        v_max[4] = i;
      }

      // Max X
      if( points_[i].z() > points_[v_max[5]].z() ){
        v_max[5] = i;
      }
    }
    step_count_=1;
    return true;
  case 1:
    // find the 3 starting points of the set to begin the hull creation
    v_3_sel.resize(3);

    // Of the 6 extreme points, two points with the biggest distance.
    max_dist = 0;
    max_i = 0;
    max_j = 0;
    for(int i=0;i<6;i++){
      for(int j=i+1;j<6;j++){
        double new_dist = DistanceSquaredBetweenPoints(points_[v_max[i]],points_[v_max[j]]);
        if( new_dist > max_dist ){
          max_dist = new_dist;
          max_i = i;
          max_j = j;
        }
      }
    }

    v_3_sel[0] = v_max[max_i];
    v_3_sel[1] = v_max[max_j];

    // Get the 3rd point to generate the two first triangles.
    max_dist = 0;
    max_k = 0;
    for(int k=0;k<6;k++){
      if(k!=max_i && k!=max_j){
        double new_dist = points_[v_max[k]].distanceToLine(points_[v_3_sel[0]],points_[v_3_sel[1]]-points_[v_3_sel[0]]);
        if( new_dist > max_dist ){
          max_dist = new_dist;
          max_k = k;
        }
      }
    }
    v_3_sel[2] = v_max[max_k];
    step_count_=2;
    return true;
  case 2:
    // find out 3 sets: the points on both sides, and coplanar points.
    // points on each side will be added to the respective polygon list, and the coplanar will be considered for the 2D convex hull algorithm to find the starting face.

    todo_poly_list.push_back(QHPoly(v_3_sel[0],v_3_sel[1],v_3_sel[2],&points_,NULL));
    pcw = &todo_poly_list.last();
    pcw->debug_color = QColor(255,0,0);
    todo_poly_list.push_back(QHPoly(v_3_sel[0],v_3_sel[2],v_3_sel[1],&points_,NULL));
    pccw = &todo_poly_list.last();
    pccw->debug_color = QColor(0,0,255);

    for(int i=0;i<points_.size();i++){
      float f = points_[i].distanceToPlane(points_[v_3_sel[0]],points_[v_3_sel[1]],points_[v_3_sel[2]]);
      if(f>=0){
        pcw->subset_v_.push_back(i);
      }
      if(f<=0){
        pccw->subset_v_.push_back(i);
      }
      //      if(f==0){
      //        pcw->face_v_.push_back(i);
      //        pccw->face_v_.push_back(i);
      //      }
    }

    //    pcw->CalcHull2D();

    v_3_sel.clear();
    v_max.clear();

    step_count_=3;
    return true;
  case 3:
    if(todo_poly_list.size()>0){

      if(todo_poly_list.first().subset_v_.size() <= 0){
        poly_.push_back(QHPoly(todo_poly_list.first(),false));
      }else{
        // If does, build the next 3 iteration triangles and remove self.
        double max_dist = 0;
        int max_i = 0;
        for(int i=0;i<todo_poly_list.first().subset_v_.size();i++){
          double new_dist = (points_[todo_poly_list.first().subset_v_[i]].distanceToPlane(points_[todo_poly_list.first().face_v_[0]],points_[todo_poly_list.first().face_v_[1]],points_[todo_poly_list.first().face_v_[2]]));
          if(new_dist > max_dist){
            max_dist = new_dist;
            max_i = i;
          }
        }
        for(int i=0;i<todo_poly_list.first().face_v_.size();i++){
          qDebug() << "adding face" << todo_poly_list.first().face_v_.size();
          todo_poly_list.push_back(QHPoly(
                                     todo_poly_list.first().face_v_[i],
                                     todo_poly_list.first().face_v_[(i+1)%todo_poly_list.first().face_v_.size()],
                                     todo_poly_list.first().subset_v_[max_i],
                                     &points_,
                                     &todo_poly_list.first()));
        }
        //      t_list.push_back(QHTriangle(t_list.first().v0_,t_list.first().v1_,t_list.first().v2_,points_));
      }
      todo_poly_list.pop_front();

      step_count_=3;
    }else{
      step_count_=100;
    }

    return true;
  default:
    return false;
  }
}

float SceneCHQuickHull::DistanceSquaredBetweenPoints(const QVector3D &p1, const QVector3D &p2) const
{
  return (p2-p1).lengthSquared();
}

















