//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef __CARREFOUR_CODA_H_
#define __CARREFOUR_CODA_H_

#include <omnetpp.h>
#include <vector>
#include "Decisore.h"
#include "Customer.h"
using namespace omnetpp;

class Coda : public cSimpleModule
{
    //Vector that contains the waiting customers
    std::vector<cMessage*> customers;
    //The reference of our decisore that we use to choose the right tie
    Decisore *decisore;
    //Instance used to get the references of all the output ports
    cGate** gates;
    //Reference to the random number generator
    cMersenneTwister* rng;
    //Variable used for statistical purposes
    simsignal_t interarrivalSignal;
    simsignal_t queueingtimeSignal;
    simsignal_t queuelenghtSignal;
    simtime_t time_prec;
    int queuelenght;

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

};

#endif

