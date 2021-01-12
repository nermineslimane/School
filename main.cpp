#include "menu.h"
#include <QSslSocket>
#include <QApplication>
#include "db_connection.h"
#include <openssl/aes.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    db_connection c;
    c.connect();
      Menu w;
    w.show();
    return a.exec();
}
