#include <QCoreApplication>
#include "src/uhvpvicollector.h"

int main(int argc, char *argv[])
{
    registerGlobalSignal;
    connectLocalQSqlDatabase;
    QCoreApplication a(argc, argv);
    UHVPVICollector testUHV2(true);
    testUHV2.start();
    return a.exec();
}
