#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QThread>

class Worker : public QObject {
    Q_OBJECT

public:
    Worker();
    ~Worker();

public slots:
    void process();
    void generations(int);
    void sleeps(int);

signals:
    void finished();
    void error(QString err);
    void updateLabel(QString);

private:
    // add your variables here
    int _generations;
    int _sleeps;

    void runGameOfLife();
};

#endif // WORKER_H
