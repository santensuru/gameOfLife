#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    ui->graphicsView;
//    ui->pushButton;

    // Connect button signal to appropriate slot
    connect(ui->start, SIGNAL (released()), this, SLOT (handleButton()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateLabel(QString text)
{
    ui->output->setText(text);
}

void MainWindow::errorString(QString error)
{
    qDebug(error.toLatin1());
}

void MainWindow::enableButton()
{
    ui->input->setDisabled(false);
    ui->start->setDisabled(false);
    ui->delay->setDisabled(false);
}

void MainWindow::handleButton()
{
    QString text = ui->input->toPlainText();
    int generations = text.toInt();

    int sleeps = ui->delay->value();
    ui->input->setDisabled(true);
    ui->start->setDisabled(true);
    ui->delay->setDisabled(true);

    QThread* thread = new QThread;
    Worker* worker = new Worker();
    worker->moveToThread(thread);
    connect(worker, SIGNAL(updateLabel(QString)), this, SLOT(updateLabel(QString)));
    connect(worker, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
    connect(thread, SIGNAL(started()), worker, SLOT(process()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), this, SLOT(enableButton()));
    worker->generations(generations);
    worker->sleeps(sleeps);
    thread->start();
}

