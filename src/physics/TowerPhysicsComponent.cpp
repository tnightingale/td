#include "../physics/TowerPhysicsComponent.h"
#include "../engine/Tower.h"
 #include <QLineF>
#define PI 3.141592653589793238
#include <math.h>

namespace td {

void TowerPhysicsComponent::update(GameObject *tower) {
    this->applyDirection((Tower*)tower);
}

void TowerPhysicsComponent::findTargets(GameObject* tower) {
    QLineF target;
    target.p1() = tower->getPos();
    if(this->getEnemy() != NULL) {
        target.p2() = this->getEnemy()->getPos();
    } else {
        target.p2() = tower->getPos();
    }
    Unit* u = new NPC();
    this->setNPCs(tower, 10);
    QSet<Unit*> units = this->getNPCs();

    QSet<Unit*>::iterator iter;
    for( iter = units.begin();iter != units.end(); ++iter){
        u = *iter;
        QLineF line;
        line.p1() = tower->getPos();
        line.p2() = u->getPos();
        if(this->getEnemy() != NULL && target.length() < 5 ) {
            break;
        } else {
            this->setTarget(u);
        }
    }
}

void TowerPhysicsComponent::applyDirection(GameObject* tower) {


    this->findTargets(tower);
    if(this->getEnemy() == NULL) {
        return;
    }
    int angle = 0;
    int degree = 0;
    int velX = this->getEnemy()->getPos().x() - this->getPos().x();
    int velY = this->getEnemy()->getPos().y() - this->getPos().y();

    if (velX == 0 && velY == 0) {
        return;
    }

    if (qAbs(velX) >= qAbs(velY)) {
        angle = atan(velY / (float)velX) * (180 / PI);

        if (velX > 0) {
            if (velY == 0) {
                degree = 0;
            } else if (velX == velY) {
                degree = 315;
            } else if (velX == (-velY)) {
                degree = 45;
            } else if (angle < 0) {
                degree =  (-angle);
            } else {
                degree = 360 - angle;
            }
        } else if (velX < 0) {
            if (velY == 0) {
                degree = 180;
            } else if (velX == velY) {
                degree = 135;
            } else if (velX == (-velY)) {
                degree = 225;
            } else {
                degree = 180 - angle;
            }
        }
    } else if (qAbs(velY) > qAbs(velX)) {
        angle = atan(velX / (float) velY) * (180 / PI);

        if (velY < 0) {
            if (velX == 0) {
                degree = 90;
            } else {
                degree = 90 + angle;
            }
        } else if (velY > 0) {
            if (velX == 0) {
                degree = 270;
            } else {
                degree = 270 + angle;
            }
        }
    }
    tower->setOrientation(degree);
}

}
