#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include "mainwindow.h"
#include "connecting.h"
#include <QVector>

namespace Ui {
class chatwindow;
}

class chatwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit chatwindow(QWidget *parent = nullptr);
    ~chatwindow();

private slots:
    void on_addButton_clicked();

    void on_removeButton_clicked();

    void on_connectButton_clicked();

    void on_disconnectButton_clicked();

    void on_sendButton_clicked();

    void on_kickButton_clicked();

signals:
    void connectToServer(QString, int, QString, QString, bool);
    void disconnectFromServer();
    void sendMessage(QString);
    void kickUser(QString);

public slots:
    void addServerToList(QString, int, QString, QString);
    void addMessage(QString);
    void addUserToList(QString);
    void removeUserFromList();
    void isConnectedStatus(QString);
    void clearMessages();

private:
    Ui::chatwindow *ui;
    MainWindow *connectWindow;
    QVector < QString > ipList;
    QVector < int > portList;
    QVector < QString > usernameList;
    QVector < QString > passwordList;
public:
    Connecting *connecting;
};

#endif // CHATWINDOW_H
