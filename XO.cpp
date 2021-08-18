#include<stdio.h>
#include<conio.h>
#include<math.h>
struct dual
{
	int k,l;
};
int top;
void Allotmentu( int A[][4][4],int s, int i, int j,struct dual ptr[]);
void Allotmento( int A[][4][4],int s, int i, int j,struct dual ptr[]);
int func(int a , int b);
struct dual val(struct dual ptr, int A[][4][4], struct dual pS[]);
void CPUmove( int A[][4][4], char game[][4], struct dual ptr[], int ms);
void Allotment(int A[][4][4],int i,int j,struct dual ptr[], int k);
void display(char game[][4]);
int main()
{

	int A[4][4][4],i;
	label:top=0;
	char game[4][4];
	for(i=0;i<=3;i++)
	{
		for(int j=1;j<=3;j++)
		{
			A[i][j][0]=0;
			A[i][j][1]=0;
			A[i][j][2]=0;
			game[i][j]='-';
		}
	}
   struct dual ptr[50];
   ptr[0].k=-1;
   i=1;
   int j;
   int ms=0;
   while(i>0)
   {
    printf("ENter the move:");
    scanf("%d%d",&i,&j);
   Allotment(A,i,j,ptr,0);
	game[i][j]='o';
	printf("\nYour move:\n");
	display(game);
    CPUmove(A,game,ptr,ms);
    ms++;
    printf("\n");
     printf("CPU's Move:\n");
	display(game);
	printf("\n-1:Exit\n2:input:\n3:New Game:");
	scanf("%d",&i);
	if(i==3)
	{
		goto label;
	}
  }

	for(i=0;i<3;i++)
	{
		for(j=1;j<=3;j++)
		{
	 printf("\t%d%d%d",A[i][j][0],A[i][j][1],A[i][j][2]);
	     }
	     printf("\n");
 }
 printf("\n%d%d %d%d",ptr[0].k,ptr[0].l,ptr[top].k, ptr[top].l);
       getch();
       return 0;
}
void Allotmentu( int A[][4][4],int s, int i, int j,struct dual ptr[])
{
		if(A[s][i][0]<0)
	{
		A[s][i][0]=5;
	}

	else if(A[s][i][0]<5)
	{
		A[s][i][0]++;
		if(ptr[0].k==-1 ||A[s][i][0]==2)
		{
	       ptr[0].k=s;
		   ptr[0].l=i;
		}
		A[s][i][A[s][i][0]]=j;
	}
}
void Allotmento( int A[][4][4],int s, int i, int j,struct dual ptr[])
{
		if(A[s][i][0]>0  && A[s][i][j]<5)
	{
		A[s][i][0]=5;
	}

	else if(A[s][i][0]<=0)
	{
		A[s][i][0]--;
		if(A[s][i][0]==-2)
		{
			top++;
	   ptr[top].k=s;
		   ptr[top].l=i;
		}
		A[s][i][-1*A[s][i][0]]=j;
	}
}
void display(char game[][4])
{
	for(int i=1;i<=3;i++)
	{
		for(int j=1;j<=3;j++)
		{
			printf("\t%c",game[i][j]);
		}
		printf("\n");
	}
}

int func(int a , int b)
{
	if(a+b==3)
	{
		return 3;
	}
	else return abs(a-b);
}
struct dual val(struct dual ptr, int A[][4][4], struct dual pS[])
{
	struct dual move;
	if(ptr.k==0)
	{
		move.k=ptr.l;
		move.l=func(A[ptr.k][ptr.l][1],A[ptr.k][ptr.l][2]);
	}
	else if(ptr.k==1)
	{
		move.l=ptr.l;
		move.k=func(A[ptr.k][ptr.l][1],A[ptr.k][ptr.l][2]);
	}
	else
	{
		if(ptr.l==1)
		{
		  move.k=func(A[ptr.k][ptr.l][1],A[ptr.k][ptr.l][2]);
		  move.l=move.k;
		}
		else
		{
		 move.k=func(A[ptr.k][ptr.l][1],A[ptr.k][ptr.l][2]);
		 move.l=abs(4-move.k);
		}
	}
	 Allotmento(A,2,2,move.k,pS);
	 Allotmento(A,2,1,move.k,pS);
     Allotmento(A,0,move.k,move.l,pS);
	 Allotmento(A,1,move.l,move.k,pS);
	return move;
}
void CPUmove( int A[][4][4], char game[][4], struct dual ptr[], int ms)
{
	struct dual move;
	if( ms==0)
    {

	    if(game[2][2]=='-')
	    {
	    game[2][2]='x';
	    Allotmento(A,2,2,2,ptr);
		Allotmento(A,2,1,2,ptr);
	    Allotmento(A,0,2,2,ptr);
	    Allotmento(A,1,2,2,ptr);
		}
	    else
	   {
		game[1][1]='x';
	Allotmento(A,2,1,1,ptr);
	    Allotmento(A,0,1,1,ptr);
	    Allotmento(A,1,1,1,ptr);
	    }
		return;
    }
	while(top>0)
	  {

	   if(A[ptr[top].k][ptr[top].l][0]==-2)
	    {
		move=val(ptr[top],A,ptr);
	game[move.k][move.l]='x';
	printf("\nYOU LOOSE!");
	return;
		}
       else top--;
	}
      if(A[ptr[0].k][ptr[0].l][0]==2)
	{
		move=val(ptr[0],A,ptr);
		game[move.k][move.l]='x';
	}
	else
	{
		int i,j,m,n;
	   for(i=0;i<=2;i++)
	   {
	     for(j=1;j<=3;j++)
	     {
		if(A[i][j][0]==-1)
		{
			m=i;
			n=j;
			goto allot;
		}
	}}
	printf("\nDRAW!");
	return;
	allot:
		if(m==2)
		{
		   game[2][2]='x';	
           Allotmento(A,2,2,2,ptr);
		   Allotmento(A,2,1,2,ptr);
    	   Allotmento(A,0,2,2,ptr);
	       Allotmento(A,1,2,2,ptr);	
		}
		else if(m==0)
		{
			game[n][3]='x';
		  Allotment(A,n,3,ptr,1);
		}
		else if(m==1)
		{
			game[3][n]='x';
           Allotment(A,3,n,ptr,1);		  
		}
	}
	
}
void Allotment(int A[][4][4],int i,int j,struct dual ptr[], int k)
{
	if(k==0)
	{
		if(i==j)
        {
	     Allotmentu(A,2,1,i,ptr);
	    }
	    if(i+j==4)
	    {
		Allotmentu(A,2,2,i,ptr);
	    }
	    Allotmentu(A,0,i,j,ptr);
	    Allotmentu(A,1,j,i,ptr);
	}
	else
	{
		if(i==j)
        {
	    Allotmento(A,2,1,i,ptr);
	    }
	    if(i+j==4)
	    {
		Allotmento(A,2,2,i,ptr);
	    }
	    Allotmento(A,0,i,j,ptr);
	    Allotmento(A,1,j,i,ptr);
	}
}
