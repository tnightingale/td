#ifndef PROJECTILEGRAPHICSCOMPONENT_H
#define PROJECTILEGRAPHICSCOMPONENT_H

#include <QObject>
#include <QPainter>
#include <QPointF>
#include "GraphicsComponent.h"

namespace td {

class ProjectileGraphicsComponent : public GraphicsComponent {
    Q_OBJECT

public:
    /**
     * Instantiates a projectile graphics component
     * @author Warren Voelkl
     */
    ProjectileGraphicsComponent();
    virtual ~ProjectileGraphicsComponent();

    /**
     * Loads a structure from the item and game component class then sends
     * the structure to the generic draw slot in GraphicsComponent.
     *
     * @author Warren Voelkl
     */
    virtual void update(GameObject* obj);

    /**
     * Gets a pixmap for the object based on its current animation state.
     *
     * @author Warren Voelkl
     */
    virtual void initPixmaps() = 0;

    /**
     * @returns the pixmap array from the current graphics object
     * @author Warren Voelkl
     */
    virtual QPixmap * getPixmapArray() = 0;

protected:
    QPointF pos_;
    float scale_;
    int degrees_;
};

} /* end namespace td */

#endif

