#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include<QFile>
#include<QResource>
#include <QDirIterator>
#include<QDebug>

class ResourceManager
{
   // Q_OBJECT
public:
    ResourceManager();
    static void loadScripts();


};

#endif // RESOURCEMANAGER_H
