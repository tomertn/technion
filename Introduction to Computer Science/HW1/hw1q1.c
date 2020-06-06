#include <stdio.h>
#include <math.h>

int main()
{
    double a=1, b=1, c=1, delta=0,sqrt1=0, sqrt2=0;
    printf("Enter a polynomial:\n");
    if(scanf(" a = %lf , b = %lf , c = %lf",&a,&b,&c)!=3)
        return 0;
    delta=(b*b)-(4*a*c);
    if(delta<0){
           printf("There are no roots\n");
           return 0;
    }
    if (delta==0){
        sqrt1=((-1)*b)/(2*a);
        printf("Root is %f\n",sqrt1);
        return 0;
    }
        sqrt1=((-1)*b+sqrt(delta))/(2*a);
        sqrt2=((-1)*b-sqrt(delta))/(2*a);
        printf("Roots are %f, %f\n",sqrt1,sqrt2);
  return 0;
}
