#include<stdio.h>
#include<math.h>
//Two dimensional Laplace's equation domain:[0,1]x[0,1]
//grid size L:Number of points between 0 and 1(assuming square grid i.e square
//domain)
//change here grid size if needed
#define L 20

//generating the matrix on fly
//tridiagonal with fringes
double	A(int i,int j){
	//diagonal
	if(i==j)return -4;
	else
	//subdiagonal and superdiagonal
	if(j-i==1 || i-j==1)return 1;
	else
	//fringes
	if(i-j==L || j-i==L)return 1;
	else return 0;
	
				
}

//---------------------------------------------------------main-----------------------------
int main(){
	double epsilon=1.0e-6;		//Tolerance
	double i_max=200;			//maximum no of iteration allowed
	
	int N=L*L;					//Dimension of matrix :to be produced on fly
	double b[N];
	double x[N];
	double r[N];
	double d[N];
	double alpha;
	double beta;
	
	FILE *file1;
	file1=fopen("Q3_soln_vector.txt","w");//to store the solution vector
	
	for(int i=0;i<N;i++){	//b vector in Ax=b
		//for laplace equtn
		if(i>=N-L)b[i]=-1.0;
		else b[i]=0.0;
	}
	//-----------------Conjugated Gradients Method-------------

	//Guess Solution
	for(int i=0;i<N;i++)
		x[i]=1.0;
	
	for(int i=0;i<N;i++){
		double temp=0;
		for(int j=0;j<N;j++){
			temp+=A(i,j)*x[j];	
		}
		r[i]=b[i]-temp;
	}

	for(int i=0;i<N;i++)
		d[i]=r[i];
	
	//double del_0;
	double del_new;
	double del_old;
	
	del_new=0;
	
	for (int i=0;i<N;i++)
		del_new+=r[i]*r[i];
	
	//del_0=del_new;
	
	int t=1;			//iteration variable
	double q[N];		//To store A.d
	
	//Conjugated gradients iteration
	
	while(t<i_max && del_new > pow(epsilon,2)){
		
		//q=A.d
		for(int i=0;i<N;i++){
			double temp=0;
			for(int j=0;j<N;j++){
				//temp+=A[i][j]*d[j];
				temp+=A(i,j)*d[j];
			}
			q[i]=temp;
		}
		
		double temp1=0;
		
		//d^T.q=d^T.A.d
		for(int i=0;i<N;i++)
			temp1+=d[i]*q[i];
		
		alpha=del_new/temp1;
		
		//x=x+alpha.d
		for(int i=0;i<N;i++)
			x[i]=x[i]+alpha*d[i];

				
		if(t%50==0)
			//r <== b-A.x
			for(int i=0;i<N;i++){
				double temp2=0;
				for(int j=0;j<N;j++){
					//temp2+=A[i][j]*x[j];
					temp2+=A(i,j)*x[j];
				}
				r[i]=b[i]-temp2;
			}

		else{
			//r <== r-alpha*A.d =: r-alpha*q
			for(int i=0;i<N;i++)
				r[i]=r[i]-alpha*q[i];
		}
		
		del_old=del_new;
		del_new=0;
		//del_new <== r^T.r
		for(int i=0;i<N;i++)
			del_new+=r[i]*r[i];
		
		//beta=r(i+1)^T.r(i+1)/r(i)^T.r(i)
		beta=del_new/del_old;
		
		//d=r + beta*d;
		for(int i=0;i<N;i++)
			d[i]=r[i] + beta*d[i];
		
		t=t+1;
	}
	//store the solution vectors in file
	for(int i=0;i<N;i++){
		fprintf(file1,"%lf\n",x[i]);
	}
	
	
	fclose(file1);
	
//solution is in vector form	
//Extract the solution in [x :y :phi(x,y)] format to a file for plotting
	file1=fopen("Q3_soln_vector.txt","r");
	double soln_vec[N];
	for(int i=0;i<N;i++){
		fscanf(file1,"%lf",&soln_vec[i]);
	}
	fclose(file1);
	
	file1=fopen("Q3_soln_plot.txt","w");
	double DEL=1.0/(L+1);
	for(int i=0;i<L+2;i++){
		for(int j=0;j<L+2;j++){
			//boundary values
			
			if(i==0){
				fprintf(file1,"%lf\t%lf\t%lf\n",j*DEL,1-i*DEL,0.0);
			}
			else if(i==L+1){
				fprintf(file1,"%lf\t%lf\t%lf\n",j*DEL,1-i*DEL,1.0);
			}
			else if(j==0||j==L+1){
				fprintf(file1,"%lf\t%lf\t%lf\n",j*DEL,1-i*DEL,0.0);
			}
			else{
				fprintf(file1,"%lf\t%lf\t%lf\n",j*DEL,1-i*DEL,soln_vec[(i-1)*L+j-1]);
			}
			
			//fprintf(file1,"%lf\t%lf\t%lf\n",j*DEL,1-i*DEL,soln_vec[i*L+j]);
		}
	}
	fclose(file1);
	return 0;
}