#include "EffectTypes.h"
#include "../util/defines.h"
#include "NPC.h"
#include "Player.h"

namespace td {

NPCPlayerEffect::NPCPlayerEffect(Unit* unit): Effect(unit, EFFECT_NPCPLAYER, NPC_PLAYER_TIME) {
    oldVelocity_ = (((PlayerPhysicsComponent*)(unit_->getPhysicsComponent()))->getMaxVelocity());
    velocityChangeValue_ = 0.5;
}

NPCPlayerEffect::~NPCPlayerEffect() {
    ((PlayerPhysicsComponent*)(unit_->getPhysicsComponent()))->setMaxVelocity(oldVelocity_);
}
void NPCPlayerEffect::apply() {
    ((PlayerPhysicsComponent*)(unit_->getPhysicsComponent()))->setMaxVelocity(velocityChangeValue_);
}

ArrowEffect::ArrowEffect(Unit* unit)
        : Effect(unit, EFFECT_ARROW, ARROW_TIME) {    

    healthChangeValue_ = -25;
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth()
        + healthChangeValue_);
}

void ArrowEffect::apply() {
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth() + healthChangeValue_);
}

PlayerTerrainSlowEffect::PlayerTerrainSlowEffect(Unit* unit)
    : Effect(unit, EFFECT_TERRAIN, NO_TIME) {
    velocityChangeValue_ = 2;
}

PlayerTerrainSlowEffect::~PlayerTerrainSlowEffect() {
    ((PlayerPhysicsComponent*)(getUnit()->getPhysicsComponent()))->setMaxVelocity(oldVelocity_);
}

void PlayerTerrainSlowEffect::apply() {
    ((PlayerPhysicsComponent*)(unit_->getPhysicsComponent()))->setMaxVelocity(velocityChangeValue_);
}

NPCTarEffect::NPCTarEffect(Unit* unit)
    : Effect(unit, EFFECT_TAR, TAR_TIME) {
    velocityChangeValue_ = 0;
    healthChangeValue_ = -25;
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth()
                                + healthChangeValue_);
}

NPCTarEffect::~NPCTarEffect() {
    ((NPCPhysicsComponent*)(unit_->getPhysicsComponent()))->setMaxVelocity(oldVelocity_);
}

void NPCTarEffect::apply() {
    velocityChangeValue_ = 0;
}

NPCBurnEffect::NPCBurnEffect(Unit* unit):Effect(unit, EFFECT_BURN, BURN_TIME) {
    healthChangeValue_ = -5;
}

void NPCBurnEffect::apply() {
    ((NPC*)unit_)->setHealth(((NPC*)unit_)->getHealth() + healthChangeValue_);
}

} /* end namespace td */

