#ifndef CRACKWIDGET_GUI_H
#define CRACKWIDGET_GUI_H

#include <QtWidgets>
#include <QWidget>

// ----------------------------------------------------------------------
class CrackWidget : public QWidget
{
    Q_OBJECT

private:
    QCheckBox*   chmodCheck;    // set file permissions
    QCheckBox*   copyCheck;     // copy file instead of overwriting
    QLineEdit*   copyName;      // name of file copy
    QLineEdit*   fileName;      // name of file
    QPushButton* crackButton;   // submit button

public:
    explicit CrackWidget(QWidget *parent = nullptr);

public slots:
    void slotCallCrack();       // capturing submit button
    void slotCopyField();       // enable/disable field for copy name

signals:
    void resetCrack();          // signal after crack failure
    void startCrack();          // signal after capturing submit button
};

#endif // CRACKWIDGET_GUI_H
