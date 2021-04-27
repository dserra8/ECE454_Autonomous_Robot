/* ###################################################################
**     Filename    : Events.c
**     Project     : LineCamera2
**     Processor   : MKL25Z128VLK4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2021-04-23, 23:17, # CodeGen: 0
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
**     Event       :  AS1_OnError (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS1_OnError(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AS1_OnRxChar (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS1_OnRxChar(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AS1_OnTxChar (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS1_OnTxChar(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  CLK_OnEnd (module Events)
**
**     Component   :  CLK [PWM]
**     Description :
**         This event is called when the specified number of cycles has
**         been generated. (Only when the component is enabled -
**         <Enable> and the events are enabled - <EnableEvent>). The
**         event is available only when the <Interrupt service/event>
**         property is enabled and selected peripheral supports
**         appropriate interrupt.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
static volatile int counter = 0;
static volatile int init = 0;
static volatile int startUp = 1;
extern volatile uint16_t cameraOutput[128];

void CLK_OnEnd(void)
{

	if(counter == 2 && startUp == 1){
		init = 1;
	}
	else if(counter < 128 && init == 0 && startUp == 0){
			A0_Measure(0);
		  }
	else if(counter >= 128 && startUp == 0 && init == 0){
			init = 1;
			counter = 0;
			startUp = 1;
			char a = 10;
			AS1_SendChar(a);
			a = 13;
			AS1_SendChar(a);

		}
	counter++;

}

/*
** ===================================================================
**     Event       :  A0_OnEnd (module Events)
**
**     Component   :  A0 [ADC]
**     Description :
**         This event is called after the measurement (which consists
**         of <1 or more conversions>) is/are finished.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void A0_OnEnd(void)
{
	uint16_t value = 0;
	char v = 'd';
	A0_GetValue16(&value);
	value = value/(65535/5);
	if(value < 2){
		cameraOutput[counter] = 0;
	}
	else if(value >= 2 && value < 6){
		cameraOutput[counter] = 1;
	}

	v = cameraOutput[counter] + 48;


	AS1_SendChar(v);
}

/*
** ===================================================================
**     Event       :  A0_OnCalibrationEnd (module Events)
**
**     Component   :  A0 [ADC]
**     Description :
**         This event is called when the calibration has been finished.
**         User should check if the calibration pass or fail by
**         Calibration status method./nThis event is enabled only if
**         the <Interrupt service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void A0_OnCalibrationEnd(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  SI_CLK_OnInterrupt (module Events)
**
**     Component   :  SI_CLK [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
static volatile int pulse = 0;
void SI_CLK_OnInterrupt(void)
{
	if(init == 1 && counter >= 2)
	{
		if(pulse == 0)
		{
			SI_SetVal(SI_Init);
		}
		else{
			counter = 0;
			init = 0;
			pulse = 0;
			startUp = 0;
			SI_ClrVal(SI_Init);
			return;
		}
		pulse++;
	}
}

/*
** ===================================================================
**     Event       :  TI1_OnInterrupt (module Events)
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

static volatile int time = 0;
static volatile int timePast = 0;
static volatile double yPast = 0;
static volatile double y = 0;
static volatile int counter2 = 0;

void TI1_OnInterrupt(void)
{

	//Motor Control

//	//Desired Speed
//	static double desiredSpeed = 36.0;
//	static double speedCommand = 5000;
//
//	//Motor Control Constant
//	const double Kp = 10.0;
//
//	//Calculations for velocity control
//	double avgSpeed = 0;
//	avgSpeed = speed/counter3;
//	count = 0;
//	speed = 0;
//	double Error = Kp*(avgSpeed - desiredSpeed);
//	speedCommand+=Error;
//
//	Motor_Control_SetDutyUS(speedCommand);

	//For the SERVO

	//This counter will tell me how many interrupts have been called, so I can figure out the time
	counter++;

	//Period of Main_Control_interrupt. Change in the Component Inspector and here.
	const int period = 200;

	//Calculating the current time.
	time = counter2*period;

	unsigned int turning = 18250; //20ms = 20000 ms, this measures off time. We want <=.5 for left, >=1 for right
		                          // =>19000 is max left, <=18000 is max right, 18250 is middle

	//TODO!!! Calculate y. We need to measure on the track how our y and the 0's in the camera correlate
	// y = ?

	//Change in y
	double changeY = y - yPast;
	yPast = y;

	//Servo Control Constants
	//TODO!! Get the correct derivative and proportional constants
	const double navKd = 10.0;
	const double navKp = 10.0;

	//Calculating change in time
	int changeTime = time - timePast;
	timePast = time;

	//Calculating the derivative
	double derivate = changeY/changeTime;

	//Calculating the navigation error
	double ErrorNav = navKp*y + navKd*derivate;
	turning+=ErrorNav;

	//Updating the servo
	Servo_Control_SetDutyUS(turning);
}

/*
 * static volatile int Start_Time = 0;
static volatile int Stop_Time = 0;
static volatile int counter3 = 0;
static volatile double speed= 0;

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

	  counter3++; //Increment count
  }


}
 */

/*
** ===================================================================
**     Event       :  PWM1_OnEnd (module Events)
**
**     Component   :  Servo_Control [PWM]
**     Description :
**         This event is called when the specified number of cycles has
**         been generated. (Only when the component is enabled -
**         <Enable> and the events are enabled - <EnableEvent>). The
**         event is available only when the <Interrupt service/event>
**         property is enabled and selected peripheral supports
**         appropriate interrupt.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void PWM1_OnEnd(void)
{
  /* Write your code here ... */
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
