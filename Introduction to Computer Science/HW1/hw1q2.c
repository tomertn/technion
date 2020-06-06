#include <stdio.h>
#include <math.h>

int main()
{
    int count=0;
    char c,letter;
    printf("Enter char to count:\n");
    scanf("%c",&c);
    if (c=='#')
        return 0;
    printf("Enter the chars sequence:\n");
    scanf("%c",&letter);
    while (letter!='#'){
            if  (letter==c)
            count++;
            scanf("%c",&letter);
    }


        printf("The char with ASCI code %d appeared %d times\n",c,count);
  return 0;
}
