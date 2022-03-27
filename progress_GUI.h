#ifndef PROGRESS_GUI_H
#define PROGRESS_GUI_H

#include <QWidget>

class QProgressBar;

// ----------------------------------------------------------------------
const int PROGRESS_RANGE = 1000;

// ----------------------------------------------------------------------
class Progress : public QWidget {
    Q_OBJECT
private:
    QProgressBar* bar;
    int           value;
    int           timerID;

public:
    Progress(QWidget* pobj = 0);

protected:
    void timerEvent(QTimerEvent *event);    // updating progressbar with time

public slots:
    void slotStartProgress();               // start progressbar
    void slotStepProgress ();               // for capturing 'step' button signal (e.g. button)
    void slotResetProgress();               // reset progressbar

signals:
    void endProgress();                     // signal after value = 100%
};

#endif // PROGRESS_GUI_H
