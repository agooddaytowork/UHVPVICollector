#include "idle.h"

idle::idle()
{
    anIf(UHVPVICollectorStateDbgEn, anTrk("idle Constructed"));
}

void idle::onEntry(QEvent *)
{
    anIf(UHVPVICollectorStateDbgEn, anTrk("Enter idle"));
}

void idle::onExit(QEvent *)
{
    anIf(UHVPVICollectorStateDbgEn, anTrk("Leave idle"));
}
