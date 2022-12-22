#include "global.h"

int present_floor=0;
int next_priority_floor=0;
int flag_floor[NO_OF_FLOOR]={0,0,0,0,0,0,0,0,0,0};
int status=INIT;
int trend_moving=UP_CASE;
/////////////////////////////////



/////////////////////////////////
//    //set your destination 
//    void setfloor(int index){
//        priority[index]=1;
//    }
//    
//    //display up or down
//    //void Animation(bool x){
//    void Animation(int status1){
//        LcdClearS();
//        LcdPrintNumS(0, 0, present_floor);
//        if(status1==0){
//            LcdPrintStringS(0, 2, "go down");
//            LcdPrintNumS(0, 10, present_floor-1);
//        }
//        else if(status1==1){
//            LcdPrintStringS(0, 2, "go up");
//            LcdPrintNumS(0, 8, present_floor+1);
//        }
//        else if(status1==2){
//            LcdPrintStringS(0,  2,  "waiting");
//        }
//        DisplayLcdScreen();
//    } 
//    
//    //check type of floor ,input is order of floor
//   // bool typefloor(int x){
//    int typefloor(int floor){
//        if(floor==9) return 1;
//        return 0;
//    }  
//
//    
//    // input is all signal from floors
//    
//    void priority(){
//        int index;
//        status=-1;
//        for(index=present_floor;index<11;index++){
//            if(priority[index] && present_floor < index && status==1){
//                status=0; break;
//            }
//        }  
//    } 
//    
//     // comparison with the near Elevator
//   // bool comparison(int){
//    
//    int comparison(int x){
//        
//    } 
//    
//    //the average of 1 person is 60Kg then check the 
//    // quantity of people in Elevator
//    //bool checkweight(float){
//    int checkweight(float x){
//        
//    } 
//    
//    
//    void warning(){
//        
//    }
//    // check time between 2 floors and ...
//    void trouble(){
//    
//    } 
//    
//    // check if don't have anyone go in, elevator will go up/down
//    void control_time()
//    {
//        
//    } 
