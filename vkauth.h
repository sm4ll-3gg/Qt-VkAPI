#ifndef VKAUTH_H
#define VKAUTH_H

#include <QObject>
#include <QString>
#include <QTimer>
#include <QUrl>
#include <QUrlQuery>

class VkAuth : public QObject
{
    Q_OBJECT

public:
    explicit VkAuth(QObject* parent = nullptr);
    ~VkAuth() {}

    const QString&  accessToken() { return access_token; }
    const QString&  userId() { return user_id; }

public slots:
    void            auth();

signals:
    void            accessTokenTimeout();

    void            successAuth();
    void            errorAuth(const QString& error, const QString& description);

private slots:
    void            slotUrlChanged(const QUrl& url);

private:
    void            processSuccessfulResult(const QUrlQuery &query);
    void            processErrorResult(const QUrlQuery& query);

private:
    QString         access_token;
    QString         user_id;

    QTimer*         timeout;
};

#endif // VKAUTH_H
