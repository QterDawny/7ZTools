#include "mainwindow.h"

#include "ziputil.h"

#include <QApplication>
#include <QDir>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    // 7z list
//    qDebug() << ZipUtil::listFiles("./7z.exe", "./7ZTools.zip");

//    // add files
//    QDir dir("");
//    QStringList fileList;
//    foreach (const QFileInfo &info, dir.entryInfoList()) {
//        if (info.isFile()) {
//            fileList.append(info.absoluteFilePath().replace("/", "\\"));
//        }
//    }
//    qDebug() << fileList;
//    qDebug() << ZipUtil::addFiles("./7z.exe", "./xx.zip", dir.entryList(QDir::Files));

//    // 7z extract
//    qDebug() << ZipUtil::extract("./7z.exe", "./7ZTools.zip", "./Extract");

//    // list base names
//    qDebug() << ZipUtil::getEntryBaseNames(ZipUtil::listFiles("./7z.exe", "./7ZTools.zip"));

    return a.exec();
}
