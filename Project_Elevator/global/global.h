/* 
 * File:   global.h
 * Author: ADMIN
 *
 * Created on October 16, 2022, 3:31 PM
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
#define TRANSITION_TIME 2000
#define WAITING_TIME 4000
    
extern int status;
extern int trend_moving;// for save previous value of status before status=WAIT_CASE
extern int present_floor; // the present floor that Elevator in
extern int next_priority_floor;    // this is not show the next floor Elevator will come,
                          // it shows the priority floor that Elavator is 
                          // tending to come
extern int flag_floor[NO_OF_FLOOR];// is 1 when have people press button
#ifdef	__cplusplus
}
#endif

#endif	/* GLOBAL_H */

