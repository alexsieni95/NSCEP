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

#include "Cassa.h"

Define_Module(Cassa);
void Cassa::initialize()
{
    //Initializing the static parameters
    numeroCassa = 0;
    seed = 1;
    //Setting the identifier of the single Cassa
    numeroCassa = numeroCasse++;
    //Obtaining the reference to the module Decisore,to use its own methods
    this->decisore = check_and_cast<Decisore *> (getParentModule()->getModuleByPath("decisore"));
    //Setting the Cassa in idle state
    isWorking = false;
}

void Cassa::handleMessage(cMessage *msg)
{
    //If it's a selfMessage means that a service is completed
    if(msg->isSelfMessage()){
        //remove the customer from the Cassa
        customers.erase(customers.begin());
        //Inform the Decisore that one of its customer leaves
        decisore->ServiceComplete(this->numeroCassa);
        //Setting the cassa in idle state
        isWorking = false;
    }else{//otherwise a new client arrives in the Cassa
        //Debugging
        EV << "Mi e' arrivato un customer"<< endl;
        //Buffering the new client
        customers.push_back(msg);

    }
    //If there's at least one customer and the Cassa isn't in the idle state
    if(customers.size() > 0 && !isWorking){
        //schedule a self message that will occur @ random time generated by a seed
        //that is different for each message that arrives in all the Casse
        //in this case is used an exponential variable ----> in the future we'll need the lognormal case
        scheduleAt(simTime()+omnetpp::exponential(getRNG(seed++), 1/getParentModule()->par("mu").longValue()), customers[0]);
        //at this point the Cassa isn't idle anymore
        isWorking = true;
    }
}
