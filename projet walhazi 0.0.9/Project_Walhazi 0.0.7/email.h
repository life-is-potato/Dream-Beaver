#ifndef EMAIL_H
#define EMAIL_H
#include <QString>
#include<openssl/ssl.h>
#include<openssl/tls1.h>
#include<openssl/thread.h>
class mailer {
public:
  mailer();
  mailer(QString, QString, QString);

  static int sendEmail(QString, QString, QString);

private:
  QString destinataire;
  QString object, body;
};

#endif // EMAIL_H
