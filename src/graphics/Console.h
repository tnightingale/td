#ifndef _console_
#define _console_

#include <QObject>
#include <QMutex>
#include <QVector>
#include <QString>
#include <QGraphicsTextItem>
#include "../util/mutex_magic.h"

namespace td {

class Console : public QObject {
    Q_OBJECT

    THREAD_SAFE_SINGLETON

private:
    
    /** The singleton instance */
    static Console* instance_;
    /** the text to be displayed */
    static QVector<QString> *display_;
    /** the label to display text */
    static QGraphicsTextItem *label_;

    explicit Console();
    ~Console();

public:

    /**
     * Creates the instance of the Console
     * shamelessly stolen from dpogue
     *
     * @author Terence Stenvold
     */
    static Console* instance() {
        mutex_.lock();
        if (instance_ == NULL) {
            instance_ = new Console();
        }
        mutex_.unlock();	
        return instance_;
    }
    
    /**
     * Adds strings of a proper length
     * to the output console
     *
     * @author Terence Stenvold
     * @param text to add to the console
     */
    void addText(QString text);

};

}

#endif