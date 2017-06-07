#include "vk_apiview.h"
#include "ui_vk_apiview.h"

Vk_APIView::Vk_APIView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Vk_APIView)
{
    ui->setupUi(this);

    api = new VkRequest(this);
    connect(ui->logIn,              &QAction::triggered,
            api->authorization(),   &VkAuth::auth);
}

Vk_APIView::~Vk_APIView()
{
    delete ui;
}
