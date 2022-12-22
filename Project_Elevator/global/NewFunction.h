#ifndef NEWFUNCTION_H
#define	NEWFUNCTION_H
//#include "..\timer\timer.h"
#include "..\global\global.h"
//#include "..\lcd\lcd.h"

#ifdef	__cplusplus
extern "C" {
#endif
    void setfloor(int);   //set your destination 
    // set value of floor
    void Animation(int); //display up or down
    // check value of previous and the next value of floor
    int typefloor(int);  //check type of floor ,input is order of floor
    // give 0/1
       
    //void priority(); // input is all signal from floors
    //check floor[MAX] to give the priority order for Elevator
    
    int comparison(int);   // comparison with the near Elevator, input is
                            // value of near present_floor
    // comparison the present floor with the near present_floor
    int checkweight(float); //the average of 1 person is 60Kg then check the 
                             // quantity of people in Elevator
    // give 0/1 
    /////////////////////////////////////////////////////////////////////
    void warning();
    // depend on value of typefloor() and checkweight()...
    void trouble(); // check time between 2 floors and ...
    // use another timer to check time and give warning
    void control_time(); // check if don't have anyone go in, elevator will go up/down
    // count time waiting -> warning and Elevator will go

#ifdef	__cplusplus
}
#endif
#endif	/* NEWFUNCTION_H */
