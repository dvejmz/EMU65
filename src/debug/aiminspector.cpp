#include "../../include/debug/aiminspector.h"

AimInspector* AimInspector::pInstance = nullptr;

AimInspector::AimInspector(QObject *parent) : QObject(parent)
{
}

AimInspector::~AimInspector()
{
}

AimInspector* AimInspector::GetInstance()
{
    if (AimInspector::pInstance == nullptr)
    {
        AimInspector::pInstance = new AimInspector();
    }

    return AimInspector::pInstance;
}

void AimInspector::UpdateCpuStatus(const std::string &data)
{
  this->SetCpuStatus(QString::fromStdString(data));
}

void AimInspector::UpdateComponentStatus(const std::string &data)
{
    this->SetComponentStatus(QString::fromStdString(data));
}

void AimInspector::UpdateLedDisplayStatus(const std::string &data)
{
    this->SetLedStatus(QString::fromStdString(data));
}

void AimInspector::UpdatePrinterStatus(const std::string &data)
{
    this->SetPrinterStatus(QString::fromStdString(data));
}

void AimInspector::UpdateKeyboardStatus(const std::string &data)
{
    this->SetKeyboardStatus(QString::fromStdString(data));
}

QString AimInspector::GetComponentStatus() const
{
    return this->m_componentStatus;
}

QString AimInspector::GetCpuStatus() const
{
    return this->m_cpuStatus;
}

QString AimInspector::GetKeyboardStatus() const
{
    return this->m_keyboardStatus;
}

QString AimInspector::GetLedStatus() const
{
    return this->m_ledStatus;
}

QString AimInspector::GetPrinterStatus() const
{
    return this->m_printerStatus;
}

void AimInspector::SetCpuStatus(QString cpuStatus)
{
    this->m_cpuStatus = cpuStatus;
    emit cpuStatusChanged();
}

void AimInspector::SetLedStatus(QString ledStatus)
{
    this->m_ledStatus = ledStatus;
    emit ledStatusChanged();
}

void AimInspector::SetPrinterStatus(QString printerStatus)
{
    this->m_ledStatus = printerStatus;
    emit printerStatusChanged();
}

void AimInspector::SetKeyboardStatus(QString keyboardStatus)
{
    this->m_keyboardStatus = keyboardStatus;
    emit keyboardStatusChanged();
}

void AimInspector::SetComponentStatus(QString ledStatus)
{
    this->m_componentStatus = ledStatus;
    emit componentStatusChanged();
}

const std::string AimInspector::CurrentDateTime()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

