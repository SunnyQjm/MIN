#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ndnrtcdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnShowNdnRtc_clicked()
{
    NDNRtcDialog ndnRtcWindow;
    ndnRtcWindow.exec();
}
