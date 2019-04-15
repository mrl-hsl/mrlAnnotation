#include <QApplication>
#include "src/tool.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  tool w;
  w.show();

  return a.exec();
}
