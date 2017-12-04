#ifndef __CARREFOUR_CASSA_H_
#define __CARREFOUR_CASSA_H_

#include <omnetpp.h>
#include <vector>
#include "Decisore.h"
using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Cassa : public cSimpleModule
{
private:
    static int numeroCasse;
    static int seed;
    int numeroCassa;
    //The reference of our decisore that we use to choose the right tie
    Decisore *decisore;
    //This attribute indicates if tills is working or in idle at the moment
    bool isWorking;
    std::vector<cMessage*> customers;
 protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    //Method used to know if this till are actually working, and used by the module "Cassa".
 public:
    Cassa(){
        numeroCasse = 0;
        seed = 1;
    }
};

#endif
