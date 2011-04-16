#include "ContextMenuGraphicsComponentTypes.h"
#include "../util/defines.h"
#include "../engine/CDriver.h"

namespace td {

QPixmap* BuildContextMenuGraphicsComponent::pixmapImgs_ = 0;

BuildContextMenuGraphicsComponent::BuildContextMenuGraphicsComponent()
        : ContextMenuGraphicsComponent() {
    emit created(this);
}

void BuildContextMenuGraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_BUILD_MENU_MAX];
    }

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_BUILD_MENU_MAIN;
    pixmapImgs_[pixmapIndex_++] = PIX_BUILD_MENU_RES;
    pixmapImgs_[pixmapIndex_++] = PIX_BUILD_MENU_T1;
    pixmapImgs_[pixmapIndex_++] = PIX_BUILD_MENU_T2;
    pixmapImgs_[pixmapIndex_++] = PIX_BUILD_MENU_T3;
    pixmapImgs_[pixmapIndex_++] = PIX_BUILD_MENU_T4;
    pixmapImgs_[pixmapIndex_++] = PIX_BUILD_MENU_T5;
    pixmapIndex_ = 0;
    initTowerRanges();
}

void BuildContextMenuGraphicsComponent::initTowerRanges() {
    int i;
    QPen pen;
    pen.setWidth(3);
    for (i = 0; i != TOWER_TYPE_MAX;++i) {
        circleRanges_[i] = new QGraphicsEllipseItem();
    }
    pen.setColor(ARROW_COLOR);
    circleRanges_[0]->setPen(pen);
    pen.setColor(CANNON_COLOR);
    circleRanges_[1]->setPen(pen);
    pen.setColor(TAR_COLOR);
    circleRanges_[2]->setPen(pen);
    pen.setColor(FLAME_COLOR);
    circleRanges_[3]->setPen(pen);
    pen.setColor(FLAK_COLOR);
    circleRanges_[4]->setPen(pen);

    for (i = 0; i != TOWER_TYPE_MAX; ++i) {
        circleRanges_[i]->setBrush(QBrush(Qt::transparent));
        CDriver::instance()->getMainWindow()->getScene()->addItem(circleRanges_[i]);
    }
}

void BuildContextMenuGraphicsComponent::draw(void* dp, int layer) {
    QPointF point = ((DrawParams*)dp)->pos;
    int radius = RADIUS_ARROW;
    circleRanges_[0]->setRect(point.x()-radius, point.y()-radius, radius * 2, radius * 2);
    radius = RADIUS_CANNON;
    circleRanges_[1]->setRect(point.x()-radius, point.y()-radius, radius * 2, radius * 2);
    radius = RADIUS_TAR;
    circleRanges_[2]->setRect(point.x()-radius, point.y()-radius, radius * 2, radius * 2);
    radius = RADIUS_FLAME;
    circleRanges_[3]->setRect(point.x()-radius, point.y()-radius, radius * 2, radius * 2);
    radius = RADIUS_FLAK;
    circleRanges_[4]->setRect(point.x()-radius, point.y()-radius, radius * 2, radius * 2);
    GraphicsComponent::draw(dp,layer);
}

void BuildContextMenuGraphicsComponent::showSelectMenu(int type,
                                                       QPointF playerPos) {
    switch(type) {
        case TOWER_ARROW:
            nextImage_ = 2;
            break;
        case TOWER_CANNON:
            nextImage_ = 3;
            break;
        case TOWER_FLAME:
            nextImage_ = 4;
            break;
        case TOWER_TAR:
            nextImage_ = 5;
            break;
        case TOWER_FLAK:
            nextImage_ = 6;
            break;
        }
    ContextMenuGraphicsComponent::showSelectMenu(type, playerPos);
}

QPixmap* BuildContextMenuGraphicsComponent::getPixmapArray() {
    return pixmapImgs_;
}

QPixmap* TowerContextMenuGraphicsComponent::pixmapImgs_ = 0;

TowerContextMenuGraphicsComponent::TowerContextMenuGraphicsComponent()
        : ContextMenuGraphicsComponent() {
    emit created(this);
}

void TowerContextMenuGraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_TOWER_MENU_MAX];
    }

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_TOWER_MENU_MAIN;
    pixmapImgs_[pixmapIndex_++] = PIX_TOWER_MENU_RES;
    pixmapImgs_[pixmapIndex_++] = PIX_TOWER_MENU_UPGR;
    pixmapImgs_[pixmapIndex_++] = PIX_TOWER_MENU_SELL;
    pixmapIndex_ = 0;
}

void TowerContextMenuGraphicsComponent::showSelectMenu(int type,
                                                       QPointF playerPos) {
    switch(type) {
        case UPGRADE_TOWER:
            nextImage_ = 2;
            break;
        case SELL_TOWER:
            nextImage_ = 3;
            break;
        }
    ContextMenuGraphicsComponent::showSelectMenu(type, playerPos);
}

QPixmap* TowerContextMenuGraphicsComponent::getPixmapArray() {
    return pixmapImgs_;
}

QPixmap* PlayerContextMenuGraphicsComponent::pixmapImgs_ = 0;

PlayerContextMenuGraphicsComponent::PlayerContextMenuGraphicsComponent()
        : ContextMenuGraphicsComponent() {
    emit created(this);
}

void PlayerContextMenuGraphicsComponent::initPixmaps() {
    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_PLAYER_MENU_MAX];
    }

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_MENU_MAIN;
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_MENU_RES;
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_MENU_SPD;
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_MENU_HAR;
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_MENU_REC;
    pixmapIndex_ = 0;
}

void PlayerContextMenuGraphicsComponent::showSelectMenu(int type,
                                                        QPointF playerPos) {
    switch(type) {
        case UPGRADE_SPEED:
            nextImage_ = 2;
            break;
        case UPGRADE_HARVEST:
            nextImage_ = 3;
            break;
        case UPGRADE_RECOVERY:
            nextImage_ = 4;
            break;
        }
    ContextMenuGraphicsComponent::showSelectMenu(type, playerPos);
}

QPixmap* PlayerContextMenuGraphicsComponent::getPixmapArray() {
    return pixmapImgs_;
}

} // end namespace td

