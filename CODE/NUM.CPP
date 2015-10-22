#include <graphics.h>
#include<dos.h>
#include<fstream.h>
#include<string.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
char matrix_2[20][3]={"1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","0"},temp={0};
char matrix[20][3]={0},matrix_3[20][3]={0};

class number{
	int cur_x,cur_y,color;
	int i,x,y,j;
	char temp;
	fstream hi_score_file;
	public:
	number()
	{ cur_x=260;cur_y=260;color=10;
		i=0;
	}
	int change();
	void cursor();
	void boundary();
	void assign();
	void swap(int n1,int n2);
	int num_activate();
};

int number::change()
{
	int temp_x,temp_y,count=0;
	for(temp_y=50;temp_y<260+50;temp_y+=70)
		for(temp_x=50;temp_x<260+50;temp_x+=70)
		{
			if(temp_x==cur_x&&temp_y==cur_y)
				return(count);
			else
				count++;
		}
}

void number::cursor()
{
	setcolor(color);
	for(int j=0;j<4;j++)
		rectangle(cur_x+i-j,cur_y+i-j,cur_x+70-i+j,cur_y+70-i+j);
}


void number::boundary()
{
	char pattern[8]={123,231,345,123,12,233,45,3465 };
	setcolor(6);
	rectangle(50,50,330,330);
	setfillstyle(3,6);
	for(i=120;i<=190+70;i+=70)
	{
		rectangle(i-1,50,i+6,330);
		rectangle(50,i-1,330,i+6);
		bar(i,50,i+5,330);
		bar(50,i,330,i+5);
	}
	setcolor(3);
	for(i=0;i<5;i++)
		rectangle(getmaxx()-220-i,getmaxy()-220-i,getmaxx()-20+i,getmaxy()-20+i);
	for(i=50;i<=150;i+=50)
	{
		line(getmaxx()-220+i,getmaxy()-220,getmaxx()-220+i,getmaxy()-20);
		line(getmaxx()-220,getmaxy()-220+i,getmaxx()-20,getmaxy()-220+i);
	}
	setcolor(4);
	rectangle(0,0,getmaxx(),getmaxy());
	line(getmaxx()-250,0,getmaxx()-250,getmaxy());
	setcolor(6);
	settextstyle(3,0,2);
	outtextxy(100,5,"FlutterBy presents");
	outtextxy(120,25,"Number Puzzle");
	settextstyle(3,0,1);
	outtextxy(400,100,"Press 'r' to restart game");
	outtextxy(400,70,"Press'Esc' to exit game");
	setcolor(3);
	outtextxy(450,230,"Initial position");
	i=0;
	for(y=259+5;y<=259+200;y+=50)
		for(x=419+20;x<=419+200;x+=50)
		{
			if(strcmp(matrix_3[i],"0")!=0)
				outtextxy(x,y,matrix_3[i]);
			i+=1;
		}
}
void number::assign()
{
	int i=0;
	boundary();
	settextstyle(3,0,2);
	setcolor(3);
	i=0 ;
	for(y=75;y<=260+50;y+=70)
		for(x=75;x<=260+50;x+=70)
		{
			if(strcmp(matrix[i],"0")!=0)
				outtextxy(x,y,matrix[i]);
			i+=1;
		}

}

void number::swap(int n1,int n2)
{
	char temp[3];
	strcpy(temp,matrix[n1]);
	strcpy(matrix[n1],matrix[n2]);
	strcpy(matrix[n2],temp);
	cleardevice();

	boundary();
	cursor();
	assign();

	sound(1100);
	delay(15*5);
	nosound();
}

int number::num_activate()
{
	int g1=DETECT,g2;
	initgraph(&g1,&g2,"BGI\\")  ;
	int high_score=3000;
	int count=0,j,i,flag=0,move=1,x,y;
	char move_cur,hi_score_name[20]={"SYSTEM"};
	new_game:
	hi_score_file.open("hinum.txt",ios::in);
	if(!hi_score_file) /*HIGH SCORE FILE */
	{
		hi_score_file.close();
		hi_score_file.open("hinum.txt",ios::out);
		hi_score_file<<high_score<<" ";
		hi_score_file<<hi_score_name;
		hi_score_file.close() ;
		cleardevice();
		hi_score_file.open("hinum.txt",ios::in);
	}
	hi_score_file>>high_score;
	hi_score_file>>hi_score_name;

	randomize();
	for(i=0;i<16;i++)
	{
		matrix[i][0]=0;
		matrix_3[i][0]=0;
	}
	for(i=0;i<16;i++)
	{
		do{
			j=rand()%16;
			if(matrix[j][0]==0)
				break;
		}while(1);
		strcpy(matrix[j],matrix_2[i]);
		strcpy(matrix_3[j],matrix_2[i]);
	}
	cleardevice();
	assign();
	do{
		do{
			color=0;
			cursor();
			if(!kbhit())
			{
				color=4;
				cursor();
			}
			move_cur=getch();
			if(move_cur==LEFT)
				cur_x-=70;
			else if(move_cur==RIGHT)
				cur_x+=70;
			else if(move_cur==UP)
				cur_y-=70;
			else  if(move_cur==DOWN)
				cur_y+=70;

			else if(move_cur=='S')
			{
				for(i=0;i<16;i++)
					if(strcmp("0",matrix[i])==0)
						break;
				count=change();
				swap(i,count);
				gotoxy(60,10);
				printf("Moves : %d",move++);
			}
			else if(move_cur==27)
			{
				setcolor(25);
				outtextxy(150,getmaxy()-130,"Quit game(y/n)");
quit_game:
				move_cur=getch();
				if(move_cur=='n'||move_cur=='N')
				{
					setcolor(0);
					outtextxy(150,getmaxy()-130,"Quit game(y/n)");
					move_cur=0;
				}
				else if(move_cur=='y'||move_cur=='Y')
				{
					setcolor(0);
					outtextxy(150,getmaxy()-130,"Quit game(y/n)");
					setcolor(25);

end_start:
					outtextxy(100,getmaxy()-130,"start another game(y/n)");
					move_cur=getch();
					if(move_cur=='y'||move_cur=='Y')
					{move=1;

						goto new_game;
					}
					else if(move_cur=='n'||move_cur=='N')
					{
						move_cur=27;

					}
					else goto end_start;

				}
				else
					goto quit_game;
			}

			else if(move_cur=='r'||move_cur=='R')
			{
				outtextxy(150,getmaxy()-50,"Restart game(y/n)");
				move_cur=getch();
				if(move_cur=='y'||move_cur=='Y')
				{
					for(i=0;i<=16;i++)
						strcpy(matrix[i],matrix_3[i]);
					cleardevice();
					move=1;
					assign();
				}
				else
				{
					setcolor(0);
					outtextxy(150,getmaxy()-50,"Restart game(y/n)");
				}
			}
			if(cur_x>260)
				cur_x=260;
			else if(cur_y>260)
				cur_y=260;
			else if(cur_x<50)
				cur_x=50;
			else if(cur_y<50)
				cur_y=50;
			if(move_cur==27)
				break;
		}while(move_cur!=13);
		count=change();
		if(strcmp(matrix[count+1],"0")==0)
			swap(count,count+1);
		else if(strcmp(matrix[count-1],"0")==0)
			swap(count,count-1);
		else if(strcmp(matrix[count+4],"0")==0)
			swap(count,count+4);
		else if(strcmp(matrix[count-4],"0")==0)
			swap(count,count-4);
		else move--;
		gotoxy(60,10);
		printf("Moves : %d",move++);
		for(i=0;i<16;i++)
		{
			if(strcmp(matrix[i],matrix_2[i])==0)
				flag++;
		}
		if(flag==16)
		{
			setcolor(6);
			outtextxy(170,getmaxy()-100,"You win");
			getch();
			if(move<high_score)
			{
				hi_score_file.close();			 /* store high score data */
				hi_score_file.open("hinum.txt",ios::out);
				high_score=move;
				hi_score_file<<move;
				cleardevice();
				settextstyle(3, HORIZ_DIR,3 );
				outtextxy(getmaxx()/2-220,getmaxy()/2-30,"Congratulations... You Scored The Highest Score..");
				outtextxy(getmaxx()/2-100,getmaxy()/2,"Enter Your Name   ");
				gotoxy(33,22);
				setcolor(70);
				rectangle(5,5,getmaxx(),getmaxy());  /* DRAW BOUNDARY*/
				scanf("%s",hi_score_name);
				hi_score_file<<hi_score_name;
				hi_score_file.close();
			}
			break;
		}
		else
			flag=0;
	}while(move_cur!=27);
	for(i=0;i<getmaxy()/2;i++)
	{
		setcolor(4);
		rectangle(i,i,getmaxx()-i,getmaxy()-i);
		delay(10);
		setcolor(0);
		rectangle(i,i,getmaxx()-i,getmaxy()-i);
	}
	cleardevice();
	setcolor(1);
	rectangle(200,150,450,280);
	rectangle(0,0,getmaxx(),getmaxy());

	gotoxy(32,12);  printf("HIGH SCORE RECORDS");
	gotoxy(30,14);  printf("HIGH SCORE BY : %s",hi_score_name);
	gotoxy(29,16);  printf("IN JUST << %d >> MOVES",high_score);
	getch();
	hi_score_file.close();
	return 0;
	closegraph();
}

int main () {
	new number()->num_activate();
}

