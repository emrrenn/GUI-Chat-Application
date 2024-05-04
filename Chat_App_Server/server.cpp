#include "server.h"
#include "./ui_server.h"

Server::Server(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);

    //Initilaize a new server
    server = new QTcpServer(this);
    qDebug() << "Server initialized";

    //Start to listen for any incoming connections
    if(server->listen(QHostAddress::LocalHost, 1234))
        qDebug() << "Server listening on IP:" << server->serverAddress().toString()
                 << "Port:" <<server->serverPort();
    else
        qDebug() << "Server failed to listen: " << server->errorString();

    //connect a slot to handle any incoming connections
    connect(server, &QTcpServer::newConnection, this, &Server::onNewConnection);

}

Server::~Server()
{
    delete ui;
}

//Function to handle new connections
void Server::onNewConnection()
{
    //Handle newly connection-requesting sockets
    while(server->hasPendingConnections())
    {
        //Add next pending connection socket to clients list
        QTcpSocket *client = server->nextPendingConnection();
        qDebug() << "New Client-"<<client->socketDescriptor();
        clients.append(client);

        connect(client, &QAbstractSocket::readyRead, this, &Server::onReadyRead);

        ui->chat_box->append("New Client added: " + QString::number(client->socketDescriptor()));
        ui->clients->addItem(QString::number(client->socketDescriptor()));

        QByteArray message = "Welcome to the server";
        client->write(message);
        client->flush();
    }
}

void Server::onReadyRead()
{
    QTcpSocket *socket = reinterpret_cast<QTcpSocket*>(sender());
    QByteArray message_array = socket->readAll();
    QString message = "Client: " + QString::fromStdString(message_array.toStdString());

    ui->chat_box->append(message);
}

