#include<stdio.h>
#include"utility.h"
#define pi 3.141
//Q2.
//INFINITE SQUARE WELL POTENTIAL (1D) :PARTICLE IN A BOX
//lowest energy state
double f_1(double y1,double y,double x){
/*f:f(y1,y,x)*/
	return -1*pi*pi*y;
}

//first excited state
double f_2(double y1,double y,double x){
	return -4*pi*pi*y;
}
//second excited state
double f_3(double y1,double y,double x){
	return -9*pi*pi*y;
}

int main(){
	double h=0.0001;/*step size*/
	double z;
	
	//lowest energy state
	printf("lowest energy state,give guesss value of slope at x=a:\n");
	scanf("%lf",&z);
	FILE * fptr;
	fptr=fopen("q2_output1.txt","w");
	
	printf("\ny(b)=%lf",shoot(&f_1,0,0,1,0,z,h,fptr));
	fclose(fptr);
	
	//first excited state
	printf("first excited state,give guesss value of slope at x=a:\n");
	scanf("%lf",&z);
	fptr=fopen("q2_output2.txt","w");
	
	printf("\ny(b)=%lf",shoot(&f_2,0,0,1,0,z,h,fptr));	
	fclose(fptr);
	//second excited state
	printf("second excited state,give guesss value of slope at x=a:\n");
	scanf("%lf",&z);
	fptr=fopen("q2_output3.txt","w");
	
	printf("\ny(b)=%lf",shoot(&f_3,0,0,1,0,z,h,fptr));
	fclose(fptr);
	return 0;
}
//output
/*
lowest energy state,give guesss value of slope at x=a:
2.5

y(b)=0.000472first excited state,give guesss value of slope at x=a:
2

y(b)=-0.000377second excited state,give guesss value of slope at x=a:
1.6

*/


//please note:the solutions(plots) are not normalized. 