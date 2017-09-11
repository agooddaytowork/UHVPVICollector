#include "uhvpvicollectordb.h"

UHVPVICollectorDB::UHVPVICollectorDB(QObject *parent) : QObject(parent)
{
    anIf(UHVPVICollectorDBDbgEn, anTrk("Construct Object"));
}

bool UHVPVICollectorDB::initialize()
{
    localDb = QSqlDatabase::addDatabase("QMYSQL");
    localDb.setHostName("localhost");
    localDb.setDatabaseName("raspberry");
    localDb.setUserName("root");
    localDb.setPassword("Ascenx123");
    localDb.setPort(3306);
    if (localDb.open())
    {
        anIf(UHVPVICollectorDBDbgEn, anAck("OK Local Database Connected !"));
        currentGlobalID = 0;
        currentQuery = QSqlQuery();        
    }
    else
    {
        anIf(UHVPVICollectorDBDbgEn, anError("Failed To Connect Local Database !"));
        emit errorOccurred();
        return false;
    }
    anIf(UHVPVICollectorDBDbgEn, anAck("OK Initialized !"));
    return true;
}

bool UHVPVICollectorDB::gotoNextRecord()
{
    anIf(UHVPVICollectorDBDbgEn, anTrk("Retrieve New Record"));
    currentQuery.exec("SELECT GlobalID,pumpAddr,pumpCH FROM stations WHERE GlobalID>" +
                        QString::number(currentGlobalID) + " ORDER BY GlobalID ASC LIMIT 1");
    if (!currentQuery.next())
    {
        currentGlobalID = 0;
        currentQuery.exec("SELECT GlobalID,pumpAddr,pumpCH FROM stations WHERE GlobalID>" +
                            QString::number(currentGlobalID) + " ORDER BY GlobalID ASC LIMIT 1");
        if (!currentQuery.next())
            return false;
    }
    currentGlobalID = currentQuery.value("GlobalID").toInt();
    currentPNo = currentQuery.value("pumpAddr").toInt();
    currentCH = currentQuery.value("pumpCH").toInt();
    if (isAnUHV2)
    {
        BinaryProtocol currentBP;
        currentBP.SetBPNo(currentPNo);
        QBAReadP = currentBP.ChannelNo(currentCH).ReadP().GenMsg();
        QBAReadV = currentBP.ChannelNo(currentCH).ReadV().GenMsg();
        QBAReadI = currentBP.ChannelNo(currentCH).ReadI().GenMsg();
    }
    else
    {
        WindowProtocol currentWP;
        currentWP.setWPNo(currentPNo);
        QBAReadP = currentWP.setChNo(currentCH).PMeasured().Read().clearDATA().genMSG();
        QBAReadV = currentWP.setChNo(currentCH).VMeasured().Read().clearDATA().genMSG();
        QBAReadI = currentWP.setChNo(currentCH).IMeasured().Read().clearDATA().genMSG();
    }
    anIf(UHVPVICollectorDBDbgEn, anVar(currentGlobalID));
    return true;
}

void UHVPVICollectorDB::emitReadP()
{
    if (gotoNextRecord())
    {
        emit CommandOut(QBAReadP);
    }
    else
    {
        anIf(UHVPVICollectorDBDbgEn, anWarn("Not Found Data!"));
        emit pause();
    }
}

void UHVPVICollectorDB::emitReadV()
{
    emit CommandOut(QBAReadV);
}

void UHVPVICollectorDB::emitReadI()
{
    emit CommandOut(QBAReadI);
}

void UHVPVICollectorDB::emitMsgToDatabaseUpdatePVI()
{
    anIf(UHVPVICollectorDBDbgEn,
            anAck("Emit PVI To Update Database !");
            anVar(currentGlobalID);
            anVar(currentPressure);
            anVar(currentVoltage);
            anVar(currentCurrent));
    emit MessageToDatabase(currentGlobalID,currentPressure,currentVoltage,currentCurrent);
}

void UHVPVICollectorDB::saveP()
{
    if (currentReplyFromPump.isEmpty())
    {
        currentPressure = "0";
    }
    else
    {
        currentPressure = getDataString();
    }
    anIf(UHVPVICollectorDBDbgEn, anVar(currentPressure));
    emit DataObtained();
}

void UHVPVICollectorDB::saveV()
{
    if (currentReplyFromPump.isEmpty())
    {
        currentVoltage = "0";
    }
    else
    {
        currentVoltage = getDataString();
    }
    anIf(UHVPVICollectorDBDbgEn, anVar(currentVoltage));
    emit DataObtained();
}

void UHVPVICollectorDB::saveI()
{
    if (currentReplyFromPump.isEmpty())
    {
        currentCurrent = "0";
    }
    else
    {
        currentCurrent = getDataString();
    }
    anIf(UHVPVICollectorDBDbgEn, anVar(currentCurrent));
    emit DataObtained();
}

void UHVPVICollectorDB::setPreviousReadState(const QString &StateObjName)
{
    previousReadState = StateObjName;
}

void UHVPVICollectorDB::resume()
{
    emit directTransitionRequest(previousReadState);
}

void UHVPVICollectorDB::processDataFromPump(const QByteArray &data)
{
    anIf(UHVPVICollectorDBDbgEn, anAck("Data From Pump Received !");anVar(data.toHex()););
    currentReplyFromPump = data;
    if (previousReadState=="emitReadP")
        saveP();
    else if (previousReadState=="emitReadV")
        saveV();
    else
        saveI();
}

QString UHVPVICollectorDB::getDataString()
{
    if (isAnUHV2)
    {
        return QString(BinaryProtocol::fromQByteArray(currentReplyFromPump).GetData());
    }
    else
    {
        return QString(WindowProtocol::fromQByteArray(currentReplyFromPump).getDATAMean());
    }
}


