#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <time.h>
using namespace std;

const int height=20;
const int width=30;
const int area=height*width;
float a[area]={0};
long int score=0,dir=1,enmy=-1;
float bullet=1.1;
long int xPos=3,yPos=4;
bool gameOn=true;

void layout()
{
	for(int j=0;j<height;j++)
	{
		for(int i=0;i<width;i++)
		{
            if(i==0 || i==width-1)
                a[i+j*width]=1;
            if(j==0 || j==height-1)
                a[i+j*width]=2;
            if((j==17 || j==18) && (i>=13 && i<=16))
                a[i+j*width]=3;
            if((j==17||j==18) && (i==13 || i==16))
                a[i+j*width]=4;
		}
	}
}

void control(char key)
{
    int flag=0;
    switch(key)
    {
        case 'd':
	        	for(int i=area;i>=0;i--)
                {
                    if(a[i]==xPos && a[i+2]!=1)
                    {
                        a[i+2]=xPos+2;;
                        a[i]=0;
                        flag=1;
                    }
                    else if(a[i]==yPos && a[i+2]!=1)
                    {
                        a[i+2]=yPos+2;
                        a[i]=0;
                        flag=1;
                    }
                    else if((a[i]==xPos && a[i+2]==1)||(a[i]==yPos && a[i+2]!=1))
                        break;
                }
                if(flag==1)
                {
                    xPos=xPos+2;
                    yPos=yPos+2;
                }
	        break;

	    case 'a':
	    	    for(int i=0;i<area;i++)
                {
                    if(a[i]==xPos && a[i-2]!=1)
                    {
                        a[i-2]=xPos+2;;
                        a[i]=0;
                        flag=1;
                    }
                    if(a[i]==yPos && a[i-2]!=1)
                    {
                        a[i-2]=yPos+2;
                        a[i]=0;
                        flag=1;
                    }
                     else if((a[i]==xPos && a[i-2]==1)||(a[i]==yPos && a[i-2]!=1))
                        break;
                }
                if(flag==1)
                {
                    xPos=xPos+2;
                    yPos=yPos+2;
                }
	        break;

        case 32:
                for(int i=0;i<area;i++)
                {
                    if(a[i+width]==xPos)
                    {
                        a[i]=bullet;
                        break;
                    }
                }
                break;
    }
}

void getEnemy()
{
    srand(time(0));
    int x[3]={0};
    int y=1;
    int temp;
    for(int i=0;i<3;i++)
    {
        do{
            temp=rand()%(width-2)+1;
            x[i]=temp;
        }while(temp%2!=0);
        a[x[i]+y*width]=enmy;
    }
}


char posvalue(float x)
{
    if(x<0)
        return '$';
    if(x==bullet)
        return 'o';
    if((int)x%2==0 && x>2)
        return '|';
    if((int)x%2==1 && x>2)
        return '#';
	if(x==1)
        return '|';
    if(x==2)
        return '-';
    if(x==0)
        return ' ';
}

void display()
{
    cout<<endl;
	for(int j=0;j<height;j++)
	{
	    cout<<"\t\t\t\t  ";
		for(int i=0;i<width;i++)
		{
           cout<<posvalue(a[i+j*width]);
		}
		cout<<endl;
	}
	cout<<"\tSCORE: "<<score;
}

void update()
{
    for(int i=0;i<area;i++)
    {
        if(a[i]==bullet)
        {
            a[i]=0;
            if(a[i-width]<0)
            {
                a[i-width]=0;
                score++;
            }
            else if(a[i-width]==2)
                a[i]=0;
            else
                a[i-width]=bullet;
        }
        if(a[i]==enmy)
        {
            a[i]=0;
            if(a[i+width]==xPos || a[i+width]==yPos)
                gameOn=false;
            else if(a[i+width]!=2)
                a[i+width]=enmy-1;
        }
    }
    enmy--;
}

int main()
{
    cout<<endl<<"\n\t\t\t\t******WELCOME TO THE PHENOM's CLUSTER !!!******"<<endl<<endl;
    cout<<"\n\n\t\t\tPress ENTER To start the game: ";
    cin.ignore();
    system("cls");
    int enChance=0;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|BACKGROUND_RED);
	layout();
	while(gameOn==true)
    {
         if(_kbhit())
         {
            control(getch());
         }
        if(enChance%4==0)
        {
            getEnemy();
        }
	    system("cls");
	    display();
	    update();
	    _sleep(400);
	    enChance++;
    }
    cout<<endl<<"\t\t\t\tGAMEOVER!!!"<<endl<<"\t\t\t\tFINAL SCORE: "<<score;
    getch();
    getch();
	return 0;
}
