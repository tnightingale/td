#include "ResManager.h"
#include "Player.h"
#include "Projectile.h"
#include "NPC.h"
#include "Resource.h"
#include "Tower.h"
#include "BuildingTower.h"

namespace td {

ResManager::ResManager(Driver* driver) : driver_(driver) {
    objects_ = QVector<QList<GameObject*> >(clsidx::kMAX_CLASS_INDEX);
}

ResManager::~ResManager() {
    objects_.clear();
}

GameObject* ResManager::internalCreateObject(unsigned char type) {
    GameObject* ret = NULL;
    unsigned int id = 0;

    switch (type) {
        case clsidx::kPlayer:
            ret = new Player((QObject*)driver_);
            id = (Player::clsIdx() << 24) | objects_[type].size();
            ret->setID(id);
            break;
        case clsidx::kProjectile:
            ret = new Projectile((QObject*)driver_);
            id = (Projectile::clsIdx() << 24) | objects_[type].size();
            ret->setID(id);
            break;
        case clsidx::kNPC:
            ret = new NPC((QObject*)driver_);
            id = (NPC::clsIdx() << 24) | objects_[type].size();
            ret->setID(id);
            break;
        case clsidx::kTower:
            ret = new Tower((QObject*)driver_);
            id = (Tower::clsIdx() <<24) | objects_[type].size();
            ret->setID(id);
            break;
        case clsidx::kBuildingTower:
            ret = new BuildingTower((QObject*)driver_);
            id = (BuildingTower::clsIdx() <<24) | objects_[type].size();
            ret->setID(id);
            break;
        case clsidx::kResource:
            ret = new Resource((QObject*)driver_);
            id = (Resource::clsIdx() << 24) | objects_[type].size();
            ret->setID(id);
            break;
        case clsidx::kCollectable:
            ret = new Collectable((QObject*)driver_);
            id = (Collectable::clsIdx() << 24) | objects_[type].size();
            ret->setID(id);
            break;
        case clsidx::kGameObject:
        case clsidx::kUnit:
        default:
            break;
    }

    return ret;
}

GameObject* ResManager::createObject(unsigned char type) {
    GameObject* ret = internalCreateObject(type);

    if (ret == NULL) {
        return NULL;
    }

    objects_[type].append(ret);

    return ret;
}

GameObject* ResManager::createObjectWithID(unsigned int id) {
    GameObject* ret = internalCreateObject((id & 0xFF000000) >> 24);

    if (ret == NULL) {
        return NULL;
    }

    ret->setID(id);

    addExistingObject(ret);

    return ret;
}

GameObject* ResManager::createTempObject(unsigned char type) {
    return internalCreateObject(type);
}

void ResManager::addExistingObject(GameObject* obj)
{
    unsigned char type = (obj->getID() & 0xFF000000) >> 24;
    int id = obj->getID() & 0x00FFFFFF;

    while (id >= objects_[type].size()) {
        objects_[type].append(NULL);
    }

    objects_[type][id] = obj;
}

GameObject* ResManager::findObject(unsigned int id) {
    unsigned char type = (id & 0xFF000000) >> 24;
    int objid = (id & 0x00FFFFFF);

    if (type >= clsidx::kMAX_CLASS_INDEX
            || objid >= objects_[type].size())
    {
        return NULL;
    }

    return objects_[type][objid];
}

void ResManager::deleteObject(unsigned int id) {
    unsigned char type = (id & 0xFF000000) >> 24;
    unsigned int objid = (id & 0x00FFFFFF);

    GameObject* obj = findObject(id);

    if (obj != NULL) {
        objects_[type][objid] = (GameObject*)-1;
        delete obj;
    }
}

void ResManager::deleteObject(GameObject* obj) {
    if (obj != (GameObject*)-1) {
        deleteObject(obj->getID());
    }
}

unsigned int ResManager::countObjects() const {
    unsigned int count = 0;

    for (int i = 0; i < clsidx::kMAX_CLASS_INDEX; i++) {
        count += countObjectsByType(i);
    }

    return count;
}

} /* end namespace td */
