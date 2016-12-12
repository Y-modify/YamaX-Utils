/*************************************
* Actions - YamaX Edison Core v1.0
* Motor control block
* made by Nyanyan, coorde Y-modify
* Copyright © 2016 Y-modify All Rights Reserved.
*************************************/

#include <iostream>
#include "posture/physicalio/physicalio.hpp"
#include <unistd.h>

using namespace yamax;

/*****Pulse Adjust*****/
#define SERVOMIN  0.5  //when 0° (ms)
#define SERVOMAX  2.3  //when 180° (ms)

/*****Object Making*****/
servos ss = servos(1, 32, 0x40, SERVOMIN, SERVOMAX); //Bus number 1, 32 servos, address 0x40~

#define servoA 0

#define servoB 27
#define servoC 4
#define servoD 5

#define servoE 26 //9
#define servoF 25 //8
#define servoG 24 //7

#define servoH 22 //6
#define servoI 21 //5

#define servoK 19 //3
#define servoL 20 //4
#define servoM 18 //2
#define servoN 17 //1
#define servoO 16 //0

#define servoQ 6
#define servoR 7
#define servoS 8
#define servoT 9
#define servoU 10

/**standDefinition**/
#define stA 90   //+90    -90

#define stB 50   //+130   -50
#define stC 90   //+90    -90
#define stD 80   //+100   -80

#define stE 100  //+80    -100
#define stF 60   //+120   -60
#define stG 70   //+110   -70

#define stH 65   //+115   -65
#define stI 80   //+100   -80

#define stK 45   //+135   -45
#define stL 110  //+70    -110
#define stM 110  //+70  -110
#define stN 65   //+115   -65
#define stO 85   //+115   -65

#define stQ 100  //+80    -100
#define stR 100  //+80    -100
#define stS 90   //+90    -90
#define stT 65   //+115   -65
#define stU 90   //+90    -90

extern void stand();
extern void bow(int deltime);
extern void foot(int times, int delaytime);
extern void foot1();
extern void foot2();
extern void walk(int times, int delaytime);
extern void walk1();
extern void walk2();
extern void turnright(int times, int delaytime);
extern void turnleft(int times, int delaytime);
extern void turnright1();
extern void turnright2();
extern void turnleft1();
extern void turnleft2();
extern void achilles1();
extern void achilles2();
extern void no(int times);
extern void bye(int times, int dir);
extern void nadenade(int times, bool dir);
extern void dance(int times);
extern void kusoran();
extern void kamae();
extern void waver();
extern void wavel();
extern void amimaki1(int times);
extern void amimaki2();
extern void amimaki3();
extern void Tparty1(int Time);
extern void Tparty2(int Time);
extern void tie(int Time);
extern void dokkoisyor();
extern void dokkoisyol();
extern void soransoran();
extern void tekogi(int times);
extern void haihai();
extern void koshimage(int t);
extern void volt1(int t);
extern void volt2(int t);
extern void human(int Time);
extern void yajiron(int times);
extern void dokkoisyo();
extern void syuwach(int t);
extern void gattsu(int times);
extern void biem(int times);
extern void dosuru(int t);

/*****Initialize Servo Driver*****/
int main(void){
  ss.setPWMFreq(50);
  kusoran();
  while(1);
  return 0;
}

/*****Base Functions*****/
void stand()
{
  ss[servoA].setDegrees(stA); //首

  ss[servoB].setDegrees(stB);
  ss[servoC].setDegrees(stC);
  ss[servoD].setDegrees(stD); //左腕

  ss[servoE].setDegrees(stE);
  ss[servoF].setDegrees(stF);
  ss[servoG].setDegrees(stG); //右腕

  ss[servoH].setDegrees(stH);
  ss[servoI].setDegrees(stI); //腰

  ss[servoK].setDegrees(stK);
  ss[servoL].setDegrees(stL); //170
  ss[servoM].setDegrees(stM);//170
  ss[servoN].setDegrees(stN);
  ss[servoO].setDegrees(stO); //右足

  ss[servoQ].setDegrees(stQ);
  ss[servoR].setDegrees(stR); //30
  ss[servoS].setDegrees(stS);//30
  ss[servoT].setDegrees(stT);
  ss[servoU].setDegrees(stU); //左足
}

void bow(int deltime)
{
  std::cout << "Bowing " << deltime << "ms" << std::endl;

  ss[servoA].setDegrees(stA); //首

  ss[servoB].setDegrees(stB);
  ss[servoC].setDegrees(stC);
  ss[servoD].setDegrees(stD); //左腕

  ss[servoE].setDegrees(stE);
  ss[servoF].setDegrees(stF);
  ss[servoG].setDegrees(stG); //右腕

  ss[servoH].setDegrees(stH);
  ss[servoI].setDegrees(stI + 50); //腰

  ss[servoK].setDegrees(stK);
  ss[servoL].setDegrees(stL - 20); //170
  ss[servoM].setDegrees(stM);//170
  ss[servoN].setDegrees(stN);
  ss[servoO].setDegrees(stO); //右足

  ss[servoQ].setDegrees(stQ);
  ss[servoR].setDegrees(stR + 20); //30
  ss[servoS].setDegrees(stS);//30
  ss[servoT].setDegrees(stT);
  ss[servoU].setDegrees(stU); //左足

  usleep((deltime)*1000);
}


void foot(int times, int delaytime)
{
  int i = 0;
  for (i = 0; i < times; i += 2)
  {
    foot1();
    usleep((delaytime)*1000);
    foot2();
    usleep((delaytime)*1000);
  }
}

void foot1()//左足上げ
{
  ss[servoA].setDegrees(stA); //首

  ss[servoB].setDegrees(stB + 20);
  ss[servoC].setDegrees(stC + 20);
  ss[servoD].setDegrees(stD); //左腕

  ss[servoE].setDegrees(stE + 20);
  ss[servoF].setDegrees(stF - 20);
  ss[servoG].setDegrees(stG); //右腕

  ss[servoH].setDegrees(stH - 40);
  ss[servoI].setDegrees(stI-5); //腰

  ss[servoK].setDegrees(stK /* - 20*/);
  ss[servoL].setDegrees(stL - 10); //170
  ss[servoM].setDegrees(stM); //170
  ss[servoN].setDegrees(stN);
  ss[servoO].setDegrees(stO - 10); //右足

  ss[servoQ].setDegrees(stQ - 30);
  ss[servoR].setDegrees(stR); //10?
  ss[servoS].setDegrees(stS); //20?
  ss[servoT].setDegrees(stT); //10?
  ss[servoU].setDegrees(stU - 30); //左足

}

void foot2()//右足上げ
{
  ss[servoA].setDegrees(stA); //首

  ss[servoB].setDegrees(stB - 20);
  ss[servoC].setDegrees(stC + 20);
  ss[servoD].setDegrees(stD); //左腕

  ss[servoE].setDegrees(stE - 20);
  ss[servoF].setDegrees(stF - 20);
  ss[servoG].setDegrees(stG); //右腕

  ss[servoH].setDegrees(stH + 40);
  ss[servoI].setDegrees(stI); //腰

  ss[servoK].setDegrees(stK + 30);
  ss[servoL].setDegrees(stL); //170
  ss[servoM].setDegrees(stM); //170
  ss[servoN].setDegrees(stN);
  ss[servoO].setDegrees(stO + 30); //右足

  ss[servoQ].setDegrees(stQ /* + 20*/);
  ss[servoR].setDegrees(stR + 10); //30
  ss[servoS].setDegrees(stS); //30
  ss[servoT].setDegrees(stT);
  ss[servoU].setDegrees(stU + 10); //左足


}

/*****Walking*****/
void walk(int times, int delaytime)
{
  std::cout << "Walking " << times << " steps with " << delaytime << "ms" << std::endl;

  int i = 0;
  for (i = 0; i < times; i += 2)
  {
    foot1();
    usleep((delaytime)*1000);
    walk1();
    usleep((delaytime)*1000);
    /*   ss[servoU].setDegrees(stU 80); //左足
       ss[servoO].setDegrees(stO 65); //右足
       //  ss[servoH].setDegrees(stH 55);*/
    usleep((100)*1000);

    foot2();
    usleep((delaytime)*1000);
    walk2();
    usleep((delaytime)*1000);
    /*   ss[servoU].setDegrees(stU 80); //左足
       ss[servoO].setDegrees(stO 65); //右足
       //   ss[servoH].setDegrees(stH 75);*/
    usleep((100)*1000);
  }
}

void walk1()//左足を出す
{
  ss[servoA].setDegrees(stA); //首

  ss[servoB].setDegrees(stB + 20);
  ss[servoC].setDegrees(stC + 20);
  ss[servoD].setDegrees(stD); //左腕

  ss[servoE].setDegrees(stE + 20);
  ss[servoF].setDegrees(stF - 20);
  ss[servoG].setDegrees(stG); //右腕

  ss[servoH].setDegrees(stH - 20);
  ss[servoI].setDegrees(stI-5); //腰

  ss[servoK].setDegrees(stK /* - 15*/);
  ss[servoL].setDegrees(stL); //170
  ss[servoM].setDegrees(stM); //170
  ss[servoN].setDegrees(stN);
  ss[servoO].setDegrees(stO - 5); //右足

  ss[servoQ].setDegrees(stQ - 15);
  ss[servoR].setDegrees(stR - 60); //30
  ss[servoS].setDegrees(stS - 40); //30
  ss[servoT].setDegrees(stT - 0);
  ss[servoU].setDegrees(stU - 40); //左足


}

void walk2()//右足を出す
{
  ss[servoA].setDegrees(stA); //首

  ss[servoB].setDegrees(stB - 20);
  ss[servoC].setDegrees(stC + 20);
  ss[servoD].setDegrees(stD); //左腕

  ss[servoE].setDegrees(stE - 20);
  ss[servoF].setDegrees(stF - 20);
  ss[servoG].setDegrees(stG); //右腕

  ss[servoH].setDegrees(stH + 20);
  ss[servoI].setDegrees(stI); //腰

  ss[servoK].setDegrees(stK + 15);
  ss[servoL].setDegrees(stL + 60); //170
  ss[servoM].setDegrees(stM + 40); //170
  ss[servoN].setDegrees(stN + 0);
  ss[servoO].setDegrees(stO + 40); //右足

  ss[servoQ].setDegrees(stQ /* + 15*/);
  ss[servoR].setDegrees(stR); //30
  ss[servoS].setDegrees(stS); //30
  ss[servoT].setDegrees(stT);
  ss[servoU].setDegrees(stU + 5); //左足


}

/*****回ろう*****/
void turnright(int times, int delaytime)
{
  std::cout << "Turning right " << times << " steps with " << delaytime << "ms" << std::endl;

  for (int i = 0; i < times; i++)
  {
    foot1();
    //ss[servoI].setDegrees(stI - 20); //腰
    //    ss[servoO].setDegrees(stO - 20); //右足
    usleep((delaytime)*1000);
    //turnright1();
    walk1();
    //ss[servoI].setDegrees(stI - 20); //腰
    usleep((delaytime)*1000);
    stand();
    usleep((delaytime)*1000);
  }
}

void turnleft(int times, int delaytime)
{
  std::cout << "Turning left " << times << " steps with " << delaytime << "ms" << std::endl;

  for (int i = 0; i < times; i++)
  {
    foot2();
    //ss[servoI].setDegrees(stI - 11); //腰
    //  ss[servoU].setDegrees(stU + 20); //左足
    usleep((delaytime)*1000);
    //turnleft1();
    walk2();
    //ss[servoI].setDegrees(stI - 11); //腰
    usleep((delaytime)*1000);
    stand();
    usleep((delaytime)*1000);
  }
}

void turnright1()//左足を出す
{
  ss[servoA].setDegrees(stA); //首

  ss[servoB].setDegrees(stB + 20);
  ss[servoC].setDegrees(stC + 20);
  ss[servoD].setDegrees(stD); //左腕

  ss[servoE].setDegrees(stE + 20);
  ss[servoF].setDegrees(stF - 20);
  ss[servoG].setDegrees(stG); //右腕

  ss[servoH].setDegrees(stH);
  ss[servoI].setDegrees(stI - 11); //腰

  ss[servoK].setDegrees(stK);
  ss[servoL].setDegrees(stL + 10); //170
  ss[servoM].setDegrees(stM); //170
  ss[servoN].setDegrees(stN);
  ss[servoO].setDegrees(stO - 10); //右足

  ss[servoQ].setDegrees(stQ);
  ss[servoR].setDegrees(stR - 60); //30
  ss[servoS].setDegrees(stS - 40); //30
  ss[servoT].setDegrees(stT - 10);
  ss[servoU].setDegrees(stU - 2); //左足


}


void turnright2()
{
  ss[servoA].setDegrees(stA); //首

  ss[servoB].setDegrees(stB - 20);
  ss[servoC].setDegrees(stC + 20);
  ss[servoD].setDegrees(stD); //左腕

  ss[servoE].setDegrees(stE - 20);
  ss[servoF].setDegrees(stF - 20);
  ss[servoG].setDegrees(stG); //右腕

  ss[servoH].setDegrees(stH);
  ss[servoI].setDegrees(stI - 11); //腰

  ss[servoK].setDegrees(stK);
  ss[servoL].setDegrees(stL + 20); //170
  ss[servoM].setDegrees(stM + 10); //170
  ss[servoN].setDegrees(stN);
  ss[servoO].setDegrees(stO + 2); //右足

  ss[servoQ].setDegrees(stQ);
  ss[servoR].setDegrees(stR - 10); //30
  ss[servoS].setDegrees(stS); //30
  ss[servoT].setDegrees(stT);
  ss[servoU].setDegrees(stU + 10); //左足
}



void turnleft1()//右足を出す
{
  ss[servoA].setDegrees(stA); //首

  ss[servoB].setDegrees(stB - 20);
  ss[servoC].setDegrees(stC + 20);
  ss[servoD].setDegrees(stD); //左腕

  ss[servoE].setDegrees(stE - 20);
  ss[servoF].setDegrees(stF - 20);
  ss[servoG].setDegrees(stG); //右腕

  ss[servoH].setDegrees(stH);
  ss[servoI].setDegrees(stI + 10); //腰

  ss[servoK].setDegrees(stK);
  ss[servoL].setDegrees(stL + 60); //170
  ss[servoM].setDegrees(stM + 40); //170
  ss[servoN].setDegrees(stN + 10);
  ss[servoO].setDegrees(stO + 2); //右足

  ss[servoQ].setDegrees(stQ);
  ss[servoR].setDegrees(stR - 10); //30
  ss[servoS].setDegrees(stS); //30
  ss[servoT].setDegrees(stT);
  ss[servoU].setDegrees(stU + 5); //左足


}
void turnleft2()
{
  ss[servoA].setDegrees(stA); //首

  ss[servoB].setDegrees(stB + 20);
  ss[servoC].setDegrees(stC + 20);
  ss[servoD].setDegrees(stD); //左腕

  ss[servoE].setDegrees(stE + 20);
  ss[servoF].setDegrees(stF - 20);
  ss[servoG].setDegrees(stG); //右腕

  ss[servoH].setDegrees(stH);
  ss[servoI].setDegrees(stI + 10); //腰

  ss[servoK].setDegrees(stK);
  ss[servoL].setDegrees(stL + 10); //170
  ss[servoM].setDegrees(stM); //170
  ss[servoN].setDegrees(stN);
  ss[servoO].setDegrees(stO - 5); //右足

  ss[servoQ].setDegrees(stQ);
  ss[servoR].setDegrees(stR - 20); //30
  ss[servoS].setDegrees(stS - 10); //30
  ss[servoT].setDegrees(stT);
  ss[servoU].setDegrees(stU - 2); //左足
}


void achilles1()

{
  ss[servoA].setDegrees(stA); //首

  ss[servoB].setDegrees(stB + 20);
  ss[servoC].setDegrees(stC + 20);
  ss[servoD].setDegrees(stD); //左腕

  ss[servoE].setDegrees(stE + 20);
  ss[servoF].setDegrees(stF - 20);
  ss[servoG].setDegrees(stG); //右腕

  ss[servoH].setDegrees(stH - 30);
  ss[servoI].setDegrees(stI + 40); //腰

  ss[servoK].setDegrees(stK);
  ss[servoL].setDegrees(stL - 60); //170
  ss[servoM].setDegrees(stM - 40); //170
  ss[servoN].setDegrees(stN);
  ss[servoO].setDegrees(stO); //右足

  ss[servoQ].setDegrees(stQ);
  ss[servoR].setDegrees(stR - 60); //30
  ss[servoS].setDegrees(stS - 40); //30
  ss[servoT].setDegrees(stT - 20);
  ss[servoU].setDegrees(stU); //左足
}

void achilles2()
{
  ss[servoA].setDegrees(stA); //首

  ss[servoB].setDegrees(stB - 20);
  ss[servoC].setDegrees(stC + 20);
  ss[servoD].setDegrees(stD); //左腕

  ss[servoE].setDegrees(stE - 20);
  ss[servoF].setDegrees(stF - 20);
  ss[servoG].setDegrees(stG); //右腕

  ss[servoH].setDegrees(stH + 30);
  ss[servoI].setDegrees(stI + 40); //腰

  ss[servoK].setDegrees(stK);
  ss[servoL].setDegrees(stL + 60); //170
  ss[servoM].setDegrees(stM + 40); //170
  ss[servoN].setDegrees(stN + 20);
  ss[servoO].setDegrees(stO); //右足

  ss[servoQ].setDegrees(stQ);
  ss[servoR].setDegrees(stR + 60); //30
  ss[servoS].setDegrees(stS + 40); //30
  ss[servoT].setDegrees(stT);
  ss[servoU].setDegrees(stU); //左足

}



/*****首*****/
void no(int times)
{
  std::cout << "Denying" << times << " times" << std::endl;

  for (int i = 0; i < times; i++)
  {
    stand();
    ss[servoA].setDegrees(stA - 60); //首
    usleep((200)*1000);
    stand();
    ss[servoA].setDegrees(stA + 60); //首
    usleep((200)*1000);
  }
}


/*****ばいばい系*****/
void bye(int times, int dir)//0:right, 1:left 2:both
{
  std::cout << "Bye " << times << " times ";

  stand();

  if (dir == 0)
  {
    std::cout << "with right hand" << std::endl;
    ss[servoE].setDegrees(stE + 50);
    ss[servoF].setDegrees(stF - 60);
    for (int i = 0; i < times; i++)
    {
      int tim = 20;
      for (int j = 0; j < 8; j++)
      {
        ss[servoG].setDegrees(stG + 80 - j * 10); //右腕
        usleep((tim)*1000);
      }
      for (int j = 0; j < 8; j++)
      {
        ss[servoG].setDegrees(stG + j * 10); //右腕
        usleep((tim)*1000);
      }
    }
  }


  if (dir == 1) {
    std::cout << "with left hand" << std::endl;
    ss[servoB].setDegrees(stB - 50);
    ss[servoC].setDegrees(stC + 80);
    for (int i = 0; i < times; i++)
    {
      int tim = 20;
      for (int j = 0; j < 8; j++)
      {
        ss[servoD].setDegrees(stD - 80 + j * 10); //左腕
        usleep((tim)*1000);
      }
      for (int j = 0; j < 8; j++)
      {
        ss[servoD].setDegrees(stD - j * 10); //左腕
        usleep((tim)*1000);
      }
    }


  }


  if (dir == 2)
  {
    std::cout << "with both hand" << std::endl;

    ss[servoB].setDegrees(stB - 50);
    ss[servoC].setDegrees(stC + 80);
    ss[servoE].setDegrees(stE + 50);
    ss[servoF].setDegrees(stF - 60);
    for (int i = 0; i < times; i++)
    {
      int tim = 20;
      for (int j = 0; j < 8; j++)
      {
        ss[servoG].setDegrees(stG + 80 - j * 10); //右腕
        ss[servoD].setDegrees(stD - 80 + j * 10);         //左腕
        usleep((tim)*1000);
      }
      for (int j = 0; j < 8; j++)
      {
        ss[servoG].setDegrees(stG + j * 10); //右腕
        ss[servoD].setDegrees(stD - j * 10);         //左腕
        usleep((tim)*1000);
      }
    }
  }

}

void nadenade(int times, bool dir) //0:right 1:left
{
  std::cout << "Nadenade " << times << " times ";

  stand();

  if (dir)
  {
    std::cout << "with left hand" << std::endl;
    ss[servoC].setDegrees(stC + 80);

    for (int i = 0; i < times; i++)
    {
      int tim = 20;
      for (int j = 0; j < 8; j++)
      {
        ss[servoD].setDegrees(stD - 80 + j * 10); //左腕
        usleep((tim)*1000);
      }
      for (int j = 0; j < 8; j++)
      {
        ss[servoD].setDegrees(stD - j * 10); //左腕
        usleep((tim)*1000);
      }
    }
  }



  if (!dir)
  {
    std::cout << "with right hand" << std::endl;
    ss[servoF].setDegrees(stF - 60);
    for (int i = 0; i < times; i++)
    {
      int tim = 20;
      for (int j = 0; j < 8; j++)
      {
        ss[servoG].setDegrees(stG + 80 - j * 10); //右腕
        usleep((tim)*1000);
      }
      for (int j = 0; j < 8; j++)
      {
        ss[servoG].setDegrees(stG + j * 10); //右腕
        usleep((tim)*1000);
      }
    }
  }


}

/**************/



/*****ダンス?*****/
void dance(int times)
{
  std::cout << "Dancing " << times << " times" << std::endl;
  for (int i = 0; i < times; i++)
  {
    foot1();
    //   ss[servoI].setDegrees(stI 90); //腰
    usleep((30)*1000);
    walk1();
    //    ss[servoI].setDegrees(stI 90); //腰
    usleep((30)*1000);
    foot2();
    //    ss[servoI].setDegrees(stI 90); //腰
    usleep((30)*1000);
    walk2();
    //    ss[servoI].setDegrees(stI 90); //腰
    usleep((30)*1000);
  }
}
/****************/

/***クソーラン節***/

#define KUSORAN_TEMPO 400
//TEMPO, CJ said it is 407.6

void kusoran()
{
  stand();
  // usleep((4000)*1000);
  kamae();
  usleep((10000)*1000);
  // setLEDColor(color.BLUE());
  usleep((1000)*1000);
  waver();
  wavel();
  amimaki1(5);
  amimaki2();
  amimaki3();
  amimaki1(5);
  amimaki2();
  amimaki3();
  amimaki1(5);
  amimaki2();
  amimaki3();
  amimaki1(2);
  amimaki2();
  Tparty1(KUSORAN_TEMPO * 2);
  Tparty2(KUSORAN_TEMPO);
  tie(KUSORAN_TEMPO);
  dokkoisyor();
  dokkoisyol();
  soransoran();
  dokkoisyor();
  dokkoisyol();
  soransoran();
  tekogi(5);
  haihai();
  koshimage(KUSORAN_TEMPO);
  amimaki1(6);
  volt1(KUSORAN_TEMPO);
  koshimage(KUSORAN_TEMPO);
  amimaki1(6);
  volt2(KUSORAN_TEMPO);
  human(KUSORAN_TEMPO);
  tie(KUSORAN_TEMPO);
  yajiron(16);
  dokkoisyo();
  dokkoisyor();
  dokkoisyol();
  soransoran();
  dokkoisyor();
  dokkoisyol();
  soransoran();
  gattsu(4);
  biem(4);
  tekogi(4);
  dosuru(KUSORAN_TEMPO * 2);
  volt1(4000);
}

void kamae()
{
  ss[servoA].setDegrees(stA); //首

  ss[servoB].setDegrees(stB + 20);
  ss[servoC].setDegrees(stC);
  ss[servoD].setDegrees(stD); //左腕

  ss[servoE].setDegrees(stE + 60);
  ss[servoF].setDegrees(stF);
  ss[servoG].setDegrees(stG + 70); //右腕

  ss[servoH].setDegrees(stH);
  ss[servoI].setDegrees(stI + 60); //腰

  ss[servoK].setDegrees(stK + 50);
  ss[servoL].setDegrees(stL + 70); //170
  ss[servoM].setDegrees(stM + 70); //170
  ss[servoN].setDegrees(stN - 20);
  ss[servoO].setDegrees(stO + 50); //右足

  ss[servoQ].setDegrees(stQ - 50);
  ss[servoR].setDegrees(stR - 70); //30
  ss[servoS].setDegrees(stS - 70); //30
  ss[servoT].setDegrees(stT + 20);
  ss[servoU].setDegrees(stU - 50); //左足
}

void waver()
{
  ss[servoB].setDegrees(stB);
  ss[servoC].setDegrees(stC);
  ss[servoD].setDegrees(stD); //左腕

  ss[servoH].setDegrees(stH);
  ss[servoI].setDegrees(stI); //腰

  ss[servoK].setDegrees(stK + 50);
  ss[servoL].setDegrees(stL + 70); //170
  ss[servoM].setDegrees(stM + 50); //170
  ss[servoN].setDegrees(stN - 30);
  ss[servoO].setDegrees(stO + 50); //右足

  ss[servoQ].setDegrees(stQ - 50);
  ss[servoR].setDegrees(stR - 70); //30
  ss[servoS].setDegrees(stS - 50); //30
  ss[servoT].setDegrees(stT + 30);
  ss[servoU].setDegrees(stU - 50); //左足

  for (int i = 0; i < 8; i++)
  {
    int j = 10 * i;
    ss[servoA].setDegrees(stA + 40 - j);//-40~+40

    ss[servoE].setDegrees(stE + 50);
    ss[servoF].setDegrees(stF + 40 - j); //-40~+40
    ss[servoG].setDegrees(stG);


    usleep((KUSORAN_TEMPO / 2)*1000);
    ss[servoG].setDegrees(stG + 30); //右腕
    usleep((KUSORAN_TEMPO / 2)*1000);
  }
}

void wavel()
{
  ss[servoE].setDegrees(stE);
  ss[servoF].setDegrees(stF);
  ss[servoG].setDegrees(stG); //右腕

  ss[servoH].setDegrees(stH);
  ss[servoI].setDegrees(stI); //腰

  ss[servoK].setDegrees(stK + 50);
  ss[servoL].setDegrees(stL + 70); //170
  ss[servoM].setDegrees(stM + 50); //170
  ss[servoN].setDegrees(stN - 30);
  ss[servoO].setDegrees(stO + 50); //右足

  ss[servoQ].setDegrees(stQ - 50);
  ss[servoR].setDegrees(stR - 70); //30
  ss[servoS].setDegrees(stS - 50); //30
  ss[servoT].setDegrees(stT + 30);
  ss[servoU].setDegrees(stU - 50); //左足

  for (int i = 0; i < 8; i++)
  {
    int j = 10 * i;
    ss[servoA].setDegrees(stA - 40 + j);//-40~+40

    ss[servoB].setDegrees(stB - 50);
    ss[servoC].setDegrees(stC - 40 + j);
    ss[servoD].setDegrees(stD);

    usleep((KUSORAN_TEMPO / 2)*1000);
    ss[servoD].setDegrees(stD - 30); //左腕
    usleep((KUSORAN_TEMPO / 2)*1000);
  }
}

void amimaki1(int times)
{
  ss[servoA].setDegrees(stA); //首

  ss[servoB].setDegrees(stB - 50);
  ss[servoC].setDegrees(stC - 20);
  ss[servoD].setDegrees(stD - 30); //左腕

  ss[servoE].setDegrees(stE + 40);
  ss[servoF].setDegrees(stF + 20);
  ss[servoG].setDegrees(stG + 30); //右腕

  ss[servoH].setDegrees(stH);
  ss[servoI].setDegrees(stI + 50); //腰

  ss[servoK].setDegrees(stK + 50);
  ss[servoL].setDegrees(stL + 70); //170
  ss[servoM].setDegrees(stM + 50); //170
  ss[servoN].setDegrees(stN - 20);
  ss[servoO].setDegrees(stO + 50); //右足

  ss[servoQ].setDegrees(stQ - 50);
  ss[servoR].setDegrees(stR - 70); //30
  ss[servoS].setDegrees(stS - 50); //30
  ss[servoT].setDegrees(stT + 20);
  ss[servoU].setDegrees(stU - 50); //左足

  for (int i = 0; i < times; i++)
  {
    ss[servoB].setDegrees(stB - 40);
    ss[servoC].setDegrees(stC - 60);
    ss[servoD].setDegrees(stD - 20); //左腕

    ss[servoE].setDegrees(stE + 50);
    ss[servoF].setDegrees(stF + 40);
    ss[servoG].setDegrees(stG + 20); //右腕

    usleep((KUSORAN_TEMPO / 2)*1000);

    ss[servoB].setDegrees(stB - 50);
    ss[servoC].setDegrees(stC - 40);
    ss[servoD].setDegrees(stD - 20); //左腕

    ss[servoE].setDegrees(stE + 40);
    ss[servoF].setDegrees(stF + 60);
    ss[servoG].setDegrees(stG + 20); //右腕

    usleep((KUSORAN_TEMPO / 2)*1000);
  }

}

void amimaki2()
{

  ss[servoB].setDegrees(stB);
  ss[servoC].setDegrees(stC);
  ss[servoD].setDegrees(stD); //左腕

  ss[servoE].setDegrees(stE + 50);
  ss[servoF].setDegrees(stF);
  ss[servoG].setDegrees(stG + 70); //右腕

  ss[servoH].setDegrees(stH);
  ss[servoI].setDegrees(stI); //腰

  ss[servoK].setDegrees(stK + 50);
  ss[servoL].setDegrees(stL + 70); //170
  ss[servoM].setDegrees(stM + 50); //170
  ss[servoN].setDegrees(stN - 20);
  ss[servoO].setDegrees(stO + 50); //右足

  ss[servoQ].setDegrees(stQ - 50);
  ss[servoR].setDegrees(stR - 70); //30
  ss[servoS].setDegrees(stS - 50); //30
  ss[servoT].setDegrees(stT + 20);
  ss[servoU].setDegrees(stU - 50); //左足

  usleep((KUSORAN_TEMPO)*1000);

  ss[servoB].setDegrees(stB - 50);
  ss[servoC].setDegrees(stC);
  ss[servoD].setDegrees(stD - 70); //左腕

  ss[servoE].setDegrees(stE);
  ss[servoF].setDegrees(stF);
  ss[servoG].setDegrees(stG); //右腕

  usleep((KUSORAN_TEMPO)*1000);
}

void amimaki3()
{
  ss[servoB].setDegrees(stB);
  ss[servoC].setDegrees(stC);
  ss[servoD].setDegrees(stD); //左腕

  ss[servoE].setDegrees(stE + 50);
  ss[servoF].setDegrees(stF);
  ss[servoG].setDegrees(stG + 70); //右腕

  ss[servoH].setDegrees(stH);
  ss[servoI].setDegrees(stI); //腰

  ss[servoK].setDegrees(stK);
  ss[servoL].setDegrees(stL); //170
  ss[servoM].setDegrees(stM); //170
  ss[servoN].setDegrees(stN);
  ss[servoO].setDegrees(stO); //右足

  ss[servoQ].setDegrees(stQ);
  ss[servoR].setDegrees(stR); //30
  ss[servoS].setDegrees(stS); //30
  ss[servoT].setDegrees(stT);
  ss[servoU].setDegrees(stU); //左足

  usleep((KUSORAN_TEMPO)*1000);

}

void Tparty1(int Time)
{
  ss[servoA].setDegrees(stA); //首

  ss[servoB].setDegrees(stB);
  ss[servoC].setDegrees(stC + 60);
  ss[servoD].setDegrees(stD); //左腕

  ss[servoE].setDegrees(stE);
  ss[servoF].setDegrees(stF - 60);
  ss[servoG].setDegrees(stG); //右腕

  ss[servoH].setDegrees(stH);
  ss[servoI].setDegrees(stI); //腰

  ss[servoK].setDegrees(stK);
  ss[servoL].setDegrees(stL); //170
  ss[servoM].setDegrees(stM);//170
  ss[servoN].setDegrees(stN);
  ss[servoO].setDegrees(stO); //右足

  ss[servoQ].setDegrees(stQ);
  ss[servoR].setDegrees(stR); //30
  ss[servoS].setDegrees(stS);//30
  ss[servoT].setDegrees(stT);
  ss[servoU].setDegrees(stU); //左足
  usleep((Time)*1000);
}

void Tparty2(int Time)
{
  ss[servoA].setDegrees(stA); //首

  ss[servoB].setDegrees(stB);
  ss[servoC].setDegrees(stC);
  ss[servoD].setDegrees(stD); //左腕

  ss[servoE].setDegrees(stE);
  ss[servoF].setDegrees(stF);
  ss[servoG].setDegrees(stG); //右腕

  ss[servoH].setDegrees(stH);
  ss[servoI].setDegrees(stI); //腰

  ss[servoK].setDegrees(stK);
  ss[servoL].setDegrees(stL); //170
  ss[servoM].setDegrees(stM);//170
  ss[servoN].setDegrees(stN);
  ss[servoO].setDegrees(stO); //右足

  ss[servoQ].setDegrees(stQ);
  ss[servoR].setDegrees(stR); //30
  ss[servoS].setDegrees(stS);//30
  ss[servoT].setDegrees(stT);
  ss[servoU].setDegrees(stU); //左足
  usleep((Time)*1000);
}

void tie(int Time)
{
  ss[servoA].setDegrees(stA); //首

  ss[servoB].setDegrees(stB);
  ss[servoC].setDegrees(stC + 60);
  ss[servoD].setDegrees(stD); //左腕

  ss[servoE].setDegrees(stE);
  ss[servoF].setDegrees(stF - 60);
  ss[servoG].setDegrees(stG); //右腕

  ss[servoH].setDegrees(stH);
  ss[servoI].setDegrees(stI); //腰

  ss[servoK].setDegrees(stK + 50);
  ss[servoL].setDegrees(stL); //170
  ss[servoM].setDegrees(stM); //170
  ss[servoN].setDegrees(stN);
  ss[servoO].setDegrees(stO + 50); //右足

  ss[servoQ].setDegrees(stQ - 50);
  ss[servoR].setDegrees(stR); //30
  ss[servoS].setDegrees(stS); //30
  ss[servoT].setDegrees(stT);
  ss[servoU].setDegrees(stU - 50); //左足

  usleep((Time)*1000);
}

void dokkoisyor()
{
  ss[servoA].setDegrees(stA + 50); //首

  ss[servoB].setDegrees(stB);
  ss[servoC].setDegrees(stC);
  ss[servoD].setDegrees(stD); //左腕

  ss[servoE].setDegrees(stE + 30);
  ss[servoF].setDegrees(stF + 90);
  ss[servoG].setDegrees(stG); //右腕

  ss[servoH].setDegrees(stH);
  ss[servoI].setDegrees(stI); //腰

  ss[servoK].setDegrees(stK + 50);
  ss[servoL].setDegrees(stL); //170
  ss[servoM].setDegrees(stM); //170
  ss[servoN].setDegrees(stN - 20);
  ss[servoO].setDegrees(stO + 50); //右足

  ss[servoQ].setDegrees(stQ - 50);
  ss[servoR].setDegrees(stR); //30
  ss[servoS].setDegrees(stS); //30
  ss[servoT].setDegrees(stT + 20);
  ss[servoU].setDegrees(stU - 50); //左足

  usleep((KUSORAN_TEMPO)*1000);

  ss[servoB].setDegrees(stB);
  ss[servoC].setDegrees(stC + 60);
  ss[servoD].setDegrees(stD); //左腕

  usleep((KUSORAN_TEMPO)*1000);

  ss[servoK].setDegrees(stK + 50);
  ss[servoL].setDegrees(stL + 70); //170
  ss[servoM].setDegrees(stM + 70); //170
  ss[servoN].setDegrees(stN - 30);
  ss[servoO].setDegrees(stO + 50); //右足

  ss[servoQ].setDegrees(stQ - 50);
  ss[servoR].setDegrees(stR); //30
  ss[servoS].setDegrees(stS); //30
  ss[servoT].setDegrees(stT + 30);
  ss[servoU].setDegrees(stU - 50); //左足

  usleep((KUSORAN_TEMPO)*1000);

  ss[servoK].setDegrees(stK + 50);
  ss[servoL].setDegrees(stL); //170
  ss[servoM].setDegrees(stM); //170
  ss[servoN].setDegrees(stN - 20);
  ss[servoO].setDegrees(stO + 50); //右足

  ss[servoQ].setDegrees(stQ - 50);
  ss[servoR].setDegrees(stR); //30
  ss[servoS].setDegrees(stS); //30
  ss[servoT].setDegrees(stT + 20);
  ss[servoU].setDegrees(stU - 50); //左足

  usleep((KUSORAN_TEMPO)*1000);

}

void dokkoisyol()
{
  ss[servoA].setDegrees(stA - 50); //首

  ss[servoB].setDegrees(stB - 30);
  ss[servoC].setDegrees(stC - 90);
  ss[servoD].setDegrees(stD); //左腕

  ss[servoE].setDegrees(stE);
  ss[servoF].setDegrees(stF);
  ss[servoG].setDegrees(stG); //右腕

  ss[servoH].setDegrees(stH);
  ss[servoI].setDegrees(stI); //腰

  ss[servoK].setDegrees(stK + 50);
  ss[servoL].setDegrees(stL); //170
  ss[servoM].setDegrees(stM); //170
  ss[servoN].setDegrees(stN - 20);
  ss[servoO].setDegrees(stO + 50); //右足

  ss[servoQ].setDegrees(stQ - 50);
  ss[servoR].setDegrees(stR); //30
  ss[servoS].setDegrees(stS); //30
  ss[servoT].setDegrees(stT + 20);
  ss[servoU].setDegrees(stU - 50); //左足

  usleep((KUSORAN_TEMPO)*1000);

  ss[servoE].setDegrees(stE);
  ss[servoF].setDegrees(stF - 60);
  ss[servoG].setDegrees(stG); //右腕

  usleep((KUSORAN_TEMPO)*1000);

  ss[servoK].setDegrees(stK + 50);
  ss[servoL].setDegrees(stL); //170
  ss[servoM].setDegrees(stM); //170
  ss[servoN].setDegrees(stN - 30);
  ss[servoO].setDegrees(stO + 50); //右足

  ss[servoQ].setDegrees(stQ - 50);
  ss[servoR].setDegrees(stR - 70); //30
  ss[servoS].setDegrees(stS - 70); //30
  ss[servoT].setDegrees(stT + 30);
  ss[servoU].setDegrees(stU - 50); //左足

  usleep((KUSORAN_TEMPO)*1000);

  ss[servoK].setDegrees(stK + 50);
  ss[servoL].setDegrees(stL); //170
  ss[servoM].setDegrees(stM); //170
  ss[servoN].setDegrees(stN - 20);
  ss[servoO].setDegrees(stO + 50); //右足

  ss[servoQ].setDegrees(stQ - 50);
  ss[servoR].setDegrees(stR); //30
  ss[servoS].setDegrees(stS); //30
  ss[servoT].setDegrees(stT + 20);
  ss[servoU].setDegrees(stU - 50); //左足

  usleep((KUSORAN_TEMPO)*1000);
}

void soransoran()
{

  for (int i = 0; i < 2; i++)
  {
    ss[servoA].setDegrees(stA); //首

    ss[servoB].setDegrees(stB - 40);
    ss[servoC].setDegrees(stC - 20);
    ss[servoD].setDegrees(stD - 20); //左腕

    ss[servoE].setDegrees(stE + 40);
    ss[servoF].setDegrees(stF + 20);
    ss[servoG].setDegrees(stG + 20); //右腕

    ss[servoH].setDegrees(stH);
    ss[servoI].setDegrees(stI + 50); //腰

    ss[servoK].setDegrees(stK + 50);
    ss[servoL].setDegrees(stL); //170
    ss[servoM].setDegrees(stM); //170
    ss[servoN].setDegrees(stN);
    ss[servoO].setDegrees(stO + 50); //右足

    ss[servoQ].setDegrees(stQ - 50);
    ss[servoR].setDegrees(stR); //30
    ss[servoS].setDegrees(stS); //30
    ss[servoT].setDegrees(stT);
    ss[servoU].setDegrees(stU - 50); //左足

    usleep((KUSORAN_TEMPO * 2)*1000);

    ss[servoB].setDegrees(stB - 50);
    ss[servoC].setDegrees(stC + 60);
    ss[servoD].setDegrees(stD - 80); //左腕

    ss[servoE].setDegrees(stE + 50);
    ss[servoF].setDegrees(stF - 60);
    ss[servoG].setDegrees(stG + 80); //右腕

    ss[servoH].setDegrees(stH);
    ss[servoI].setDegrees(stI); //腰

    ss[servoK].setDegrees(stK + 50);
    ss[servoL].setDegrees(stL + 70); //170
    ss[servoM].setDegrees(stM + 50); //170
    ss[servoN].setDegrees(stN - 30);
    ss[servoO].setDegrees(stO + 50); //右足

    ss[servoQ].setDegrees(stQ - 50);
    ss[servoR].setDegrees(stR - 70); //30
    ss[servoS].setDegrees(stS - 50); //30
    ss[servoT].setDegrees(stT + 30);
    ss[servoU].setDegrees(stU - 50); //左足

    usleep((KUSORAN_TEMPO * 2)*1000);
  }
}

void tekogi(int times)
{
  for (int i = 0; i < times; i++)
  {
    ss[servoA].setDegrees(stA); //首

    ss[servoB].setDegrees(stB - 50);
    ss[servoC].setDegrees(stC + 60);
    ss[servoD].setDegrees(stD - 80); //左腕

    ss[servoE].setDegrees(stE + 50);
    ss[servoF].setDegrees(stF - 60);
    ss[servoG].setDegrees(stG + 80); //右腕

    ss[servoH].setDegrees(stH);
    ss[servoI].setDegrees(stI - 20); //腰

    ss[servoK].setDegrees(stK + 50);
    ss[servoL].setDegrees(stL - 30); //170
    ss[servoM].setDegrees(stM - 30); //170
    ss[servoN].setDegrees(stN - 30);
    ss[servoO].setDegrees(stO + 50); //右足

    ss[servoQ].setDegrees(stQ - 50);
    ss[servoR].setDegrees(stR + 30); //30
    ss[servoS].setDegrees(stS + 30); //30
    ss[servoT].setDegrees(stT + 30);
    ss[servoU].setDegrees(stU - 50); //左足

    usleep((KUSORAN_TEMPO * 2)*1000);

    ss[servoA].setDegrees(stA); //首

    ss[servoB].setDegrees(stB);
    ss[servoC].setDegrees(stC + 60);
    ss[servoD].setDegrees(stD - 80); //左腕

    ss[servoE].setDegrees(stE);
    ss[servoF].setDegrees(stF - 60);
    ss[servoG].setDegrees(stG + 80); //右腕

    ss[servoH].setDegrees(stH);
    ss[servoI].setDegrees(stI); //腰

    ss[servoK].setDegrees(stK + 50);
    ss[servoL].setDegrees(stL + 70); //170
    ss[servoM].setDegrees(stM + 40); //170
    ss[servoN].setDegrees(stN - 30);
    ss[servoO].setDegrees(stO + 50); //右足

    ss[servoQ].setDegrees(stQ - 50);
    ss[servoR].setDegrees(stR - 70); //30
    ss[servoS].setDegrees(stS - 40); //30
    ss[servoT].setDegrees(stT + 30);
    ss[servoU].setDegrees(stU - 50); //左足

    usleep((KUSORAN_TEMPO * 2)*1000);
  }

}

void haihai()
{
  for (int i = 0; i < 2; i++)
  {
    ss[servoA].setDegrees(stA); //首

    ss[servoB].setDegrees(stB);
    ss[servoC].setDegrees(stC);
    ss[servoD].setDegrees(stD); //左腕

    ss[servoE].setDegrees(stE + 80);
    ss[servoF].setDegrees(stF);
    ss[servoG].setDegrees(stG + 90); //右腕

    ss[servoH].setDegrees(stH);
    ss[servoI].setDegrees(stI); //腰

    ss[servoK].setDegrees(stK + 50);
    ss[servoL].setDegrees(stL); //170
    ss[servoM].setDegrees(stM); //170
    ss[servoN].setDegrees(stN);
    ss[servoO].setDegrees(stO + 50); //右足

    ss[servoQ].setDegrees(stQ - 50);
    ss[servoR].setDegrees(stR); //30
    ss[servoS].setDegrees(stS); //30
    ss[servoT].setDegrees(stT);
    ss[servoU].setDegrees(stU - 50); //左足

    usleep((KUSORAN_TEMPO / 2)*1000);

    ss[servoA].setDegrees(stA); //首

    ss[servoB].setDegrees(stB);
    ss[servoC].setDegrees(stC);
    ss[servoD].setDegrees(stD); //左腕

    ss[servoE].setDegrees(stE + 80);
    ss[servoF].setDegrees(stF);
    ss[servoG].setDegrees(stG + 40); //右腕

    usleep((KUSORAN_TEMPO / 2)*1000);
  }

}

void koshimage(int t)
{
  ss[servoA].setDegrees(stA); //首

  ss[servoB].setDegrees(stB - 60);
  ss[servoC].setDegrees(stC - 40);
  ss[servoD].setDegrees(stD - 40); //左腕

  ss[servoE].setDegrees(stE + 40);
  ss[servoF].setDegrees(stF + 40);
  ss[servoG].setDegrees(stG + 40); //右腕

  ss[servoH].setDegrees(stH);
  ss[servoI].setDegrees(stI + 50); //腰

  ss[servoK].setDegrees(stK + 50);
  ss[servoL].setDegrees(stL + 70); //170
  ss[servoM].setDegrees(stM + 50); //170
  ss[servoN].setDegrees(stN - 20);
  ss[servoO].setDegrees(stO + 50); //右足

  ss[servoQ].setDegrees(stQ - 50);
  ss[servoR].setDegrees(stR - 70); //30
  ss[servoS].setDegrees(stS - 50); //30
  ss[servoT].setDegrees(stT + 20);
  ss[servoU].setDegrees(stU - 50); //左足
  usleep((t)*1000);
}

void volt1(int t)
{
  ss[servoA].setDegrees(stA + 50); //首

  ss[servoE].setDegrees(stE + 30);
  ss[servoF].setDegrees(stF + 90);
  ss[servoG].setDegrees(stG); //右腕

  ss[servoB].setDegrees(stB);
  ss[servoC].setDegrees(stC + 60);
  ss[servoD].setDegrees(stD); //左腕

  ss[servoH].setDegrees(stH);
  ss[servoI].setDegrees(stI); //腰

  ss[servoK].setDegrees(stK + 50);
  ss[servoL].setDegrees(stL); //170
  ss[servoM].setDegrees(stM); //170
  ss[servoN].setDegrees(stN);
  ss[servoO].setDegrees(stO + 50); //右足

  ss[servoQ].setDegrees(stQ - 50);
  ss[servoR].setDegrees(stR); //30
  ss[servoS].setDegrees(stS); //30
  ss[servoT].setDegrees(stT);
  ss[servoU].setDegrees(stU - 50); //左足

  usleep((t)*1000);
}

void volt2(int t)
{
  ss[servoA].setDegrees(stA - 50); //首

  ss[servoB].setDegrees(stB - 30);
  ss[servoC].setDegrees(stC - 90);
  ss[servoD].setDegrees(stD); //左腕

  ss[servoE].setDegrees(stE);
  ss[servoF].setDegrees(stF - 60);
  ss[servoG].setDegrees(stG); //右腕

  ss[servoH].setDegrees(stH);
  ss[servoI].setDegrees(stI); //腰

  ss[servoK].setDegrees(stK + 50);
  ss[servoL].setDegrees(stL); //170
  ss[servoM].setDegrees(stM); //170
  ss[servoN].setDegrees(stN);
  ss[servoO].setDegrees(stO + 50); //右足

  ss[servoQ].setDegrees(stQ - 50);
  ss[servoR].setDegrees(stR); //30
  ss[servoS].setDegrees(stS); //30
  ss[servoT].setDegrees(stT);
  ss[servoU].setDegrees(stU - 50); //左足
  usleep((t)*1000);
}

void human(int Time)
{
  ss[servoA].setDegrees(stA); //首

  ss[servoB].setDegrees(stB);
  ss[servoC].setDegrees(stC);
  ss[servoD].setDegrees(stD); //左腕

  ss[servoE].setDegrees(stE);
  ss[servoF].setDegrees(stF);
  ss[servoG].setDegrees(stG); //右腕

  ss[servoH].setDegrees(stH);
  ss[servoI].setDegrees(stI); //腰

  ss[servoK].setDegrees(stK + 50);
  ss[servoL].setDegrees(stL); //170
  ss[servoM].setDegrees(stM); //170
  ss[servoN].setDegrees(stN);
  ss[servoO].setDegrees(stO + 50); //右足

  ss[servoQ].setDegrees(stQ - 50);
  ss[servoR].setDegrees(stR); //30
  ss[servoS].setDegrees(stS); //30
  ss[servoT].setDegrees(stT);
  ss[servoU].setDegrees(stU - 50); //左足
  usleep((Time)*1000);
}

void yajiron(int times)
{
  for (int i = 0; i < times; i++)
  {
    ss[servoA].setDegrees(stA); //首

    ss[servoB].setDegrees(stB);
    ss[servoC].setDegrees(stC);
    ss[servoD].setDegrees(stD); //左腕

    ss[servoE].setDegrees(stE);
    ss[servoF].setDegrees(stF - 60);
    ss[servoG].setDegrees(stG); //右腕

    ss[servoH].setDegrees(stH);
    ss[servoI].setDegrees(stI); //腰

    ss[servoK].setDegrees(stK + 50);
    ss[servoL].setDegrees(stL); //170
    ss[servoM].setDegrees(stM); //170
    ss[servoN].setDegrees(stN);
    ss[servoO].setDegrees(stO + 50); //右足

    ss[servoQ].setDegrees(stQ - 50);
    ss[servoR].setDegrees(stR); //30
    ss[servoS].setDegrees(stS); //30
    ss[servoT].setDegrees(stT);
    ss[servoU].setDegrees(stU - 50); //左足

    usleep((KUSORAN_TEMPO / 2)*1000);

    ss[servoB].setDegrees(stB);
    ss[servoC].setDegrees(stC + 60);
    ss[servoD].setDegrees(stD); //左腕

    ss[servoE].setDegrees(stE);
    ss[servoF].setDegrees(stF);
    ss[servoG].setDegrees(stG); //右腕

    usleep((KUSORAN_TEMPO / 2)*1000);
  }
}

void dokkoisyo()
{
  Tparty1(KUSORAN_TEMPO);
  syuwach(KUSORAN_TEMPO);
}

void syuwach(int t)
{
  ss[servoA].setDegrees(stA); //首

  ss[servoB].setDegrees(stB - 30);
  ss[servoC].setDegrees(stC - 80);
  ss[servoD].setDegrees(stD); //左腕

  ss[servoE].setDegrees(stE + 80);
  ss[servoF].setDegrees(stF);
  ss[servoG].setDegrees(stG + 90); //右腕

  ss[servoH].setDegrees(stH);
  ss[servoI].setDegrees(stI); //腰

  ss[servoK].setDegrees(stK + 50);
  ss[servoL].setDegrees(stL); //170
  ss[servoM].setDegrees(stM); //170
  ss[servoN].setDegrees(stN);
  ss[servoO].setDegrees(stO + 50); //右足

  ss[servoQ].setDegrees(stQ - 50);
  ss[servoR].setDegrees(stR); //30
  ss[servoS].setDegrees(stS); //30
  ss[servoT].setDegrees(stT);
  ss[servoU].setDegrees(stU - 50); //左足

  usleep((t)*1000);

  ss[servoE].setDegrees(stE + 80);
  ss[servoF].setDegrees(stF);
  ss[servoG].setDegrees(stG + 40); //右腕
  usleep((t * 2)*1000);
}

void gattsu(int times)
{
  for (int i = 0; i < times; i++)
  {
    ss[servoA].setDegrees(stA); //首

    ss[servoB].setDegrees(stB);
    ss[servoC].setDegrees(stC);
    ss[servoD].setDegrees(stD - 80); //左腕

    ss[servoE].setDegrees(stE);
    ss[servoF].setDegrees(stF);
    ss[servoG].setDegrees(stG + 80); //右腕

    ss[servoH].setDegrees(stH);
    ss[servoI].setDegrees(stI); //腰

    ss[servoK].setDegrees(stK + 50);
    ss[servoL].setDegrees(stL + 70); //170
    ss[servoM].setDegrees(stM + 40); //170
    ss[servoN].setDegrees(stN - 30);
    ss[servoO].setDegrees(stO + 50); //右足

    ss[servoQ].setDegrees(stQ - 50);
    ss[servoR].setDegrees(stR - 70); //30
    ss[servoS].setDegrees(stS - 40); //30
    ss[servoT].setDegrees(stT + 30);
    ss[servoU].setDegrees(stU - 50); //左足

    usleep((KUSORAN_TEMPO * 2)*1000);

    ss[servoA].setDegrees(stA); //首

    ss[servoB].setDegrees(stB);
    ss[servoC].setDegrees(stC);
    ss[servoD].setDegrees(stD - 80); //左腕

    ss[servoE].setDegrees(stE);
    ss[servoF].setDegrees(stF);
    ss[servoG].setDegrees(stG + 80); //右腕

    ss[servoH].setDegrees(stH);
    ss[servoI].setDegrees(stI); //腰

    ss[servoK].setDegrees(stK + 50);
    ss[servoL].setDegrees(stL); //170
    ss[servoM].setDegrees(stM); //170
    ss[servoN].setDegrees(stN);
    ss[servoO].setDegrees(stO + 50); //右足

    ss[servoQ].setDegrees(stQ - 50);
    ss[servoR].setDegrees(stR); //30
    ss[servoS].setDegrees(stS); //30
    ss[servoT].setDegrees(stT);
    ss[servoU].setDegrees(stU - 50); //左足

    usleep((KUSORAN_TEMPO * 2)*1000);

    ss[servoB].setDegrees(stB - 10);
    ss[servoE].setDegrees(stE + 10);
    usleep((KUSORAN_TEMPO)*1000);

    ss[servoB].setDegrees(stB - 20);
    ss[servoE].setDegrees(stE + 20);
    usleep((KUSORAN_TEMPO)*1000);

    ss[servoB].setDegrees(stB - 30);
    ss[servoE].setDegrees(stE + 30);
    usleep((KUSORAN_TEMPO)*1000);

    ss[servoB].setDegrees(stB - 40);
    ss[servoE].setDegrees(stE + 40);
    usleep((KUSORAN_TEMPO)*1000);


  }
}

void biem(int times)
{
  for (int i = 0; i < times / 2; i++)
  {
    volt1(KUSORAN_TEMPO);
    volt2(KUSORAN_TEMPO);
    volt1(KUSORAN_TEMPO * 2);

    volt2(KUSORAN_TEMPO);
    volt1(KUSORAN_TEMPO);
    volt2(KUSORAN_TEMPO * 2);
  }
}

void dosuru(int t)
{
  ss[servoA].setDegrees(stA); //首

  ss[servoB].setDegrees(stB - 40);
  ss[servoC].setDegrees(stC);
  ss[servoD].setDegrees(stD - 80); //左腕

  ss[servoE].setDegrees(stE + 40);
  ss[servoF].setDegrees(stF);
  ss[servoG].setDegrees(stG + 80); //右腕

  ss[servoH].setDegrees(stH);
  ss[servoI].setDegrees(stI); //腰

  ss[servoK].setDegrees(stK + 50);
  ss[servoL].setDegrees(stL); //170
  ss[servoM].setDegrees(stM); //170
  ss[servoN].setDegrees(stN);
  ss[servoO].setDegrees(stO + 50); //右足

  ss[servoQ].setDegrees(stQ - 50);
  ss[servoR].setDegrees(stR); //30
  ss[servoS].setDegrees(stS); //30
  ss[servoT].setDegrees(stT);
  ss[servoU].setDegrees(stU - 50); //左足

  usleep(t*1000);
}
