// importing files
#include "chatwindow.h"
#include "ui_chatwindow.h"


chatwindow::chatwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::chatwindow)
{
    ui->setupUi(this);
    // creating new connecting object
    connecting = new Connecting();
    // connecting signals to slots
    connect(connecting, SIGNAL(addServerToList(QString, int, QString, QString)), this, SLOT(addServerToList(QString, int, QString, QString)));
    connect(this, SIGNAL(connectToServer(QString, int, QString, QString, bool)), connecting, SLOT(connecting(QString, int, QString, QString, bool)));
    connect(this, SIGNAL(disconnectFromServer()), connecting, SLOT(disconnecting()));
    connect(this, SIGNAL(sendMessage(QString)), connecting, SLOT(sendMessage(QString)));
    connect(connecting, SIGNAL(addMessage(QString)), this, SLOT(addMessage(QString)));
    connect(connecting, SIGNAL(addUserToList(QString)), this, SLOT(addUserToList(QString)));
    connect(connecting, SIGNAL(removeUserFromList()), this, SLOT(removeUserFromList()));
    connect(this, SIGNAL(kickUser(QString)), connecting, SLOT(kickUser(QString)));
    connect(connecting, SIGNAL(isConnectedStatus(QString)), this, SLOT(isConnectedStatus(QString)));
    connect(connecting, SIGNAL(clearMessages()), this, SLOT(clearMessages()));

    // showing messange on status bar
    ui->statusBar->showMessage("Not connected to any server.");
}

chatwindow::~chatwindow()
{
    // deleting connecting object
    delete connecting;
    // deleting ui object
    delete ui;
}

void chatwindow::on_addButton_clicked()
{
    // creating new connecting window
    connectWindow = new MainWindow(this);
    // connecting signal which is starting connecting to slot
    connect(connectWindow, SIGNAL(startConnecting(QString, int, QString, QString, bool)), connecting, SLOT(connecting(QString, int, QString, QString, bool)));
    // opening connectWindow
    connectWindow->show();
}

void chatwindow::addServerToList(QString IP, int PORT, QString username, QString password)
{
    // adding elements needed to connect with the server to vectors
    ipList.push_back(IP);
    portList.push_back(PORT);
    usernameList.push_back(username);
    passwordList.push_back(password);
    // adding server to list
    ui->serversList->addItem(IP);
}

void chatwindow::addMessage(QString message)
{
    // adding message to plainTextEdit
    ui->chatText->insertPlainText(message + "\n");
}

void chatwindow::addUserToList(QString user)
{
    // adding user to list
    ui->usersList->addItem(user);
}

void chatwindow::removeUserFromList()
{
    // removing user from list
    ui->usersList->clear();
}

void chatwindow::isConnectedStatus(QString text)
{
    // showing message on status bar
    ui->statusBar->showMessage(text);
}

void chatwindow::clearMessages()
{
    // clear plainTextEdit
    ui->chatText->clear();
}

void chatwindow::on_removeButton_clicked()
{
    if(ui->serversList->selectedItems().size() !=0)
    {
        // removing elements needed to connect with the server from vector
        ipList.remove(ui->serversList->currentRow());
        portList.remove(ui->serversList->currentRow());
        usernameList.remove(ui->serversList->currentRow());
        passwordList.remove(ui->serversList->currentRow());
        // removing elements needed to connect with the server from list
        delete ui->serversList->takeItem(ui->serversList->currentRow());
    }

}


void chatwindow::on_disconnectButton_clicked()
{
    // emiting signal for disconnecting from the server
    emit disconnectFromServer();
}

void chatwindow::on_connectButton_clicked()
{
    // emiting signal for connecting to the server
    emit connectToServer(
            ipList[ui->serversList->currentRow()],
            portList[ui->serversList->currentRow()],
            usernameList[ui->serversList->currentRow()],
            passwordList[ui->serversList->currentRow()],
            false);
}

void chatwindow::on_sendButton_clicked()
{
    // emiting signal for sending message
    emit sendMessage(ui->messageLineEdit->text());
    // clear message in line edit
    ui->messageLineEdit->setText("");
}


void chatwindow::on_kickButton_clicked()
{
    // emit signal for kick user
    emit kickUser(ui->usersList->currentItem()->text());
}
