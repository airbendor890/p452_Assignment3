#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>

//Q1 assignment 3 P452

double f(double x){return exp(-1*x*x);}

//importance sampling distribution	e/(e-1)*e^-x:
double q(double x){return (exp(1)*exp(-1*x))/(exp(1)-1);}

//exponential distribution random numbers
double exp_rand(double a ,double b,double lambda){
	double temp=1.0*rand()/RAND_MAX;
	temp=exp(-1*lambda*temp);
	temp=(1/(exp(lambda)-1))*(temp*exp(lambda)-1);
	//map to [a,b]
	temp=a+(b-a)*temp;
	return temp;
}

void main(){
	time_t t;
	srand((unsigned) time(&t));

	int N=1000000;
	double arr[N];
	double var=0;
	double f_sum=0;
	//normal montecarlo integration
	for(int i=0;i<N;i++){
			double x=1.0*rand()/RAND_MAX;
			arr[i]=f(x);
			f_sum+=arr[i];
	}
	//value of integration
	f_sum=f_sum/N;
	//variance
	for(int i=0;i<N;i++){
		var+=pow(arr[i]-f_sum,2);
	}
	var=var/N;
	
	printf("\nNormal Montecarlo:\n");
	printf("I=%lf\tstd.dev=%lf\n",f_sum,sqrt(var));
	
	//importance sampling Integration
	var=0;
	f_sum=0;
	for(int i=0;i<N;i++){
		//sample with importance sampling distribution
			double x=exp_rand(0,1,1);
			
			arr[i]=f(x)/q(x);
			f_sum+=arr[i];
	}
	//value of integration
	f_sum=f_sum/N;
	//variance
	for(int i=0;i<N;i++){
		var+=pow(arr[i]-f_sum,2);
	}
	var=var/N;
	
	printf("\nImportance sampling Montecarlo:\n");
	printf("I=%lf\tstd.dev=%lf\n",f_sum,sqrt(var));
	
	
}