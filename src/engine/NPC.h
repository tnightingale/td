#ifndef NPC_H
#define NPC_H

#include "Unit.h"

class NPC : public Unit {
    Q_OBJECT
public:
    NPC(PhysicsComponent* physics);

    virtual void update();
    size_t getHealth();
    void setHealth(size_t);
    size_t getDamage();
    void setDamage(size_t);

private:
    size_t health_;
    size_t damage_;
};

#endif // NPC_H