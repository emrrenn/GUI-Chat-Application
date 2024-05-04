#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Client; }
QT_END_NAMESPACE

class Client : public QMainWindow
{
    Q_OBJECT

public:
    Client(QWidget *parent = nullptr);
    ~Client();

public slots:
    void onReadyRead();
    void write_data();

private:
    Ui::Client *ui;
    QTcpSocket *client;
};
#endif // CLIENT_H
