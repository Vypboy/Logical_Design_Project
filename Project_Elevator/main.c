#include "main.h"
// Noi khai bao hang so
#define     LED     PORTB
#define     LIGHT   PORTA
#define     RED_ON     4
#define     GREEN_ON   8
#define     YELLOW_ON   16
#define     RED_OFF     251
#define     GREEN_OFF   247
#define     YELLOW_OFF  239
#define     ON      1
#define     OFF     0

#define     INIT_SYSTEM        0
#define     ENTER_PASSWORD     1
#define     CHECK_PASSWORD     2
#define     CORRECT_PASSWORD   3
#define     WRONG_PASSWORD     4
#define     RUN_ELEVATOR       5
#define     SELECT_FLOOR       6
#define     ENTER_OLD_PASSWORD 7
#define     ENTER_NEW_PASSWORD 8
#define     CHANGE_PASSWORD    9
/////////////////////////////////////////////////////
#define SEG7_PORT 	PORTE
#define SEG7_PORT_OUT(x)         SEG7_PORT &= 0x00; SEG7_PORT |= (x);
#define BUZZER_PORT PORTD
#define BUZZER_PORT_OUT(x)      BUZZER_PORT = 0x0; BUZZER_PORT |= (x);



    int setfloor();   //set your destination by press the button from 0->9
    // set value of floor
    void Animation(int status1); //display up or down
    // check value of previous and the next value of floor
    void update_next_priority_floor();
    void run_Elevator();
    void DisplayStatus(int status);
    
//////////////////////////////////////////////////////


// Noi khai bao bien toan cuc
unsigned char arrayMapOfOutput [8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
unsigned char statusOutput[8] = {0,0,0,0,0,0,0,0};
// Khai bao cac ham co ban IO
void init_system(void);
void delay_ms(int value);
//Chuong trinh Password Door
//unsigned char arrayMapOfNumber [16] = {1,2,3,'A',4,5,6,'B',
//                                       7,8,9,'C','*',0,'E','D'};
unsigned char arrayMapOfNumber [16] ={0,1,2,3,4,5,6,7,8,9,'A','B','C','D','E','*'};
unsigned char arrayMapOfPassword [1][4]= {
  {1,2,3,4},
};
unsigned char arrayPassword[4];
unsigned char statusPassword = INIT_SYSTEM;
unsigned char statusElevator = INIT_SYSTEM;
unsigned char indexOfNumber = 0;
int timeDelay = 0;

void System_Elevator();
unsigned char CheckPassword();
void changePassword();
unsigned char isButtonNumber();
unsigned char isButtonNumber1();
unsigned char numberValue;
unsigned char numberPasswordIncorrect;
int chang_pass;
int control_print;
unsigned char isButtonEnter();
unsigned char isButtonEnter1();
void UnlockDoor();
void LockDoor();

#define     LIGHT_ON      1
#define     LIGHT_OFF     0
unsigned char isButtonLight();
unsigned char statusLight = LIGHT_OFF;
void LightOn();
void LightOff();
void BuzzerFunction(int status);
////////////////////////////////////////////////////////////////////
//Hien thuc cac chuong trinh con, ham, module, function duoi cho nay
////////////////////////////////////////////////////////////////////

void main(void)
{
	init_system();
	while (1)
	{
               
        // thuc hien cac cong viec duoi day         
        scan_key_matrix_update();  
        System_Elevator();
        DisplayLcdScreen();
	}
}

// Hien thuc cac module co ban cua chuong trinh
void delay_ms(int value)
{
	int i,j;
	for(i=0;i<value;i++)
		//for(j=0;j<238;j++);
        for(j=0;j<100;j++);
}

void init_system(void)
{
    PORTA = 0x0;
    PORTD = 0x00;
        TRISB = 0x00;		//setup PORTB is output
        TRISD = 0x00;
        TRISA = 0x0;
        init_lcd();
        LcdClearS();
//        LED = 0x00;
    
        init_interrupt();
        delay_ms(1000);
        //init_timer0(4695);//dinh thoi 1ms sai so 1%
//        init_timer1(9s390);//dinh thoi 2ms
        init_timer3(46950);//dinh thoi 10ms
//        init_timer3(9870);
        //SetTimer0_ms(100);
//        SetTimer1_ms(100);
        SetTimer3_ms(100); //Chu ky thuc hien viec xu ly input,proccess,output
        init_key_matrix();
}

void System_Elevator(){
    switch (statusElevator)
    {
        case INIT_SYSTEM:
            BuzzerFunction(0);
            indexOfNumber = 0;
            timeDelay = 0;
            chang_pass=0;
            control_print=0;
            numberPasswordIncorrect=0;
            LcdPrintStringS(0,0,"PRESS * TO OPEN ");
            LcdPrintStringS(1,0,"                ");
            if (isButtonEnter())
            {
                indexOfNumber = 0;
                timeDelay = 0;
                statusElevator = SELECT_FLOOR;
            }
            else if(setfloor()){
                SetTimer3_ms(WAITING_TIME);
                statusElevator=RUN_ELEVATOR;
            }
            break;
        case RUN_ELEVATOR:
            run_Elevator();
            if(isButtonEnter()){
                timeDelay = 0;
                statusElevator = SELECT_FLOOR;
            }
            break;
        case SELECT_FLOOR:
            DisplayStatus(2);
            LcdPrintStringS(0,0,"SELECT: 0 -> 9  ");
            LcdPrintStringS(1,0,"# TO CHANGE PASS");
            if(isButtonEnter1()){
                statusElevator=ENTER_PASSWORD;
                indexOfNumber=0;
                chang_pass=1;
                timeDelay=0;
            }
            if(isButtonNumber()){
                if(numberValue==9){
                    statusElevator=ENTER_PASSWORD;
                    control_print=0;
                    timeDelay=0;
                }
                else{
                    SetTimer3_ms(WAITING_TIME);
                    timeDelay=0;
                    flag_floor[numberValue]=1;
                    statusElevator=RUN_ELEVATOR;
                }
            }
            timeDelay++;
            if(timeDelay>=500)
                statusElevator=INIT_SYSTEM;
            break;
        case ENTER_PASSWORD:
            BuzzerFunction(0);
            if(chang_pass==0) LcdPrintStringS(0,0,"ENTER PASSWORD  ");
            if(chang_pass==1) LcdPrintStringS(0,0,"ENTER OLD PASS  ");
            if(control_print==0){
                LcdPrintStringS(1,0,"                ");
                indexOfNumber=0;
                control_print=1;
            }
            timeDelay ++;
            if (isButtonNumber1())
            {
                LcdPrintStringS(1,indexOfNumber,"*");
                arrayPassword [indexOfNumber] = numberValue;
                indexOfNumber ++;
                timeDelay = 0;
            }
            if (indexOfNumber >= 4)
                statusElevator = CHECK_PASSWORD;
            if (timeDelay >= 500)
                statusElevator = INIT_SYSTEM;
            break;
        case CHECK_PASSWORD:
            timeDelay = 0;
            if (CheckPassword())
                statusElevator = CORRECT_PASSWORD;
            else
                statusElevator = WRONG_PASSWORD;
            break;
        case CORRECT_PASSWORD:
            timeDelay ++;
            LcdPrintStringS(0,0,"PASSWORD CORRECT");
            //UnlockDoor();
            if (timeDelay == 200){
                timeDelay=0;
                if(chang_pass==0){
                    flag_floor[9]=1;
                    SetTimer3_ms(WAITING_TIME);
                    statusElevator = RUN_ELEVATOR;
                }
                if(chang_pass==1){
                    statusElevator=ENTER_NEW_PASSWORD;
                    indexOfNumber=0;
                    control_print=0;
                }
            }
            break;
        case WRONG_PASSWORD:
            BuzzerFunction(1);
            timeDelay ++;
            LcdPrintStringS(0,0,"PASSWORD WRONG  ");
            if (timeDelay == 200){
                numberPasswordIncorrect++;
                if(numberPasswordIncorrect>=3)
                    statusElevator=INIT_SYSTEM;
                else{
                    timeDelay=0;
                    statusElevator=ENTER_PASSWORD;
                    control_print=0;
                }
            }
            break;
        case ENTER_NEW_PASSWORD:
            LcdPrintStringS(0,0,"ENTER NEW PASS  ");
            if(control_print==0){
                LcdPrintStringS(1,0,"                ");
                indexOfNumber=0;
                control_print=1;
            }
            timeDelay ++;
            if (isButtonNumber1())
            {
                LcdPrintStringS(1,indexOfNumber,"*");
                arrayPassword [indexOfNumber] = numberValue;
                indexOfNumber ++;
                timeDelay = 0;
            }
            if (indexOfNumber >= 4)
                statusElevator = CHANGE_PASSWORD;
            if (timeDelay == 200)
                statusElevator = INIT_SYSTEM;
            break;
        case CHANGE_PASSWORD:
            LcdPrintStringS(0,0,"CHANGE PASSWORD ");
            LcdPrintStringS(1,0,"                ");
            changePassword();
            timeDelay++;
            if(timeDelay==200)
                statusElevator=INIT_SYSTEM;
            break;
        default:
            break;

    }
}

unsigned char CheckPassword()
{
    unsigned char i,j;
    unsigned result = 1;
    for (i=0;i<5;i++)
    {
        result = 1;
        for (j=0;j<4;j++)
        {
            if (arrayPassword[j] != arrayMapOfPassword[i][j])
                result = 0;
        }
        if (result == 1)
            return (i+1);
    }

}

void changePassword(){
    unsigned char i;
    for (i=0;i<4;i++)
    {
        arrayMapOfPassword[0][i]=arrayPassword[i];
    }
}
unsigned char isButtonNumber()
{
    unsigned char i;
    for (i = 0; i<=NO_OF_FLOOR-1; i++)
        if (key_code[i] == 1)
        {
            numberValue = arrayMapOfNumber[i];
            return 1;
        }
    return 0;
}

unsigned char isButtonNumber1(){
    unsigned char i;
    for (i = 0; i<=15; i++)
        if (key_code[i] == 1)
        {
            numberValue = arrayMapOfNumber[i];
            return 1;
        }
    return 0;
}

unsigned char isButtonEnter()
{
    if (key_code[14] == 1)
        return 1;
    else
        return 0;
}

unsigned char isButtonEnter1()
{
    if (key_code[15] == 1)
        return 1;
    else
        return 0;
}



////////////////////////////////////////////////////////////

void BuzzerFunction(int status){
    if(status==0) BUZZER_PORT &= (0x0);
    else BUZZER_PORT |= (0x1);
}

    //set your destination(if you're in Elevator) 
    //or request Elevator (if you're out Elevator 
    //and standing in this index's floor)
    //return false if there's no person press

    int setfloor(){
        int i;     
        for(i=0;i<NO_OF_FLOOR;i++){
            if(flag_floor[i]==1) return 1;
        }
        return 0;
    }
    void unsetfloor(){
        flag_floor[present_floor]=0;
    }
    
    void DisplayStatus(int status){
        if(status==0){
            //LIGHT&=0x0;
            LIGHT|=0x4;
        }
        if(status==1){
            //LIGHT&=0x0;
            LIGHT|=0x8;
        }
        if(status==2){
            //LIGHT&=0x0;
            LIGHT|=0x20;
        }
    }
    //display up or down
    void Animation(int status){
        LcdClearS();
        if(status==0){
            DisplayStatus(status);
            LcdPrintNumS(0, 0, present_floor);
            LcdPrintStringS(0, 2, "GO DOWN        ");
            LcdPrintStringS(1,0,"PRESS * TO OPEN");
            //LcdPrintNumS(0, 10, present_floor-1);
            //DisplayLcdScreen();
            //LcdPrintNumS(0, 10, present_floor);
        }
        else if(status==1){
            DisplayStatus(status);
            LcdPrintNumS(0, 0, present_floor);
            LcdPrintStringS(0, 2, "GO UP          ");
            LcdPrintStringS(1,0,"PRESS * TO OPEN");
            //LcdPrintNumS(0, 8, present_floor+1);
            //DisplayLcdScreen();
            //LcdPrintNumS(0, 8, present_floor);
        }
        else if(status==2){
            DisplayStatus(status);
            LcdPrintNumS(0, 0, present_floor);
            LcdPrintStringS(0,  2,  "WAITING        ");
            LcdPrintStringS(1,0,"PRESS * TO OPEN");
            //DisplayLcdScreen();
        }
    }

      
    //note:
    //case_down: dang di xuong thi uu tien ??n t?ng th?p nh?t
    // trên ???ng di chuy?n n?u có t?ng pr[i]=1 ta v?n m?(waiting)
    // nh?ng v?n gi? nguyên giá tr? next_floor
    //
    //case_up: t??ng t? khi ?i lên ?u tiên t?ng cao nh?t nh?ng
    // nh?ng case2 trên ???ng ?i lên ta ko ?oán t?ng có t?ng pr[i]=1 mà
    // ch? khi thang máy chuy?n sang case_down
    
    //update the value of next_floor   
    void update_next_priority_floor(){
        int i;
        switch(trend_moving){
            case DOWN_CASE:
                //xet tu duoi lên, tang thap nhat se la tang can tim 
                for(i=present_floor-1;i>=0;i--){
                    if(flag_floor[i]==1) {
                        if(status !=WAIT_CASE ) {
                            if(i!=present_floor-1) next_priority_floor=i; 
                        }
                        else next_priority_floor=i;
                        break;
                    }
                }
//                //if there is no people in lower floor pressing , change trend_moving
                if(next_priority_floor>=present_floor) trend_moving= UP_CASE;
                break;
            case UP_CASE:
                for(i=present_floor+1;i<NO_OF_FLOOR;i++){
                    if(flag_floor[i]==1) {
                        if(status !=WAIT_CASE) {
                            if(i!=present_floor+1) next_priority_floor=i;  
                        }
                        else next_priority_floor=i; 
                        
                        break;
                    }
                }
                if(next_priority_floor<=present_floor) trend_moving= DOWN_CASE;
                break;
            default:
                break;
        }                   
    }
     
    
    void run_Elevator(){   
        //setfloor();
        update_next_priority_floor();
        switch(status){
            case INIT:// Elevator is in floor 0
                Animation(WAIT_CASE);
                if(setfloor()==1){
                    SetTimer3_ms(WAITING_TIME);
                    trend_moving =UP_CASE;
                    status = WAIT_CASE;//to set the next_priority_floor
                }
                break;
            case DOWN_CASE:
                Animation(status);
                
                trend_moving=status;
                //chuyen trang thai
                /////////////////////////////////////
                if(flag_timer3==1){   
                    SetTimer3_ms(TRANSITION_TIME);
                    present_floor--;
                    status=DOWN_CASE; 
                }
//                if(flag_floor[present_floor]==1 
//                   || present_floor==next_priority_floor){
                if(present_floor==next_priority_floor){
                    SetTimer3_ms(WAITING_TIME);
                    status=WAIT_CASE;
                }                               
                ///////////////////////////////////
                break;
            case UP_CASE:
                Animation(status);
                
                trend_moving=status;
                //chuyen trang thai
                /////////////////////////////////////
                if(flag_timer3==1){    
                    SetTimer3_ms(TRANSITION_TIME);  
                    present_floor++;
                    status=UP_CASE; 
                }
                if(present_floor==next_priority_floor){
                    SetTimer3_ms(WAITING_TIME);
                    status=WAIT_CASE;
                }                               
                ///////////////////////////////////
                break;
            case WAIT_CASE://when Elevator come      
                Animation(status);
                unsetfloor();//erase flag of the present floor
                update_next_priority_floor();
                if(flag_timer3==1){
                    SetTimer3_ms(TRANSITION_TIME);
                    update_next_priority_floor();
                    if(present_floor<next_priority_floor){
                        //keep going down
                        status=UP_CASE;
                        trend_moving=UP_CASE;
                        
                    }
                    else if(present_floor>next_priority_floor){
                        status=DOWN_CASE;
                        trend_moving=DOWN_CASE;                        
                    }
                    else status=WAIT_CASE;
                }
                break;  
            default:
                break;
        }
        
    }
    
 