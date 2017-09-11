#ifndef UHVPVICOLLECTORDB_H
#define UHVPVICOLLECTORDB_H

#define UHVPVICollectorDBDbgEn 1
#define UHVPVICollectorStateDbgEn 1

#include <QObject>
#include "anlogger.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QByteArray>
#include "binaryprotocol.h"
#include "windowprotocol.h"

class UHVPVICollectorDB : public QObject
{
    Q_OBJECT
public:
    explicit UHVPVICollectorDB(QObject *parent = nullptr);
    quint32 currentGlobalID;
    quint32 breakIntervalMSecs = 1000;
    quint32 waitIntervalMSecs = 5000;
    QSqlDatabase localDb;
    QSqlQuery currentQuery;
    QByteArray currentReplyFromPump;
    QString currentPressure;
    QString currentVoltage;
    QString currentCurrent;
    QString previousReadState;
    quint8 currentPNo;
    quint8 currentCH;
    bool isAnUHV2;
    QByteArray QBAReadP;
    QByteArray QBAReadV;
    QByteArray QBAReadI;
signals:
    void errorOccurred();
    void pause();
    void directTransitionRequest(const QString &);
    void CommandOut(const QByteArray &);
    void DataObtained();
    void MessageToDatabase(quint32 GlobalID, const QString &Pressure, const QString &Voltage, const QString &Current);
public slots:
    bool initialize();
    bool gotoNextRecord();
    void emitReadP();
    void emitReadV();
    void emitReadI();
    void emitMsgToDatabaseUpdatePVI();
    void saveP();
    void saveV();
    void saveI();
    void setPreviousReadState(const QString &StateObjName);
    void resume();
    void processDataFromPump(const QByteArray &data);
private:
    QString getDataString();
};

#endif // UHVPVICOLLECTORDB_H
