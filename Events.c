/* ###################################################################
**     Filename    : Events.c
**     Project     : Velocity_Control
**     Processor   : MKL25Z128VLK4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2021-04-19, 21:42, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MKL25Z128LK4]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  Hall_Effect_Sensor_OnCapture (module Events)
**
**     Component   :  Hall_Effect_Sensor [Capture]
**     Description :
**         This event is called on capturing of Timer/Counter actual
**         value (only when the component is enabled - <Enable> and the
**         events are enabled - <EnableEvent>.This event is available
**         only if a <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
static volatile int Start_Time = 0;
static volatile int Stop_Time = 0;
static volatile int count = 0;
static volatile double speed= 0;

//extern static volatile double speed;
//extern static volatile double avgSpeed;
//extern static volatile char speedFlag;

void Hall_Effect_Sensor_OnCapture(void)
{
  double arcLength = 2.0 * (3.14/2.0); //assuming 2 inches wheel radius, inches.
  if(Start_Time == 0){
	  Hall_Effect_Sensor_GetCaptureValue(&Start_Time);

  }
  else{
	  Hall_Effect_Sensor_GetCaptureValue(&Stop_Time);

	  if( Start_Time >= Stop_Time){
		  Stop_Time += (int)(0.400 / 163840.0);
	  }

	  //Calculate the current speed
	  double Delta_Time = (Stop_Time - Start_Time) / 163840.0; //Time in seconds
	  speed += arcLength / Delta_Time;

	  Start_Time = Stop_Time;

	  count++; //Increment count
  }


}

/*
** ===================================================================
**     Event       :  Main_Control_OnInterrupt (module Events)
**
**     Component   :  Main_Control [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Main_Control_OnInterrupt(void)
{
	static double desiredSpeed = 36.0; // inches per second
	static double speedCommand = 5000; //us
	const double Kp = 10.0;
	//Calculate the average speed of the wheels
	double avgSpeed = 0;
	avgSpeed = speed/count; // inches per second
	count = 0;
	speed = 0;

	//From Hall Effect Sensor, update the motor
	double Error = Kp * (avgSpeed - desiredSpeed);
	speedCommand += Error; //Larger command is a slower speed

	Motor_Control_SetDutyUS(speedCommand);

	//From line camera data, update the servo.

}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
