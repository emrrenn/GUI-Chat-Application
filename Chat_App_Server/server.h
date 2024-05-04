#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Server; }
QT_END_NAMESPACE

class Server : public QMainWindow
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);
    ~Server();

public slots:
    void onNewConnection();
    void onReadyRead();

private:
    Ui::Server *ui;

    QTcpServer *server;
    QList<QTcpSocket*> clients;
};
#endif // SERVER_H
