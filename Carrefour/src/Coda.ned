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

package carrefour;

//
// TODO auto-generated module
//
simple Coda
{
    parameters:
        int casse;
        @signal[Interarrivals](type = simtime_t);
        @signal[Queuing](type = simtime_t);
        @signal[QueueLenght](type = long);
        @statistic[1_Lambda](title="1/lambda";source=Interarrivals;record=mean,vector,min,max); 
        @statistic[E_W](title="E[W]";source=Queuing;record=mean,vector,min,max);
        @statistic[E_Nq](title="E[Nq]";source=QueueLenght;record=mean,vector,min,max); 
    gates : 
        input in[casse];
        output out[casse];
}
