    /*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdbool.h>



/*=========================================================================
  Constants and definitions:
==========================================================================*/

#define N 5// number of tax level
#define idLength 9// number of id digits
#define numSalerys 12// number of salerys to check.

bool idGetCheck();
float montnTax(int salery, int texTable [][2]);

bool idGetCheck()// this funcsion get id number and return true if its good id
{
    int idNumber=0;
     int tempSum=0;// this number save all the counters
     int idNum[idLength]={0};// this is the arr that we keep the gidit
     if (scanf(" %d", &idNumber)!=1)//checking the input
        return 0;
     for  (int i=idLength-1; i>=0; i--)// putting the id into arr
     {
           idNum[i]=idNumber%10;
           idNumber=idNumber/10;

     }
    for (int i=0; i<4; i++)//after we get real number id ,we check if it leagel.
        {
            tempSum=tempSum+ (((idNum[i])+(idNum[i+4]))%(4+i));
        }
            return(tempSum%10==(idNum[idLength-1]));//if the id pass all the check, return true (1); else false(0)

}
float montnTax(int salery, int texTable [N+1][2])//this funcsion get one month salary and the tax info and return the month tax.
{
    float tax=0;//the total tax for the month
   for(int i=1;i<N+1;i++)// this loop take the tax between every 2 tax level.
   {
                   tax+=((((float)(texTable[i][0])-(texTable[i-1][0]))/100)*texTable[i][1])*(salery>=texTable[i][0]);
                   tax+=((((float)(salery-texTable[i-1][0]))/100)*texTable[i][1])*((salery>texTable[i-1][0])&&(salery<texTable[i][0]));

   }
    return tax;
}

int main()// we getting tax level, id and 12 salerys; we return the year tax;
{
  float yearTax=0;//the tax that man need to pay for all the year
  int texTable[N+1][2]={{0},{0}};//we are geting the tex table info frome the user and saved it into arry.
  double sumSalery=0;//count all the salerys ;
  texTable[0][0]=0;//here we said the button tax level it 0(it important to the cuoclate);
  texTable[0][1]=1;
  for (int i=1; i<N+1; i++)//getting the tax info,check it, and saved it into arr;
  {
      if(scanf(" %d %d",&texTable[i][0],&texTable[i][1])!=2)
        return -1;
  }
   texTable[N][0]=999999999;
  printf("Please, enter your ID and your last 12 salaries:\n");
  bool idState= idGetCheck();//get the id and save true for legal and false for illegal;
  int salerys [numSalerys];//getting the salerys and check them
  for (int i=0; i<numSalerys; i++)
        if (scanf(" %d",&salerys[i])!=1)
            return 0;
   for  (int i=0; i<numSalerys; i++)//cacolate the total taxes and salerys//
   {
        yearTax+=montnTax(salerys[i],texTable);
        sumSalery+=salerys[i];
   }

    yearTax=sumSalery*(!idState)+yearTax*(idState);// if idState is true we give the normal tax; if false, the tax is all the year salerys;
    yearTax=yearTax+((yearTax-(int)yearTax)>0.5);// if the fraction is bigger the 0.5 we make the year tax ++;
    printf("Total tax:     %d\n",(int)yearTax);// return the tax without the fraction
    return 0;

}
