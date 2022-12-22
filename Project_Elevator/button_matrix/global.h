/* 
 * File:   global.h
 * Author: ACER
 *
 * Created on December 8, 2022, 5:25 PM
 */

#ifndef GLOBAL_H
#define	GLOBAL_H

#ifdef	__cplusplus
extern "C" {
#endif

#define INIT      4
#define DOWN_CASE 0
#define UP_CASE   1
#define WAIT_CASE 2
    
#define NO_OF_FLOOR 10
extern int status;
extern int trend_moving;// for save previous value of status before status=WAIT_CASE
extern int present_floor; // the present floor that Elevator in
extern int next_priority_floor;    // this is not show the next floor Elevator will come,
                          // it shows the priority floor that Elavator is 
                          // tending to come
extern int flag_floor[NO_OF_FLOOR];// is 1 when have people press button


/////////////////////////////
#define TRANSITION_TIME 1000
#define WAITING_TIME 1000






//    void setfloor(int index);   //set your destination 
//    // set value of floor
//    void Animation(int status1); //display up or down
//    // check value of previous and the next value of floor
//    int typefloor(int floor);  //check type of floor ,input is order of floor
//    // give 0/1
//       
//    void priority(); // input is all signal from floors
//    //check floor[MAX] to give the priority order for Elevator
//    
//    int comparison(int x);   // comparison with the near Elevator, input is
//                            // value of near present_floor
//    // comparison the present floor with the near present_floor
//    int checkweight(float x); //the average of 1 person is 60Kg then check the 
//                             // quantity of people in Elevator
//    // give 0/1 
//    /////////////////////////////////////////////////////////////////////
//    void warning();
//    // depend on value of typefloor() and checkweight()...
//    void trouble(); // check time between 2 floors and ...
//    // use another timer to check time and give warning
//    void control_time(); // check if don't have anyone go in, elevator will go up/down
//    // count time waiting -> warning and Elevator will go#define INIT      4
#define DOWN_CASE 0
#define UP_CASE   1
#define WAIT_CASE 2
    
#define NO_OF_FLOOR 10
extern int status;
extern int trend_moving;// for save previous value of status before status=WAIT_CASE
extern int present_floor; // the present floor that Elevator in
extern int next_priority_floor;    // this is not show the next floor Elevator will come,
                          // it shows the priority floor that Elavator is 
                          // tending to come
extern int flag_floor[NO_OF_FLOOR];// is 1 when have people press button


/////////////////////////////
#define TRANSITION_TIME 1000
#define WAITING_TIME 1000






//    void setfloor(int index);   //set your destination 
//    // set value of floor
//    void Animation(int status1); //display up or down
//    // check value of previous and the next value of floor
//    int typefloor(int floor);  //check type of floor ,input is order of floor
//    // give 0/1
//       
//    void priority(); // input is all signal from floors
//    //check floor[MAX] to give the priority order for Elevator
//    
//    int comparison(int x);   // comparison with the near Elevator, input is
//                            // value of near present_floor
//    // comparison the present floor with the near present_floor
//    int checkweight(float x); //the average of 1 person is 60Kg then check the 
//                             // quantity of people in Elevator
//    // give 0/1 
//    /////////////////////////////////////////////////////////////////////
//    void warning();
//    // depend on value of typefloor() and checkweight()...
//    void trouble(); // check time between 2 floors and ...
//    // use another timer to check time and give warning
//    void control_time(); // check if don't have anyone go in, elevator will go up/down
//    // count time waiting -> warning and Elevator will go


#ifdef	__cplusplus
}
#endif

#endif	/* GLOBAL_H */

