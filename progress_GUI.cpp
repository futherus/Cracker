#include <QtWidgets>
#include "progress_GUI.h"

// ----------------------------------------------------------------------
Progress::Progress(QWidget* pwgt/*= 0*/)
    : QWidget(pwgt)
    , value(0)
    , timerID(-1)
{
    bar = new QProgressBar;                                     // setup QProgressBar
    bar->setInvertedAppearance(true);
    QPalette pal;
    bar->setPalette(pal);
    //bar->setOrientation(Qt::Vertical);
    bar->setRange(0, PROGRESS_RANGE);
    //bar->setMinimumWidth(200);
    bar->setAlignment(Qt::AlignCenter);

    QPushButton* pcmdStep  = new QPushButton("&Help");          // setup 'step'  button (increases value of progressbar)
    QPushButton* pcmdReset = new QPushButton("&Satisfaction");  // setup 'reset' button (resets value to 0)

    QObject::connect(pcmdStep,  SIGNAL(clicked()), SLOT(slotStepProgress()));
    QObject::connect(pcmdReset, SIGNAL(clicked()), SLOT(slotResetProgress()));

    QVBoxLayout* pvbxLayout = new QVBoxLayout;                  // setup layout
    QHBoxLayout* phbxLayout = new QHBoxLayout;

    phbxLayout->addWidget(pcmdStep);
    phbxLayout->addWidget(pcmdReset);
    pvbxLayout->addWidget(bar);
    pvbxLayout->addLayout(phbxLayout);

    setLayout(pvbxLayout);
}

// ----------------------------------------------------------------------
void Progress::timerEvent(QTimerEvent*)
{
    if(value >= PROGRESS_RANGE)
    {
        killTimer(timerID);
        timerID = -1;
        emit endProgress();
        return;
    }

    bar->setValue(++value);
}

// ----------------------------------------------------------------------
void Progress::slotStartProgress()
{
    if(timerID != -1)
        killTimer(timerID);

    timerID = startTimer(100);
}

// ----------------------------------------------------------------------
void Progress::slotStepProgress()
{
    value += 5;
    bar->setValue(value);
}

// ----------------------------------------------------------------------
void Progress::slotResetProgress()
{
    value = 0;
    bar->reset();
}
