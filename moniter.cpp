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
int getnum(char c)
{
	if(c=='u')
	return 0;
	else if(c=='d')
	return 1;
	else if(c=='l')
	return 2;
	else return 3;
}
int main()
{
	int pid,i,j,n,box;
	scanf("%d",&pid);
	
	//10*10 grid
	// matrix[i] contains status of upper,lower,left,right side of box i
	int position; 
	
	if(pid==-256) // first call
	{
		give_initial_input();
		return 0;
	}
		
	scanf("%d",&box);
	cin>>side;
	
	for(i=0;i<100;i++)
		for(j=0;j<4;j++)
			scanf("%d",&matrix[i][j]);
	
	if(!((box>=1)&&(box<=100)&&(side=='u'||side=='d'||side=='l'||side=='r')&&(matrix[box-1][getnum(side)]==0)))
	{
		cout<<"-1";  // wrong output by user
		return 0;
	}
		
	if(side=='u')
	{
		matrix[box-1][0]=1;
		if(box>10)
			matrix[box-10-1][1]=1;
	}
	else if(side=='d')
	{
		matrix[box-1][1]=1;
		if(box<91)
			matrix[box+10-1][0]=1;
	}
	else if(side=='l')
	{
		matrix[box-1][2]=1;
		if(box%10!=1)
			matrix[box-1-1][3]=1;
	}
	else
	{
		matrix[box-1][3]=1;
		if(box%10!=0)
			matrix[box+1-1][2]=1;
	}
	
	int flag=0;
	for(i=0;i<100;i++)
		for(j=0;j<4;j++)
			if(matrix[i][j]==0)
				flag++;
				
	if(flag==0)
		{
			// game completed and box made
			if(side=='l')
			{
				if(box%10==1)
				{
					cout<<"501\n";   //1 box created by current player
				}
				else
				{
					cout<<"502\n";   // 2 box created by current player
				}
			}
			else if(side=='r')
			{
				if(box%10==0)
				{
					cout<<"501\n";   // box created by current player
				}
				else
				{
					cout<<"502\n";   // 2 box created by current player
				}
			}
			else if(side=='u')
			{
				if(box<11)
				{
					cout<<"501\n";   // box created by current player
				}
				else
				{
					cout<<"502\n";   // 2 box created by current player
				}
			}
			else if(side=='d')
			{
				if(box>90)
				{
					cout<<"501\n";   // box created by current player
				}
				else
				{
					cout<<"502\n";   // 2 box created by current player	
				}
			}
			return 0;
		}
		
		if(side=='l')
		{
			if(box%10==1)
			{
				if((matrix[box-1][0]==1)&&(matrix[box-1][1]==1)&&(matrix[box-1][2]==1)&&(matrix[box-1][3]==1))
					cout<<"601\n";   // box created by current player, give him another turn
				else
					cout<<"700\n";  // nothing special happened
			}
			else
			{
				if(((matrix[box-1][0]==1)&&(matrix[box-1][1]==1)&&(matrix[box-1][2]==1)&&(matrix[box-1][3]==1))&&(matrix[box-2][0]==1)&&(matrix[box-2][1]==1)&&(matrix[box-2][2]==1)&&(matrix[box-2][3]==1))
					cout<<"602\n";   // 2 box created by current player, give him another turn
				else if(((matrix[box-1][0]==1)&&(matrix[box-1][1]==1)&&(matrix[box-1][2]==1)&&(matrix[box-1][3]==1))||((matrix[box-2][0]==1)&&(matrix[box-2][1]==1)&&(matrix[box-2][2]==1)&&(matrix[box-2][3]==1)))
					cout<<"601\n";   // box created by current player, give him another turn
				else
					cout<<"700\n";  // nothing special happened
			}
		}
		else if(side=='r')
		{
			if(box%10==0)
			{
				if((matrix[box-1][0]==1)&&(matrix[box-1][1]==1)&&(matrix[box-1][2]==1)&&(matrix[box-1][3]==1))
					cout<<"601\n";   // box created by current player, give him another turn
				else
					cout<<"700\n";  // nothing special happened
			}
			else
			{
				if(((matrix[box-1][0]==1)&&(matrix[box-1][1]==1)&&(matrix[box-1][2]==1)&&(matrix[box-1][3]==1))&&(matrix[box][0]==1)&&(matrix[box][1]==1)&&(matrix[box][2]==1)&&(matrix[box][3]==1))
					cout<<"602\n";   // 2 box created by current player, give him another turn
				else if(((matrix[box-1][0]==1)&&(matrix[box-1][1]==1)&&(matrix[box-1][2]==1)&&(matrix[box-1][3]==1))||((matrix[box][0]==1)&&(matrix[box][1]==1)&&(matrix[box][2]==1)&&(matrix[box][3]==1)))
					cout<<"601\n";   // box created by current player, give him another turn
				else
					cout<<"700\n";  // nothing special happened
			}
		}
		else if(side=='u')
		{
			if(box<11)
			{
				if((matrix[box-1][0]==1)&&(matrix[box-1][1]==1)&&(matrix[box-1][2]==1)&&(matrix[box-1][3]==1))
					cout<<"601\n";   // box created by current player, give him another turn
				else
					cout<<"700\n";  // nothing special happened
			}
			else
			{
				if(((matrix[box-1][0]==1)&&(matrix[box-1][1]==1)&&(matrix[box-1][2]==1)&&(matrix[box-1][3]==1))&&(matrix[box-10-1][0]==1)&&(matrix[box-10-1][1]==1)&&(matrix[box-10-1][2]==1)&&(matrix[box-10-1][3]==1))
					cout<<"602\n";   // 2 box created by current player, give him another turn
				else if(((matrix[box-1][0]==1)&&(matrix[box-1][1]==1)&&(matrix[box-1][2]==1)&&(matrix[box-1][3]==1))||((matrix[box-10-1][0]==1)&&(matrix[box-10-1][1]==1)&&(matrix[box-10-1][2]==1)&&(matrix[box-10-1][3]==1)))
					cout<<"601\n";   // box created by current player, give him another turn
				else
					cout<<"700\n";  // nothing special happened
			}
		}
		else if(side=='d')
		{
			if(box>90)
			{
				if((matrix[box-1][0]==1)&&(matrix[box-1][1]==1)&&(matrix[box-1][2]==1)&&(matrix[box-1][3]==1))
					cout<<"601\n";   // box created by current player, give him another turn
				else
					cout<<"700\n";  // nothing special happened
			}
			else
			{
				if(((matrix[box-1][0]==1)&&(matrix[box-1][1]==1)&&(matrix[box-1][2]==1)&&(matrix[box-1][3]==1))&&(matrix[box+10-1][0]==1)&&(matrix[box+10-1][1]==1)&&(matrix[box+10-1][2]==1)&&(matrix[box+10-1][3]==1))
					cout<<"602\n";   // 2 box created by current player, give him another turn
				else if(((matrix[box-1][0]==1)&&(matrix[box-1][1]==1)&&(matrix[box-1][2]==1)&&(matrix[box-1][3]==1))||((matrix[box+10-1][0]==1)&&(matrix[box+10-1][1]==1)&&(matrix[box+10-1][2]==1)&&(matrix[box+10-1][3]==1)))
					cout<<"601\n";   // box created by current player, give him another turn
				else
					cout<<"700\n";  // nothing special happened
			}
		}
		
		for(i=0;i<100;i++)
		{
			for(j=0;j<4;j++)
				cout<<matrix[i][j]<<" ";
			if(i!=99)
			cout<<"\n";
		}
}

/*
if returned value is 600 or 700, also read matrix else dont read anything else

Also, you need to keep the count of boxes made by both players
*/
