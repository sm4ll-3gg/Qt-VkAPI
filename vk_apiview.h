#ifndef VK_APIVIEW_H
#define VK_APIVIEW_H

#include "vkrequest.h"

#include <QMainWindow>

namespace Ui {
class Vk_APIView;
}

class Vk_APIView : public QMainWindow
{
    Q_OBJECT

public:
    explicit Vk_APIView(QWidget *parent = 0);
    ~Vk_APIView();

private:
    Ui::Vk_APIView *ui;

    VkRequest* api;
};

#endif // VK_APIVIEW_H
