#include <Task.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Task t;
    t.show();
    return a.exec();
}
