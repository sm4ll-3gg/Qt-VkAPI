#include "vkauth.h"

#include <QWebEngineView>
#include <QUrlQuery>

VkAuth::VkAuth(QObject *parent)
    :QObject(parent),
     access_token(""),
     user_id("")
{
    timeout = new QTimer(this);
    connect(timeout, &QTimer::timeout,
            this,    &VkAuth::accessTokenTimeout);
}

void VkAuth::slotUrlChanged(const QUrl& url)
{
    QUrl url_{ url.toString().replace('#', '?') };
    QUrlQuery query{ url_.query() };

    if(query.hasQueryItem("access_token"))
        processSuccessfulResult(query);
    else if(query.hasQueryItem("error"))
        processErrorResult(query);
}

void VkAuth::processSuccessfulResult(const QUrlQuery &query)
{
    timeout->stop();

    access_token = query.queryItemValue("access_token");
    user_id = query.queryItemValue("user_id");

    emit successAuth();

    int expires_in = query.queryItemValue("expires_in").toInt();
    if(expires_in == 0)
        return;

    expires_in *= 1000; // to seconds
    timeout->setInterval(expires_in);
    timeout->start();
}

void VkAuth::processErrorResult(const QUrlQuery &query)
{
    timeout->stop();

    emit errorAuth(query.queryItemValue("error"),
                   query.queryItemValue("error_description"));
}

void VkAuth::auth()
{
    QWebEngineView* authPage = new QWebEngineView;
    connect(authPage,   &QWebEngineView::destroyed,
            authPage,   &QWebEngineView::deleteLater);
    connect(authPage,   &QWebEngineView::urlChanged,
            this,       &VkAuth::slotUrlChanged);

    QUrl url{"https://oauth.vk.com/authorize"};
    QUrlQuery query;
    query.addQueryItem("client_id", "6058402");
    query.addQueryItem("redirect_uri", "https://oauth.vk.com/blank.html");
    query.addQueryItem("response_type", "token");
    query.addQueryItem("v", "5.65");
    query.addQueryItem("scope", "6274306");
    //query.addQueryItem("revoke", "1");
    url.setQuery(query);

    authPage->load(url);

    authPage->show();
}
