#ifndef MAINWINDOW_GUI_H
#define MAINWINDOW_GUI_H

#include <QtWidgets>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QSound>

#include "crackwidget_GUI.h"
#include "progress_GUI.h"

// ----------------------------------------------------------------------
class MainWindow : public QLabel
{
    Q_OBJECT

private:
    CrackWidget*  crack;                // crack options
    Progress*     progressbar;
    QPushButton*  quit;                 // quit button
    QMediaPlayer* player;
    QVideoWidget* video;
    QMovie*       mov;                  // background widget
    QLabel*       message;              // status message

public:
    explicit MainWindow(QApplication* app, QWidget* parent = nullptr);

    void setMessage(const QString &);   // change status message

public slots:
    void slotStart();                   // capturing start crack
    void slotEnd();                     // capturing progress end
    void slotReset();                   // capturing reset crack

signals:
    void start();                       // signal after capturing start crack
};

#endif // MAINWINDOW_GUI_H
