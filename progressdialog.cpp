#include "progressdialog.h"
#include "ui_progressdialog.h"
#include <QCloseEvent>

// ProgressDialog

ProgressDialog::ProgressDialog(const QString &title, QWidget *parent) :
    QProgressDialog(parent),
    ui(new Ui::ProgressDialog)
{
    ui->setupUi(this);
    setWindowTitle(title);
}

ProgressDialog::~ProgressDialog()
{
    delete ui;
    delete messageBox;
}

void ProgressDialog::setETA(int seconds)
{
    static const QString eta = tr("Estimated time of arrival: ");
    static const QString hour = tr(" hours");
    static const QString min = tr(" minuts");
    static const QString sec = tr(" seconds");

}

QProgressBar * ProgressDialog::progressBar()
{
    return ui->progressBar;
}

void ProgressDialog::closeEvent(QCloseEvent *event)
{
    if (ProgressMessageBox::question(this, tr("Cancel?"), tr("Are you sure you want to cancel and leave progress?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
        emit progressAborted();
        event->accept();
    }
    else
        event->ignore();
}

// ProgressMessageBox

ProgressMessageBox::ProgressMessageBox(Icon icon, const QString &title, const QString &text, StandardButtons buttons, QWidget *parent) :
    QMessageBox(icon,title,text,buttons,parent) {}

QMessageBox::StandardButton ProgressMessageBox::question(ProgressDialog *parent, const QString &title, const QString &text, StandardButtons buttons, StandardButton defaultButton)
{
    parent->messageBox = new ProgressMessageBox(Question,title,text,buttons,parent);
    parent->messageBox->setDefaultButton(defaultButton);
    return static_cast<StandardButton> (parent->messageBox->exec());
}
