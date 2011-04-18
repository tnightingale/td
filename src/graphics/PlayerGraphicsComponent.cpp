#include "PlayerGraphicsComponent.h"
#include "../engine/Player.h"
#include "../engine/CDriver.h"
#include <QDebug>

namespace td {

QPixmap * PlayerGraphicsComponent::pixmapImgs_ = 0;

PlayerGraphicsComponent::PlayerGraphicsComponent(QString nickname)
        : GraphicsComponent(), nickname_(nickname),
          showName_(false), nameShowing_(false)
{
    animateMod_ = 4;
    animateCount_ = 0; 
    resourceProgressBar_ = new QGraphicsRectItem(QRectF(OFFSCREEN,OFFSCREEN,
                                                    RESBAR_WIDTH, RESBAR_HEIGHT));
    resourceProgressBar_->setBrush(QBrush(Qt::blue));
    resourcePixmapItem_ = 0;
    resourceType_ = RESOURCE_NONE;

    CDriver::instance()->getMainWindow()->getScene()->addItem(resourceProgressBar_);
    emit created(this);
}

void PlayerGraphicsComponent::update(GameObject* obj) {
    Player* player = (Player*)obj;

    if (player->getHarvestCountdown() != player->getHarvestTime()) {
        resourceProgressShowing_ = true;
        resourceProgress_ = (double) player->getHarvestCountdown()
                            / player->getHarvestTime();
    }

    if (!player->isDirty() && pixmapIndex_ == 0 && !resourceProgressShowing_) {
        //checks if object is dirty or in mid-animation, or if the resource progress
        //bar is being updated
        return;
    }

    if (player->getHarvestCountdown() == player->getHarvestTime()) {
        resourceProgressShowing_ = false;
    }

    player->resetDirty();

    DrawParamsPlayer* dp = new DrawParamsPlayer();
    dp->pos     = player->getPos();
    //dp->moving  = player->getVelocity().length() != 0;
    dp->moving = player->getMoving();
    dp->scale   = 1;
    dp->degrees = player->getOrientation();
    dp->animate = animate_;
    dp->resourceProgressShowing = resourceProgressShowing_;
    dp->resourceProgress = resourceProgress_;
    dp->resourceType = player->getResource();
    dp->showName = showName_;
    emit signalDraw(dp, this, LAYER_PLAYER);
}

void PlayerGraphicsComponent::draw(void* dp, int layer) {
    DrawParamsPlayer *dpPlayer = (DrawParamsPlayer*) dp;
    isMoving_ = dpPlayer->moving;
    
    if (dpPlayer->resourceProgressShowing) {
        resourceProgressBar_->setVisible(true);
        resourceProgressBar_->setRect(0, 0,
                                  RESBAR_WIDTH * dpPlayer->resourceProgress, RESBAR_HEIGHT);
        resourceProgressBar_->setPos((dpPlayer->pos.x()
                    - resourceProgressBar_->boundingRect().center().x()),
                    (dpPlayer->pos.y()
                    - (getPixmapItem()->boundingRect().height())/2));
        resourceProgressBar_->setZValue(layer);
        resourceProgressBar_->update();
    } else {
        resourceProgressBar_->setVisible(false);
    }
    if (dpPlayer->resourceType >= 0) {
        resourcePixmapItem_->setPixmap(pixmapImgs_[PIX_PLAYER_MAX + dpPlayer->resourceType]);
        resourcePixmapItem_->setVisible(true);

        resourcePixmapItem_->setZValue(layer);
        resourcePixmapItem_->setScale(.7);
        resourcePixmapItem_->setPos(dpPlayer->pos.x() + 8, dpPlayer->pos.y() + 17);
        resourcePixmapItem_->update();
    } else {
        resourcePixmapItem_->setVisible(false);
    }

    if (dpPlayer->showName) {
        label_->setPos(dpPlayer->pos.x() - label_->boundingRect().center().x(),
                       dpPlayer->pos.y() - getPixmapItem()->boundingRect().height());
        label_->setZValue(layer);
        label_->setVisible(true);
        label_->update();
        nameShowing_ = true;
    } else {
        if (nameShowing_) {
            label_->setVisible(false);
            label_->update();
            nameShowing_ = false;
        }
    }

    GraphicsComponent::draw(dp, layer);
}

void PlayerGraphicsComponent::animate() {
    int pos;
    
    if (!isMoving_) {
        pixmapIndex_ = 0;
        setImgIndex(pixmapIndex_);
        return;
    }

    if (pixmapIndex_ == 0) {
	pos = rand() % 2 + 1;
        pos == 1 ? pixmapIndex_ = 0 : pixmapIndex_ = 3;
    }
    
    if (!(animateCount_++ % animateMod_)) {
        ++pixmapIndex_ >= PIX_PLAYER_MAX ? pixmapIndex_ = 1 : pixmapIndex_;
        setImgIndex(pixmapIndex_);
    }
}

void PlayerGraphicsComponent::initPixmaps() {
    label_ = new QGraphicsTextItem(nickname_);
    resourcePixmapItem_ = new QGraphicsPixmapItem();
    resourcePixmapItem_->setVisible(false);
    CDriver::instance()->getMainWindow()->getScene()->addItem(resourcePixmapItem_);


    label_->setDefaultTextColor (QColor(0,255,0));
    CDriver::instance()->getMainWindow()->getScene()->addItem(label_);
    label_->setVisible(false);

    if (pixmapImgs_) {
        return;
    } else {
        pixmapImgs_ = new QPixmap[PIX_PLAYER_MAX + PIX_RESOURCE_MAX];
    }
    int random = ((rand() % 700) / 100) + 1;

    pixmapIndex_ = 0;
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_0(random);
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_1(random);
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_2(random);
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_3(random);
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_4(random);
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_5(random);
    pixmapImgs_[pixmapIndex_++] = PIX_PLAYER_6(random);
    pixmapImgs_[pixmapIndex_++] = PIX_ICON_WOOD;
    pixmapImgs_[pixmapIndex_++] = PIX_ICON_STONE;
    pixmapImgs_[pixmapIndex_++] = PIX_ICON_BONE;
    pixmapImgs_[pixmapIndex_++] = PIX_ICON_TAR;
    pixmapIndex_ = 0;
}

void PlayerGraphicsComponent::setCurrentResource(int resourceType) {
    resourceType_ = resourceType;
}

} /* end namespace td */
