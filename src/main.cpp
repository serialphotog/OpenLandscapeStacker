#include <QApplication>

#include "ui/main_window.h"

int main(int argc, char *argv[])
{
  // Setup the application
  QApplication app(argc, argv);
  app.setApplicationName("Open Landscape Stacker");
  app.setOrganizationName("serialphotog");
  app.setOrganizationDomain("serialphotog.com");

  MainWindow win;
  win.show();
  return app.exec();
}
