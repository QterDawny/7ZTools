#ifndef ZIPUTIL_H
#define ZIPUTIL_H

#include <QObject>


// use 7z
class ZipUtil : public QObject
{
    Q_OBJECT
public:
    explicit ZipUtil(QObject *parent = 0);

    static QStringList listFiles(const QString &exe, const QString &archive);
    static bool addFiles(const QString &exe, const QString destFile, const QStringList &files);
    static bool extract(const QString &exe, const QString &archive, const QString &destDir, const QString &passwrod = "");

    static QStringList getEntryBaseNames(const QStringList &entries);
    static QString getEntryName(const QStringList &entries, const QString baseName);

signals:

public slots:
};

#endif // ZIPUTIL_H
