/*
 * PID.h
 *
 *  Created on: Jun 9, 2011
 *      Author: B36745
 */

// PID portion only taken specifically from arm_math.h for PID Control

#ifndef PID_H_
#define PID_H_

#define __INLINE         inline   /*!< inline keyword for GNU Compiler       */
  /**
   * @brief 32-bit floating-point type definition.
   */
  typedef float float32_t;
  

  /**
   * @brief Instance structure for the floating-point PID Control.
   */
  typedef struct
  {
    float32_t A0;          /**< The derived gain, A0 = Kp + Ki + Kd . */
    float32_t A1;          /**< The derived gain, A1 = -Kp - 2Kd. */
    float32_t A2;          /**< The derived gain, A2 = Kd . */
    float32_t state[3];    /**< The state array of length 3. */
    float32_t Kp;               /**< The proportional gain. */
    float32_t Ki;               /**< The integral gain. */
    float32_t Kd;               /**< The derivative gain. */
  } arm_pid_instance_f32;
  
  

/**
  * @brief  Initialization function for the floating-point PID Control.
  * @param[in,out] *S      points to an instance of the PID structure.
  * @param[in]     resetStateFlag  flag to reset the state. 0 = no change in state 1 = reset the state.
  * @return none.
  */

 void arm_pid_init_f32(
			arm_pid_instance_f32 * S,
			int32_t resetStateFlag);

 /**
  * @brief  Reset function for the floating-point PID Control.
  * @param[in,out] *S is an instance of the floating-point PID Control structure
  * @return none
  */
 //void arm_pid_reset_f32(
			// arm_pid_instance_f32 * S);

 

 /**
   * @ingroup groupController
   */

  /**
   * @defgroup PID PID Motor Control
   *
   * A Proportional Integral Derivative (PID) controller is a generic feedback control 
   * loop mechanism widely used in industrial control systems.
   * A PID controller is the most commonly used type of feedback controller.
   *
   * This set of functions implements (PID) controllers
   * for Q15, Q31, and floating-point data types.  The functions operate on a single sample
   * of data and each call to the function returns a single processed value.
   * <code>S</code> points to an instance of the PID control data structure.  <code>in</code>
   * is the input sample value. The functions return the output value.
   *
   * \par Algorithm:
   * <pre>
   *    y[n] = y[n-1] + A0 * x[n] + A1 * x[n-1] + A2 * x[n-2]
   *    A0 = Kp + Ki + Kd
   *    A1 = (-Kp ) - (2 * Kd )
   *    A2 = Kd  </pre>
   *
   * \par
   * where \c Kp is proportional constant, \c Ki is Integral constant and \c Kd is Derivative constant
   * 
   * \par 
   * \image html PID.gif "Proportional Integral Derivative Controller" 
   *
   * \par
   * The PID controller calculates an "error" value as the difference between
   * the measured output and the reference input.
   * The controller attempts to minimize the error by adjusting the process control inputs.  
   * The proportional value determines the reaction to the current error, 
   * the integral value determines the reaction based on the sum of recent errors, 
   * and the derivative value determines the reaction based on the rate at which the error has been changing.
   *
   * \par Instance Structure 
   * The Gains A0, A1, A2 and state variables for a PID controller are stored together in an instance data structure. 
   * A separate instance structure must be defined for each PID Controller. 
   * There are separate instance structure declarations for each of the 3 supported data types. 
   * 
   * \par Reset Functions 
   * There is also an associated reset function for each data type which clears the state array. 
   *
   * \par Initialization Functions 
   * There is also an associated initialization function for each data type. 
   * The initialization function performs the following operations: 
   * - Initializes the Gains A0, A1, A2 from Kp,Ki, Kd gains.
   * - Zeros out the values in the state buffer.   
   * 
   * \par 
   * Instance structure cannot be placed into a const data section and it is recommended to use the initialization function. 
   *
   * \par Fixed-Point Behavior 
   * Care must be taken when using the fixed-point versions of the PID Controller functions. 
   * In particular, the overflow and saturation behavior of the accumulator used in each function must be considered. 
   * Refer to the function specific documentation below for usage guidelines. 
   */

  /**
   * @addtogroup PID
   * @{
   */

  /**
   * @brief  Process function for the floating-point PID Control.
   * @param[in,out] *S is an instance of the floating-point PID Control structure
   * @param[in] in input sample to process
   * @return out processed output sample.
   */


  static __INLINE float32_t arm_pid_f32(
					arm_pid_instance_f32 * S,
					float32_t in)
  {
    float32_t out;

    /* y[n] = y[n-1] + A0 * x[n] + A1 * x[n-1] + A2 * x[n-2]  */
    out = (S->A0 * in) +
      (S->A1 * S->state[0]) + (S->A2 * S->state[1]) + (S->state[2]);

    /* Update state */
    S->state[1] = S->state[0];
    S->state[0] = in;
    S->state[2] = out;

    /* return to application */
    return (out);

  }

#endif /* PID_H_ */
