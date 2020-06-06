/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdbool.h>



/*=========================================================================
  Constants and definitions:
========================================================================== */
#define subjects 6



/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/
double StudentaAverage (int studentTable[][subjects+1],int id);
double courseAverage (int studentTable[][subjects+1],int course);
int excelled (int studentTable[][subjects+1]);
int failed (int studentTable[][subjects+1]);
void queryTheSystem (int studentTable[][subjects+1]);
int getNumOfSubjects(int studentTable[][subjects+1], int id);

int getNumOfSubjects(int studentTable[4096][subjects+1], int id)// get the number of courses that the student took.
{
    int numOfSubjects=0;
    int i=0;
    while ((studentTable[i][0]!=id)&&(i<4096))//we finding the the student in the array
        {
            i++;
        }
    for (int j=1; j<subjects+1; j++)// we count the student courses
    {
        if (studentTable[i][j]!=-1)
        {
             numOfSubjects++;
        }
    }
    return numOfSubjects;

}
void queryTheSystem (int studentTable[4096][subjects+1])// this function get digits from the user and printing the answers
{
    int id=0;
    char command='0';
    bool keepWork=true;
    printf("You may query the grading system now:\n");
    if((scanf(" %c",&command)==EOF))//checking that the first comman isnt EOF
       keepWork=false;
       while  (keepWork)// for every char we print the function returns
       {
          switch (command)
           {
               case 'S' : if (scanf(" %d",&id)==1)
                            printf("Average grade of %d is: %.2f\n", id, StudentaAverage(studentTable,id)); break;
               case 'C' : if (scanf(" %d",&id)==1)
                            printf("Average per course %d is: %.2f\n", id, courseAverage(studentTable,id)); break;
               case 'A' : printf("%d excelled\n",excelled(studentTable)); break;
               case 'F' : printf("%d failed\n", failed(studentTable)); break;
           default: printf("Invalid command, please try again:\n");
           }
          if((scanf(" %c",&command)==EOF))
            keepWork=false;
       }
       printf("Session Ended.\n");
}
double StudentaAverage (int studentTable[4096][subjects+1],int id)//we get arr of id's and grades and one id number; we return Student's average;
{
    double gradesSum=0;
    int numOfSubjects=0;
    int i=0;
    while ((studentTable[i][0]!=id)&&(i<4096))//we finding the the student in the array
        {
            i++;
        }

    if (i==4096)// if the student dont exist we return 0
        return 0;
    for (int j=1; j<subjects+1; j++)// we sum the student grades
    {
        if (studentTable[i][j]!=-1)
        {
            gradesSum+=studentTable[i][j];
             numOfSubjects++;
        }
    }
    if(numOfSubjects==0)// if the student didnt take any subject we return 0
        return 0;
    return (gradesSum/numOfSubjects);// return the average


}
double courseAverage (int studentTable[4096][subjects+1],int course)//we get arr of id's and grades and one course number; we return course average;
{
    double gradesSum=0;
    int studentaInCourse=0;
    int i=0;
    while ((studentTable[i][0]!=0)&&(i<4096))// we running on all the student and we sum all the real grades
        {
             if (studentTable[i][course]!=-1)
             {
                 gradesSum+=studentTable[i][course];
                 studentaInCourse++;
             }
            i++;
        }
    if(studentaInCourse==0)// if no student in the course we return 0;
        return 0;
   return (gradesSum/studentaInCourse);//return the average;

}
int excelled (int studentTable[4096][subjects+1])// we get array of ids and grades; we return the number of excelled students
{
    int excelledStudents=0;
    int i=0;
    int average=0;
    while ((studentTable[i][0]!=0)&&(i<4096))// we running on all the student and count the excelled
        {
            average=StudentaAverage(studentTable, studentTable[i][0]);// count the average
             if ((average>86)&&(getNumOfSubjects(studentTable,studentTable[i][0])>=4))// checking if the student is excelled
                {
                 excelledStudents++;// counting the excelled students
                }
            i++;
        }
   return (excelledStudents);//return the excelled students;

}
int failed (int studentTable[4096][subjects+1])//// we get array of ids and grades; we return the number of failed students
{
    int average=0;
    int failedSubjects=0;
    int failesStudents=0;
    int i=0;
    while ((studentTable[i][0]!=0)&&(i<4096))// we running on all the student and count the faileds
        {
            for (int j=1; j<subjects+1; j++)// counting the failed subjects
                {
                    if (studentTable[i][j]==0)
                            failedSubjects++;
                }
             average=StudentaAverage(studentTable, studentTable[i][0]);// getting the average
             if (getNumOfSubjects(studentTable,studentTable[i][0])!=0)// checking if the student didnt take anny courese
                if ((average<65)||(((double)failedSubjects/getNumOfSubjects(studentTable,studentTable[i][0]))*100>33))
                {
                 failesStudents++;// countint the failes
                }
                failedSubjects=0;
                i++;
        }
   return (failesStudents);// return the number of the failed

}
int main()// we getting number of student and grades of them; and we answer any query we get;
{

    char  thisGrade='0';
    int studensNum=0;
    int studentTable[4096][7]={{0},{0}};
    printf("Enter the number of students:\n");
    if ((scanf(" %d",&studensNum)!=1))// checking the input
        {
             printf("Error\n");
             return 0;
        }
    if (studensNum<0)
        {
             printf("Error\n");
             return 0;
        }
     printf("Enter student IDs followed by 6 grades:\n");
    for (int i=0; i<studensNum; i++)
    {
        printf("Student #%d:\n",(i+1));
        if ((scanf(" %d",&studentTable[i][0])!=1))// checking the id
            {
                printf("Error\n");
                return 0;
            }
        if(studentTable[i][0]>999999999)
            {
                printf("Error\n");
                return 0;
            }
        for (int j=1; j<7; j++)// getting the grades and "casting" them to int;
            {
                if (scanf(" %c",&thisGrade)!=1)
                    {
                        printf("Error\n");
                        return 0;
                    }
                switch (thisGrade)
                    {
                        case 'A' : studentTable[i][j]=100; break;
                        case 'B' :  studentTable[i][j]=85; break;
                        case 'C' :  studentTable[i][j]=70; break;
                        case 'D' :  studentTable[i][j]=55; break;
                        case 'F' :  studentTable[i][j]=0; break;
                        case '-':  studentTable[i][j]=-1; break;
                        default: printf("Error\n"); return 0;
                    }
            }
    }
    queryTheSystem(studentTable);// answer the question of the user;
         return 0;
}
