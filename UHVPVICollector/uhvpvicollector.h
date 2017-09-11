#ifndef UHVPVICOLLECTOR_H
#define UHVPVICOLLECTOR_H

#define UHVPVICollectorDbgEn 1

#include <QStateMachine>
#include <QObject>
#include "uhvpvicollectordb.h"
#include "emitreadp.h"
#include "wait4p.h"
#include "emitreadv.h"
#include "wait4v.h"
#include "emitreadi.h"
#include "wait4i.h"
#include "idle.h"
#include "directtransition.h"

class UHVPVICollector : public QStateMachine
{
    Q_OBJECT
public:
    UHVPVICollector(bool isUHV2, QObject *parent = 0);
signals:
public slots:
    void pause();
    void resume();
    void DataFromPump(const QByteArray &data);
private:
    UHVPVICollectorDB * currentDb = Q_NULLPTR;
};

#endif // UHVPVICOLLECTOR_H
