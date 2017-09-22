#include "uhvpvicollectordb.h"

UHVPVICollectorDB::UHVPVICollectorDB(QObject *parent) : QObject(parent)
{
    anIf(UHVPVICollectorDBDbgEn, anTrk("Construct Object"));
}

bool UHVPVICollectorDB::initialize()
{
    localDb = QSqlDatabase::database();
    if (localDb.isOpen())
    {
        anIf(UHVPVICollectorDBDbgEn, anAck("OK Local Database Already Connected !"));
        currentGlobalID = 0;
        currentQuery = QSqlQuery();
        previousReadState = "emitReadP";
        GlobalSignal iamReady;
        iamReady.Type = QVariant::fromValue(UHVPVICollectorDB::readyToWork);
        iamReady.Data = QVariant::fromValue(this->parent()->objectName());
        iamReady.SignalPriority = 100;
        emit Out(iamReady);
    }
    else
    {
        anIf(UHVPVICollectorDBDbgEn, anError("Local Database Not Connected !"));
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
    GS2UHVreadP.Type = QVariant::fromValue(SerialPortWorkerProperty::addAGlobalSignal);
    GS2UHVreadV = GS2UHVreadP;
    GS2UHVreadI = GS2UHVreadP;
    if (isAnUHV2)
    {
        BinaryProtocol currentBP;
        currentBP.SetBPNo(currentPNo);
        GS2UHVreadP.Data = QVariant::fromValue(SerialPortWorkerProperty::DataMessage(currentBP.ChannelNo(currentCH).ReadP().GenMsg(),QStringLiteral("")));
        GS2UHVreadV.Data = QVariant::fromValue(SerialPortWorkerProperty::DataMessage(currentBP.ChannelNo(currentCH).ReadV().GenMsg(),QStringLiteral("")));
        GS2UHVreadI.Data = QVariant::fromValue(SerialPortWorkerProperty::DataMessage(currentBP.ChannelNo(currentCH).ReadI().GenMsg(),QStringLiteral("")));
    }
    else
    {
        WindowProtocol currentWP;
        currentWP.setWPNo(currentPNo);
        GS2UHVreadP.Data = QVariant::fromValue(SerialPortWorkerProperty::DataMessage(currentWP.setChNo(currentCH).PMeasured().Read().clearDATA().genMSG(),QStringLiteral("")));
        GS2UHVreadV.Data = QVariant::fromValue(SerialPortWorkerProperty::DataMessage(currentWP.setChNo(currentCH).VMeasured().Read().clearDATA().genMSG(),QStringLiteral("")));
        GS2UHVreadI.Data = QVariant::fromValue(SerialPortWorkerProperty::DataMessage(currentWP.setChNo(currentCH).IMeasured().Read().clearDATA().genMSG(),QStringLiteral("")));
    }
    anIf(UHVPVICollectorDBDbgEn, anVar(currentGlobalID));
    return true;
}

void UHVPVICollectorDB::emitReadP()
{
    if (gotoNextRecord())
    {
        emit Out(GS2UHVreadP);
        emit SignalToUHVEmitted();
    }
    else
    {
        anIf(UHVPVICollectorDBDbgEn, anWarn("Not Found Data!"));
        emit pause();
    }
}

void UHVPVICollectorDB::emitReadV()
{
    emit Out(GS2UHVreadV);
    emit SignalToUHVEmitted();
}

void UHVPVICollectorDB::emitReadI()
{
    emit Out(GS2UHVreadI);
    emit SignalToUHVEmitted();
}

void UHVPVICollectorDB::emitMsgToDatabaseUpdatePVI()
{
    anIf(UHVPVICollectorDBDbgEn,
            anAck("Emit PVI To Update Database !");
            anVar(currentGlobalID);
            anVar(currentPressure);
            anVar(currentVoltage);
            anVar(currentCurrent));    
    piLocalDBWorkerVarSet::PVIData currentPVIData;
    currentPVIData.GlobalID = currentGlobalID;
    currentPVIData.Pressure = currentPressure;
    currentPVIData.Voltage = currentVoltage;
    currentPVIData.Current = currentCurrent;
    GlobalSignal updateLocalDatabaseWithPVIData;
    updateLocalDatabaseWithPVIData.Type = QVariant::fromValue(piLocalDBWorkerVarSet::updatePVIData);
    updateLocalDatabaseWithPVIData.Data = QVariant::fromValue(currentPVIData);
    emit Out(updateLocalDatabaseWithPVIData);
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
    emit DataFromUHVObtained();
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
    emit DataFromUHVObtained();
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
    emit DataFromUHVObtained();
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

const QMetaEnum UHVPVICollectorDB::DataMetaEnum = QMetaEnum::fromType<UHVPVICollectorDB::Data>();
const QMetaEnum UHVPVICollectorDB::ErrorMetaEnum = QMetaEnum::fromType<UHVPVICollectorDB::Error>();
const QMetaEnum UHVPVICollectorDB::WarningMetaEnum = QMetaEnum::fromType<UHVPVICollectorDB::Warning>();
const QMetaEnum UHVPVICollectorDB::NotificationMetaEnum = QMetaEnum::fromType<UHVPVICollectorDB::Notification>();
