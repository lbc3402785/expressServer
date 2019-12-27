#ifndef SETTINGS_H
#define SETTINGS_H
#include <QString>
#include "thread/threadsynglobalobj.h"
const QString SETTINGS_FILE{"ExpressionServerConfig"};
class Settings
{
public:
    static Settings& instance() {static Settings obj; return obj; }
    void saveSettings();
    void reset();
    QString getOutputDir() const;
    void setOutputDir(const QString &value);
    int getPort() const;
    void setPort(int value);

    int getInterval() const;
    void setInterval(int value);

    int getWidth() const;
    void setWidth(int value);

    int getHeight() const;
    void setHeight(int value);

    QString getG8M2BFM() const;
    void setG8M2BFM(const QString &value);

    QString getBFM2G8M() const;
    void setBFM2G8M(const QString &value);

    QString getBFMModel() const;
    void setBFMModel(const QString &value);

    QString getDlibModel() const;
    void setDlibModel(const QString &value);

    QString getBFMKeyIndexes() const;
    void setBFMKeyIndexes(const QString &value);
    ThreadSynGlobalObj obj;
    QString getSelectEB() const;
    void setSelectEB(const QString &value);

    QString getG8MKeyIndexes() const;
    void setG8MKeyIndexes(const QString &value);

    QString getG8MModel() const;
    void setG8MModel(const QString &value);

private:
    Settings();
    void loadSettings();
    QString getDefaultOutputDir();
    QString getDefaultDlibModelPath();
    QString getDefaultBFMModelPath();
    QString getDefaultG8MModelPath();
    QString getDefaultG8M2BFMPath();
    QString getDefaultBFM2G8MPath();
    QString getDefaultSelectEBPath();
    QString getDefaultBFMKeyIndexesPath();
    QString getDefaultG8MKeyIndexesPath();
    int getDefaultPort();
    int getDefaultInterval();
    int getDefaultWidth();
    int getDefaultHeight();
    int port;
    int interval;
    int width;
    int height;
    QString G8M2BFM;
    QString BFM2G8M;
    QString BFMModel;
    QString G8MModel;
    QString SelectEB;
    QString DlibModel;
    QString BFMKeyIndexes;
    QString G8MKeyIndexes;
    QString outputDir;

};

#endif // SETTINGS_H
