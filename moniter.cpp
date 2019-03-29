#include<bits/stdc++.h>
#define ll long long
using namespace std;
void give_initial_input()
{
	for(int i=0;i<100;i++){
	cout<<"0 0 0 0";
	if(i!=99)
	cout<<"\n";}
}

int main()
{
	int pid,i=0,j=0,n,mat[50][3],p1money=100,p2money=100,t,position,p1bid,p2bid,move;
	scanf("%d",&pid);
	
	FILE *fp;
	fp=fopen("temp.txt","r+") //file to keep previous valid bids and moves

	
	if(pid==-256) // first call
	{
		give_initial_input();
		return 0;
	}
	
	while(fscanf(fp,"%d",&mat[i][j])) // take inputs from the files
	{
		j++;
		if(j==3)
		{
			i++;
			j=0;
		}
	}
	fclose(fp);

	t=i;		// number of steps
	for(i=0;i<50;i++)
	{
		p1money-=mat[0][i];
		p2money-=mat[1][i];
		position+=mat[2][i];
	}

	scanf("%d %d",&p1bid,&p2bid)

	if(p1bid>p1money)
	{
		printf("-1");    //p1 made wrong move
		return 0;
	}

	if(p2bid>p2money)
	{
		printf("-2");
		return 0;
	}

	if(p1bid>p2bid)
	{
		move = log(p1bid)/log(p2bid);
		move=-move;
		fp=fopen("temp.txt","a");
		fprintf(fp,"%d %d %d\n",p1bid,p2bid,move)
		fclose(fp);
		if(position-move<=0)
		{
			printf("-3");   // Player 1 won
			return 0;
		}
	}

	else if(p2bid>p1bid)
	{
		move = log(p2bid)/log(p1bid);
		fp=fopen("temp.txt","a");
		fprintf(fp,"%d %d %d\n",p1bid,p2bid,move)
		fclose(fp);
		if(position+move>=24)
		{
			printf("-4"); // Player 2 won
			return 0;
		}
	}
	else
	{
		move=0;
		fp=fopen("temp.txt","a");
		fprintf(fp,"%d %d %d\n",p1bid,p2bid,move)
		fclose(fp);
	}

	position+=move;
	p1money-=p1bid;
	p2money-=p2bid;

	if(p1money<=1)
	{
		move=p2money-p1money;
		position+=move;
		fp=fopen("temp.txt","a");
		fprintf(fp,"%d %d %d\n",p1bid,p2bid,move)
		fclose(fp);
		printf("-5"); //Player 1 only 1 rupee left
		return 0;
	}

	if(p2money<=1)
	{
		move=p2money-p1money;
		position+=move;
		fp=fopen("temp.txt","a");
		fprintf(fp,"%d %d %d\n",p1bid,p2bid,move)
		fclose(fp);
		printf("-6"); //Player 1 has 0 rupee left
	}

	

}
