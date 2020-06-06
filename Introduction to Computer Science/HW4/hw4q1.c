/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdbool.h>



/*=========================================================================
  Constants and definitions:
========================================================================== */
#define M 50
#define REC_TOP 0
#define REC_LEFT 1
#define REC_BOTTOM 2
#define REC_RIGHT 3

/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/
void compute_integral_image(int image[][M], int n, int m,
                             int integral_image[][M]);
int sum_rect(int integral_image[][M], int rect[4]);
void sliding_average(int image[][M], int n, int m,
                      int h, int w, int average[][M]);
int setImageArry(int imageArry [][M], int *imageLines,int *imageRows);

/*lines 14
this function get dimensions of image and image*/
int setImageArry(int imageArry [][M], int *imageLines,int *imageRows)
{
    for (int i=0; i<M; i++)
        for (int j=0; j<M; j++)
            imageArry[i][j]=0;
    printf("Enter image dimensions:\n");
    if (scanf(" %d %d",imageLines,imageRows)!=2)
    {
        printf("error");
        return -1;
    }
    printf("Enter image:\n");
    for (int i=0; i<*imageLines; i++)
        for (int j=0; j<*imageRows; j++)
            if (scanf(" %d",&imageArry[i][j])!=1)
            {
                printf("error");
                return -1;
            }
    return 0;
}
/*lines 9
this function get dimensions of sliding window*/
int setWindow(int window [],int imageLines,int imageRows)
{
    printf("Enter sliding window dimensions:\n");
    if (scanf(" %d %d",&window[0], &window[1])!=2)
    {
        printf("error");
        return -1;
    }
    if ((window[0]<0)||(window[1]<0)||(window[0]%2==0)|| (window[1]%2==0)
        ||(window[0]>imageLines) ||(window[1]>imageRows))//check if the
        // dimensions are legal.
    {
        printf("error\n");
        return -1;
    }
    return 0;
}

/*lines 8
this function compute integral image of image*/
void compute_integral_image(int image[][M], int n, int m,
                             int integral_image[][M])
{
    integral_image[0][0]=image[0][0];
    for (int j=1; j<m;j++)// compute the first row
        integral_image[0][j]= integral_image[0][j-1]+image[0][j];
    for (int i=1; i<n;i++)
    {
        integral_image[i][0]= integral_image[i-1][0]+image[i][0];//compute
        //the first integral for each row
        for (int j=1; j<m;j++)//computing the rest integrals
        {
            integral_image[i][j]=integral_image[i][j-1]+
            integral_image[i-1][j]+image[i][j]-integral_image[i-1][j-1];
        }
    }
}
/*lines 9
this function compute the sum of one rectangle in image */
int sum_rect(int integral_image[][M], int rect[4])
{
    int sumLeft=0,sumUp=0,sumCover=0;
    if (rect[REC_TOP]>0)//compute the sum from the top right corner
        sumUp=integral_image[rect[REC_TOP]-1][rect[REC_RIGHT]];
    if (rect[REC_LEFT]>0)//compute the sum from the bottom left corner
        sumLeft=integral_image[rect[REC_BOTTOM]][rect[REC_LEFT]-1];
    if (rect[REC_TOP]>0&&rect[REC_LEFT]>0)//compute the cover area
        sumCover=integral_image[rect[REC_TOP]-1][rect[REC_LEFT]-1];
    return integral_image[rect[REC_BOTTOM]][rect[REC_RIGHT]]
    +sumCover-sumLeft-sumUp;
}
/*lines 15
this function computing array of sliding average */
void sliding_average(int image[][M], int n, int m, int h, int w,
                     int average[][M])
{
    int rect [4]={0};
    int integral_image[M][M]={{0}};
    compute_integral_image(image,n,m,integral_image);
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
        {
            rect[REC_TOP]=i-(h/2);
            rect[REC_LEFT]=j-(w/2);
            rect[REC_BOTTOM]=i+(h/2);
            rect[REC_RIGHT]=j+(w/2);
            if (rect[REC_BOTTOM]>=n)
                rect[REC_BOTTOM]=n-1;
            if (rect[REC_RIGHT]>=m)
                rect[REC_RIGHT]=m-1;
            average[i][j] =(int)((((double) sum_rect(integral_image,rect))
                                  /(w*h))+0.5);
        }
}

/*lines 22
 this main function get from the user one image and one dimensions of
 sliding window and computed and print the integral image and smoothed
 image*/
int main()
{
    int imageLines=0, imageRows=0,integral_image[M][M]= {{0}};
    int imageArry [M][M]={{0}},average[M][M]={{0}},window [2]={0};
    if (setImageArry(imageArry,&imageLines,&imageRows)==-1)
        return -1;
    if (setWindow(window,imageLines,imageRows)==-1)
        return -1;
    compute_integral_image(imageArry,imageLines,imageRows,integral_image);
    sliding_average(imageArry,imageLines,imageRows,window[0],window[1],
                    average);
    printf("Integral image is:\n");
    for(int i=0; i<imageLines; i++)
        {
            printf("%d",integral_image[i][0]);
            for(int j=1; j<imageRows; j++)
                printf(" %d",integral_image[i][j]);
            printf("\n");
        }
    printf("Smoothed image is:\n");
    for(int i=0; i<imageLines; i++)
        {
            printf("%d",average[i][0]);
            for(int j=1; j<imageRows; j++)
                printf(" %d",average[i][j]);
            printf("\n");
        }
    return 0;
}
