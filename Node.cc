#include "Node.h"

Define_Module(Node);

using namespace std;

void Node::initialize()
{
    this->id = par("id");
    this->simlength = par("simlength");
    this->master = 0;
    this->time = 0;
    this->father = -1;
    //times table to help scheduling time updates
    for(int i = 0; i < this->simlength; i++){
        this->times[i] = this->time + i;
    }
    // initialize the used array for the tarry's algorithm
    for(int i = 0; i < this->gateSize("g"); i++){
            cGate *gate = this->gate("g$o", i);
            cModule *nextGateOwner = gate->getNextGate()->getOwnerModule();
            this->used[i][0] = int(nextGateOwner->par("id"));
            this->used[i][1] = 0;
        }
    if(id == 0){
        // initialize the master variables
        this->frequency = par("frequency");
        this->totalUpdates = 0;
        this->master = 1;
        this->father = id;
        this->stdDeviation = 0;
        cMessage *msg = new cMessage("token");
        scheduleAt(simTime(), msg->dup());
        delete msg;
    }
}


void Node::handleMessage(cMessage *msg)
{
    if(strcmp(msg->getName(), "update") == 0){
        this->time += intuniform(0,100)/100.0;
        if(this->master == 1){
            // every {frequency} updates send a request for all node times
            this->totalUpdates += 1;
            if(this->totalUpdates % this->frequency == 0){
                Node::getAllTimes();
            }
            if(this->totalUpdates == this->simlength){
                cMessage *dummy = new cMessage("");
                int totalMessages = dummy->getTotalMessageCount() - 1 - int(this->par("totalNodes"))*this->simlength;
                FILE *nodes;
                string name = "messagesFile_nodes_" + to_string(int(this->par("totalNodes"))) + ".txt";
                nodes = fopen(name.c_str(), "a");
                fprintf(nodes, "%s", (to_string(totalMessages)+ "\n").c_str());
                fclose(nodes);
                delete dummy;
            }
        }
        delete msg;
    }
    else if(strcmp(msg->getName(), "token") == 0){
        // on token run tarry's
        tarrys(msg->dup());
        delete msg;
    }
    else if(strcmp(msg->getName(), "imYourChild") == 0){
        // update child id vector
        this->children.push_back(int(msg->getSenderModule()->par("id")));
        delete msg;
    }
    else if(strcmp(msg->getName(), "gimmeTime") == 0){
        // respond with time to father and pass the request to children
        for (int i : this->children){
            for (int j = 0; j < this->gateSize("g"); j++){
                if(int(gate("g$o",j)->getPathEndGate()->getOwnerModule()->par("id")) == i){
                    send(msg->dup(), gate("g$o", j));
                }
            }
        }
        TimeResponse *response = new TimeResponse("myTime");
        double idTime[2]= {double(this->id), this->time};
        response->setNodeIdTime(0, idTime[0]);
        response->setNodeIdTime(1, idTime[1]);
        for(int i = 0; i < this->gateSize("g"); i++){
            if(int(gate("g$o", i)->getPathEndGate()->getOwnerModule()->par("id")) == this->father){
                send(response->dup(), gate("g$o", i));
                break;
            }
        }
        delete msg;
        delete response;
    }
    else if((strcmp(msg->getName(), "myTime") == 0) && (this->master == 0) ){
        // pass the timestamp response to the father
        for(int i = 0; i < this->gateSize("g"); i++){
            if(int(gate("g$o", i)->getPathEndGate()->getOwnerModule()->par("id")) == this->father){
                send(msg->dup(), gate("g$o", i));
                delete msg;
                break;
            }
        }
    }
    else if(strcmp(msg->getName(), "myTime") == 0){
        // update the time response messages vector
        TimeResponse *response = (TimeResponse*)msg;
        double idTime[2] = {response->getNodeIdTime(0), response->getNodeIdTime(1)};
        this->allTimes.push_back(array<double, 2> {idTime[0], idTime[1]});
        delete response;
        if(this->allTimes.size() == int(this->par("totalNodes")) - 1){
            // on all response gathered :
            this->allTimes.push_back(array<double, 2> {double(this->id), this->time}); // add master time and id
            double sum = 0;
            double n = this->allTimes.size();
            double* themtimes = new double[int(this->par("totalNodes"))]; // all timestamps array
            for(int i = 0; i<int(n); i++){
                themtimes[i] = this->allTimes[i][1];
            }
            for(int i = 0; i < int(n); i++){
                sum += themtimes[i]; // get the sum
            }
            double mean = sum/n; // calculate the mean value
            sum = 0;
            for(int i = 0; i < int(n); i++){
                sum += pow(themtimes[i] - mean, 2);
            }
            double variance = sum/(n-1); // calculate the variance
            this->stdDeviation = sqrt(variance); // calculate the deviation
            /*FILE *deviation;
            string name = "deviationFile_frequency_" + to_string(int(this->par("frequency"))) + ".txt";
            deviation = fopen(name.c_str(), "a");
            fprintf(deviation, "%s", (to_string(stdDeviation)+ "\n").c_str()); //record the deviation on each offset update in the deviation file
            fclose(deviation);*/
            sum = 0;
            int j = 0;
            for(int i = 0; i < int(n); i++){
                if(abs(themtimes[i]-mean) < 2*this->stdDeviation){
                    sum += themtimes[i];
                    j += 1;
                }
            }
            delete[] themtimes;
            mean = sum/j; // mean value ignoring the timestamps with more than two standard deviation offsets from the mean value
            double offset = 0;
            Offset* theOffset = new Offset("offset");
            theOffset->setIdArraySize((unsigned int)n+1);
            theOffset->setOffsetArraySize((unsigned int)n+1);
            // calculate the time offsets
            for(int i = 0; i < int(n); i++){
                offset = mean - this->allTimes[i][1];
                theOffset->setId(i, this->allTimes[i][0]);
                theOffset->setOffset(i, offset);
                EV<<"id: "<< this->allTimes[i][0] << "  offset: " << offset << "\n" ;
                if(this->allTimes[i][0] == this->id){
                   // uppdate masters'time
                   this->time += mean - this->allTimes[i][1];
                }
            }
            // send offset messages to all children
            for(int k: children){
                for(j = 0; j < this->gateSize("g"); j++){
                    if(int(gate("g$o", j)->getPathEndGate()->getOwnerModule()->par("id")) == k){
                        send(theOffset->dup(), gate("g$o", j));
                    }
                }
            }
            delete theOffset;
            this->allTimes.clear();
        }
    }
    else if(strcmp(msg->getName(), "offset") == 0){
        Offset* theOffset = (Offset*)msg;
        vector<int> ids;
        vector<double> gottenTimes;
        // synchronize using the gotten offset for this->id
        for(int i = 0; i < int(this->par("totalNodes")); i++){
            ids.push_back(theOffset->getId(i));
            gottenTimes.push_back(theOffset->getOffset(i));
            if(ids.back() == this->id){
                this->time += gottenTimes.back();
            }
        }
        // pass the offset message all children
        for(int i: children){
            for(int j = 0; j< this->gateSize("g"); j++){
                if(int(gate("g$o", j)->getPathEndGate()->getOwnerModule()->par("id")) == i){
                    send(theOffset->dup(), gate("g$o", j));
                }
            }
        }
        delete theOffset;
    }
}


void Node::start(double *times, int frequency){
    // start the main algorithm
    cMessage *msg = new cMessage("update");
    for(int i = 0; i < int(simlength); i++){
        scheduleAt(times[i], msg->dup());
    }
    delete msg;
}

void Node::getAllTimes(){
    // send getTime requests to all children
    bubble("Im getting them times");
    cMessage *getTimes = new cMessage("gimmeTime");
    for(int i : this->children){
        for(int j = 0; j < this->gateSize("g"); j++){
            if(int(gate("g$o",j)->getPathEndGate()->getOwnerModule()->par("id")) == i){
                send(getTimes->dup(), gate("g$o", j));
            }
        }
    }
    delete getTimes;
}


void Node::tarrys(cMessage *msg){
    // run the tarry's algorithm to make a path for requests and answers
    // if the node has no father, make the sender its father, tell him you are his child
    if(this->father == -1){
        EV<<"I got no father\n";
        cModule *sender = msg->getSenderModule();
        this->father = int(sender->par("id"));
        cMessage *setChild = new cMessage("imYourChild");
        for(int i = 0; i < this->gateSize("g"); i++){
            if(int(gate("g$o",i)->getPathEndGate()->getOwnerModule()->par("id")) == this->father){
                send(setChild->dup(), gate("g$o", i));
                delete setChild;
                break;
            }
        }
    }

    int checker = 0;
    vector<int> notUsed;
    int i;
    //check if there are nodes that have not been visited
    for(i = 0; i < this->gateSize("g"); i++){
        if(used[i][1] == 0){
            if(used[i][0] != this->father){
                notUsed.push_back(used[i][0]);
            }
            checker = 1;
        }
    }
    // if no, finish
    if(checker == 0){
        Node::start(times);
        delete msg;
    }
    //if the node can reply only to the father, he replies to father and finishes
    else if (notUsed.size() == 0){
        EV<<notUsed.size()<<"\n";
        EV<<"I am replying to my father";
        for(i = 0; i < this->gateSize("g"); i++){
            if(used[i][0] == this->father){
                used[i][1] = 1;
                int j;
                for(j = 0; j < this->gateSize("g"); j++){
                    if(int(gate("g$o",i)->getPathEndGate()->getOwnerModule()->par("id")) == this->father){
                        send(msg->dup(), gate("g$o", i));
                        delete msg;
                        break;
                    }
                }
                notUsed.clear();
                Node::start(times);
            }
        }
    }
    //else the node chooses one of his neighbors that he did not send a message
    else{
        int chosenId = notUsed[intuniform(0, notUsed.size()-1)];
        EV<<"chosen id :"<<chosenId<<"\n"<<notUsed.size()<<"\n";
        for(i = 0; i < this->gateSize("g"); i++){
            if(int(gate("g$o",i)->getPathEndGate()->getOwnerModule()->par("id")) == chosenId){
                send(msg->dup(), gate("g$o", i));
                delete msg;
                int j;
                for(j = 0; j < this->gateSize("g"); j++){
                    if(used[j][0]==chosenId){
                        used[j][1] = 1;
                        break;
                    }
                }
                break;
            }
        }
        notUsed.clear();
    }
}
