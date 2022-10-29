# include "iGraphics.h"
# include<stdlib.h>
# include<stdio.h>
# include<time.h>
# include<windows.h>
# include<mmsystem.h>
#include<string.h>

//background
typedef struct bg{int l,w;}b_g;
b_g dspl={.l=900,.w=1600};

//chicken position
typedef struct cps{int x,y;}cps;
cps c1={.x=0,.y=740};
cps c2={.x=0,.y=610};
cps c3={.x=0,.y=480};
//int cps;

//basket position
typedef struct bp{int x,dx;}b_p;
b_p bsp={.x=800,.dx=30};


//egg position ,p is a flag for omelet
int egg_y=c1.y,egg_dy=10,egg_x,p=1,egg_c=0;
//test , t1 score, t2 basketed egg flag
int score1=0, t2=1,t3=1;
//scores  flag ,example sfe = score flag egg
int sfe=0,sfbe=0,sfge=0,sfp=0;


//2nd egg position ,p is a flag for omelet
int egg1_y=c2.y,egg1_dy=7,egg1_x,p1=1,egg1_c=0;
//test , t1 score, t2 basketed egg flag
int score2=0, t12=1,t13=1;
//scores  flag ,example sfe = score flag egg
int sfe1=0,sfbe1=0,sfge1=0,sfp1=0;


//3rd egg position ,p is a flag for omelet
int egg2_y=c3.y,egg2_dy=5,egg2_x,p2=1,egg2_c=0;
//test , t1 score, t2 basketed egg flag
int score3=0, t22=1,t23=1;
//scores  flag ,example sfe = score flag egg
int sfe2=0,sfbe2=0,sfge2=0,sfp2=0;


//final score
int fscore;
//timer variables
int sec=-1;

//game state , -1 for homepage
int game_state= -1;
char pages[4][20]={"file\\home.bmp","file\\duration.bmp","file\\help.bmp","file\\bg2.bmp"};


//buttons
typedef struct button{int lx,ly,rx,ry;}button;
//home
// play
button play={.lx=665,.ly=510,.rx=845,.ry=565};
// resume
button resume={.lx=645,.ly=415,.rx=860,.ry=470};
//high score
button high_score={.lx=585,.ly=335,.rx=895,.ry=385};
//help
button help={.lx=680,.ly=250,.rx=810,.ry=305};
//exit
button exitgame={.lx=675,.ly=160,.rx=820,.ry=215};

//duration
//1.5 minutes
button dur15={.lx=280,.ly=555,.rx=605,.ry=600};
//3 minutes
button dur3={.lx=300,.ly=450,.rx=580,.ry=495};
//5 minutes
button dur5={.lx=305,.ly=355,.rx=590,.ry=395};

//help
button help_back={.lx=1360,.ly=790,.rx=1490,.ry=885};

//sound flags
int mainsound=1,durationsound[3]={0,0,0},homesound=0;

//airflow variables
int ax=1,ai=0,al=0,ar=0;

//for high score
int durr,plri=0;
char plrname[100]={'\0'};
char dscore[3][50]={"file\\s1.5.txt","file\\s3.txt","file\\s5.txt"};
char dname[3][50]={"file\\n1.5.txt","file\\n3.txt","file\\n5.txt"};

//for showing highscore
char pn1[10][100],pn3[10][100],pn5[10][100];
int ps1[10],ps3[10],ps5[10];
char psc1[10][20],psc2[10][20],psc3[10][20];

/*
	function iDraw() is called again and again by the system.
*/
void showhighscore()
{
    FILE *fpn1=NULL;
    FILE *fpn3=NULL;
    FILE *fpn5=NULL;
    FILE *fps1=NULL;
    FILE *fps3=NULL;
    FILE *fps5=NULL;
    fpn1=fopen(dname[0],"r");
    for(int i=0;i<10;i++)
        fscanf(fpn1,"%s",&pn1[i]);
    fclose(fpn1);
    fpn3=fopen(dname[1],"r");
    for(int i=0;i<10;i++)
        fscanf(fpn3,"%s",&pn3[i]);
    fclose(fpn3);
    fpn5=fopen(dname[2],"r");
    for(int i=0;i<10;i++)
        fscanf(fpn5,"%s",&pn5[i]);
    fclose(fpn5);
    fps1=fopen(dscore[0],"r");
    for(int i=0;i<10;i++){
        fscanf(fps1,"%d",&ps1[i]);
        itoa(ps1[i],psc1[i],10);}
    fclose(fps1);
    fps3=fopen(dscore[1],"r");
    for(int i=0;i<10;i++){
        fscanf(fps3,"%d",&ps3[i]);
        itoa(ps3[i],psc2[i],10);}
    fclose(fps3);
    fps5=fopen(dscore[2],"r");
    for(int i=0;i<10;i++){
        fscanf(fps5,"%d",&ps5[i]);
        itoa(ps5[i],psc3[i],10);}
    fclose(fps5);

}





//save players name
void saveplayersname(int j, int ts)
{
    FILE *sr=NULL;
    FILE *sw=NULL;
    FILE *nr=NULL;
    FILE *nw=NULL;
    int gs[10],idx=-1;
    char gn[10][100],tn[100];
    strcpy(tn,plrname);
    plrname[0]='\0';
    plri=0;
    fscore=0;

    sr=fopen(dscore[j],"r");

    for(int i=0;i<10;i++)
        fscanf(sr,"%d",&gs[i]);
    fclose(sr);
    if(ts>gs[9])
    {
        gs[9]=ts;
        for(int i=9;i>0;i--)
        {
            int t=0;
            if(gs[i]>gs[i-1])
            {
                t=gs[i];
                gs[i]=gs[i-1];
                gs[i-1]=t;
                idx=i-1;
            }
            else{break;}
        }
    }
    sw=fopen(dscore[j],"w");
    for(int i=0;i<10;i++)
        fprintf(sw,"%d\n",gs[i]);
    fflush(sw);
    fclose(sw);


    if(idx!=-1)
        {

    nr=fopen(dname[j],"r");
    for(int i=0;i<10;i++)
        fscanf(nr,"%s",gn[i]);
    fclose(nr);
    strcpy(gn[9],tn);
    for(int i=9;i>idx;i--)
    {
        char temp[100];
        strcpy(temp,gn[i]);
        strcpy(gn[i],gn[i-1]);
        strcpy(gn[i-1],temp);
    }
    nw=fopen(dname[j],"w");

    for(int i=0;i<10;i++)
        fprintf(nw,"%s\n",gn[i]);

    fflush(nw);
    fclose(nw);


    }
}





//make file flag 0
void makefileflag0()
{
    FILE  *f=NULL;
    f=fopen("file\\savedgame.txt","w");
    fprintf(f,"%d",0);
    fflush(f);
    fclose(f);
}
//for saving game
void savegame()
{
    FILE *f=NULL;
    f=fopen("file\\savedgame.txt","w");
    fprintf(f,"%d\n",1);
    fprintf(f,"%d\n",sec);
    fprintf(f,"%d\n",bsp.x);
    //chicken and egg 1
    fprintf(f,"%d\n",score1);
    fprintf(f,"%d\n",c1.x);
    fprintf(f,"%d\n",egg_y);
    fprintf(f,"%d\n",t2);
    fprintf(f,"%d\n",egg_c);
    fprintf(f,"%d\n",egg_x);
    //chicken and egg 2
    fprintf(f,"%d\n",score2);
    fprintf(f,"%d\n",c2.x);
    fprintf(f,"%d\n",egg1_y);
    fprintf(f,"%d\n",t12);
    fprintf(f,"%d\n",egg1_c);
    fprintf(f,"%d\n",egg1_x);
    //chicken and egg 3
    fprintf(f,"%d\n",score3);
    fprintf(f,"%d\n",c3.x);
    fprintf(f,"%d\n",egg2_y);
    fprintf(f,"%d\n",t22);
    fprintf(f,"%d\n",egg2_c);
    fprintf(f,"%d\n",egg2_x);
    //sound
    fprintf(f,"%d\n",durationsound[0]);
    fprintf(f,"%d\n",durationsound[1]);
    fprintf(f,"%d\n",durationsound[2]);

    //high score
    fprintf(f,"%d\n",durr);


    fflush(f);
    fclose(f);


}

int gameissaved()
{
    FILE *f=NULL;
    f=fopen("file\\savedgame.txt","r");
    int x;
    fscanf(f,"%d",&x);
    fclose(f);
    return x;
}

void returntosavedgame()
{
    FILE *f=NULL;
    int temp;
    f=fopen("file\\savedgame.txt","r");
    fscanf(f,"%d",&temp);
    fscanf(f,"%d",&sec);
    fscanf(f,"%d",&bsp.x);
    //chicken and egg 1
    fscanf(f,"%d",&score1);
    fscanf(f,"%d",&c1.x);
    fscanf(f,"%d",&egg_y);
    fscanf(f,"%d",&t2);
    fscanf(f,"%d",&egg_c);
    fscanf(f,"%d",&egg_x);
    //chicken and egg 2
    fscanf(f,"%d",&score2);
    fscanf(f,"%d",&c2.x);
    fscanf(f,"%d",&egg1_y);
    fscanf(f,"%d",&t12);
    fscanf(f,"%d",&egg1_c);
    fscanf(f,"%d",&egg1_x);
    //chicken and egg 3
    fscanf(f,"%d",&score3);
    fscanf(f,"%d",&c3.x);
    fscanf(f,"%d",&egg2_y);
    fscanf(f,"%d",&t22);
    fscanf(f,"%d",&egg2_c);
    fscanf(f,"%d",&egg2_x);
    //sound
    fscanf(f,"%d",&durationsound[0]);
    fscanf(f,"%d",&durationsound[1]);
    fscanf(f,"%d",&durationsound[2]);

    //high score
    fscanf(f,"%d",&durr);


    fclose(f);
    makefileflag0();
}
void watch()
{
    char tme[5];
    tme[0]=sec/60+'0';
    tme[1]=':';
    tme[2]=(sec%60)/10+'0';
    tme[3]=(sec%60)%10+'0';
    tme[4]='\0';
    iSetColor(2,219,228);
    iText(1500,850,tme,GLUT_BITMAP_TIMES_ROMAN_24);
    iText(1315,850,"TIME REMAING",GLUT_BITMAP_TIMES_ROMAN_24);

}
void scoreshow()
{
    iSetColor(251,127,27);
    char score[20];
    itoa(score1+score2+score3,score,10);
    iText(40,850,"SCORE",GLUT_BITMAP_TIMES_ROMAN_24);
    iText(130,850,score,GLUT_BITMAP_TIMES_ROMAN_24);
}
//air flooow
void airflow()
{
    if((ax%997==0)&&(ai<200))
    {   if(egg_x<1500)egg_x+=3;
        else ai=200;
        if(egg1_x<1500)egg1_x+=3;
        else ai=200;
        if(egg2_x<1500)egg2_x+=3;
        else ai=200;
        ai++;
        ar=1;
    }
    else if((ax%991==0)&&(ai<200))
    {   if(egg_x>20)egg_x-=3;
        else ai=200;
        if(egg1_x>20)egg1_x-=3;
        else ai=200;
        if(egg2_x>20)egg2_x-=3;
        else ai=200;
        al=1;
        ai++;
    }
    else
    {
        ax=rand();
        ai=0;
        ar=0;
        al=0;
    }
}
void chickenegg1()
{
    //ROPE
    iSetColor(244,227,123);
    iFilledRectangle(0,c1.y,1600,5);
    //chicken
    iShowBMP2(c1.x,c1.y,"1.bmp",0xFFFFFF);
    //dropping
    if((bsp.x<egg_x)&&(egg_x<(bsp.x+105))&&(egg_y<90)&&(t2))
    {
        p=0;
        t2=0;
        if(sfe){score1+=1;printf("egg\n");}
        else if(sfbe){score1+=5;printf("blue egg\n");}
        else if(sfge){score1+=10;printf("golden egg\n");}
        else if(sfp){score1-=10;printf("poop\n");}
        printf("The score is %d\n",score1);
        printf("caught eggs %d\n",t3++);

    }

        egg_y-=egg_dy;
    if((egg_c%5==0)&&(t2)){
            if(ar)iShowBMP2(egg_x,egg_y,"file\\egg.bluer.bmp",0xFFFFFF);
       else if(al)iShowBMP2(egg_x,egg_y,"file\\egg.bluel.bmp",0xFFFFFF);
       else iShowBMP2(egg_x,egg_y,"egg.blue.bmp",0xFFFFFF);
       sfbe=1;sfe=0;sfge=0;sfp=0;}
    else if((egg_c%7==0)&&(t2)){
            if(ar)iShowBMP2(egg_x,egg_y,"file\\egg.goldenr.bmp",0xFFFFFF);
       else if(al)iShowBMP2(egg_x,egg_y,"file\\egg.goldenl.bmp",0xFFFFFF);
       else iShowBMP2(egg_x,egg_y,"egg.golden.bmp",0xFFFFFF);
    sfge=1;sfe=0;sfbe=0;sfp=0;}
    else if((egg_c%11==0)&&(t2)){
        iShowBMP2(egg_x,egg_y,"poop.bmp",0xFFFFFF);p=0;sfp=1;sfe=0;sfbe=0;sfge=0;}
    else if(t2){
            if(ar)iShowBMP2(egg_x,egg_y,"file\\eggr.bmp",0xFFFFFF);
       else if(al)iShowBMP2(egg_x,egg_y,"file\\eggl.bmp",0xFFFFFF);
       else iShowBMP2(egg_x,egg_y,"egg.bmp",0xFFFFFF);
    sfe=1;sfbe=0;sfge=0;sfp=0;}

    if(egg_y<30){
        if(p)
            iShowBMP2(egg_x,egg_y,"4.bmp",0xFFFFFF);
        p=1;
        egg_y=c1.y;
        egg_c=rand();
        t2=1;
    }
}
void chickenegg2()
{
    //ROPE
    iSetColor(244,227,123);
    iFilledRectangle(0,c2.y,1600,5);
    //chicken
    iShowBMP2(c2.x,c2.y,"1.1.bmp",0xFFFFFF);
    //dropping
    if((bsp.x<egg1_x)&&(egg1_x<(bsp.x+105))&&(egg1_y<90)&&(t12))
    {
        p1=0;
        t12=0;
        if(sfe1){score2+=1;printf("egg\n");}
        else if(sfbe1){score2+=5;printf("blue egg\n");}
        else if(sfge1){score2+=10;printf("golden egg\n");}
        else if(sfp1){score2-=10;printf("poop\n");}
        printf("The score is %d\n",score2);
        printf("caught eggs %d\n",t13++);

    }

        egg1_y-=egg1_dy;
    if((egg1_c%5==0)&&(t12)){
        if(ar)iShowBMP2(egg1_x,egg1_y,"file\\egg.bluer.bmp",0xFFFFFF);
    else if(al)iShowBMP2(egg1_x,egg1_y,"file\\egg.bluel.bmp",0xFFFFFF);
    else iShowBMP2(egg1_x,egg1_y,"egg.blue.bmp",0xFFFFFF);
    sfbe1=1;sfe1=0;sfge1=0;sfp1=0;}

    else if((egg1_c%7==0)&&(t12)){
        if(ar)iShowBMP2(egg1_x,egg1_y,"file\\egg.goldenr.bmp",0xFFFFFF);
    else if(al)iShowBMP2(egg1_x,egg1_y,"file\\egg.goldenl.bmp",0xFFFFFF);
    else iShowBMP2(egg1_x,egg1_y,"egg.golden.bmp",0xFFFFFF);
    sfge1=1;sfe1=0;sfbe1=0;sfp1=0;}

    else if((egg1_c%11==0)&&(t12)){
        iShowBMP2(egg1_x,egg1_y,"poop.bmp",0xFFFFFF);p1=0;sfp1=1;sfe1=0;sfbe1=0;sfge1=0;}

    else if(t12){
             if(ar)iShowBMP2(egg1_x,egg1_y,"file\\eggr.bmp",0xFFFFFF);
       else if(al)iShowBMP2(egg1_x,egg1_y,"file\\eggl.bmp",0xFFFFFF);
       else iShowBMP2(egg1_x,egg1_y,"egg.bmp",0xFFFFFF);
        sfe1=1;sfbe1=0;sfge1=0;sfp1=0;}

    if(egg1_y<30){
        if(p1)
            iShowBMP2(egg1_x,egg1_y,"4.bmp",0xFFFFFF);
        p1=1;
        egg1_y=c2.y;
        egg1_c=rand();
        t12=1;
    }
}

void chickenegg3()
{
    //ROPE
    iSetColor(244,227,123);
    iFilledRectangle(0,c3.y,1600,5);
    //chicken
    iShowBMP2(c3.x,c3.y,"1.bmp",0xFFFFFF);
    //dropping
    if((bsp.x<egg2_x)&&(egg2_x<(bsp.x+105))&&(egg2_y<90)&&(t22))
    {
        p2=0;
        t22=0;
        if(sfe2){score3+=1;printf("egg\n");}
        else if(sfbe2){score3+=5;printf("blue egg\n");}
        else if(sfge2){score3+=10;printf("golden egg\n");}
        else if(sfp2){score3-=10;printf("poop\n");}
        printf("The score is %d\n",score3);
        printf("caught eggs %d\n",t23++);

    }

        egg2_y-=egg2_dy;
    if((egg2_c%5==0)&&(t22)){
        if(ar)iShowBMP2(egg2_x,egg2_y,"file\\egg.bluer.bmp",0xFFFFFF);
    else if(al)iShowBMP2(egg2_x,egg2_y,"file\\egg.bluel.bmp",0xFFFFFF);
    else  iShowBMP2(egg2_x,egg2_y,"egg.blue.bmp",0xFFFFFF);
    sfbe2=1;sfe2=0;sfge2=0;sfp2=0;}

    else if((egg2_c%7==0)&&(t22)){
        if(ar)iShowBMP2(egg2_x,egg2_y,"file\\egg.goldenr.bmp",0xFFFFFF);
    else if(al)iShowBMP2(egg2_x,egg2_y,"file\\egg.goldenl.bmp",0xFFFFFF);
    else iShowBMP2(egg2_x,egg2_y,"egg.golden.bmp",0xFFFFFF);
    sfge2=1;sfe2=0;sfbe2=0;sfp2=0;}

    else if((egg2_c%11==0)&&(t22)){
        iShowBMP2(egg2_x,egg2_y,"poop.bmp",0xFFFFFF);p2=0;sfp2=1;sfe2=0;sfbe2=0;sfge2=0;}

    else if(t22){
        if(ar)iShowBMP2(egg2_x,egg2_y,"file\\eggr.bmp",0xFFFFFF);
    else if(al)iShowBMP2(egg2_x,egg2_y,"file\\eggl.bmp",0xFFFFFF);
       else iShowBMP2(egg2_x,egg2_y,"egg.bmp",0xFFFFFF);
       sfe2=1;sfbe2=0;sfge2=0;sfp2=0;}

    if(egg2_y<30){
        if(p2)
            iShowBMP2(egg2_x,egg2_y,"4.bmp",0xFFFFFF);
        p2=1;
        egg2_y=c3.y;
        egg2_c=rand();
        t22=1;
    }
}

void iDraw()
{
    //place your drawing codes here
    iClear();
    if(game_state==1)
    {
    //background
    iShowBMP(0,0,pages[3]);
    //basket
    iShowBMP2(bsp.x,5,"file\\t2.bmp",0xFFFFFF);
    iShowBMP2(775,825,"pause.bmp",0xFFFFFF);
    airflow();
    chickenegg1();
    chickenegg2();
    chickenegg3();
    scoreshow();
    watch();
    }
    //homepage
    if(game_state==-1)
    {
        iShowBMP(0,0,pages[0]);

    }
    //duration
    if(game_state==0)
    {
        iShowBMP(0,0,pages[1]);
    }
    //help
    if(game_state==2)
    {
        iShowBMP(0,0,pages[2]);
        iSetColor(250,125,62);
        iText(125,60,"Press the up key to toggle sound",GLUT_BITMAP_TIMES_ROMAN_24);
    }
    //save players name
    if(game_state==3)
    {
        iText(775,700,"Type your name",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(775,600,plrname,GLUT_BITMAP_TIMES_ROMAN_24);
    }
    //show high score
    if(game_state==4)
    {   iSetColor(15,120,240);
        iShowBMP(0,0,"file\\high score.bmp");
        iText(250,700,"Welcome to Hall of Fame",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(50,600,"1.5 MINUTES",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(300,600,"3 MINUTES",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(550,600,"5 MINUTES",GLUT_BITMAP_TIMES_ROMAN_24);
        for(int i=0,j=500;i<10;i++,j-=30)
            iText(30,j,pn1[i],GLUT_BITMAP_TIMES_ROMAN_24);
        for(int i=0,j=500;i<10;i++,j-=30)
            iText(300,j,pn3[i],GLUT_BITMAP_TIMES_ROMAN_24);
        for(int i=0,j=500;i<10;i++,j-=30)
            iText(600,j,pn5[i],GLUT_BITMAP_TIMES_ROMAN_24);
        for(int i=0,j=500;i<10;i++,j-=30)
            iText(180,j,psc1[i],GLUT_BITMAP_TIMES_ROMAN_24);
        for(int i=0,j=500;i<10;i++,j-=30)
            iText(450,j,psc2[i],GLUT_BITMAP_TIMES_ROMAN_24);
        for(int i=0,j=500;i<10;i++,j-=30)
            iText(750,j,psc3[i],GLUT_BITMAP_TIMES_ROMAN_24);

        iText(250,100,"Press q to go to main menu",GLUT_BITMAP_TIMES_ROMAN_24);


    }

    if(mainsound)iShowBMP2(1455,200,"file\\s on1.bmp",0xFFFFFF);
    else iShowBMP2(1455,200,"file\\s off.bmp",0xFFFFFF);
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    //printf("x = %d, y= %d\n",mx,my);
    //place your codes here
    if((mx>0)&&(mx<1600)&&(game_state==1))
    bsp.x=mx;
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {

        if(game_state==-1)
        {
            if(play.lx<mx&&mx<play.rx&&play.ly<my&&my<play.ry)
            {
                if(gameissaved())makefileflag0();
                game_state=0;
            }
            else if((resume.lx<mx)&&(mx<resume.rx)&&(resume.ly<my)&&(my<resume.ry))
            {
                if(gameissaved())returntosavedgame();
                if(sec==-1){game_state=0;PlaySound("music\\home.wav",NULL,SND_ASYNC);}
                else  {game_state=1;
            if(durationsound[0])
            PlaySound("music\\1.5 minute.wav",NULL,SND_ASYNC);
            if(durationsound[1])
            PlaySound("music\\3 minute.wav",NULL,SND_ASYNC);
            if(durationsound[2])
            PlaySound("music\\5 minute.wav",NULL,SND_ASYNC);
                }
            }
            else if((high_score.lx<mx)&&(mx<high_score.rx)&&(high_score.ly<my)&&(my<high_score.ry))
            {
                showhighscore();
                game_state=4;
            }
            else if((help.lx<mx)&&(mx<help.rx)&&(help.ly<my)&&(my<help.ry))
            {
                game_state=2;
            }
            else if((exitgame.lx<mx)&&(mx<exitgame.rx)&&(exitgame.ly<my)&&(my<exitgame.ry))
            {
                if(sec==-1)makefileflag0();
                else savegame();
                exit(0);
            }
        }
        //duration
        if(game_state==0)

        {   score1=0;
            score2=0;
            score3=0;
           if((dur15.lx<mx)&&(mx<dur15.rx)&&(dur15.ly<my)&&(my<dur15.ry))
            {
                sec=90;
                durationsound[0]=1;
                durationsound[1]=0;
                durationsound[2]=0;
                game_state=1;
                PlaySound("music\\1.5 minute.wav",NULL,SND_ASYNC);
                durr=0;
            }
            else if((dur3.lx<mx)&&(mx<dur3.rx)&&(dur3.ly<my)&&(my<dur3.ry))
            {
                sec=180;
                durationsound[0]=0;
                durationsound[1]=1;
                durationsound[2]=0;
                game_state=1;
                PlaySound("music\\3 minute.wav",NULL,SND_ASYNC);
                durr=1;
            }
            else if((dur5.lx<mx)&&(mx<dur5.rx)&&(dur5.ly<my)&&(my<dur5.ry))
            {
                sec=300;
                durationsound[0]=0;
                durationsound[1]=0;
                durationsound[2]=1;
                game_state=1;
                PlaySound("music\\5 minute.wav",NULL,SND_ASYNC);
                durr=2;
            }

        }

        //help
        if(game_state==2)
        {
            if((help_back.lx<mx)&&(mx<help_back.rx)&&(help_back.ly<my)&&(my<help_back.ry))
            {
                game_state=-1;
            }
        }
        //pause
        if(game_state==1)
        {
            if((775<mx)&&(mx<825)&&(825<my)&&(my<875))
            {

                game_state=-1;
                PlaySound("music\\home.wav",NULL,SND_ASYNC);


            }
        }






    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
    }
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    if(game_state==3)
    {
        if((key!='\r')&&(key!=' '))
        {
            plrname[plri]=key;
            plrname[plri+1]='\0';
            plri++;
        }
        else
        {
            game_state=-1;
            fscore=score1+score2+score3;
            saveplayersname(durr,fscore);
        }
    }
    if(game_state==4)
    {
        if(key=='q')game_state=-1;
    }

    //place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

    if(key == GLUT_KEY_END)
    {
        exit(0);
    }
    if(key==GLUT_KEY_LEFT)
    {
        if(bsp.x>30)
        bsp.x-=bsp.dx;
        else bsp.x=0;
    }
    if(key==GLUT_KEY_RIGHT)
    {
        if(bsp.x<1550)
        bsp.x+=bsp.dx;
    }
    if(key==GLUT_KEY_UP)
    {

        if(mainsound)
        {
            mainsound=0;
            PlaySound(0,NULL,0);
        }
        else
        {
            mainsound=1;
            if(game_state!=1)
            PlaySound("music\\home.wav",NULL,SND_ASYNC);
            if(game_state==1){
            if(durationsound[0])
            PlaySound("music\\1.5 minute.wav",NULL,SND_ASYNC);
            if(durationsound[1])
            PlaySound("music\\3 minute.wav",NULL,SND_ASYNC);
            if(durationsound[2])
            PlaySound("music\\5 minute.wav",NULL,SND_ASYNC);
            }

        }
    }

    //place your codes for other keys here
}
//chicken moving function
void chickenmove()
{
    if(game_state==1){
    if(egg_y==c1.y){
    c1.x=rand()%1500;
    egg_x=c1.x;
    //printf("t2 %d\n",t2++);
    }
    if(egg1_y==c2.y){
    c2.x=rand()%1500;
    egg1_x=c2.x;
    //printf("t2 %d\n",t2++);
    }
    if(egg2_y==c3.y){
    c3.x=rand()%1500;
    egg2_x=c3.x;
    //printf("t2 %d\n",t2++);
    }
    }
}

void timer()
{
    if(game_state==1)
        sec--;
    if(!sec){
        PlaySound("music\\home.wav",NULL,SND_ASYNC);
        game_state=3;
        sec=-1;}
}
int main()
{
    //place your own initialization codes here.
    if(mainsound)
    PlaySound("music\\home.wav",NULL,SND_ASYNC);
    //for chicken move
    srand(time(0));
    iSetTimer(20,chickenmove);
    iSetTimer(1000,timer);
    iInitialize(dspl.w,dspl.l ,"Under Construction");


    return 0;
}
