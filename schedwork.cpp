#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here

//
bool scheduleHelper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, 
DailySchedule& sched, vector<size_t>& workerShifts, size_t day, size_t slot);

bool isValid(const AvailabilityMatrix& avail, const size_t maxShifts, const DailySchedule& sched,
const vector<size_t>& workerShifts, size_t day, size_t slot, Worker_T workerId);
// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below


//create schedule matrix with the size
sched.resize(avail.size(), vector<Worker_T>(dailyNeed, INVALID_ID));

//tracks how many shifts assiigned for each worker
vector<size_t> workerShifts(avail[0].size(), 0);


return scheduleHelper(avail, dailyNeed, maxShifts, sched, workerShifts, 0, 0);



}

bool scheduleHelper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched,
vector<size_t>& workerShifts, size_t day, size_t slot){

    if(day >= avail.size()){
        return true;
    }

    if(slot>=dailyNeed){
        return scheduleHelper(avail, dailyNeed, maxShifts, sched, workerShifts, day+1, 0);
    }

    for(Worker_T workerId=0; workerId < avail[0].size(); workerId++){ //for each worker


        if(isValid(avail, maxShifts, sched, workerShifts, day, slot, workerId)){

            sched[day][slot] = workerId;//assign worker on the slot
            workerShifts[workerId]++; //shift counts increment

            if(scheduleHelper(avail, dailyNeed, maxShifts, sched, workerShifts, day, slot+1)){ //recursively try to fill
						
              return true;
            }

            sched[day][slot] = INVALID_ID; //if recursion didnt work, undoing assignments

            workerShifts[workerId]--;
        }
    }

    return false;
}

bool isValid(const AvailabilityMatrix& avail, const size_t maxShifts, const DailySchedule& sched, const vector<size_t>& workerShifts,
size_t day, size_t slot, Worker_T workerId){
//checks if it is valid to assinged to a worker to a given slot


    if(!avail[day][workerId]){ //worker is not available
        
        return false;
    }

    for(size_t i=0; i<slot; i++){ //worker is already scheduked

        if(sched[day][i]==workerId){

            return false;
        }
    }

    if(workerShifts[workerId] >= maxShifts){ //worker reaches max shifts
			
        return false;
    }

    return true; //else assiigned is valid
}

