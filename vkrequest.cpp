#include "vkrequest.h"

#include <QMessageBox>
#include <QDebug>

VkRequest::VkRequest(QObject *parent)
    :QObject(parent)
{
    _auth = new VkAuth(this);
    connect(_auth,  &VkAuth::accessTokenTimeout,
            this,   &VkRequest::slotAuthRequest);
}

void VkRequest::slotAuthRequest()
{
    int reply = QMessageBox::question(nullptr,
                                      "Время доступа к данному диалогу истекло",
                                      "Время доступа к данному диалогу истекло. \n"
                                      "Запросить доступ повторно?",
                                      QMessageBox::Yes, QMessageBox::No);

    if(reply == QMessageBox::Yes)
        _auth->auth();
}


