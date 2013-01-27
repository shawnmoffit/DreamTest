/*
 * CameraInterface.h
 *
 *  Created on: Mar 19, 2011
 *      Author: Shawn
 */


#ifndef CAMERAINTERFACE_H_  //Pre processor directive - if symbol is not defined do everything after
// the ifndef ...  "If it hasn't been defined, define it"  Protecting you from redefining your prototypes..
#define CAMERAINTERFACE_H_


void ImageCapture(int * ImageData);
//void ImageCapture();
void InitTAOS();

#endif /* CAMERAINTERFACE_H_ */
