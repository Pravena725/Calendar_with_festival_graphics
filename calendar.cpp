#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <string.h>
#include <graphics.h>
#include <time.h>
#include <dos.h>
#include<windows.h>

void val_timezones(void);
int isLeapYear( int year );        //True if leap year
int leapYears( int year );         //The number of leap year
int todayOf( int y, int m, int d); //The number of days since the beginning of the year
long days( int y, int m, int d);   //Total number of days
void calendar(int y, int m);       //display calendar at m y
int getDayNumber(int d,int m,int y);
const char *getName(int day);
void festival(char ch[20]);

void flush()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

typedef struct
{
  int day;
  int month;
  int year;
  char note[255];
} Note;

void minSecPos1(int xrad, int midx, int midy, int x[60], int y[60])
{
    int i, j=45;
    for (i=360; i>=0; i=i-6)
    {
        x[j] = midx-(xrad*cos((i*3.14)/180));
        y[j--] = midy-(xrad*sin((i*3.14)/180));
        j = (j==-1)?59:j;
    }
    return;
}

void calcPoints1(int radius, int midx, int midy, int x[12], int y[12])
{
  int x1, y1;
  x[0] = midx, y[0] = midy-radius;
  x[6] = midx, y[6] = midy+radius;
  x[3] = midx+radius, y[3] = midy;
  x[9] = midx-radius, y[9] = midy;

  x1 = (int) ((radius/2)*sqrt(3));
  y1 = (radius/2);
  x[2] = midx+x1, y[2] = midy-y1;
  x[4] = midx+x1, y[4] = midy+y1;
  x[8] = midx-x1, y[8] = midy+y1;
  x[10] = midx-x1, y[10] = midy-y1;

  x1 = radius/2;
  y1 = (int) ((radius/2)*sqrt(3));
  x[1] = midx+x1, y[1] = midy-y1;
  x[5] = midx+x1, y[5] = midy+y1;
  x[7] = midx-x1, y[7] = midy+y1;
  x[11] = midx-x1, y[11] = midy-y1;
  return;
}

void cal_timezones()
{
    struct tm *local;
    time_t t;
    int ch;
    t=time(NULL);
    local=localtime(&t);

    local->tm_mon+=1;
    local->tm_year+=1900;

    printf("Some of the major countries in the world are -:\n");
    printf("1)Argentina  2)Algeria  3)Australia  4)Austria  5)Brazil  6)Belgium  7)Bhutan\n");
    printf("8)China  9)Canada  10)Denmark  11)Egypt  12)France  13)Finland  14)Germany\n");
    printf("15)Greece  16)Indonesia  17)Italy  18)Japan  19)Mexico  20)Malaysia  21)New Zealand\n");
    printf("22)Russia  23)Sweden  24)Switzerland  25)Singapore  26)USA  27)UK  28)UAE\n\n");

    printf("Enter the no.\t");
    scanf("%d",&ch);
    if(ch==1 || ch==5)
    {
        local->tm_hour-=8;
        local->tm_min-=30;
    }
    if(ch==2 || ch==4 || ch==6  || ch==10 || ch==12 || ch==14 || ch==17 || ch==23 || ch==24)
    {
        local->tm_hour-=4;
        local->tm_min-=30;
    }
    if(ch==3)
    {
        local->tm_hour+=3;
        local->tm_min+=15;
    }
    if(ch==7)
    {
        local->tm_min+=30;
    }
    if(ch==8 || ch==20 || ch==25)
    {
        local->tm_hour+=2;
        local->tm_min+=30;
    }
    if(ch==9 || ch==26)
    {
        local->tm_hour-=10;
        local->tm_min-=30;
    }
    if(ch==11 || ch==13 || ch==15)
    {
        local->tm_hour-=3;
        local->tm_min-=30;
    }
    if(ch==16)
    {
        local->tm_hour+=2;
        local->tm_min+=30;
    }
    if(ch==18)
    {
        local->tm_hour+=3;
        local->tm_min+=30;
    }
    if(ch==19)
    {
        local->tm_hour-=11;
        local->tm_min-=30;
    }
    if(ch==21)
    {
        local->tm_hour+=7;
        local->tm_min+=30;
    }
    if(ch==22)
    {
        local->tm_hour+=1;
        local->tm_min+=30;
    }
    if(ch==28)
    {
        local->tm_hour-=1;
        local->tm_min-=30;
    }

    if(local->tm_min>60)
    {
        local->tm_min-=60;
        local->tm_hour+=1;
    }

    if(local->tm_min<0)
    {
        local->tm_min+=60;
        local->tm_hour-=1;
    }
    if(local->tm_hour>24)
    {
       local->tm_hour-=24;
       local->tm_mday+=1;
    }

    if(local->tm_hour<0)
    {
        local->tm_mday-=1;
        local->tm_hour+=24;

    }
    printf("\n\n");
    printf("THE DATE is -: %d / %d / %d \n",local->tm_mday,local->tm_mon,local->tm_year);
    printf("THE TIME in 24 HOUR format is -: %d: %d: %d \n",local->tm_hour,local->tm_min,local->tm_sec);
    printf("\nTHE TIME on ANALOG CLOCK is -:\n");

    delay(4000);


    int gd=DETECT, gm, err, tmp;
    initgraph(&gd, &gm, "");

    int i, j, midx, midy, radius, hr, min, sec;
    int x[12], y[12], minx[60], miny[60];
    int hrx[12], hry[12], secx[60], secy[60];
    int secx1, secy1;
    char str[256];

    err = graphresult();

    if (err != grOk)
    {
        printf("Graphics Error: %s",grapherrormsg(err));
        //return 0;
    }

    midx = getmaxx()/2;
    midy = getmaxy()/2;

    radius = 200;

    calcPoints1(radius-30, midx, midy, x, y);
    calcPoints1(radius-90, midx, midy, hrx, hry);

    minSecPos1(radius-50, midx, midy, minx, miny);
    minSecPos1(radius-70, midx, midy, secx, secy);

    while (!kbhit())
    {
        setlinestyle(SOLID_LINE, 1, 3);
        settextstyle(GOTHIC_FONT, 0, 3);

        circle(midx, midy, radius);

        for (j=0; j<12; j++)
        {
            if (j==0)
                sprintf(str, "%d", 12);
            else
                sprintf(str, "%d", j);

            settextjustify(CENTER_TEXT, CENTER_TEXT);
            moveto(x[j], y[j]);
            outtext(str);
        }
        sec = local->tm_sec % 60;
        line(midx, midy,secx[sec], secy[sec]);

        min = local->tm_min % 60;
        line(midx, midy, minx[min], miny[min]);

        hr = local->tm_hour % 12;
        line(midx, midy, hrx[hr], hry[hr]);
        delay(1000);
        local->tm_sec+=1;
        if(local->tm_sec==60)
            local->tm_min+=1;
        cleardevice();
    }
    closegraph();
}

int main(int argc, char* argv[])
{
    int year,month, day;
    char choice;
    Note note;
    FILE *fp;

    fp = fopen("note.bin", "r");
    if (fp == NULL)
        fp = fopen("note.bin", "w");
    fclose(fp);

    while(1)
    {
        printf("1. Find the day\n");
        printf("2. Print calendar of a month\n");
        printf("3. Add Note\n");
        printf("4. Time presently in INDIA\n");
        printf("5. Time at a different zone\n");
        printf("6. Alarm\n");
        printf("7. Date of a particular Festival\n");
        printf("8. EXIT\n");
        printf("Enter your choice: ");
        scanf("\n%c", &choice);
        printf("\n");
        switch(choice)
        {
            case '1':
                printf("Enter the day, month and year: ");
                scanf("%d %d %d", &day, &month, &year);
                printf("The day is : %s\n", getName(getDayNumber(day, month, year)));
                delay(5000);
                system("cls");
            break;
            case '2':
                printf("Enter the month and year: ");
                scanf("%d %d", &month, &year);
                printf("Please enter 's' to see the notes\n Press any other key to continue\n");
                calendar(year, month);
                delay(5000);
                system("cls");
            break;
            case '3':
                printf("Enter the day, month and year: ");
                scanf("%d %d %d", &note.day, &note.month, &note.year);
                flush();
                printf("Enter the note: ");
                fgets(note.note, 255, stdin);
                fp = fopen("note.bin", "ab+");
                if (fp == NULL)
                {
                    printf("File note.bin can not be opened\n");
                    exit(1);
                }
                fwrite(&note, sizeof(Note), 1, fp);
                printf("Note added sucessfully\n");
                delay(5000);
                fclose(fp);
                system("cls");
            break;
            case '4':
            {
                int gd=DETECT;//to detect the drive
                int gm;
                initgraph(&gd,&gm,"");//to load the graphics drive and put the system into graphics mode

                time_t rawTime;//for representing time ,which is returned by time function

                struct tm * currentTime;//structure type variable which gives details of current time
                char a[100];

                while (!kbhit())
                {
                    rawTime=time(NULL);//time function returns the value as a time_t object
                    currentTime=localtime(&rawTime);//local time return a pointer to a tm struct with all the time information
                    //fillled in its memeber
                    strftime(a,100,"%I:%M:%S",currentTime);//%I -> no. of hours
                    //%M -> no. of minutes
                    //%S -> no. of seconds    ....returns all these to char a

                    setcolor(9);
                    settextstyle(3, HORIZ_DIR, 10);
                    outtextxy(200,100,a);

                    strftime(a,100, "%p", currentTime);//%p format specifier for AM PM
                    settextstyle(3, HORIZ_DIR, 2);
                    outtextxy(600,8,a);

                    strftime(a,100, "%a, %d %b, %Y", currentTime);//%a for day
                    //%d for day of month
                    //%b for month
                    //%y for year
                    settextstyle(3, HORIZ_DIR, 5);
                    outtextxy(130,310,a);

                    delay(1000);
                    cleardevice();
                }
                closegraph();
                system("cls");
            }
            break;
            case '5':
            {
                cal_timezones();
                system("cls");
            }
            break;
            case '6':
            {
                time_t now;
                struct tm *right_now;
                int hour,minutes;
                printf("Enter Hour:");
                scanf("%d",&hour);
                printf("Enter minutes:");
                scanf("%d",&minutes);
                while(1)
                {
                    time(&now);
                    right_now=localtime(&now);
                    if(hour == right_now->tm_hour & minutes == right_now->tm_min)
                    {
                        printf("\nTime up!!\n");
                        printf("\a"); //to give the sound
                        break;
                    }
                    else
                    {
                        free(right_now);
                    }
                }
                //system("cls");
            }
            break;
            case '7':
            {
                char ch[20];
                while(1)
                {
                    printf("List of festivals for which date can be searched\n\n");
                    printf("1) New year\t2) Sankranthi\t3)Republic Day\t4) Holi\t5) Ramzan\t6) Bakrid\n");
                    printf("7) Independence Day\t8) Ganesh Chaturthi\t9) Mohoram\t10) Onam\t11) Teachers Day\n");
                    printf("12) Gandhi Jayanthi\t13) Dussehra\t14) Childrens Day\t15) Diwali\t16) Christmas\n\n");
                    printf("Enter 'done' if you want to quit \n\n");
                    printf("Enter festival name whose date you want to know\n\n");
                    if(strcmp(ch,"done")==0)
                        break;
                    festival(gets(ch));
                    system("cls");
                }
            }
            break;
            case '8':
                printf("Bye!!");
                exit(0);
                system("cls");
            break;
            default:
                printf("Not a valid option\n");
                system("cls");
            break;
        }
    }
    return 0;
}

int isLeapYear( int y )
{
    return(y % 400 == 0) || ((y % 4 == 0) && (y % 100 != 0));
}

void festival(char ch[20])
{
    if(strcmp(ch,"New year")==0)
    {
        printf("Celebrated on January 1");
        delay(2000);
        int gd=DETECT,gm,i,x,y,rad=1;
        initgraph(&gd, &gm, " ");
	    settextstyle(GOTHIC_FONT,HORIZ_DIR,5);
        outtextxy(70, 150, "Happy New Year !!");
        delay(5000);
        cleardevice();
    }

    if(strcmp(ch,"Sankranthi")==0)
    {
        printf("Celebrated on January 15");
        delay(3000);
        int gd=DETECT,gm;
        initgraph(&gd,&gm,"");
        int color;
        int x=10,y=1,tx=10,ty=10,i=0;
        int poly[10];

        while(i!=50)
        {
            x += tx;
            if(x > 200)
                tx = -5;
            if(x < 0 )
                tx = 10;
            y += tx;
            if(y > 100)
                ty = -10;
            if(y < 0 )
                ty = 10;
            cleardevice();
            setcolor(WHITE);
            //setbkcolor(BLUE);
            poly[0]=100+x;
            poly[1]=50+y;
            poly[2]=140+x;
            poly[3]=100+y;
            poly[4]=100+x;
            poly[5]=155+y;
            poly[6]=60+x;
            poly[7]=100+y;
            poly[8]=100+x;
            poly[9]=50+y;
            drawpoly(5,poly);
            setfillstyle(SOLID_FILL,LIGHTBLUE);
            fillpoly(3,poly);
            setlinestyle(SOLID_LINE,1,3);
            line(100+x,155+y,100+x,180+y);
            line(100+x,155+y,110+x,180+y);
            line(100+x,155+y,90+x,180+y);
            setlinestyle(SOLID_LINE,1,0);
            line(0,480,100+x,90+y);
            line(100+x,90+y,130+x,100+y);
            line(100+x,90+y,70+x,100+y);
            line(100+x,90+y,100+x,70+y);
            setcolor(GREEN);
            settextstyle(GOTHIC_FONT,HORIZ_DIR,35 );
            outtextxy(200,100,"HAPPY SANKRANTHI !!");
            delay(200);
            i++;
        }

        setlinestyle(SOLID_LINE,0,0);
        fflush(stdin);
    }
    if(strcmp(ch,"Republic Day")==0)
    {
        printf("Celebrated on January 26");
        delay(2000);
        int gd=DETECT,gm;
        int r,i,a,b,x,y;
        float PI=3.14;
        initgraph(&gd,&gm,"");
        //for the top rectangle and to color it
        setcolor(LIGHTRED);
        rectangle(100,100,450,150);
        setfillstyle(SOLID_FILL,LIGHTRED);
        floodfill(101,101,LIGHTRED);
        //for the middle rectangle and to color it
        setcolor(WHITE);
        rectangle(100,150,450,200);
        setfillstyle(SOLID_FILL,WHITE);
        floodfill(101,151,WHITE);
        //for the bottom rectangle and to color it
        setcolor(GREEN);
        rectangle(100,200,450,250);
        setfillstyle(SOLID_FILL,GREEN);
        floodfill(101,201,GREEN);
    	//draw the circle
        setcolor(BLUE);
        a=275;
        b=175;
        r=25;
        circle(a,b,r);
        //spokes
        for(i=0;i<=360;i=i+15)
        {
            x=r*cos(i*PI/180);
            y=r*sin(i*PI/180);
            line(a,b,a+x,b-y);
        }
    	//the stand
        setcolor(WHITE);
        line(100,200,100,600);
        //text
        setcolor(GREEN);
        settextstyle(GOTHIC_FONT,HORIZ_DIR,50 );
        outtextxy(250,300,"JAI HIND !!");
        delay(7000);
        cleardevice();
    }

    if(strcmp(ch,"Holi")==0)
    {
        printf("Celebrated on March 10");
        delay(2000);
        int gd=DETECT,gm,i=0,a=0;
        float r=20;
        initgraph(&gd,&gm,"");

        for(i=1;i<100;i++)
        {
            if(a!=i/15)
                delay(300);
            a=i/15;
            setcolor(a);
            arc(200,350,0,180,r+i);
        }
        setcolor(GREEN);
        settextstyle(GOTHIC_FONT,HORIZ_DIR,35 );
        outtextxy(100,100,"HAPPY HOLI !!");
        delay(2000);
    }
    if(strcmp(ch,"Ramzan")==0)
    {
        printf("Celebrated on May 24");
        delay(2000);
        int gdriver=DETECT,gmode;
        initgraph(&gdriver,&gmode,"");
        //moon
        for(int i=0;i<200;i++)
        {
            arc(300+i,300,80,320,100);
            arc(300+i,300,130,270,70);
            line(250+i,250,317+i,200);
            line(300+i,370,375+i,366);
            outtextxy(100,100,"RAMADAN MUBARAK");
            //star
            line(350+i,300,450+i,300);
            line(350+i,300,400+i,250);
            line(400+i,250,450+i,300);

            line(400+i,320,350+i,265);
            line(350+i,265,445+i,265);
            line(445+i,265,400+i,320);
            //color
            setfillstyle(8,9);
            floodfill(300,250,WHITE);
            floodfill(400,20,WHITE);

            delay(5);
            cleardevice();
        }
    }
    if(strcmp(ch,"Bakrid")==0)
    {
        printf("Celebrated on August 3");
        delay(2000);
        int gdriver=DETECT,gmode;
        initgraph(&gdriver,&gmode,"");
        //moon
        for(int i=0;i<200;i++)
        {
            arc(300+i,300,80,320,100);
            arc(300+i,300,130,270,70);
            line(250+i,250,317+i,200);
            line(300+i,370,375+i,366);
            outtextxy(100,100,"EID MUBARAK");
            //star
            line(350+i,300,450+i,300);
            line(350+i,300,400+i,250);
            line(400+i,250,450+i,300);

            line(400+i,320,350+i,265);
            line(350+i,265,445+i,265);
            line(445+i,265,400+i,320);
            //color
            setfillstyle(8,3);
            floodfill(300,250,WHITE);
            floodfill(400,20,WHITE);

            delay(5);
            cleardevice();
        }
    }
    if(strcmp(ch,"Independence Day")==0)
    {
        printf("Celebrated on August 15");
        delay(4000);
        printf("Celebrated on January 26");
        delay(4000);
        int gd=DETECT,gm;
        int r,i,a,b,x,y;
        float PI=3.14;
        initgraph(&gd,&gm,"");
        //for the top rectangle and to color it
        setcolor(LIGHTRED);
        rectangle(100,100,450,150);
        setfillstyle(SOLID_FILL,LIGHTRED);
        floodfill(101,101,LIGHTRED);
        //for the middle rectangle and to color it
        setcolor(WHITE);
        rectangle(100,150,450,200);
        setfillstyle(SOLID_FILL,WHITE);
        floodfill(101,151,WHITE);
        //for the bottom rectangle and to color it
        setcolor(GREEN);
        rectangle(100,200,450,250);
        setfillstyle(SOLID_FILL,GREEN);
        floodfill(101,201,GREEN);
    	//draw the circle
        setcolor(BLUE);
        a=275;
        b=175;
        r=25;
        circle(a,b,r);
        //spokes
        for(i=0;i<=360;i=i+15)
        {
            x=r*cos(i*PI/180);
            y=r*sin(i*PI/180);
            line(a,b,a+x,b-y);
        }
    	//the stand
        setcolor(WHITE);
        line(100,200,100,600);
        //text
        setcolor(GREEN);
        settextstyle(GOTHIC_FONT,HORIZ_DIR,50 );
        outtextxy(250,300,"JAI HIND !!");
        delay(7000);
        cleardevice();
    }
    if(strcmp(ch,"Ganesh Chaturthi")==0)
    {
        printf("Celebrated on August 22");
        delay(2000);
        int gm,gd,i,a=0;
        gm=gd=DETECT;
        initgraph(&gm,&gd,"");

        for(i=0;i<15;i++)
        {
            setcolor(GREEN);
            settextstyle(GOTHIC_FONT,HORIZ_DIR,25 );
            outtextxy(100,50,"Happy Ganesh Caturthi !!");
            setcolor(i);
            ellipse(235,250,130,420,100,90);
            ellipse(240,320,0,360,4,4);
            //leg
            ellipse(170,330,105,355,100,50);
            ellipse(343,330,195,100,80,50);
            //head
            ellipse(245,147,50,140,40,51);
            ellipse(186,150,50,140,40,51);
            //ear
            arc(240,138,290,410,50);
            arc(195,135,150,260,50);
            //trunk
            setcolor(i+1);
            ellipse(185,180,550,290,0,10);
            ellipse(225,200,170,280,40,30);
            ellipse(250,180,550,290,0,10);
            ellipse(285,173,200,280,40,30);
            ellipse(260,229,0,360,40,1);
            ellipse(270,277,9,100,80,50);
            ellipse(270,250,6,90,80,50);
            //eyes
            ellipse(200,150,0,70,10,10);
            ellipse(240,150,98,180,10,10);
            delay(400);
            cleardevice();
        }
    }
    if(strcmp(ch,"Mohoram")==0)
    {
        printf("Its on August 29");
        delay(2000);
        int gd=DETECT,gm,i,x,y,rad=i;
        initgraph(&gd,&gm," ");
        int a=0;
        arc(300+i,300,80,320,100);
        arc(300+i,300,130,270,70);
        line(250+i,250,317+i,200);
        line(300+i,370,375+i,366);
        //star
        line(350+i,300,450+i,300);
        line(350+i,300,400+i,250);
        line(400+i,250,450+i,300);
        line(400+i,320,350+i,265);
        line(350+i,265,445+i,265);
        line(445+i,265,400+i,320);
        //color
        setfillstyle(8,4);
        floodfill(300,250,WHITE);
        floodfill(400,20,WHITE);
        while(!kbhit())
        {
            setcolor(a++);
            settextstyle(GOTHIC_FONT,HORIZ_DIR,5);
            outtextxy(50,50,"SAAL MUBARAK");
            delay(100);

        }
    }
    if(strcmp(ch,"Onam")==0)
    {
        printf("Celebrated on August 31");
        delay(2000);
        int gdriver = DETECT, gmode, err;
        int i = 0, j, x, y, x1, y1, x2, y2;
        initgraph(&gdriver, &gmode, "C:/TURBOC3/BGI");
        err = graphresult();
        outtextxy(50,50,"HAPPY ONAM");
        if (err != grOk)
        {
            printf("Graphics Error: %s\n",
            grapherrormsg(err));
        }
        j = 0;
        //initialize position for boat
        x = 50, y = getmaxy() / 2 + 140;
        while (x + 60 < getmaxx() && (!kbhit()))
        {
            //setting the color of the river/sea
            setcolor(LIGHTBLUE);
            setlinestyle(SOLID_LINE, 1, 1);
            setfillstyle(SOLID_FILL, LIGHTBLUE);
            //draw the river/sea
            rectangle(0, getmaxy() / 2 + 150, getmaxx(), getmaxy());
            floodfill(getmaxx() - 10, getmaxy() - 10, LIGHTBLUE);
            //drawing the boat
            setlinestyle(SOLID_LINE, 1, 2);
            setcolor(BROWN);
            setfillstyle(SOLID_FILL, BROWN);
            sector(x, y, 180, 360, 50, 10);
            setcolor(DARKGRAY);
            setlinestyle(SOLID_LINE, 1, 3);
            //leg and body of stick man
            line(x + 40, y - 15, x + 40, y - 40);
            line(x + 40, y - 15, x + 45, y - 10);
            line(x + 45, y - 10, x + 45, y);
            line(x + 40, y - 15, x + 37, y);
            //head and hand of stick man
            circle(x + 40, y - 45, 5);
            line(x + 40, y - 35, x + 50, y - 30);
            line(x + 40, y - 35, x + 35, y - 32);
            line(x + 35, y - 32, x + 45, y - 25);
            line(x + 60, y - 45, x + 27, y + 10);
            //moving the position of boat and stick man
            x++;
            setcolor(LIGHTBLUE);
            delay(600);
            cleardevice();
            //drawing sea/river
            setlinestyle(SOLID_LINE, 1, 1);
            setfillstyle(SOLID_FILL, LIGHTBLUE);
            rectangle(0, getmaxy() / 2 + 150, getmaxx(), getmaxy());
            floodfill(getmaxx() - 10, getmaxy() - 10, LIGHTBLUE);
            cleardevice();
            j++;
        }

    }
    if(strcmp(ch,"Teachers Day")==0)
    {
        printf("Celebrated on September 5");
        delay(2000);
        int i,gdriver=DETECT,gmode=4;
        initgraph(&gdriver,&gmode,"");
        setcolor(RED);
        circle(230,200,40);
        arc(260,160,290,180,32);
        arc(285,219,202,118,32);
        arc(232,255,140,50,30);
        arc(180,222,75,338,32);
        arc(195,160,0,263,32);
        arc(100,255,300,0,162);
        arc(102,275,300,12,164);
        outtextxy(100,425," ***  HAPPY TEACHER'S DAY  ***");
        getch();
        cleardevice();
    }

    if(strcmp(ch,"Gandhi Jayanthi")==0)
    {
        printf("Celebrated on October 2");
        delay(2000);
        int gd=DETECT,gm;
        initgraph(&gd,&gm,"");
        circle(200,200,50);
        circle(400,200,50);
        line(250,200,350,200);
        setfillstyle(8,4);
        int a=0;
        while(!kbhit())
        {
            setcolor(a++);
            settextstyle(GOTHIC_FONT,HORIZ_DIR,2);
            outtextxy(50,50,"HAPPY GANDHI JAYANTHI");
            delay(100);
        }
        getch();
    }
    if(strcmp(ch,"Dussehra")==0)
    {
        printf("Celebrated on October 25");
        delay(2000);
        int gd,gm;
        int x,y;
        int i,j,kk;
        detectgraph(&gd,&gm);
        initgraph(&gd,&gm,"c:\\tc\\bgi");
        setcolor(WHITE);
        line(0,400,640,400);
        rectangle(300,330,340,400);
        rectangle(310,320,330,330);
        setcolor(4);
        line(319,280,319,398);
        line(320,280,320,398);
        rectangle(320,280,330,300);
        outtextxy(340,280,"PRESS ANY KEY TO IGNITE THE ROCKET");
        getch();
        for(j=400;j<640;j++)
        {
            cleardevice();
            setcolor(WHITE);
            line(0,j,640,j);
            rectangle(300,j-70,340,j);
            rectangle(310,j-80,330,j-70);
            setcolor(RED);
            line(319,280,319,400);
            line(320,280,320,400);
            rectangle(320,280,330,300);
            setcolor(YELLOW);
            circle(325,300,2);
            delay(5);
        }
        for(i=400;i>340;i--)
        {
            cleardevice();
            setcolor(RED);
            line(319,i,319,i-120);
            line(320,i,320,i-120);
            rectangle(320,i-120,330,i-100);
            setcolor(YELLOW);
            circle(325,i-100,2);
            delay(25);
        }
        cleardevice();
        kk=0;
        for(j=100;j<350;j++)
        {
            if(j%20==0)
            {
                setcolor(kk);
                kk=kk+3;
                delay(50);
            }
            ellipse(320,30,0,360,j+100,j+0);
        }
        for(j=100;j<350;j++)
        {
            if(j%20==0)
            {
                setcolor(BLACK);
                delay(2);
            }
            ellipse(320,30,0,360,j+100,j+0);
        }
        cleardevice();
        for(i=0;i<70;i++)
        {
            setcolor(i);
            settextstyle(GOTHIC_FONT,HORIZ_DIR,3);
            outtextxy(110,150,"HAPPY DUSSEHRA !!");
            delay(90);
        }
    }
    if(strcmp(ch,"Childrens Day")==0)
    {
        printf("Celebrated on November 14");
        delay(2000);
        int ldisp=0;
        int gd=DETECT,gm,x=0;
        initgraph(&gd,&gm," ");
        while(!kbhit())
        {
            line(0,getmaxy()*0.75,getmaxx(),getmaxy()*0.75);
            ldisp=(ldisp+2)%20;
            circle(x,getmaxy()*0.75-90,10);
            rectangle(x,getmaxy()*0.75-80,x,getmaxy()*0.75-30);
            line(x,getmaxy()*0.75-70,x+10,getmaxy()*0.75-60);
            line(x,getmaxy()*0.75-65,x+10,getmaxy()*0.75-55);
            line(x+10,getmaxy()*0.75-60,x+20,getmaxy()*0.75-70);
            line(x+10,getmaxy()*0.75-55,x+20,getmaxy()*0.75-70);
            line(x,getmaxy()*0.75-30,x+ldisp,getmaxy()*0.75);
            line(x,getmaxy()*0.75-30,x-ldisp,getmaxy()*0.75);
            fillellipse(x+20, getmaxy()*0.75-120,20,20);
            line(x+20,getmaxy()*0.75-75,x+20,getmaxy()*0.75-70);
            delay(75);
            cleardevice();
            x=(x+2)%getmaxx();
            setcolor(BLUE);
            settextstyle(GOTHIC_FONT,HORIZ_DIR,5);
            outtextxy(70,150,"Children's Day");
        }
    }
    if(strcmp(ch,"Diwali")==0)
    {
        printf("Celebrated on November 16");
        delay(2000);
        int gd, gm;
	    int x, y;
        int i, j, kk;
        detectgraph(&gd, &gm);
        initgraph(&gd, &gm," ");
        cleardevice();
        kk = 0;
        for (j=100; j<350; j++)
        {
            if (j%20==0)
            {
                setcolor(kk);
                kk=kk+3;
                delay(50);
            }
            ellipse(320, 30, 0, 360, j+100, j+0);
        }
        for (j=100; j<350; j++)
        {
            if (j%20==0)
            {
                setcolor(BLACK);
                delay(2);
            }
            ellipse(320, 30, 0, 360, j+100, j+0);
        }
        cleardevice();
        i = 0;
        while (!kbhit())
        {
            setcolor(i++);
            settextstyle(GOTHIC_FONT,HORIZ_DIR,5);
            outtextxy(70, 150, "Diwali");
            delay(90);
        }
    }
    if(strcmp(ch,"Christmas")==0)
    {
        printf("Celebrated on December 25");
        delay(2000);
        int gm=DETECT,gd,i;
        initgraph(&gm, &gd, " ");
        setcolor(WHITE);
        setfillstyle(SOLID_FILL,BLACK);
        setfillstyle(SOLID_FILL,GREEN);
        line(240,420,275,420);
        line(240,420,245,405);
        line(275,420,270,405);
        line(245,405,240,405);
        line(270,405,275,405);
        line(240,405,245,390);
        line(275,405,270,390);
        line(245,390,240,390);
        line(270,390,275,390);
        line(240,390,258,370);
        line(275,390,257,370);
        floodfill(259,375,WHITE);
        setcolor(WHITE);
        setfillstyle(SOLID_FILL,BROWN);
        line(250,460,250,420);
        line(265,460,265,420);
        line(250,460,265,460);
        line(250,420,265,420);
        floodfill(255,441,WHITE);
        while (!kbhit())
        {
            settextstyle(GOTHIC_FONT,HORIZ_DIR,5);
            outtextxy(70, 150, "Merry Christmas");
            delay(90);
        }
    }
    if(strcmp(ch,"done")==0)
    {
       printf("You will return back to main menu");
       delay(4000);
    }
    closegraph();

}

int leapYears( int y )
{
    return y/4 - y/100 + y/400;
}


int todayOf( int y, int m, int d)
{
    static int DayOfMonth[] = { -1,0,31,59,90,120,151,181,212,243,273,304,334};
    return DayOfMonth[m] + d + ((m>2 && isLeapYear(y))? 1 : 0);
}

long days( int y, int m, int d)
{
    int lastYear;
    lastYear = y - 1;
    return 365L * lastYear + leapYears(lastYear) + todayOf(y,m,d);
}


void calendar(int y, int m)
{
    FILE *fp;
    Note* notes, note;
    int len, j, hasNote = 0;
    char choice;
    const char *NameOfMonth[] = { NULL,"January", "February", "March", "April", "May", "June",
                                  "July", "August", "September", "October", "November", "December"};
    char Week[] = "Su   Mo   Tu   We   Th   Fr   Sa";
    int DayOfMonth[] = { -1,31,28,31,30,31,30,31,31,30,31,30,31 };
    int weekOfTopDay;
    int i,day;

    weekOfTopDay = days(y, m, 1) % 7;

    fp = fopen("note.bin", "rb");
    if (fp == NULL)
        printf("Couldn't read notes\n");

    len = 0;
    while(fread(&note, sizeof(Note), 1, fp))
    {
        if (note.year == y && note.month == m)
            len++;
    }
    rewind(fp);
    j = 0;
    notes = (Note*) malloc (sizeof(Note) * len);
    while(fread(&note, sizeof(Note), 1, fp))
    {
        if (note.year == y && note.month == m)
        {
            notes[j] = note;
            j++;
        }
    }

    fclose(fp);

    if(isLeapYear(y))
        DayOfMonth[2] = 29;
    printf("\n     %s %d\n%s\n", NameOfMonth[m], y, Week);

    for(i=0;i<weekOfTopDay;i++)
        printf("   ");

    for(i=weekOfTopDay,day=1;day <= DayOfMonth[m];i++,day++)
    {
        hasNote = 0;
        for (j = 0; j < len; j++)
        {
            if (notes[j].day == day)
            {
                printf("|%2d| ",day);
                hasNote = 1;
                break;
            }
        }
        if (hasNote == 0)
            printf("%2d   ",day);

        if(i % 7 == 6)
            printf("\n");
    }

    printf("\n");
    scanf("\n%c", &choice);
    if (choice == 's')
    {
        printf("Here are list of notes for %d %d\n", m, y);
        for (j = 0; j < len; j++)
            printf("%d: %s\n", notes[j].day, notes[j].note);
    }
    else
        return;

}

int getDayNumber(int d, int m, int y)
{ //retuns the day number
    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    y -= m < 3;
    return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}

const char *getName(int day)
{ //returns the name of the day
    switch(day)
    {
        case 0 :return("Sunday");
        case 1 :return("Monday");
        case 2 :return("Tuesday");
        case 3 :return("Wednesday");
        case 4 :return("Thursday");
        case 5 :return("Friday");
        case 6 :return("Saturday");
        default:return("Error: Invalid Argument Passed");
    }
}
