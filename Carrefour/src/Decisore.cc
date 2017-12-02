/*
 * Decisore.cpp
 *
 *  Created on: 30 nov 2017
 *      Author: elena
 */

#include "Decisore.h"

Decisore::Decisore() {

    //I get the number of ties acceding to the parent of this module,that in this case is the
    //network itself, and with the help of the method par(), i get the requestd parameter
    this->numerocasse = getParentModule().par("numerocasse");
    //I generate an array of integer with a length equal to the number of ties, because in position
    //is contained the number of person in queue who are waiting to be served at the i-tie
    clientiallacassa = new int[numerocasse];
    //At the beginning i set to 0 all the element of the array with the function memset. In this
    //function the third parameter is computed by the number of element of the array times tbe size
    //of a single element(in byte)
    memset(clientiallacassa,0,sizeof(int)*numerocasse);
  }

Decisore::~Decisore() {
    //Dealocating the array of ties
    delete[] this->clientiAllaCassa;
}
//This function is used to find what tie has ties has the minimum number of people who are waiting
//to be served. At the beginning we check the parameter who indicates the type of simulation we want to
//execute: ties with a common queue (case 1) or ties with own queue (case 2)
//Input parameter : parametro(int) - Is used to define which case we are simulating
//Output : int - The function return the index of the tie with the minimum number of element in queue,
//               and if the ties have only one element, the first free tie.If two or more ties has the same
//               element in queue,the function choose the till with the lowest index.


int Decisore::findlowest(int parametro){

    //Paramtro = 0 -> We want to operate with tills without each own single queue
    if(parametro == 0) {
    //I scroll all the tills
        for(int i = 0; i < this->numerocasse;i++)
            //I'm stop when the first free till is reached, because we want the nearest till, and after that
            //position is returned to the caller
            if(this->clientiAllaCassa[i] == 0)
                return i;
    }
    //Parametro = 1 -> We want to operate with tills who have each own queue
    else if(parametro == 1){
        //I'm applying the common algorithm to find the minimum value in the array, with the difference that
        //I want to store the relative index, because in the event of a tie I'll choose the smaller index
        int indice = 0;
        int minore = this->clientiallacassa[0];
        //I scroll all the tills
        for(int i = 1; i < this->numerocasse;i++){
            //I check if the actual value is lower or equal to the actual minimum
            if(this->clientiAllaCassa[i] <= minore){
                if(this->clientiAllaCassa[i] == minore)
                    //If are equal the algorithm chooses the smaller index
                    indice = (i < indice) ? i : indice;
            }
            else{
                //The algorithm set the next index and the new minimum values
                indice = i;
                minore = this->clientiAllaCassa[i];
            }
        }
        return i;
    }
    else
        //This return is to indicate that the passed parameter is not correct
        return -1;
}
//This function must find the right till for the new customer; once it was found it must we the correct time,
//because we want to simulate the time reach the till, and only after that time is elapsed our new customer
//is added to the queue
//Input parameter : parameter(int) - Is used to define which case we are simulating
//Output          : int            - In this implementation the function return the position of the till
int Decisore::newCustomer(int parameter){
    //Finding the right till
    int position = this->findlowest(parameter);
    //Retrieving the minimum delay
    double delay = getParentModule().par("delay");
    //Computing the delay by multiplying the delay with the index incremented by one (because the first till is in
    //position 0
    double waiting_time = delay*(position+1);
    //This function must simulate the time occurs to the customer to reach the right till once he know when he know to go
    wait(waiting_time);
    //Incrementing by one the number in queue at this till because now the customer is arrived
    this->clientiAllaCassa[position]++;
    return position;
}