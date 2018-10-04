/*
  This is free and unencumbered software released into the public domain.
  Author: pavel.hromada@gmail.com
*/

#ifndef BUILDINFOPROVIDER_H
#define BUILDINFOPROVIDER_H

#include <memory>
#include <QObject>
#include <QUrl>

enum class BuildStatus {
    Success,
    Running,
    Failed
};

class QNetworkAccessManager;
class QNetworkReply;
class QJsonObject;

class BuildInfoProvider : public QObject
{
    Q_OBJECT
public:
    explicit BuildInfoProvider( const QUrl& teamCityBaseUrl,
                                std::shared_ptr<QNetworkAccessManager>& nam,
                                const QJsonObject& config );

    BuildStatus status() const;
    QString name() const;
    QString lastCommitee() const;
    QString formatedLastCommitee() const;
signals:
    void statusChanged();
    void lastCommiteeChanged();

private:
    void requestStatus();
    void requestLastCommitee();
    void processStatusResponse();
    void processLastCommiteeResponse();

    BuildStatus                             status_ = BuildStatus::Running;
    QString                                 lastCommitee_ {""};
    QString                                 name_;
    std::shared_ptr<QNetworkAccessManager>  nam_;
    QUrl                                    buildStatusUrl_;
    QUrl                                    lastCommiteeUrl_;
    QNetworkReply*                          responseStatus_ = nullptr;
    QNetworkReply*                          responseLastCommitee_ = nullptr;
};

using BuildInfoProviderContainer = std::vector<std::unique_ptr<BuildInfoProvider>>;

#endif // BUILDINFOPROVIDER_H
