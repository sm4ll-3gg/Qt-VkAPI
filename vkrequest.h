#ifndef VK_API_H
#define VK_API_H

#include "vkauth.h"

#include <QObject>
#include <QString>
#include <QTimer>

class VkRequest : public QObject
{
    Q_OBJECT

public:
    explicit VkRequest(QObject* parent = nullptr);
    ~VkRequest() {}

    VkAuth* authorization() { return _auth; }

private slots:
    void    slotAuthRequest();

private:
    VkAuth* _auth;
};

#endif // VK_API_H
