#include "mainwindow.h"
#include <QApplication>
#include "test.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    Test::testG8M("E:\\facedata\\frame_0004.png");
//    Test::testG8M("E:\\11.jpg");
    //Test::testObstacleMethod();
    return a.exec();
}
