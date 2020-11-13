#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chatwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    // deleting ui object
    delete ui;
}


void MainWindow::on_connectButton_clicked()
{
    // closing window
    close();
    // starting connecting
    emit startConnecting(ui->ipField->text(), ui->portField->text().toInt(), ui->usernameField->text(), ui->passwordField->text(), true);

}

