#include <QtGui>
#include <QTimer>
#include <QApplication>
#include <QVector>
#include <QWidget>
#include "GameInfo.h"
#include "GameObject.h"
#include "CDriver.h"

CDriver::CDriver(QObject *gui) {
    CDriver::gameTimer_ = new QTimer(this);
    CDriver::human_ = createHumanPlayer(gui);
    
    connect(gameTimer_, SIGNAL(timeout()), human_, SLOT(update()));
}

CDriver::~CDriver() {
    delete CDriver::gameTimer_;
    delete CDriver::human_;
}


//void CDriver::bindAll() {
   // QVector<GameObject>::iterator it;
    //for(it = CDriver::objects.begin(); it != CDriver::objects.end(); ++it) {
       // bindSingle(*it);
    //}
//}

void CDriver::bindSingle(const GameObject& obj) {
  //  connect(&CDriver::gameTimer_, SIGNAL(timeout()), obj, SLOT(update()));
}

Player* CDriver::createHumanPlayer(QObject *gui) {
    PhysicsComponent* physics = new PlayerPhysicsComponent();
    GraphicsComponent* graphics = new PlayerGraphicsComponent("arrow.png");

    InputComponent* input = new PlayerInputComponent();
    gui->installEventFilter(input);
    
    return new Player(input, physics, graphics);
}

void CDriver::startGame() {
    CDriver::gameTimer_ -> start(30);
}

void CDriver::endGame() {
    CDriver::gameTimer_ -> stop();
    //cleanup code
}

//int CDriver::loadMap(char* map) {
    //open map file, parse all map data, create map object,
    //create tiles and stuff, store everything in map object, store map object
    //in gameinfo.

    //return false on any type of failure,
    //return true on success
//}
