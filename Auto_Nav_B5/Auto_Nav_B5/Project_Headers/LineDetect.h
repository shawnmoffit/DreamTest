

#ifndef LINEDETECT_H_
#define LINEDETECT_H_



 /**
   * @brief Instance structure for the floating-point PID Control.
   */
  typedef struct
  {
    int	 RawCameraData[128]; // not sure if this will work
    int  derivative_data[128];
    int  derivative_max_value;
    int  derivative_min_value;
    int  derivative_max_location;
    int  derivative_min_location;
    int LineFound;
    int RawLineLocation;
   
    int LineLocBuff[8];
    int LineLocIndex;
    int FilterLineLoc;
    
    
  } line_scan_instance;
 
/**
  * @brief  Initialization function for the line detect algorithm.
  * @param[in,out] *S      points to an instance of the line structure.
  * @param[in]     resetStateFlag  flag to reset the state. 0 = no change in state 1 = reset the state.
  * @return none.
  */

 void LineDetect_init(
			line_scan_instance * L
		     ); 
  
/*a bit confused if this has to be actually defined here... when I 
 * created a .c file for my pid - it didn't work, had to put function in PID.h*/  
void LineDetect(line_scan_instance * L);
					
//int LineDetect (unsigned char * CameraData);



#endif /* LINEDETECT_H_ */
