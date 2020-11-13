// importing files
#include "connecting.h"
#include "chatwindow.h"

Connecting::Connecting()
{
    // setting time which socket is waiting for connect
    waitingForConnectTime = 5000;

    // creating new socket
    socket = new QTcpSocket();

    // connecting socket signals to slots
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    // setting connecting error dialog
    connectingError.setText("Can not connect to the server! Please chceck IP, PORT and your internet.");
    connectingError.setIcon(QMessageBox::Warning);
    connectingError.setStandardButtons(QMessageBox::Ok);

    // setting nickname error dialog
    nicknameError.setText("Wrong nickname!");
    nicknameError.setIcon(QMessageBox::Warning);
    nicknameError.setStandardButtons(QMessageBox::Ok);

    // setting password error
    passwordError.setText("Wrong password!");
    passwordError.setIcon(QMessageBox::Warning);
    passwordError.setStandardButtons(QMessageBox::Ok);

    // setting kick no user error
    kickError.setText("Can not kick this user!");
    kickError.setIcon(QMessageBox::Warning);
    kickError.setStandardButtons(QMessageBox::Ok);

}

void Connecting::connecting(QString IP, int PORT, QString username, QString password, bool addToList = false)
{
    // setting global ip variable
    ip = IP;

    // connecting socket to the server
    socket->connectToHost(IP, PORT);


    // setting username and password variables
    if(password == "")
    {
        userPassword = "none";
    }
    else
    {
        userPassword = password;
    }

    if(username == "")
    {
        userName = "NoNameUser";
    }
    else
    {
        userName = username;
    }

    // waiting for connecting
    if(!socket->waitForConnected(waitingForConnectTime))
    {
        // displaying connecting error dialog
        connectingError.exec();
    }
    else
    {
        // adding server to list
        if(addToList == true)
        {
          emit addServerToList(IP, PORT, username, password);
        }
    }
}

void Connecting::disconnecting()
{
    // closing connection
    if(isConncted == true)
    {
        socket->close();
    }
}

void Connecting::sendMessage(QString message)
{
    // sending message
    if(isConncted == true)
    {
        message = "m" + message;
        socket->write(message.toUtf8());
    }

}

void Connecting::kickUser(QString user)
{
    // kick user
    user = "k " + user;
    socket->write(user.toUtf8());
}

void Connecting::connected()
{
    isConncted = true;
    // reading data from the server
    socket->readAll();
    // setting status
    emit isConnectedStatus("Connected to the server: " + ip);
}

void Connecting::disconnected()
{
    isConncted = false;
    // emiting signal which is removing all users from the list
    emit removeUserFromList();
    // emiting signal which is removing all messages
    emit clearMessages();
    // setting status
    emit isConnectedStatus("Not connected to any server");

}

void Connecting::readyRead()
{
    // reading messages
    getMessage = socket->readAll();
    if(getMessage == "pSend")
    {
        // sending password
        socket->write(userPassword.toUtf8());
    }
    if(getMessage == "nSend")
    {
        // sending nickaname
        socket->write(userName.toUtf8());
    }
    if(getMessage == "nInvalid")
    {
        // showing nickname error
        nicknameError.show();
    }
    if(getMessage == "pInvalid")
    {
        // showing password error
        passwordError.show();
    }
    if(getMessage == "kPremission")
    {
        // showing kicking error
        kickError.show();
    }
    if(getMessage == "pAdmin")
    {
        // setting status
         emit isConnectedStatus("Connected as admin to the server: " + ip);
    }
    if(getMessage.at(0) == "n" && getMessage.at(1) == "A")
    {
        getMessage = getMessage.remove(0, 2);
        // emiting signal which is adding user to the list
        emit addUserToList(getMessage);
    }
    if(getMessage.at(0) == "m")
    {
        // emiting signal which is adding message to the plainTextEdit
        emit addMessage(getMessage.remove(0,1));
    }
    if(getMessage.at(0) == "n" && getMessage.at(1) == "U")
    {
        // emiting signal which is removing all users from the list
        emit removeUserFromList();
    }

}
