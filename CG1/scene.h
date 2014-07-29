#ifndef SCENE_H
#define SCENE_H

class Scene
{
public:
  Scene();

  // Camera Manipulation
  void setZoom(int zoom);
  void addZoom(int zoom);

  void rotate(int rot_x, int rot_y);

  // Init OpenGL
  void initialize();
  void resize(int w,int h);

  // Paint OpenGL
  void pre_draw();
  void draw();
  void post_draw();
private:
  int zoom_;

  int rot_x_;
  int rot_y_;
  int rot_z_;
};

#endif // SCENE_H
