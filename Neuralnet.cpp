#include<stdio.h>
#include<conio.h>
#include<math.h>
double sigmoid(float x)
{
	float exp_value;
     float return_value;

     /*** Exponential calculation ***/
     exp_value = exp((double) -x);

     /*** Final sigmoid value ***/
     return_value = 1 / (1 + exp_value);

     return return_value;
}
int main()
{
	double input[4][2] = {{1,1},{1,0},{0,1},{0,0}};
	double target[4] = {1,0,0,0};
	double weight[2]= {0.5,0.5};
	double bias = 0.5;
	double lr = 0.15;
	for(int i=0; i<300; i++)
	{
		for(int j=0; j<4;j++)
		{
			double signal = bias;
			for(int k=0;k<2;k++)
			{
				signal += input[j][k]*weight[k];
			}
			double output = sigmoid(signal);
			double error = target[j]-output;
			printf("%f\n",pow(error,2));
			double dsigmoid = output/(1-output);
			for(int k=0;k<2;k++)
			{
				weight[k] += lr*error*dsigmoid*input[j][k];
			}
			bias += lr*error*dsigmoid;
		}
	}
	
	printf("\n\n");
	for(int j=0; j<4;j++)
	{
			double output = bias;
			for(int k=0;k<2;k++)
			{
				output += input[j][k]*weight[k];
			}
			output = sigmoid(output);
			if(output>0.5)
			{
				printf("%d ^ %d :%d\n",(int)input[j][0],(int)input[j][1],1);
			}
			else
			{
				printf("%d ^ %d :%d\n",input[j][0],(int)input[j][1],0);
			}
	}
}
