#ifndef __BERKELEY_NODE_H_
#define __BERKELEY_NODE_H_
#include <vector>
#include <array>
#include <omnetpp.h>
#include <cmath>
#include "TimeResponse_m.h"
#include "Offset_m.h"
#include <string>

using namespace std;
using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Node : public cSimpleModule
{
  protected:
    int id;
    int master;
    double time;
    int simlength;
    double times[3600];
    int father;
    int used[1000][2];
    vector<int> children;
    int frequency;
    int totalUpdates;
    double stdDeviation;
    vector<array<double, 2>> allTimes;  //0: IDs, 1:times
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void start(double *times, int frequency = 0);
    virtual void tarrys(cMessage *msg);
    virtual void getAllTimes();
};

#endif
