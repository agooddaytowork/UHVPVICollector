#include "idleuhvpvicollector.h"

idleUHVPVICollector::idleUHVPVICollector()
{
    anIf(UHVPVICollectorStateDbgEn, anTrk("idleUHVPVICollector Constructed"));
}

void idleUHVPVICollector::onEntry(QEvent *)
{
    anIf(UHVPVICollectorStateDbgEn, anTrk("Enter idleUHVPVICollector"));
}

void idleUHVPVICollector::onExit(QEvent *)
{
    anIf(UHVPVICollectorStateDbgEn, anTrk("Leave idleUHVPVICollector"));
}
