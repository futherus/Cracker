#include <unistd.h>
#include "crackwidget_GUI.h"
#include "cracker.h"
#include "mainwindow_GUI.h"
#include "util.h"

// ----------------------------------------------------------------------
CrackWidget::CrackWidget(QWidget *parent)
    : QWidget{parent}
{
    crackButton = new QPushButton("Crack");                     // setup submitting crack button
    QObject::connect(crackButton, SIGNAL(clicked()),
                     this,        SLOT(slotCallCrack())
                    );

    copyCheck = new QCheckBox("Create cracked copy");           // setup checkbox for copying
    copyCheck->setObjectName("copyCheck");
    QPalette pal;
    pal.setColor(copyCheck->foregroundRole(), Qt::white);
    copyCheck->setPalette(pal);
    QObject::connect(copyCheck, SIGNAL(stateChanged(int)),
                     this,      SLOT(slotCopyField())
                    );

    chmodCheck = new QCheckBox("Set '777' permission");         // setup checkbox for permissions
    chmodCheck->setObjectName("chmodCheck");
    pal.setColor(chmodCheck->foregroundRole(), Qt::white);
    chmodCheck->setPalette(pal);

    QLabel* fileLabel = new QLabel("File:");                    // setup fields for filenames
    fileName = new QLineEdit;
    fileName->setMaxLength(BUFSIZ - 1);
    QLabel* copyLabel = new QLabel("Copy:");
    copyName = new QLineEdit;
    copyName->setEnabled(false);
    copyName->setMaxLength(BUFSIZ - 1);

    QGridLayout* namesLayout = new QGridLayout;                 // apply layouts
    namesLayout->addWidget(fileLabel, 0, 0);
    namesLayout->addWidget(fileName, 0, 1);
    namesLayout->addWidget(copyLabel, 1, 0);
    namesLayout->addWidget(copyName, 1, 1);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->setSpacing(15);
    buttonLayout->addWidget(crackButton);

    QVBoxLayout* wgtLayout = new QVBoxLayout;
    wgtLayout->addLayout(namesLayout);
    wgtLayout->addWidget(copyCheck);
    wgtLayout->addWidget(chmodCheck);
    wgtLayout->addLayout(buttonLayout, Qt::AlignCenter);

    setLayout(wgtLayout);
}

// ----------------------------------------------------------------------
void CrackWidget::slotCallCrack()
{
    this->setDisabled(true);                                    // disable widget after submitting button

    QByteArray filename = fileName->text().toLatin1();          // extract filenames
    QByteArray copyname = copyName->text().toLatin1();
    MainWindow* par = (MainWindow*) parent();

    const char* file_ptr = filename.constData();
    int err = 0;

    par->setMessage("Cracking started...");

    if(filename.isEmpty())
    {
        par->setMessage("Enter filename");
        qWarning("Filename not specified");
        emit resetCrack();
        return;
    }

    if(copyCheck->isChecked())                                  // maintain copying if needed
    {
        if(copyname.isEmpty())
        {
            par->setMessage("Enter copy filename");
            qWarning("Copyname not specified");
            emit resetCrack();
            return;
        }

        err = copy_file(filename.constData(), copyname.constData());
        if(err)
        {
            par->setMessage("Copying failed");
            qWarning("Copying failed");
            emit resetCrack();
            return;
        }

        file_ptr = copyname.constData();
    }

    if(chmodCheck->isChecked())                                 // maintain permissions change if needed
    {
        err = chmod(file_ptr, "777");
        if(err)
        {
            par->setMessage("Changing permission failed");
            qWarning("Changing permission failed");
            emit resetCrack();
            return;
        }
    }

    err = crack(file_ptr);                                      // crack file
    if(err == 1)
    {
        par->setMessage("Already cracked");
        return;
    }
    else if(err != 0)
    {
        par->setMessage("Crack failed");
        qWarning("Crack failed");
        emit resetCrack();
        return;
    }

    emit startCrack();

    return;
}

// ----------------------------------------------------------------------
void CrackWidget::slotCopyField()
{
    copyName->setEnabled(copyCheck->isChecked());
}
