#include "vk_api.h"

#include <QWebEngineView>
#include <QUrl>
#include <QUrlQuery>
#include <QString>

Vk_API::Vk_API(QWidget *parent)
    : QWidget(parent),
      token("")
{
    auth();
}

Vk_API::~Vk_API()
{

}

void Vk_API::slotUrlChanged(const QUrl& url)
{    
    QUrl url_{ url.toString().replace('#', '?') };
    QUrlQuery query{ url_.query() };
    QString token_ = query.queryItemValue("code");

    if(token_ != "")
        token = token_;
}

QString Vk_API::getTokenFromUrl(const QUrl &url)
{
    QString urlStr = url.toString();
    QString token = "";
    for(auto it = urlStr.end() - 1; it != urlStr.begin(); --it)
        if(*it == '=')
            break;
        else
            token += *it;

    return token;
}

void Vk_API::auth()
{
    QWebEngineView* authPage = new QWebEngineView(this);
    connect(authPage, &QWebEngineView::destroyed,
            authPage, &QWebEngineView::deleteLater);
    connect(authPage, &QWebEngineView::urlChanged,
            this, &Vk_API::slotUrlChanged);

    QUrl url{"https://oauth.vk.com/authorize"};
    QUrlQuery query;
    query.addQueryItem("client_id", "6058402");
    query.addQueryItem("redirect_uri", "https://oauth.vk.com/blank.html");
    query.addQueryItem("v", "5.65");
    query.addQueryItem("scope", "4102");
    query.addQueryItem("revoke", "1");
    url.setQuery(query);

    authPage->load(url);

    authPage->show();
}

