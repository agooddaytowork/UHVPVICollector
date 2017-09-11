#include "idle.h"

idle::idle()
{
    anIf(UHVPVICollectorStateDbgEn, anTrk("Construct Object"));
}

void idle::onEntry(QEvent *)
{
    anIf(UHVPVICollectorStateDbgEn, anTrk("Enter State"));
}

void idle::onExit(QEvent *)
{
    anIf(UHVPVICollectorStateDbgEn, anTrk("Leave State"));
}
