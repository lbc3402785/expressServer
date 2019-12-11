#include "settings.h"
#include <QSettings>
#include <QDir>
#include <QStandardPaths>
Settings::Settings()
{
    loadSettings();
}

void Settings::loadSettings()
{
    QSettings settings(SETTINGS_FILE);
    port=settings.value("port", getDefaultPort()).toInt();
    interval=settings.value("interval", getDefaultInterval()).toInt();
    width=settings.value("width", getDefaultWidth()).toInt();
    height=settings.value("height", getDefaultHeight()).toInt();
    G8M2BFM=settings.value("G8M2BFM", getDefaultG8M2BFMPath()).toString();
    BFM2G8M=settings.value("BFM2G8M", getDefaultBFM2G8MPath()).toString();
    BFMModel=settings.value("BFMModel", getDefaultBFMModelPath()).toString();
    DlibModel=settings.value("DlibModel", getDefaultDlibModelPath()).toString();
    BFMKeyIndexes=settings.value("BFMKeyIndexes", getDefaultBFMKeyIndexesPath()).toString();
    outputDir=settings.value("outputDir", getDefaultOutputDir()).toString();
}


QString Settings::getDefaultOutputDir()
{
    return "E:\\model\\output_male";
}

QString Settings::getDefaultDlibModelPath()
{
    return "E:\\model\\shape_predictor_68_face_landmarks.dat";
}

QString Settings::getDefaultBFMModelPath()
{
    return "E:\\model\\BFMUV.obj.npz";
}

QString Settings::getDefaultG8M2BFMPath()
{
    return "E:\\model\\output_male\\G8M_BFM_EXPRESS.npz";
}

QString Settings::getDefaultBFM2G8MPath()
{
    return "E:\\model\\output_male\\BFM_G8M_EXPRESS.npz";
}

QString Settings::getDefaultBFMKeyIndexesPath()
{
    return "E:\\model\\BFM.ini";
}

int Settings::getDefaultPort()
{
    return 8765;
}

int Settings::getDefaultInterval()
{
    return 33;
}

int Settings::getDefaultWidth()
{
    return 1920;
}

int Settings::getDefaultHeight()
{
    return 1080;
}

QString Settings::getBFMKeyIndexes() const
{
    return BFMKeyIndexes;
}

void Settings::setBFMKeyIndexes(const QString &value)
{
    BFMKeyIndexes = value;
}

QString Settings::getDlibModel() const
{
    return DlibModel;
}

void Settings::setDlibModel(const QString &value)
{
    DlibModel = value;
}

QString Settings::getBFMModel() const
{
    return BFMModel;
}

void Settings::setBFMModel(const QString &value)
{
    BFMModel = value;
}

QString Settings::getBFM2G8M() const
{
    return BFM2G8M;
}

void Settings::setBFM2G8M(const QString &value)
{
    BFM2G8M = value;
}

QString Settings::getG8M2BFM() const
{
    return G8M2BFM;
}

void Settings::setG8M2BFM(const QString &value)
{
    G8M2BFM = value;
}

int Settings::getHeight() const
{
    return height;
}

void Settings::setHeight(int value)
{
    height = value;
}

int Settings::getWidth() const
{
    return width;
}

void Settings::setWidth(int value)
{
    width = value;
}

int Settings::getInterval() const
{
    return interval;
}

void Settings::setInterval(int value)
{
    interval = value;
}

int Settings::getPort() const
{
    return port;
}

void Settings::setPort(int value)
{
    port = value;
}

QString Settings::getOutputDir() const
{
    return outputDir;
}

void Settings::setOutputDir(const QString &value)
{
    outputDir = value;
}

void Settings::saveSettings()
{
    QSettings settings(SETTINGS_FILE);
    settings.setValue("port", port);
    settings.setValue("interval", interval);
    settings.setValue("width", width);
    settings.setValue("height", height);
    settings.setValue("G8M2BFM", G8M2BFM);
    settings.setValue("BFM2G8M", BFM2G8M);
    settings.setValue("BFMModel", BFMModel);
    settings.setValue("DlibModel", DlibModel);
    settings.setValue("BFMKeyIndexes", BFMKeyIndexes);
    settings.sync();
}

void Settings::reset()
{
    port=getDefaultPort();
    interval=getDefaultInterval();
    width=getDefaultWidth();
    height=getDefaultHeight();
    G8M2BFM=getDefaultG8M2BFMPath();
    BFM2G8M=getDefaultBFM2G8MPath();
    BFMModel=getDefaultBFMModelPath();
    DlibModel=getDefaultDlibModelPath();
    BFMKeyIndexes=getDefaultBFMKeyIndexesPath();
    outputDir=getDefaultOutputDir();
}


