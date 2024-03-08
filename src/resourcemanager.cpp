#include "resourcemanager.h"

ResourceManager::ResourceManager()
{

}


void ResourceManager::loadScripts()
{
    QDirIterator it(":/PythonScripts/pyScripts/trial.py",QStringList()<<"*.py",QDir::Files|QDir::NoSymLinks,QDirIterator::Subdirectories);
    qDebug()<<it.filePath();
    while(it.hasNext())
    {

        QFile f(it.filePath());
        if(!f.open(QIODevice::ReadOnly)){
            qDebug() << "Failed to open the resource file!";
            return;
        }

        // 写入到应用程序的运行目录中
        QFile outFile(f.fileName());
        if(!outFile.open(QIODevice::WriteOnly)){
            qDebug() << "Failed to open the out file!";
            return;
        }

        outFile.write(f.readAll());

        outFile.close();
        f.close();
        it.next();
    }
}
