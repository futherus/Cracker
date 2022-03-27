#include "mainwindow_GUI.h"


// ----------------------------------------------------------------------
MainWindow::MainWindow(QApplication* app, QWidget *parent)
    : QLabel{parent}
{
    mov = new QMovie(":/background.gif");                       // setup background widget
    mov->start();
    mov->setPaused(true);

    setMovie(mov);
    setFixedSize(mov->frameRect().size());
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    player = new QMediaPlayer(this);                            // setup player
    video = new QVideoWidget;
    player->setVideoOutput(video);

    QUrl url = QUrl("qrc:///video.mp4");
    QMediaPlaylist* playlist = new QMediaPlaylist;
    playlist->addMedia(url);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    player->setPlaylist(playlist);

    video->setFixedSize(320, 180);
    //qDebug() << player->state();

    crack        = new CrackWidget;
    progressbar  = new Progress;
    quit         = new QPushButton("Quit");
    message      = new QLabel("...");

    QObject::connect(crack      , SIGNAL(startCrack()),         // setup connections
                     this       , SLOT  (slotStart())
                    );
    QObject::connect(crack      , SIGNAL(resetCrack()),
                     this       , SLOT  (slotReset())
                    );
    QObject::connect(this       , SIGNAL(start()),
                     progressbar, SLOT  (slotStartProgress())
                    );
    QObject::connect(progressbar, SIGNAL(endProgress()),
                     this       , SLOT  (slotEnd())
                    );
    QObject::connect(quit       , SIGNAL(clicked()),
                     app        , SLOT(quit())
                    );

    progressbar->setEnabled(false);

    QGridLayout* layout = new QGridLayout;                      // setup layouts
    layout->addWidget(crack, 0, 0, Qt::AlignLeft);
    layout->addWidget(video, 0, 1, Qt::AlignCenter);
    layout->addWidget(message, 1, 0, Qt::AlignLeft);
    video->hide();
    layout->addWidget(progressbar, 2, 0, 1, 1);
    layout->addWidget(quit, 2, 1);

    setLayout(layout);
}

// ----------------------------------------------------------------------
void MainWindow::slotStart()
{
    progressbar->setEnabled(true);
    quit->setEnabled(false);
    crack->setEnabled(false);
    mov->setPaused(false);
    video->show();
    player->play();
    //qDebug() << player->state();

    emit start();
}

// ----------------------------------------------------------------------
void MainWindow::slotEnd()
{
    quit->setEnabled(true);
    progressbar->setEnabled(false);
    mov->setPaused(true);
    message->setText("Patched successfully");
    //qDebug() << player->state();
}

// ----------------------------------------------------------------------
void MainWindow::slotReset()
{
    quit->setEnabled(true);
    progressbar->setEnabled(false);
    mov->setPaused(true);
    crack->setEnabled(true);
}

// ----------------------------------------------------------------------
void MainWindow::setMessage(const QString& str)
{
    message->setText(str);
}

