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
#include "Motor_Diesel_paC.h"


//-----------------Direcciones IP-----

#define SERVER "169.254.5.28"   //Direcion IP del Inversor
#define PORTL 8887			//Puerto Local
#define PORTR 8886			//Puerto Remoto



//===============================================================
#include <string.h> //memset
#include <stdlib.h> //exit(0);
#include <arpa/inet.h>
#include <sys/socket.h>
//===============================================================

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

//===============================================================
void die(char *);
void setUDP(void);
double receive (void);
void sendm(double);
//===============================================================



int b=1;

double *ac;
double u1;
double u2;
double inv1;
double inv2;
double vdc=340;
double flujo=1;
double vdcmdiesel=0;

//===============================================================
struct sockaddr_in si_me, si_other, si_other2; //
int BUFLEN=512;
int s, slen = sizeof(si_other) , recv_len;
char buf[512];
//===============================================================
//==============Variables Panel Solar============================
double Vg,Vc,n,Ns,T1,Voc_T1,Isc_T1,Isc_T2,T2,Voc_T2,Ics_T2,TaK,K0,IL_T1,IL,I0,I0_T1,Xv,dVdI_Voc,k,q,Rs,A,Vt_Ta,Ia;
double Suns,TaC,Va;
int cont=0;
int Temp,Volt,Irra;
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

//==============Variables para graficar==========================
#include <math.h>
#define NUM_POINTS 10000

double xvals[NUM_POINTS];
double yvals[NUM_POINTS];
char * commandsForGnuplot[] = {"set title \"Diesel\"", "plot 'data.temp'"};
FILE * temp ;//= fopen("data.temp", "w");
FILE * gnuplotPipe;// = popen ("gnuplot -persistent", "w");
//int k;
int i;
//===============================================================
void die(char *s)
{
    perror(s);
    exit(1);
}

void setUDP(void)
{
	
    //create a UDP socket
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
    
    //Setting timeout for socket for 1ms
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 1000;
    if (setsockopt(s, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv)) < 0) {
		perror("Error");
	}
     
    // zero out the structure
    memset((char *) &si_other, 0, sizeof(si_other));
     
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORTR);
    if (inet_aton(SERVER , &si_other.sin_addr) == 0) 
	{
		fprintf(stderr, "inet_aton() failed\n");
		exit(1);
	}
		
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORTL);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
	
	//bind socket to port
	//Crea socket para MPC
    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    {
        die("bind s1");
    }
}

double receive (void)
{
	double x = 1.0;
	printf("Waiting for data...");
	memset(buf,'\0', BUFLEN);

	//try to receive some data, this is a blocking call
	if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, (socklen_t*)&slen)) < 0)
	{
		printf("Timeout o fallo de recepción\n");
		x=-1.0;
		return x;
		//die("recvfrom()");
	}
	
	//Para llegar aca tuvo que haber recepción exitosa desde inversor
	sendm(vdcmdiesel);
	/*memset(buf,'\0', BUFLEN);
	sprintf(buf, "%5.2f", vdcmdiesel);
	printf("Dato a enviar: %s\n",buf);
	
	if (sendto(s, buf, BUFLEN, 0, (struct sockaddr*) &si_other, slen) == -1)
	{
		die("sendto()");
	}
	*/
	
	return x;
}

void sendm(double mensaje)
{
	memset(buf,'\0', BUFLEN);
	sprintf(buf, "%5.2f", mensaje);
	printf("Dato a enviar: %s\n",buf);
	
	//print details of the client/peer and the data received
	//printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
	//printf("Data: %s\n" , buf);
	//printf("Numeric Data %3.2f\n",x);
	//now reply the client with the same data
	if (sendto(s, buf, BUFLEN, 0, (struct sockaddr*) &si_other, slen) == -1)
	{
		die("sendto()");
	}
	
}

//===============================================================

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
  
	//-----------------Calculo fuente emulada Diesel----------------------
	vdcmdiesel=Motor_Diesel_paC_step(flujo);
	vdcmdiesel*=295.7;
	printf("Velocidad %5.2f\n",vdcmdiesel);

	//----------------Calculo fuente emulada solar------------------------
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
	
	//---------------Inversores--------------------------
	//===============Inversor Diesel=====================
	
	guardarVdc(vdcmdiesel);
	guardarU(1.17); //u1=1.17
	guardarU2(1.17);
	inv1=inversor_step(vdcmdiesel,1.17);
	printf("La corriente en el inversor es: %3.2f \n",inv1);
	
	//==============Inversor Panel=======================
	
	guardarVdc(Y1_K);
	guardarU(3); //u2=3
	guardarU2(3);
	inv2=inversor_step(Y1_K,3);
	printf("La corriente en el inversor es: %3.2f \n",inv2);
	
	//MPC
	MPC_step(inv1,inv2,1.17,2.9);
	u1=getU();
    u2=getU2();
	printf("La variable U1 es: %3.2f \n",u1);
	printf("La variable U2 es: %3.2f \n",u2);

  
	
  //sendm(vdcmdiesel);
  //receive();		//Revisa por 1ms si hay petición de dato desde Inversor
  
  
  //------Grafica del voltaje del diesel--------
  //if (k==255){
	  //printf("Ahi voy\n");
	  /*
	  double xvals[NUM_POINTS];
	  double yvals[NUM_POINTS];
	  char * commandsForGnuplot[] = {"set title \"Diesel\"", "plot 'data.temp'"};
	  FILE * temp = fopen("data.temp", "w");
	  FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");*/
	  //while(i<255){
	  
	  /*if (i<10000 && Y1_K>330){
			//printf("Su i es: %i \n",i);
			xvals[i]=i+0.00001;
			yvals[i]=inv1;//+inv2;//0.05*xvals[i]*xvals[i]*xvals[i]-10*xvals[i]*xvals[i]+xvals[i];//sin(xvals[i]);	 y=0.05*x.^3-10*x.^2+x;	
			fprintf(temp, "%lf %lf \n", xvals[i], yvals[i]); //Write the data to a temporary file
			fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[1]);
			i=i+1;
			printf("i es %d\n",i);
		}*/
		
	
	//
  //------Grafica del voltaje del diesel--------
  
  //~ 
  //~ MPC_step(inv1,inv2,1.17,2.9);
  //~ u1=getU();
  //~ u2=getU2();
  //~ 
  //~ guardarVdc(vdc);
  //~ guardarU(u1);    
  //~ inv1=inversor_step(vdc,u1);
  //~ //Inversor 2
  //~ guardarVdc(vdc);
  //~ guardarU2(u2);
  //~ inv2=inversor_step(vdc,u2);
  //~ 
  //~ 
  //~ 
  //~ printf("La corriente del inversor es: %3.2f \n",inv1);
  //~ printf("La corriente del inversor 2 es: %3.2f \n",inv2);
  //~ printf("La accion 1 es: %3.2f \n",u1);
  //~ printf("La accion 2 es: %3.2f \n",u2);
  
  
  //~ 
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
  
  i=0;
  k=1;
  temp = fopen("data.temp", "w");
  gnuplotPipe = popen ("gnuplot -persistent", "w");
  fprintf(gnuplotPipe,"set grid \n");
  //Inicializar comunicacion UDP---------------------------------------------------------
  setUDP();
  
  //-------------------------------------------------------------------------------------
  
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
