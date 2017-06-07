#include "vk_apiview.h"
#include <QApplication>

// TODO: Catch auth errors

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Vk_APIView view;
    view.show();

    return a.exec();
}
