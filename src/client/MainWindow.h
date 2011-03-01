#ifndef MainWindow_H
#define MainWindow_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include "../graphics/DrawParams.h"

class GraphicsComponent;

namespace td {
class MainWindow : public QMainWindow {
    Q_OBJECT

private:

    MainWindow();
    virtual ~MainWindow();
    
    /**
     * The single instance of this class that can be created.
     */
    static MainWindow* instance_;
    
    /**
     * The graphics scene which contains all the objects
     */
    QGraphicsScene* scene_;

    /**
     * The view which displays the graphics scene.
     */
    QGraphicsView* view_;

public:
    /**
     * Creates an instance of the class if one doesn't exist yet.
     *
     * @author Dean Morin
     * @returns An new instance of the class if one doesn't exist yet, or
     * if one does, it returns a pointer to that instance.
     */
    static MainWindow* init();
   
    /**
     * Returns the instance of this Singleton class. Should only be used if
     * you know that init() has already been called.
     *
     * @author Dean Morin
     * @returns A pointer to the one available instance of this class.
     */
    static MainWindow* instance() {
        return instance_;
    }
    
    QGraphicsScene* getScene() { return scene_; }
    
protected:
    virtual bool event(QEvent*);
    
    /**
     * Deals with keyboard presses. Arrow keys are handled elsewhere.
     *
     * @author Dean Morin
     * @param event The key press event.
     */
    virtual void keyPressEvent(QKeyEvent * event);
    virtual void keyReleaseEvent(QKeyEvent *);

public slots:
    /**
     * Calls the graphics objects initfunction
     * Which loads all pixmap images then draws the object
     * offscreen.
     *
     * @author Darryl Pogue
     * @author Warren Voelkl
     * @param gc The GraphicsComponent of the game object.
     */
    void createGraphicRepr(GraphicsComponent* gc);

    /**
     * Draws the graphical representation of the game object.
     *
     * @author Darryl Pogue
     * @param gc The GraphicsComponent of the game object.
     */
    void drawItem(DrawParams* dp, GraphicsComponent* gc);
    void animateItem(GraphicsComponent* gc);
    
signals:
    void signalKeyPressed(int);
    void signalKeyReleased(int);
    void signalNumberPressed(int);
    void signalSpacebarPressed();
    void signalFPressed();
};

} /* end namespace td */

#endif
