#include<stdio.h>
#include<conio.h>
#include<math.h>
struct att {
  double mean;
  double var;
  double sumX;
  double sumX2;	// summation of ( X^2 -mean)
};

double e=2.71828, pi=3.14159;
int main()
{ 
    int c;
    printf("Enter the number of classes:\n");// Here classes are male and female so C=2
    scanf("%d",&c);
    c=2;// Here classes are male and female so C=2
    double pd[c]={0.5,0.5};// since probabiliy of sample being male and female is 0.5 of you invole other then it changes to 0.33 for male 0.33 for feamle and 0.33 for other :-P
    int n;
    printf("Enter the number of Attributes:\n");// the number of attributes of the data set like weight height foot size analogus to columns in a table
    scanf("%d",&n);
    int m;
	double v[n]={6,130,8};//Here there are 3 attributes to the sample to be classified as male and female has 3 values if you have more attributes the nadd more values in the {} brackets 
    printf("Enter the number of datasets:\n");// number to training data rows 5 is prefferable 
    scanf("%d",&m);
    double holder[m];
    struct att list[c][n];
  for(int k=0;k<c;k++){
    for(int i=0;i<n;i++)
    {
    	list[k][i].sumX=0.0;
    	list[k][i].sumX2=0.0;
    	printf("Attribute %d:",i);
    	for(int j=0;j<m;j++)
    	{
    		scanf("%lf",&holder[j]);
    		list[k][i].sumX+=holder[j];
		}
		list[k][i].mean=(list[k][i].sumX)/m;
		for(int j=0;j<m;j++)
		{
			list[k][i].sumX2+=pow(holder[j]-list[k][i].mean,2);
		}
		list[k][i].var=(list[k][i].sumX2)/(m-1);
		printf("%lf %lf\n",list[k][i].mean, list[k][i].var);
		pd[k]*=(pow(e,-1*pow(v[i]-list[k][i].mean,2)/(2*list[k][i].var))/sqrt(2*pi*list[k][i].var))*10000.0;//depending on the attributes of the sample its closeness to the mean of both male and female's normal distribution is calculated...if it is closer to males mean the the probability density wrt male will be high comapred to female and same for feamle  
	}
 }
    int ans=0, ans2=0,k=0;
    while(ans2>=0)
    {
    	if(pd[0]>pd[1])
    	{
    		printf("Subject is a male? %lf probability density of male %lf probability density of female\nEnter 0 if yes and 1 if no:",pd[0], pd[1]);
    		scanf("%d",&ans);
		}else 
		{
			printf("Subject is a female? %lf probability density of male %lf probability density of female\nEnter 1 if yes and 0 if no:",pd[0], pd[1]);
    		scanf("%d",&ans);
		}
		printf("Add more training data?\nEnter 1 if yes and -1 if no:");
		scanf("%d",&ans2);
		if(ans2==1){
	        printf("\n");
	    	m++;
		     for( int i=0;i<n;i++)// the values are added to the data set and the mean and variance of the data attributes are recalculated here to make the predictions more accurate 
		    {     
			  list[ans][i].sumX+=v[i];
			  list[ans][i].mean=(list[ans][i].sumX)/m;
			  list[ans][i].sumX2+=pow(v[i]-list[k][i].mean,2);
			  list[ans][i].var=(list[ans][i].sumX2)/m;
			  printf("Enter the attribute %d of the new data:",i);
		      scanf("%lf",&v[i]);
			  } 
			  
		    for(int k=0;k<c;k++)
		    {
		    	pd[k]=0.5;
		    	for(int i=0;i<n;i++)
		    	{
		    		pd[k]*=(pow(e,-1*pow(v[i]-list[k][i].mean,2)/(2*list[k][i].var))/sqrt(2*pi*list[k][i].var))*10000.0;
				}
			}
	   }
	}
}


//(pow(e,-1*pow(v[i]-mean[i],2)/(2*var[i]))/sqrt(2*pi*var[i]))*10000.0
