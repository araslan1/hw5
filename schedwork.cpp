#ifndef RECCHECK
#include <set>
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

bool solve(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, size_t row, size_t col); 
bool isValid(DailySchedule& sched, size_t row, size_t col, size_t num_of_workers, const size_t maxShifts, size_t curr_col); 
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
    //initialize sched to invalid ids
    for (size_t i = 0; i < avail.size(); i++){
        vector<Worker_T> my_vec(dailyNeed, -1); 
        sched.push_back(my_vec);             
    }
    return solve(avail, dailyNeed, maxShifts, sched, 0, 0); 
}


bool solve(
    const AvailabilityMatrix& avail, 
    const size_t dailyNeed, 
    const size_t maxShifts, 
    DailySchedule& sched, 
    size_t row, size_t col
)
{
    //get number of days to be scheduled
    size_t n_days = avail.size();
    size_t number_of_workers = avail[0].size();
    // if we filled the schedule, return true
    if (row == n_days){
        return true; 
    }
    // if we have filled a day, go to next day
    if (col == dailyNeed){
        row += 1; 
        col = 0; 
    }

    // iterate through options
    // i < number of of workers
    for (size_t i = 0; i < number_of_workers ; i++){
        //loop through each worker, if a worker is available on this day add them to schedule
        if (row == n_days){
          return true; 
        }
        if (avail[row][i] == 1){
            sched[row][col] = i; 
            if (isValid(sched, row, dailyNeed, number_of_workers, maxShifts, col)){
                int col_ = col + 1; 
                if (col == dailyNeed){
                    row += 1; 
                    col = 0; 
                    col_ = 0;
                }
    
                if (solve(avail, dailyNeed, maxShifts, sched, row, col_)){
                    return true; 
                }
            }
            sched[row][col] = -1; 
        }
    }

    return false; 
}


bool isValid(DailySchedule& sched, size_t row, size_t col, size_t num_of_workers, const size_t maxShifts, size_t curr_col){
    //check if maxshifts for each worker have been exceeded 
    vector<int> counter(num_of_workers, 0); 
    int curr_id = sched[row][curr_col]; 
    for (size_t i = 0; i <= row; i++){
      for (size_t j = 0; j < col; j++){
        if(sched[i][j] != -1){
          counter[sched[i][j]] += 1; 
          if (counter[sched[i][j]] > maxShifts){
            return false; 
          }
          if (i == row && i < curr_col){
            if (sched[row][i] == curr_id) return false; 
          }
        }
      }
    }
    return true;
}
