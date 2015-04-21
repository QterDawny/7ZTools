#include "ziputil.h"

#include <QProcess>
#include <QDebug>

static QString getBaseName(const QString &in) {
    int n = in.lastIndexOf('/');
    if(n != -1) {
        return in.mid(n+1);
    }

    n = in.lastIndexOf('\\');
    if(n != -1) {
        return in.mid(n+1);
    }
    return in;
}

ZipUtil::ZipUtil(QObject *parent) : QObject(parent)
{

}

QStringList ZipUtil::listFiles(const QString &exe, const QString &archive)
{
    QString command = exe + QString(" l \"%1\"").arg(archive);  // 7z.exe l "xxx.zip"
    QProcess process;
    process.start(command.trimmed());
    if (!process.waitForFinished()) {
        qDebug() << "List fail: " << process.errorString();
        return QStringList();
    }

    QByteArray out = process.readAllStandardOutput();
    QTextStream in(&out);
    QStringList fileList;
    QString mark = "------------------- ----- ------------ ------------  ------------------------";
    int markCount = 0;
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.compare(mark) == 0) {
            markCount++;
            if (1 == markCount)
                continue;
        }

        if (1 != markCount)
            continue;
        if (2 == markCount)
            break;

        QString name = line.mid(53);
        fileList.append(name);
    }
    return fileList;
}

bool ZipUtil::addFiles(const QString &exe, const QString destFile, const QStringList &files)
{
    int ret = QProcess::execute(exe, QStringList() << "a" << destFile << files.join(" "));
    if (-2 != ret && -1 != ret) {
        return true;
    } else {
        return false;
    }
}

bool ZipUtil::extract(const QString &exe, const QString &archive, const QString &destDir, const QString &passwrod)
{
    QString command = exe
            + QString(" x \"%1\"").arg(archive)
            + QString(" -o\"%1\"").arg(destDir)
            + QString(" -p\"%1\"").arg(passwrod)
            + QString(" -aoa");

    QProcess process;
    process.start(command.trimmed());
    if (!process.waitForFinished(-1)) {
        qDebug() << "List fail: " << process.errorString();
        return false;
    }
    return true;
}

QStringList ZipUtil::getEntryBaseNames(const QStringList &entries) {
    QStringList list;
    foreach (const QString &entry, entries) {
        list.append(getBaseName(entry));
    }
    return list;
}

QString ZipUtil::getEntryName(const QStringList &entries, const QString baseName) {
    int len = baseName.length();
    foreach (const QString &entry, entries) {
        if (entry.right(len) == baseName) {
            return entry;
        }
    }
    return "";
}
