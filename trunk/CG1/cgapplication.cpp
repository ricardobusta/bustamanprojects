#include "cgapplication.h"

CGApplication::CGApplication(int argc, char *argv[]):
  QApplication(argc,argv)
{
  main_window_.init();
  main_window_.show();
}

CGApplication::~CGApplication()
{
}

MainWindow *CGApplication::getMainWindow()
{
  return &main_window_;
}