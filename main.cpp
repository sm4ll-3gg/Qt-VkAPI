#include "vk_api.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Vk_API w;
    w.show();

    return a.exec();
}
