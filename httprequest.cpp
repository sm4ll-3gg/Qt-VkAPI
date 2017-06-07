#include "httprequest.h"

#include <QUrlQuery>

HttpRequest::HttpRequest()
{
    nam = new QNetworkAccessManager;
    connect(nam, &QNetworkAccessManager::finished,
            this, &HttpRequest::slotRequestFinished);
}

HttpRequest::~HttpRequest()
{
    delete nam;
}

void HttpRequest::slotRequestFinished(QNetworkReply *reply)
{
    qDebug() << "Request finished";
    if(reply->error() != QNetworkReply::NoError)
        emit error(reply->errorString());
    else
        emit done(reply->url(), reply->readAll());

    reply->deleteLater();
}

QUrl HttpRequest::addParametres(const QUrl& url, const Parametres &param)
{
    QUrl res{url};
    QUrlQuery query;
    for(auto it = param.begin(); it != param.end(); ++it)
        query.addQueryItem( it.key(), it.value() );

    res.setQuery(query);

    return res;
}

void HttpRequest::get(const QUrl &url, const Parametres& parametres,
                      const Headers& headers)
{
    QUrl resUrl(url);
    if(!parametres.isEmpty())
        resUrl = addParametres(url, parametres);

    QNetworkRequest request(resUrl);
    if(!headers.isEmpty())
    {
        for(auto it = headers.begin(); it != headers.end(); ++it)
            request.setRawHeader(it.key(), it.value());
    }

    nam->get(request);
}

void HttpRequest::post(const QUrl &url, const QByteArray &data,
                       const HttpRequest::Parametres &p, const HttpRequest::Headers &h)
{
    QUrl resUrl;
    if(!p.isEmpty())
        resUrl = addParametres(url, p);

    QNetworkRequest request(resUrl);
    if(!h.isEmpty())
    {
        for(auto it = h.begin(); it != h.end(); ++it)
            request.setRawHeader(it.key(), it.value());
    }

    nam->post(request, data);
}
