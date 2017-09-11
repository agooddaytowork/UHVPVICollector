#include "wait4p.h"

wait4P::wait4P(UHVPVICollectorDB *database)
{
    anIf(UHVPVICollectorStateDbgEn, anTrk("Construct Object"));
    timer.setParent(this);
    timer.setInterval(database->waitIntervalMSecs);
    timer.setSingleShot(true);
    QObject::connect(&timer, &QTimer::timeout, this, [database](){
        anIf(UHVPVICollectorStateDbgEn, anWarn("Wait For P Timed Out !"));
        database->saveP();
    });
}

void wait4P::onEntry(QEvent *)
{
    anIf(UHVPVICollectorStateDbgEn, anTrk("Enter State"));
    timer.start();
}

void wait4P::onExit(QEvent *)
{
    anIf(UHVPVICollectorStateDbgEn, anTrk("Leave State"));
    timer.stop();
}
