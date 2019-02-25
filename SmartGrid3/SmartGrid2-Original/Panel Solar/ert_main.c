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
#include <math.h>

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

double Vg,Vc,n,Ns,T1,Voc_T1,Isc_T1,Isc_T2,T2,Voc_T2,Ics_T2,TaK,K0,IL_T1,IL,I0,I0_T1,Xv,dVdI_Voc,k,q,Rs,A,Vt_Ta,Ia;
double Suns,TaC,Va;

int Temp,Volt,Irra;

//Variables para el elevador de tension
int E=150;
double R=28.8;
double C=0.001;
int L=1;
#define X2ss sqrt(2)*240

#define Uss E/X2ss;
double X1ss=0.0384;
//Matriz dinamica Ad
double a11=1;
double a12=-0.0002;
double a21= 0.1756;
double a22=0.9862;
//Matriz de entradas
double b11=-0.1358;
double b21=0.0033;
//Matriz de salidas
double c11=0.0878;
double c12=0.9931;
//Matriz de control
double kp1=-1.5328;
double kp2=-0.1980;
double ki=0.0030;
//Referencia
double ref;
double K;
//Estados x(k+1)
double X_1K_1=0;
double X_2K_1=0;
//variables de Estados x(k)
double X_1K=0;
double X_2K=0;
//Accion de control u(k)
double U_K=0;
double W_K=0;
double V_K=0;
double W_K_1=0;
//Salida y(k)
double Y1_K=0;

//bool r=false;

int cont=0;

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


//Codigo emulacion PFV + elevador

TaC=25; //Entrada del sistema
Va=Va+0.01;
  if (Va>18.5)  Va=0;
Suns=1; //Entrada del sistema

TaK = 273 + TaC;
  IL_T1 = Isc_T1 * Suns; 
  IL = IL_T1 + K0*(TaK - T1); 
  I0= I0_T1*pow((TaK/T1),(3/n))*exp(-q*Vg/(n*k)*((1/TaK)-(1/T1)));
  Vt_Ta = A * k * TaK / q;
  Vc = Va/Ns;
  int j;
  for (j=1;j<=5;j++){
    Ia=Ia- (IL - Ia - I0*( exp((Vc+Ia*Rs)/Vt_Ta) -1))/(-1 - (I0*( exp((Vc+Ia*Rs)/Vt_Ta) -1))*Rs/Vt_Ta);
    }
while (cont<1000){
ref=Va;
K=X2ss/ref;
ref=K*ref;
 //Elevador de tension Controlador
 Y1_K=c11*X_1K+c12*X_2K;
 W_K=ref-Y1_K+W_K_1;
 U_K=-kp1*X_1K-kp2*X_2K-ki*W_K;
 X_1K_1=a11*X_1K+a12*X_2K+b11*U_K;
 X_2K_1=a21*X_1K+a22*X_2K+b21*U_K;

 X_1K=X_1K_1;
 X_2K=X_2K_1;
 W_K_1=W_K;

cont=cont+1;
}


printf("La salida del panel es: %3.2f \n",Y1_K);


  /* Step the model for base rate */
  
  /*
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
  printf("La accion 2 es: %3.2f \n",u2);*/
  
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


q=1.6*pow(10,-19);
  k=1.38*pow(10,-23);

 A=1;
n=1.12;
Vg=1.12;
Ns=36;
T1=273+25;
Voc_T1=21.06/Ns;
Isc_T1=3.3;//3.8;
Voc_T2=19/Ns;//17.05/Ns;
Isc_T2=3.4;//3.92;
K0=(Isc_T2 - Isc_T1)/(T2 - T1);
I0_T1=Isc_T1/(exp(q*Voc_T1/(n*k*T1))-1);
Xv = I0_T1*q/(n*k*T1) * exp(q*Voc_T1/(n*k*T1));
dVdI_Voc = - 1.15/Ns / 2;
Rs = - dVdI_Voc - 1/Xv;
  
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
