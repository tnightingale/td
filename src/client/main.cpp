#include <QObject>
#include <QApplication>
#include <QThreadPool>
#include "MainWindow.h"
#include "../util/thread.h"
#include "../graphics/MapDisplayer.h"
#include "../engine/CDriver.h"
#include "../audio/manager.h"

int main(int argc, char **argv) {
    QApplication a(argc, argv);
    QDir bin(QCoreApplication::applicationDirPath());
    QQueue<QString> musicList;

    /* Set working directory */
    bin.cdUp();
#if defined(Q_WS_MAC)
    bin.cdUp();    /* Fix this on Mac because of the .app folder, */
    bin.cdUp();    /* which means that the actual executable is   */
    bin.cdUp();    /* three levels deep. Grrr.                    */
#endif
    QDir::setCurrent(bin.absolutePath());

    td::MainWindow* qmw = td::MainWindow::init();
    td::CDriver clientDriver(qmw);
    td::Thread* driverThread = new td::Thread();
    musicList = td::AudioManager::instance()->musicDir("./sound/music/");
    QThreadPool::globalInstance()->setMaxThreadCount(16);

    QObject::connect(driverThread, SIGNAL(started()),
                     &clientDriver, SLOT(startGame()));
    clientDriver.moveToThread(driverThread);

    driverThread->start();
    
    td::AudioManager::instance()->playMusic(musicList);
   // Construct a map
    /*MapDisplayer map(qmw.getScene());
    // Show the map
    map.viewMap(QString("../maps/desert.tmx"));*/
    qmw->show();
    
    return a.exec();
}
