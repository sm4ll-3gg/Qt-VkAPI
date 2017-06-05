#ifndef VK_API_H
#define VK_API_H

#include <QWidget>
#include <QString>

class Vk_API : public QWidget
{
    Q_OBJECT

public:
    Vk_API(QWidget *parent = 0);
    ~Vk_API();

private slots:
    void    slotUrlChanged(const QUrl& url);
    QString getTokenFromUrl(const QUrl& url);

private: // Methods
    void    auth();

private:
    QString token;
};

#endif // VK_API_H
