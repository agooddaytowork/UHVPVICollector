#ifndef IDLEUHVPVICOLLECTOR_H
#define IDLEUHVPVICOLLECTOR_H

#include <QState>
#include "uhvpvicollectordb.h"

class idleUHVPVICollector : public QState
{
public:
    idleUHVPVICollector();
protected:
    void onEntry(QEvent *) override;
    void onExit(QEvent *) override;
};

#endif // IDLEUHVPVICOLLECTOR_H
