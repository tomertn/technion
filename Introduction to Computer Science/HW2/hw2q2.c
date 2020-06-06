/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdbool.h>



/*=========================================================================
  Constants and definitions:
==========================================================================*/



/*-------------------------------------------------------------------------
  The main program.
 -------------------------------------------------------------------------*/
int average (int gradeCnt[]);
int min (int gradeCnt[]);
int man (int gradeCnt[]);
int medianGrade (int gradeCnt[]);
int upGrade(int gradeCnt[],int gradeToUp);
int downGrade(int gradeCnt[],int gradeToDown);
int factor(int gradeCnt[],int passGrade, int percentage);

int average (int gradeCnt[])//we get the grades array and return the average of the course
{
    double gradesSum=0;
    int studentNum=0;
    double average=0;
    for (int i=0; i<101; i++)//sum the grades and students;
    {
        gradesSum+=gradeCnt[i]*(i);
        studentNum+=gradeCnt[i];
    }
    if (studentNum==0)
        return 0;
   average=gradesSum/studentNum;// calculate the average
   if(((average-(int)average)>0.5))
        average++;
    return (int)average;
}
int max (int gradeCnt[])//we get the grades array and return the max grade of the course
{
   int max=0;
   int i=100;
    while((max==0)&& (i>0))
    {
        if(gradeCnt[i]!=0)
            max=i;
        i--;
    }
   return max;
}

int min (int gradeCnt[])//we get the grades array and return the min grade of the course
{
   int min=100;
   int i=0;
    while((min==100)&& (i<100))
    {
        if(gradeCnt[i]!=0)
            min=i;
        i++;
    }
    return min;
}
int medianGrade (int gradeCnt[])//we get the grades array and return the median grade of the course
{
    int studentNumTotal=0;
    int studentUnderMedian=0;
    for (int i=0; i<101; i++)
    {
        studentNumTotal+=gradeCnt[i];
    }
    for (int i=0; i<101; i++)// we running on the grades from 0 and when we sum at list half of the student we return the midian;
    {
        studentUnderMedian+=gradeCnt[i];
        if ((studentUnderMedian*2)>=studentNumTotal)
            return i;
    }
    return 0;
}
int upGrade(int gradeCnt[],int gradeToUp)//we get the grades array and one grade; we return the how many students are bigger them him
{
   int counter=0;
    for (int i=gradeToUp+1; i<=100; i++)
    {
       counter+=gradeCnt[i];
    }
    return counter;
}
int downGrade(int gradeCnt[],int gradeToDown)//we get the grades array and one grade; we return the how many students are smaller them him
{
   int counter=0;
    for (int i=0; i<gradeToDown; i++)
    {
       counter+=gradeCnt[i];
    }
    return counter;
}

int factor(int gradeCnt[],int passGrade, int percentage)//we get the grades array, grade and percentage; we return factor needed to make that the percentage of student get at list the grade;
{
  double studentNumTotal=0;
  int studentPass=0;
  if ((passGrade>100)||(passGrade<0)||(percentage>100)||(percentage<0))// checking the input;
      return 0;
    for (int i=0; i<101; i++)// getting the number of students
    {
        studentNumTotal+=gradeCnt[i];
    }
     studentPass=upGrade(gradeCnt,passGrade)+gradeCnt[passGrade];
     int j=passGrade;
     while(((percentage*studentNumTotal))/100>studentPass)// checking that the grade that we have the percentage student abuth him.
     {
         studentPass+=gradeCnt[j-1];
         j--;
     }
     return passGrade-j;// calculate and return the factor;
}
int main()// we getting grades and answer commands about them;
{
    int gradesTable[101]={0};
    int thisGrade=0; int percentage=0;
    int gradeToCheck=0;
    char command=0;
    bool keepWork=false;
    while(thisGrade!=-1)// checking the input;
        if(scanf(" %d",&thisGrade)==1)
            if((thisGrade>=0)&&(thisGrade<=100))
                gradesTable[thisGrade]++;
    if((scanf(" %c",&command)!=EOF))// checking there is coomand to answer;
       keepWork=true;
       while  (keepWork)// answer commands
       {
           switch (command)
           {
               case 'V' : printf("%d\n",average(gradesTable)); break;
               case 'X' : printf("%d\n",max(gradesTable)); break;
               case 'I' : printf("%d\n",min(gradesTable)); break;
               case 'M' : printf("%d\n",medianGrade(gradesTable)); break;
               case 'A' : if (scanf(" %d",&gradeToCheck)==1)
                            printf("%d\n",upGrade(gradesTable,gradeToCheck)); break;
               case 'B' : if (scanf(" %d",&gradeToCheck)==1)
                             printf("%d\n",downGrade(gradesTable,gradeToCheck)); break;
               case 'F' : if (scanf(" %d %d",&gradeToCheck,&percentage)==2)
                                printf("%d\n",factor(gradesTable,gradeToCheck,percentage)); break;
           default: printf("This command is not currently supported by the system.\n");
           }
          if((scanf(" %c",&command)==EOF))
            keepWork=false;
       }
  return 0;
}
