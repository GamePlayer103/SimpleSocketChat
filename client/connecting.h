#ifndef CONNECTING_H
#define CONNECTING_H

#include <QObject>
#include <QTcpSocket>
#include <QtCore>
#include <QAbstractSocket>
#include <QMessageBox>

class Connecting : public QObject
{
    Q_OBJECT
public:
    Connecting();
    int waitingForConnectTime;

signals:
    void addServerToList(QString, int, QString, QString);
    void addMessage(QString);
    void addUserToList(QString);
    void removeUserFromList();
    void isConnectedStatus(QString);
    void clearMessages();

public slots:
    void connected();
    void disconnected();
    void readyRead();
    void connecting(QString, int, QString, QString, bool);
    void disconnecting();
    void sendMessage(QString);
    void kickUser(QString);

private:
    QTcpSocket *socket;
    QMessageBox connectingError;
    QMessageBox nicknameError;
    QMessageBox passwordError;
    QMessageBox kickError;
    QString userName;
    QString userPassword;
    QString getMessage;
    bool isConncted;
    QString ip;
};

#endif // CONNECTING_H
