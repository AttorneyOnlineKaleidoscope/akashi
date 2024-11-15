#pragma once

#include <QCoreApplication>
#include <QtNetwork>

class ConfigManager;

/**
 * @brief A class for handling all Discord webhook requests.
 */
class Discord : public QObject
{
  Q_OBJECT

public:
  /**
   * @brief Constructor for the Discord object
   *
   * @param f_webhook_url The URL to send webhook POST requests to.
   * @param f_webhook_content The content to include in the webhook POST request.
   * @param f_webhook_sendfile Whether or not to send a file containing area logs with the webhook POST request.
   * @param parent Qt-based parent, passed along to inherited constructor from QObject.
   */
  Discord(QObject *parent = nullptr);

  /**
   * @brief Deconstructor for the Discord class.
   *
   * @details Marks the network access manager to be deleted later.
   */
  ~Discord();

  /**
   * @brief Method to start the Uptime Webhook posting timer.
   */
  void startUptimeTimer();

  /**
   * @brief Method to stop the Uptime Webhook posting timer.
   */
  void stopUptimeTimer();

public Q_SLOTS:
  /**
   * @brief Handles a modcall webhook request.
   *
   * @param f_name The name of the modcall sender.
   * @param f_area The name of the area the modcall was sent from.
   * @param f_reason The reason for the modcall.
   * @param f_buffer The area's log buffer.
   */
  void onModcallWebhookRequested(const QString &f_name, const QString &f_area, const QString &f_reason, const QQueue<QString> &f_buffer);

  /**
   * @brief Handles a ban webhook request.
   *
   * @param f_ipid The IPID of the client.
   * @param f_moderator The name of the moderator banning.
   * @param f_duration The date the ban expires.
   * @param f_reason The reason of the ban.
   */
  void onBanWebhookRequested(const QString &f_ipid, const QString &f_moderator, const QString &f_duration, const QString &f_reason, const int &f_banID);

private:
  /**
   * @brief The QNetworkAccessManager for webhooks.
   */
  QNetworkAccessManager *m_nam;

  /**
   * @brief The QNetworkRequest for webhooks.
   */
  QNetworkRequest m_request;

  /**
   * @brief Constructs a new JSON document for modcalls.
   *
   * @param f_name The name of the modcall sender.
   * @param f_area The name of the area the modcall was sent from.
   * @param f_reason The reason for the modcall.
   *
   * @return A JSON document for the modcall.
   */
  QJsonDocument constructModcallJson(const QString &f_name, const QString &f_area, const QString &f_reason) const;

  /**
   * @brief Constructs a new QHttpMultiPart document for log files.
   *
   * @param f_buffer The area's log buffer.
   *
   * @return A QHttpMultiPart containing the log file.
   */
  QHttpMultiPart *constructLogMultipart(const QQueue<QString> &f_buffer) const;

private Q_SLOTS:
  /**
   * @brief Handles a network reply from a webhook POST request.
   *
   * @param f_reply Pointer to the QNetworkReply created by the webhook POST request.
   */
  void onReplyFinished(QNetworkReply *f_reply);

  /**
   * @brief Sends a webhook POST request with the given JSON document.
   *
   * @param f_json The JSON document to send.
   */
  void postJsonWebhook(const QJsonDocument &f_json);

  /**
   * @brief Sends a webhook POST request with the given QHttpMultiPart.
   *
   * @param f_multipart The QHttpMultiPart to send.
   */
  void postMultipartWebhook(QHttpMultiPart &f_multipart);

  /**
   * @brief Constructs a new JSON document for bans.
   *
   * @param f_ipid The IPID of the client.
   * @param f_moderator The name of the moderator banning.
   * @param f_duration The date the ban expires.
   * @param f_reason The reason of the ban.
   *
   * @return A JSON document for the ban.
   */
  QJsonDocument constructBanJson(const QString &f_ipid, const QString &f_moderator, const QString &f_duration, const QString &f_reason, const int &f_banID);
};
