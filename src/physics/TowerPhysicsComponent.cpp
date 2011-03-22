#include "../physics/TowerPhysicsComponent.h"
#include "../engine/Tower.h"
#include "../engine/Player.h"
#include <QLineF>
#include <typeinfo>
#define PI 3.141592653589793238
#include <math.h>

namespace td {

TowerPhysicsComponent::TowerPhysicsComponent(Tower* tower, size_t fireInterval)
        : PhysicsComponent(), tower_(tower), fireInterval_(fireInterval) {
    fireCountdown_ = 0;
    target_ = 0;
    enemies_ = QSet<Unit*>();
    radius_ = 5;
}

TowerPhysicsComponent::~TowerPhysicsComponent() {}

void TowerPhysicsComponent::update(GameObject *tower) {
    this->applyDirection((Tower*)tower);
    this->fire();
}

void TowerPhysicsComponent::findTargets(GameObject* tower, int radius) {
    QLineF projectilePath;
    projectilePath.p1() = tower->getPos();

    if (target_ != NULL) {
        projectilePath.p2() = target_->getPos();
    } else {
        projectilePath.p2() = tower->getPos();
    }

    setNPCs(tower, radius);
    
    if (enemies_.isEmpty()) {
        target_ = NULL;
        return;
    }

    QSet<Unit*>::iterator iter;

    for (iter = enemies_.begin(); iter != enemies_.end(); ++iter) {
        QLineF line;
        line.p1() = tower->getPos();

        if (target_ != NULL && projectilePath.length() < radius 
                && projectilePath.length() != 0) {
            return;

        } else {
            if (enemies_.size() == 1 &&
                (((*iter)->getID()&0xFF000000)>>24) == Player::clsIdx()) {
                target_ = NULL;
            }
            if((((*iter)->getID()&0xFF000000)>>24) == NPC::clsIdx()) {
                target_ = *iter;
            }
        }
    }
}

void TowerPhysicsComponent::fire() {
    if (fireCountdown_ != 0) {
        fireCountdown_--;
        return;
    }
    if (target_ == NULL) {
        return;
    }
    emit fireProjectile(tower_->getPos(), target_->getPos());
    fireCountdown_ = fireInterval_;
}

void TowerPhysicsComponent::applyDirection(GameObject* tower) {


    this->findTargets(tower, getRadius());
    if(target_ == NULL || enemies_.isEmpty()) {
        return;
    }
    int angle = 0;
    int degree = 0;
    int velX = target_->getPos().x() - tower->getPos().x();
    int velY = target_->getPos().y() - tower->getPos().y();

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

void TowerPhysicsComponent::targetDied() {
    target_ = NULL;
}

}
