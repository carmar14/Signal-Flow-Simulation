/*
 * File: ert_main.c
 *
 * Code generated for Simulink model 'inversor'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Tue Jan 30 13:58:44 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include <stddef.h>
#include <stdio.h>                     /* This ert_main.c example uses printf/fflush */
#include "inversor.h"                  /* Model's header file */
#include "rtwtypes.h"
#include <wiringPi.h> 
#include <signal.h>
#include <sys/time.h>
#include "MPC.h"

/*
 * Associating rt_OneStep with a real-time clock or interrupt service routine
 * is what makes the generated code "real-time".  The function rt_OneStep is
 * always associated with the base rate of the model.  Subrates are managed
 * by the base rate from inside the generated code.  Enabling/disabling
 * interrupts and floating point context switches are target specific.  This
 * example code indicates where these should take place relative to executing
 * the generated code step function.  Overrun behavior should be tailored to
 * your application needs.  This example simply sets an error status in the
 * real-time model and returns from rt_OneStep.
 */
void rt_OneStep(void);
void timer_handler (int);



int b=1;

double *ac;
double u1;
double u2;
double inv1;
double inv2;
double vdc=340;

void timer_handler(int signum)
{
	
	//rt_OneStep();
	
	if (b==1){
		digitalWrite(0,HIGH);
		b=0;
		//printf("prendi\n");
	}else{
		digitalWrite(0,LOW);
		b=1;
		//printf("apague\n");
	}

	
}

void rt_OneStep(void)
{
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(inversor_M, "Overrun");
    return;
  }

  OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */

  /* Step the model for base rate */
  
  
  MPC_step(inv1,inv2,1.17,2.9);
  u1=getU();
  u2=getU2();
  
  guardarVdc(vdc);
  guardarU(u1);    
  inv1=inversor_step(vdc,u1);
  //Inversor 2
  guardarVdc(vdc);
  guardarU2(u2);
  inv2=inversor_step(vdc,u2);
  
  
  
  printf("La corriente del inversor es: %3.2f \n",inv1);
  printf("La corriente del inversor 2 es: %3.2f \n",inv2);
  printf("La accion 1 es: %3.2f \n",u1);
  printf("La accion 2 es: %3.2f \n",u2);
  
  /*printf("La accion 1 es: %3.2f \n",ac                                                                                                        );
  printf("La accion 1 es: %3.2f \n",u1);
  printf("La accion 2 es: %3.2f \n",u2);
*/

  /* Get model outputs here */

  /* Indicate task complete */
  OverrunFlag = false;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}

/*
 * The example "main" function illustrates what is required by your
 * application code to initialize, execute, and terminate the generated code.
 * Attaching rt_OneStep to a real-time clock is target specific.  This example
 * illustrates how you do this relative to initializing the model.
 */
int_T main(int_T argc, const char *argv[])
{
  /* Unused arguments */
  (void)(argc);
  (void)(argv);
  
  /* Initialize model */
  inversor_initialize();
  
  /*Inicializamos GPIO */
  wiringPiSetup () ;
  pinMode(0,OUTPUT);
	
	/*
	struct sigaction sa;
	struct itimerval timer;

	/* Install timer_handler as the signal handler for SIGVTALRM. */
	//memset (&sa, 0, sizeof (sa));
	//sa.sa_handler = &timer_handler;
	//sigaction (SIGVTALRM, &sa, NULL);

	/* Configure the timer to expire after 250 msec... */ //10msec
	//timer.it_value.tv_sec = 1;
	//timer.it_value.tv_usec = 0;//250000;
	/* ... and every 250 msec after that. */
	//timer.it_interval.tv_sec = 0;
	//timer.it_interval.tv_usec = 1;
	/* Start a virtual timer. It counts down whenever this process is
	executing. */
	//setitimer (ITIMER_VIRTUAL, &timer, NULL);
	
	while(1){
		rt_OneStep();
	
		if (b==1){
			digitalWrite(0,HIGH);
			b=0;
			//printf("prendi\n");
		}else{
			digitalWrite(0,LOW);
			b=1;
			//printf("apague\n");
		}
		
		delayMicroseconds(1);	
	}
  

  /* Simulating the model step behavior (in non real-time) to
   *  simulate model behavior at stop time.
   */
  while ((rtmGetErrorStatus(inversor_M) == (NULL)) && !rtmGetStopRequested
         (inversor_M)) {
    rt_OneStep();
    
  }

  /* Disable rt_OneStep() here */

  /* Terminate model */
  inversor_terminate();
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
