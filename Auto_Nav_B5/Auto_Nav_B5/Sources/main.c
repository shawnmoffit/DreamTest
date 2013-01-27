#include "SystemHeaders.h"


float Scale_Motor = 1;  // setting for motor.. 
float MotorPwm = 50; 
char lost_count = 0;
float Actual_Line_Position = 64.0;
float Servo_Angle_Translation = 45.0;
float Desired_Line_Angle = 45.0;
float Error = 0.0;
float NewServoAngle = 45.0;

float line_change_threshold;
int intensity_threshold = 17;

//variables used for line recovery
int found = 0;

//PID variables
float Proportional_Gain = 1.22;// / was 1.15 
float Integral_Gain = 0.0; // 0.013 works
float Derivative_Gain = 0;//was at .8 works
int nolinetick = 0;
int min_max_count = 0;


arm_pid_instance_f32 Steer;
line_scan_instance Line;

main(void){

    int i;
    int z;
    int pot;
    float Temp;
    InitClock();
    InitK40GPIO();
    InitSysTick();  //printf("LED Example with interrupts \n\r");
    InitADCs();
    Init_PWM_Servo ();
    InitMotorPWM();
    PWM_Servo_Angle (45);
    
    /*create an instance of the PID Structure to store the steering PID Data
	 * set the proportional, integral and derivative gains
	 * initialize the PID
	 * reset to known state
	*/
	
	//tune proportional gain by slowly increasing by factor of 10	
	Steer.Kp = Proportional_Gain;// set proportional Gain  (at motor setting 50, use 1)
	
	//tune integral gain by slowly increasing by a factor of 1
	Steer.Ki = Integral_Gain;// set integral Gain
	
	//tune derivative gain by slowly increasing by a factor of 1 
	Steer.Kd = Derivative_Gain;// set derivative Gain
		
	arm_pid_init_f32(&Steer,1);//initialize the pid
	arm_pid_reset_f32(&Steer); //reset the pid     
    LineDetect_init(&Line);
	
    for(;;)
    {
    	//pot = ReadADCChannel(20);
        /********* begin working algorithm code  *******/
        //add a separate timer tick here if we want to control speed of this... 
        
        
    	if(ImageCaptureTick>10)		
    	{
    		ImageCaptureTick = 0;
    		ImageCapture(&Line.RawCameraData[0]);//point to the first element in the array
    		LineDetect(&Line);
    	}
    	//PWM_Servo_Angle(((float)(ReadADCChannel(20))/255.0)*90.0);
    	
    	if(ServoTickVar>0)
    	{
    		ServoTickVar = 0;
    	
    		Steer.Kp = ((float)(ReadADCChannel(20))/255.0) *2;
    		arm_pid_init_f32(&Steer,0);
    		
    		if(Line.LineFound == 1)
    		  {
				MotorPwm = Scale_Motor * 85; //80 works
				 ;
				
				//Temp Line.FilterLineLoc - 64
				
				Servo_Angle_Translation = (45 -(((Line.FilterLineLoc)/128.0)*90.0));
							
				//Desired_Line_Angle = 45.0;  // "Reference Input for PID"
				//Error = Servo_Angle_Translation - Desired_Line_Angle;
				
				//Servo_Angle_Translation = (((Line.FilterLineLoc)/128.0)*90.0));
									
				
				NewServoAngle = arm_pid_f32(&Steer,Servo_Angle_Translation);
				
				NewServoAngle +=45;
				
				// limit the control response to the Maximum/Min Possible steering Value	
				if (NewServoAngle >= 90.0)
				{
					NewServoAngle=90.0;
				}
				else if (NewServoAngle <=0.0)
				{
					NewServoAngle=0.0;
				}
				
				PWM_Servo_Angle (NewServoAngle);  
				lost_count = 0;
				}
    		
    		 else
    		  {
    			 if (lost_count>50)
    			{
    				 SetMotorPWM(50);
    			}
    			 else{
    				 lost_count++;
    				 SetMotorPWM(70); 
    			 }
    		  }	
    		
    	}
	}

    
return 0;   
}
