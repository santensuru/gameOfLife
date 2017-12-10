#include "worker.h"
#include "world.h"

using namespace gameOfLife;

// --- CONSTRUCTOR ---
Worker::Worker() {
    // you could copy data from constructor arguments to internal variables here.
}

// --- DECONSTRUCTOR ---
Worker::~Worker() {
    // free resources
}

// --- PROCESS ---
// Start processing data.
void Worker::process() {
    // allocate resources using new here

    //qDebug("Thread Started!");
    runGameOfLife();
    //qDebug("Thread Finished!");

    emit finished();
}

void Worker::generations(int generations)
{
    _generations = generations;
}

void Worker::sleeps(int sleeps)
{
    _sleeps = sleeps;
}

void Worker::runGameOfLife()
{
    World _newWorld;
    _newWorld.generate();
    //_newWorld.printStates(false);

    //ui->output->setText(_newWorld.printStatesToString(false));
    emit updateLabel(_newWorld.printStatesToString(false));

    int i=0;
    for (;;)
    {
        //std::cout << i+1 << ")" << std::endl;
        _newWorld.update(i % 2 == 0);
        //_newWorld.printStates(i % 2 == 0);

        //ui->output->setText(_newWorld.printStatesToString(i % 2 == 0));
        emit updateLabel(_newWorld.printStatesToString(i % 2 == 0));

        i++;

        if (i==_generations)
        {
            break;
        }

        QThread::msleep(_sleeps);
    }
}
