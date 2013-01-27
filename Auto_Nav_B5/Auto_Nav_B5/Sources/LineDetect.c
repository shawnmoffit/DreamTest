
#include "SystemHeaders.h"

void FindMax(int *Data,int *value,int *location);
void FindMin(int *Data,int *value,int *location);

/*This function, when given camera data - returns the center of the line
 * as an integer index value between 0 and 127
 * it also stores the min, max value locations, as well as minimum and maximum
 * actual values of intensity
 * the function also acts as a memory storage mechanism for history 
 * previous 8 values 
 */

void LineDetect_init(
			line_scan_instance * L
			)
{
  /*set initial values of ... */
  memset(L->RawCameraData,255 , 128u * sizeof(unsigned char)); 
  memset(L->derivative_data,0, 128*sizeof(int));
  L->derivative_max_value =0;
  L->derivative_max_location = 64;
  L->derivative_min_value =0;
  L->derivative_min_location = 64;
  L->LineFound = 0;
}



//Double Check accessing this properly
void LineDetect (line_scan_instance * L)
{
	int z,i;
	int iline;
	
	
	//Calculate derivative of the line
	for(z=0;z<128;z++)//derive raw data for line calculations
	{
		//begin case for derivative data
		if (z==0)
		{
			L->derivative_data[z] = 0;			
		}
		//calculate, imin, imax (register values of max and minimum intensity values)
		else	
		{
			L->derivative_data[z]=L->RawCameraData[z]-L->RawCameraData[z-1];  
		}
	}
	
	FindMax(&(L->derivative_data[0]),&(L->derivative_max_value),&(L->derivative_max_location));
	FindMin(&(L->derivative_data[0]),&(L->derivative_min_value),&(L->derivative_min_location));
	
	if(L->derivative_min_value<-5 &  L->derivative_max_value>5 &&
	   L->derivative_min_location < L->derivative_max_location)		
	{
		L->LineFound = 1;
		L->RawLineLocation = (L->derivative_max_location + L->derivative_min_location)/2;
		
		
		//Implement Running Average Filter
		L->LineLocIndex++;
		if(L->LineLocIndex>3)
		{
			L->LineLocIndex = 0;
		}
		
		L->LineLocBuff[L->LineLocIndex] = L->RawLineLocation;
		L->FilterLineLoc = 0;
		for(i=0;i<4;i++)
		{
			L->FilterLineLoc+= L->LineLocBuff[i];
		}
		L->FilterLineLoc = L->FilterLineLoc/4;
	}
	else
	{
		L->LineFound = 0;
	}
}
	

void FindMax(int *Data,int *value,int *location)
{
	int i;
	int TempMax=-255;
	int TempLoc = 64;
	
	for(i=0;i<128;i++)
	{
		if(Data[i] > TempMax)
		{
			TempMax = Data[i];
			TempLoc = i;
		}
	}

	*value = TempMax;
	*location = TempLoc;
}

void FindMin(int *Data,int *value,int *location)
{
	int i;
	int TempMin=255;
	int TempLoc = 64;
	
	for(i=0;i<128;i++)
	{
		if(Data[i]<TempMin)
		{
			TempMin = Data[i];
			TempLoc = i;
		}
	}

	*value = TempMin;
	*location = TempLoc;
}











/******************************Andy's old code************************
int LineDetect (unsigned char cam_data_raw[]){
	int i;
	unsigned char min = 255;
	int mins = 255;
	for(i=0; i<127;i++){
		if(cam_data_raw[i] <= min){
			mins = i;
		}
	return mins;
	}
}
*/
/*	
	//in order to normalize the data we must find the max and min
	//Then we can scale it from 0 to 1
	unsigned char raw_max;
	unsigned char raw_min;
	
	//Magnatude of the part in question
	signed char drop = 0;
	signed char rise = 0;
	
	//Thresholding for drop and rise
	signed char drop_threshold = .01;
	double rise_threshold = .01;
	
	//boolean values to say if the drop has been found
	int dropFound = 0;
	int riseFound = 0;

	int line_Position;
	double max_camera_value = 0;
	int cam_data_norm[127];
	
	//For the for loops :)
	int i;

	//obtains data from camera and puts it into array cam_data_Raw
	raw_max = cam_data_raw[0];
	raw_min = cam_data_raw[0];
	
	//Normalize the data
	//	1. Find the Max and Min points from the raw data
	//	2. Apply the equation to put all values between 0 and 1.
	
	for(i=0; i<127; i++){
		if(cam_data_raw[i] > raw_max){
			raw_max = cam_data_raw[i];
		}
		if(cam_data_raw[i] < raw_min){
			raw_min = cam_data_raw[i];
		}
	}
	for(i=0; i<127;i++){
		cam_data_norm[i] = (cam_data_raw[i]-raw_min)/(raw_max-raw_min);
	}


	//Line detection

	//Find the drop in magnitude.  this is accomplished by the following
	//1.	using a sliding window (Think tcp packet window) it takes the difference between
	//	each point. when sucessful this will result in a negative number 
	//2.		
	while(dropFound == 0){
		for(i=0; i<127; i++){
			drop = 	(cam_data_norm[i+1]-cam_data_norm[i])+
				(cam_data_norm[i+2]-cam_data_norm[i+1]);

			

			
			if(drop >= drop_threshold){
				dropFound = 1;
				drop = i;
			}
		}
	}
	//search for largest rise in magnitude and store it
	while(riseFound == 0){
		for(i=0; i<127; i++){
			rise = 	(cam_data_norm[i+1]-cam_data_norm[i]);
					(cam_data_norm[i+2]-cam_data_norm[i+1]);
				
					

			
			if(rise > rise_threshold){
				riseFound = 1;
				rise = i;
			}
		}
	}
	
	//measure distance between 
	line_Position = (rise+drop)/2;
	return line_Position;
	
	*/


/*	EXTRa stuf
	//take derrivative of data d/dx(cam_data_norm)
	int data_derivative[128];
	//find d/dx for i+1 	
	for(int i=1;i<128;i++){
		//looks at dx before and after the point that is being considered.
		//averages the pre and post to get an averaged dx.
		pre_dx  = cam_data_norm[i]-cam_data_norm[i-1];
		post_dx = cam_data_norm[i]-cam_data_norm[i+1]; 
		data_derivative[i] = (pre_dx+post_dx)/2;
	}
*/

/*				(cam_data_norm[i+3]-cam_data_norm[i+2])+
				(cam_data_norm[i+4]-cam_data_norm[i+3])+
				(cam_data_norm[i+5]-cam_data_norm[i+4])+
				(cam_data_norm[i+6]-cam_data_norm[i+5])+
				(cam_data_norm[i+7]-cam_data_norm[i+6])+
				(cam_data_norm[i+8]-cam_data_norm[i+7])+
				(cam_data_norm[i+9]-cam_data_norm[i+8])+
				(cam_data_norm[i+10]-cam_data_norm[i+9])+
				(cam_data_norm[i+11]-cam_data_norm[i+10])+
				(cam_data_norm[i+12]-cam_data_norm[i+11])+
				(cam_data_norm[i+13]-cam_data_norm[i+12])+
				(cam_data_norm[i+14]-cam_data_norm[i+13])+
				(cam_data_norm[i+15]-cam_data_norm[i+14])*/

/*(cam_data_norm[i+3]-cam_data_norm[i+2])+
(cam_data_norm[i+4]-cam_data_norm[i+3])+
(cam_data_norm[i+5]-cam_data_norm[i+4])+
(cam_data_norm[i+6]-cam_data_norm[i+5])+
(cam_data_norm[i+7]-cam_data_norm[i+6])+
(cam_data_norm[i+8]-cam_data_norm[i+7])+
(cam_data_norm[i+9]-cam_data_norm[i+8])+
(cam_data_norm[i+10]-cam_data_norm[i+9])+
(cam_data_norm[i+11]-cam_data_norm[i+10])+
(cam_data_norm[i+12]-cam_data_norm[i+11])+
(cam_data_norm[i+13]-cam_data_norm[i+12])+
(cam_data_norm[i+14]-cam_data_norm[i+13])+
(cam_data_norm[i+15]-cam_data_norm[i+14])*/

