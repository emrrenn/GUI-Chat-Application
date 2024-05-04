#include "client.h"
#include "./ui_client.h"

Client::Client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);

    client = new QTcpSocket(this);

    //Attempt to connect an available server
    client->connectToHost(QHostAddress("176.33.69.38"), 1234);

    if(!client->waitForConnected(1000))
        qDebug() << "Error connecting:" << client->errorString();
    else
    {
        qDebug() << "Client" << client->socketDescriptor() << "Connected to Server.";
        connect(client, &QAbstractSocket::readyRead, this, &Client::onReadyRead);
        connect(ui->send_button, &QPushButton::clicked, this, &Client::write_data);
    }
}

Client::~Client()
{
    delete ui;
}

void Client::onReadyRead()
{
    QByteArray data = client->readAll();
    ui->chat_box->append(data);
}

void Client::write_data()
{
    QString message = ui->message->text();
    client->write(message.toStdString().c_str());
    ui->chat_box->append("Client:" + message);
}

