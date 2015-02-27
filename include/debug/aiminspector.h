#ifndef AIMINSPECTOR_H
#define AIMINSPECTOR_H

#include <QObject>
#include <QString>
#include "../globals.h"
#include <time.h>

/**
 * Singleton debugging class. Contains information about the current state of
 * all the components of the emulator: CPU context, components registers, etc.
 */
class AimInspector : public QObject
{
    Q_OBJECT
    Q_PROPERTY (QString cpuStatus
                READ GetCpuStatus
                WRITE SetCpuStatus
                NOTIFY cpuStatusChanged)
    Q_PROPERTY (QString componentStatus
                READ GetComponentStatus
                WRITE SetComponentStatus
                NOTIFY componentStatusChanged)
    Q_PROPERTY (QString printerStatus
                READ GetPrinterStatus
                WRITE SetPrinterStatus
                NOTIFY printerStatusChanged)
    Q_PROPERTY (QString keyboardStatus
                READ GetKeyboardStatus
                WRITE SetKeyboardStatus
                NOTIFY keyboardStatusChanged)
    Q_PROPERTY (QString ledStatus
                READ GetLedStatus
                WRITE SetLedStatus
                NOTIFY ledStatusChanged)
public:
    explicit AimInspector(QObject *parent = 0);
    virtual ~AimInspector();
    static AimInspector* GetInstance();
    static const std::string CurrentDateTime();
    void UpdateCpuStatus(const std::string &data);
    void UpdateLedDisplayStatus(const std::string &data);
    void UpdateComponentStatus(const std::string &data);
    void UpdateKeyboardStatus(const std::string &data);
    void UpdatePrinterStatus(const std::string &data);
    QString GetCpuStatus() const;
    QString GetComponentStatus() const;
    QString GetLedStatus() const;
    QString GetKeyboardStatus() const;
    QString GetPrinterStatus() const;
signals:
    void cpuStatusChanged();
    void ledStatusChanged();
    void componentStatusChanged();
    void printerStatusChanged();
    void keyboardStatusChanged();
public slots:
private:
    static AimInspector *pInstance;
    QString m_cpuStatus;
    QString m_componentStatus;
    QString m_ledStatus;
    QString m_printerStatus;
    QString m_keyboardStatus;

    DISALLOW_COPY_AND_ASSIGN(AimInspector);
    void SetCpuStatus(QString cpuStatus);
    void SetLedStatus(QString ledStatus);
    void SetComponentStatus(QString componentStatus);
    void SetKeyboardStatus(QString keyboardStatus);
    void SetPrinterStatus(QString printerStatus);
};

#endif /* AIMINSPECTOR_H */
