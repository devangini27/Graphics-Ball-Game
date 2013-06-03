#include<stdio.h>
#include<string.h>
#include<math.h>
#include<dos.h>
#include<conio.h>
#include<iostream.h>
#include<graphics.h>
#include<stdlib.h>
#include <_defs.h>

#define SPACE '\x20'
#define LEFT '\x61'
#define RIGHT '\x64'
#define TOP '\x77'
#define DOWN '\x73'
#define RADIUS 10
#define XINC 10
#define YINC 10
#define BALLNO 6

int lives=3;
int energy=100;
int posx=80;
int posy=290;
int posxb[BALLNO]={120,170,480,300,220,410};
int posyb[BALLNO]={250,270,220,250,260,280};
int cols[BALLNO]={4,2,2,1,3,4};
int stop1=1;
int dir1=1;
int dir2=-1;
int ballok[BALLNO]={1,1,1,1,1,1};

int points=0;
char pointstr[3]="000";
float pt[3]={0,0,0};
float tmp[3]={0,0,0};
float t[3][3]={1,0,0,0,1,0,0,0,1};

int intro();
int drawscreen();
int instr();
int play();
int play1();
int drawback1();
int drawstatus();
int drawchar();
int remchar();
int gameover();
int mul31(float [3][3],float [3]);
int translate(float,float);
int drawball(int);
int remball(int);
int mov1();
int mov2();

int check();
int getpoint();
int lifegone();
int givelife();
int giveenergy();

int left();
int right();
int up();
int down();

struct time t1;
struct time currt;

int main(void)
{
   char d;
   /* request auto detection */
   int gdriver = DETECT, gmode, errorcode;

   /* initialize graphics and local variables */
   initgraph(&gdriver, &gmode, "");

   /* read result of initialization */
   errorcode = graphresult();
   /* an error occurred */
   if (errorcode != grOk)
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1);
   }

   drawscreen();
   delay(2000);
   intro();

   char opt[55]="Press space to skip";
   opt[55]='\0';
   settextstyle(3,HORIZ_DIR,2);
   outtextxy(70,400,opt);

   if(kbhit)
   {
	d=getch();
	if(d!='\x20')
	{
	     drawscreen();
	     instr();
	     setcolor(15);
	     strcpy(opt,"Press space to continue");
	     opt[23]='\0';
	     outtextxy(70,400,opt);

AB:	     if(kbhit)
	     {
		 d=getch();
		 if(d!=SPACE)
		    goto AB;
	     }

	}
   }
   drawscreen();
   strcpy(opt,"Press space to commence");
   opt[23]='\0';
   setcolor(15);
   outtextxy(80,200,opt);
CD:
   if(kbhit)
   {
	d=getch();
	if(d!=SPACE)
	  goto CD;
   }

   play();

   /* clean up */
   getch();
   closegraph();
   return 0;
}

int intro()
{
    char buffer[]="WeLcOmE tO tHe WoRlD oF bAlLs!";
    int start=200,end=150,i,j=0;
    char c[2];
    setcolor(15);
    settextstyle(2,HORIZ_DIR,10);
    buffer[30]='\0';
    c[1]='\0';
    for(i=0;i<30;i++)
    {
	if(buffer[i]==' ')
	{
	   end=end+30;
	   if(j==0)
	   {
	      start=230;
	   }
	   gotoxy(start,end);
	}
	else
	{
	     c[0]=buffer[i];
	     outtextxy(start,end,c);
	     start=start+20;
	     delay(200);
	}
    }
     return(0);
}

int drawscreen()
{
      cleardevice();

      setcolor(5);
      rectangle(50,50,590,430);
      setfillstyle(SOLID_FILL,9);
      floodfill(60,60,5);
      char list[40]="created and designed by Devangini Patel";
      list[39]='\0';
      settextstyle(2,HORIZ_DIR,6);
      outtextxy(250,460,list);
      return(0);
}

int gameover()
{
     setcolor(0);
     char buffer[9]="Game over";
     buffer[9]='\0';
     outtextxy(250,200,buffer);
     delay(1000);
     return(0);
}

int win()
{
    setcolor(0);
    char buffer[7]="You win";
    buffer[7]='\0';
    outtextxy(250,200,buffer);
    delay(1000);
    return(0);
}

int drawstatus()
{
     int cent[3][2]={510,130,540,130,570,130};
     char buffer[6]="energy";
     buffer[6]='\0';
     setcolor(15);
     outtextxy(420,80,buffer);
     setcolor(14);
     rectangle(490,70,590,100);
     setfillstyle(SOLID_FILL,0);
     floodfill(510,80,14);
     setcolor(15);
     if(energy>0)
     {
	rectangle(490,70,490+energy,100);
	setfillstyle(SOLID_FILL,15);
	floodfill(491,80,15);
     }
     else
     {
	 lives=lives-1;
	 energy=100;
     }
     setcolor(15);
     strcpy(buffer,"lives");
     buffer[5]='\0';
     outtextxy(420,120,buffer);
     if(lives>0)
     {
	  for(int i=0;i<lives;i++)
	  {
		setcolor(1);
		setfillstyle(SOLID_FILL,1);
		circle(cent[i][0],cent[1][1],10);
		floodfill(cent[i][0],cent[i][1],1);
	  }
	  for(int j=lives;j<3;j++)
	  {
	      setcolor(9);
	      setfillstyle(SOLID_FILL,9);
	      circle(cent[j][0],cent[j][1],10);
	      floodfill(cent[j][0],cent[j][1],9);
	  }
     }
     else
     {
	 gameover();
     }
     setcolor(15);
     strcpy(buffer,"Points");
     buffer[6]='\0';
     outtextxy(420,160,buffer);
     outtextxy(510,160,pointstr);
     return(0);
}

int instr()
{
    setcolor(0);
    char in[12]="Instructions";
    in[12]='\0';
    outtextxy(70,70,in);

    setcolor(4);
    circle(70,120,15);
    setfillstyle(SOLID_FILL,4);
    floodfill(70,120,4);
    setcolor(15);
    char buffer[21]="balls to be collected";
    buffer[21]='\0';
    outtextxy(150,130,buffer);

    setcolor(2);
    circle(70,180,15);
    setfillstyle(SOLID_FILL,2);
    floodfill(70,180,2);
    setcolor(15);
    strcpy(buffer,"danger balls");
    buffer[12]='\0';
    outtextxy(150,190,buffer);

    setcolor(1);
    circle(70,240,15);
    setfillstyle(SOLID_FILL,1);
    floodfill(70,240,1);
    setcolor(15);
    strcpy(buffer,"life balls");
     buffer[10]='\0';
     outtextxy(150,250,buffer);

     setcolor(3);
    circle(70,310,15);
    setfillstyle(SOLID_FILL,3);
    floodfill(70,310,3);
    setcolor(15);
    strcpy(buffer,"energy balls");
     buffer[12]='\0';
     outtextxy(150,330,buffer);

    setcolor(0);
    strcpy(buffer,"Controls");
    buffer[8]='\0';
    outtextxy(450,300,buffer);

    setcolor(13);
    rectangle(420,360,450,390);
    rectangle(460,360,490,390);
    rectangle(500,360,530,390);
    rectangle(460,320,490,350);

    setcolor(14);
    strcpy(buffer,"a");
    buffer[1]='\0';
    outtextxy(435,370,buffer);
    strcpy(buffer,"s");
    outtextxy(475,370,buffer);
    strcpy(buffer,"d");
    outtextxy(515,370,buffer);
    strcpy(buffer,"w");
    outtextxy(475,330,buffer);

    return(0);
}

int drawback1()
{
    int i;
    char buffer[3]="end";
    buffer[3]='\0';
    setcolor(6);
    rectangle(50,301,590,330);
    setfillstyle(SOLID_FILL,6);
    floodfill(60,310,6);

    for(i=0;i<BALLNO;i++)
    {
	drawball(i);
    }
    setcolor(0);
    line(560,400,560,300);
    outtextxy(557,405,buffer);
    return(0);
}

int drawchar()
{
    setcolor(11);
    circle(posx,posy,RADIUS);
    setfillstyle(SOLID_FILL,11);
    floodfill(posx,posy,11);
    return(0);
}

int drawball(int i)
{
    setcolor(cols[i]);
    circle(posxb[i],posyb[i],RADIUS);
    setfillstyle(SOLID_FILL,cols[i]);
    floodfill(posxb[i],posyb[i],cols[i]);
    return(0);
}

int remball(int i)
{
    setcolor(9);
    circle(posxb[i],posyb[i],RADIUS);
    setfillstyle(SOLID_FILL,9);
    floodfill(posxb[i],posyb[i],9);
    return(0);
}

int remchar()
{
    setcolor(9);
    circle(posx,posy,RADIUS);
    setfillstyle(SOLID_FILL,9);
    floodfill(posx,posy,9);
    return(0);
}

int mul31(float a[3][3],float b[3])
{
    int i,j;
    for(i=0;i<3;i++)
    {
	tmp[i]=0;
	for(j=0;j<3;j++)
	{
	    tmp[i]=tmp[i]+(a[i][j])*(b[j]);
	}
    }
    return(0);
}

int translate(float tx,float ty)
{
    int i;
    t[0][2]=tx;
    t[1][2]=ty;
	pt[0]=posx;
	pt[1]=posy;
	pt[2]=1;
	mul31(t,pt);
	posx=tmp[0];
	posy=tmp[1];
    return(0);
}

int mov1()
{
    if(dir1==1)
    {
       if(posyb[1]>200)
       {
	   remball(1);
	   posyb[1]=posyb[1]-10;
	   drawball(1);
       }
       else
	  dir1=-1;
    }
    else
    {
	  if(posyb[1]>270)
	     dir1=1;
	  else
	  {
	      remball(1);
	      posyb[1]=posyb[1]+10;
	      drawball(1);
	  }
    }
    return(0);
}

int mov2()
{
    if(dir2==1)
    {
       if(posyb[2]>200)
       {
	   remball(2);
	   posyb[2]=posyb[2]-10;
	   drawball(2);
       }
       else
	  dir2=-1;
    }
    else
    {
	  if(posyb[2]>270)
	     dir2=1;
	  else
	  {
	      remball(2);
	      posyb[2]=posyb[2]+10;
	      drawball(2);
	  }
    }
    return(0);
}


int down()
{
    if(ballok[1])
       mov1();
    if(ballok[2])
       mov2();
    remchar();
    translate(0,YINC);
    drawchar();
    delay(300);
    check();
    return(0);
}

int up()
{
   if(ballok[1])
      mov1();
   if(ballok[2])
      mov2();
   remchar();
   translate(0,-YINC);
   drawchar();
   energy=energy-2;
   drawstatus();
   delay(300);
   check();
   return(0);
}

int left()
{
   if(ballok[1])
     mov1();
   if(ballok[2])
      mov2();
   remchar();
   translate(-XINC,0);
   drawchar();
   energy=energy-2;
   drawstatus();
   delay(300);
   check();
   return(0);
}

int right()
{
   if(ballok[1])
       mov1();
   if(ballok[2])
       mov2();
   remchar();
   translate(XINC,0);
   drawchar();
   energy=energy-2;
   drawstatus();
   delay(300);
   check();
   return(0);
}

int getpoint()
{
    points=points+1;
    setcolor(9);
    outtextxy(510,160,pointstr);
    setcolor(15);
    pointstr[1]=char(points)+48;
    drawstatus();
    return(0);
}

int lifegone()
{
    lives=lives-1;
    drawstatus();
    return(0);
}

int givelife()
{
    if(lives<3)
       lives=lives+1;
    drawstatus();
    return(0);
}

int giveenergy()
{
    if(energy<=50)
       energy=energy+50;
    else
       energy=100;
    return(0);
}

int check()
{
    int i;
    float a,b,c;
    for(i=0;i<BALLNO;i++)
    {
	if(!ballok[i])
	    continue;
	a=posx-posxb[i];
	b=posy-posyb[i];
	c=a*a+b*b;
	c=sqrt(c);
	if(c<=2*RADIUS)
	{
	    ballok[i]=0;
	    remchar();
	    remball(i);
	    if(i==0)
		getpoint();
	    else if(i==1)
		lifegone();
	    else if(i==2)
	       lifegone();
	    else if(i==3)
		givelife();
	    else if(i==4)
		giveenergy();
	    else if(i==5)
		getpoint();
	    drawchar();
	}
    }
    return(0);
}

int play1()
{
    int over=0,count=0,i;
    char c,c1,c2;
    drawback1();
    drawchar();

    while(!over)
    {
	if(lives==0)
	    over=1;
	if(posx>=560)
	{
	   win();
	   over=1;
	}
	if(kbhit)
	{
	       c=getch();
	       if(c==DOWN)
	       {
		  if(posy<290)
		  {
		      down();
		      delay(300);
		  }
	       }
	       else if(c==RIGHT)
	       {
		  if(posx<560)
		  {
		      right();
		      delay(300);
		  }
	       }
	       else if(c==LEFT)
	       {
		   if(posx>80)
		   {
		     left();
		     delay(300);
		   }
	       }
	       else if(c==TOP)
	       {
		   count++;
		   up();
		   if(kbhit)
		   {
		       c=getch();
		       if(c==RIGHT)
		       {
			     right();
			     if(kbhit)
				  c=getch();
		       }
		       if(c==LEFT)
		       {
			    left();
			    if(kbhit)
			       c=getch();
		       }
		       if(c==DOWN)
		       {
			    count--;
			    down();
		       }
		       if(c==TOP)         //triple jump
		       {
			   count++;
			   up();
			   if(kbhit)
			   {
			       c=getch();
			       if(c==RIGHT)
			       {
				   right();
				   if(kbhit)
				      c=getch();
			       }
			       if(c==LEFT)
			       {
				   left();
				   if(kbhit)
				      c=getch();
			       }
			       if(c==DOWN)
			       {
				   count--;
				   down();
			       }
			       if(c==TOP)
			       {
				    count++;
				    up();
			       }
			   }
		       }
		   }
		   for(i=0;i<count;i++)
		   {
		       if(kbhit)
		       {
			   c=getch();
			   if(c==LEFT)
			       left();
			   else if(c==RIGHT)
			      right();
		       }
		       down();
		       delay(300);
		   }
		   count=0;
	       }

	    }
    }

    return(0);
}

int play()
{
    drawscreen();
    drawstatus();
    play1();
    return(0);
}