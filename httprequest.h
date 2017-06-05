#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QByteArray>
#include <QUrl>
#include <QHash>

class HttpRequest : public QObject
{
    Q_OBJECT

    using Headers       = QHash<QByteArray, QByteArray>;
    using Parametres    = QHash<QString, QString>;

public:    
    HttpRequest();
    ~HttpRequest();

    void    get                 (const QUrl& url,
                                 const Parametres& p = Parametres(),
                                 const Headers &h = Headers()                   );
    void    post                (const QUrl& url, const QByteArray& data,
                                 const Parametres& p = Parametres(),
                                 const Headers& h = Headers()                   );

signals:
    void    error               (const QString& message                         );
    void    done                (const QUrl& url, const QByteArray& data);

private slots:
    void    slotRequestFinished (QNetworkReply* reply                           );

private: // Methods
    QUrl    addParametres       (const QUrl &url,
                                 const Parametres& parametres                   );

private:
    QNetworkAccessManager*  nam;
};

#endif // HTTPREQUEST_H
