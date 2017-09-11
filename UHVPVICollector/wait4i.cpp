#include "wait4i.h"

wait4I::wait4I(UHVPVICollectorDB *database) : dbPtr(database)
{
    anIf(UHVPVICollectorStateDbgEn, anTrk("Construct Object"));
    timer.setInterval(database->waitIntervalMSecs);
    timer.setSingleShot(true);
    QObject::connect(&timer, &QTimer::timeout, this, [database](){
        anIf(UHVPVICollectorStateDbgEn, anWarn("Wait For I Timed Out !"));
        database->saveI();
    });
}

void wait4I::onEntry(QEvent *)
{
    anIf(UHVPVICollectorStateDbgEn, anTrk("Enter State"));
    timer.start();
}

void wait4I::onExit(QEvent *)
{
    anIf(UHVPVICollectorStateDbgEn, anTrk("Leave State"));
    timer.stop();
    dbPtr->emitMsgToDatabaseUpdatePVI();
}
