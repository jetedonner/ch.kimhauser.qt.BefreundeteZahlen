#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QtCore/qmath.h>

class Worker : public QObject {
    Q_OBJECT

public:
    Worker(int _nFrom, int _nTo);
    ~Worker();
    void exit();

public slots:
    void process();

signals:
    void finished();
    void error(QString err);
    void numberFound(int nNumber1, int nNumber2);
    void numberProcessed(int nStart, int nEnd, int  nNumber);

private:
    int nFrom;
    int nTo;
    QList<int> *list;
    int calcSum(int nNum);
    bool bAbort;

};

#endif // WORKER_H
