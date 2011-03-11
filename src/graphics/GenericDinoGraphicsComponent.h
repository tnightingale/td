#ifndef TOWERGRAPHICSCOMPONENT_H
#define TOWERGRAPHICSCOMPONENT_H

#include <QObject>
#include <QPainter>
#include <QPointF>
#include "NPCGraphicsComponent.h"
#include "GraphicsComponent.h"


namespace td {

    class GenericDinoGraphicsComponent :public GraphicsComponent {//: public NPCGraphicsComponent {
    Q_OBJECT

public:
    /**
     * Instantiates a GenericDino graphics component
     * @author Warren Voelkl
     */
    GenericDinoGraphicsComponent();
    virtual ~GenericDinoGraphicsComponent();

    /**
     * Gets a pixmap for the object based on its current animation state.
     *
     * @author Warren Voelkl
     */
    virtual void initPixmaps();

    /**
     * The primary method used to determine the behaviours of animation
     *
     * @author Warren Voelkl
     */
    virtual void animate();

private:
    static QPixmap * pixmapImgs_;

    /**
     * @returns the pixmap array from the subclasses
     */
    virtual QPixmap * getPixmapArray();

};

} /* end namespace td */

#endif

