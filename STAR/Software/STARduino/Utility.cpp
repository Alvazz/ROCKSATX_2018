
#include "Utility.h"

uint32_t millis_epoch = 0;

uint32_t get_MET(){
/*
 * Calculates the current MET (mission elapsed time) from the 
 * mission epoch (which defaults to zero, but is resettable). 
 * 
 * Inputs: 
 * none
 * 
 * Output:
 * none
 * 
 * Return:
 * MET value
 * 
 */
  return millis() - millis_epoch;
}


bool time_for_cycle(uint32_t last_cycle_time){
/*
 * checks if 
 * 
 * Inputs: 
 * last_cycle_time - last time the cycle began
 * 
 * Output:
 * Boolean
 * 
 * Return:
 * Boolean indicating if it is time for the next cycle to start
 */
 return (get_MET() - last_cycle_time) > (1000/DESIRED_CYCLE_HZ);
}

void print_datestamp(File write_file, uint32_t time_millis){
/*
 * Prints a datestamp to a file.
 * 
 * Inputs: 
 * write_file - file to write to
 * time_millis - time to write
 * 
 * Output:
 * none
 * 
 * Return:
 * none
 * 
 */
 
  uint32_t nowMS = time_millis/1000;
  uint32_t h = nowMS / 3600;
  uint32_t m = nowMS % 3600 / 60;
  uint32_t s = nowMS % 3600 % 60;
  char buf[23];
  sprintf(buf, "%02d/%02d/%02dT%02d:%02d:%02d.%03d,", 0, 0, 0, h, m, s, time_millis%1000);  // print milliseconds);
  write_file.print(buf);
}

void set_epoch(){
/*
 * Resets the mission epoch.
 * 
 * Inputs: 
 * none
 * 
 * Output:
 * none
 * 
 * Return:
 * none
 * 
 */
  millis_epoch = millis();
}

void getFreeFilename(char *filename){

  int n = 0;
  
  snprintf(filename, sizeof(filename), "data%03d.csv", n); // includes a three-digit sequence number in the file name
  
  while(SD.exists(filename)) {
    n++;
    snprintf(filename, sizeof(filename), "data%03d.csv", n);
  }


}

