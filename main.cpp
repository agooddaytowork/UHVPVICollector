#include <QCoreApplication>
#include "UHVPVICollector/uhvpvicollector.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    UHVPVICollector testUHV2(true);
    testUHV2.start();
    return a.exec();
}
