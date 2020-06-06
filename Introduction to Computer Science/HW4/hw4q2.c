/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdbool.h>



/*=========================================================================
  Constants and definitions:
==========================================================================*/

/* put your #defines and typedefs here*/
#define N_NOUNS 6
#define N_VERBS 5
#define N_ADJS 6
#define MAX_DIGITS 32

/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/
bool is_suffix_in_dict(char *str, char *dict[], int n);
int compare_char(char letterA, char letterB);
int strlength(char *s);
char get_next_letter_in_small(char *str,int *position);
bool read_sentence(char *noun_suffixes[], int noun_suffixes_len,
char *verb_suffixes[], int verb_suffixes_len,
char *adj_suffixes[], int adj_suffixes_len,
int *num_of_nouns, int *num_of_verbs, int *num_of_adjs);
int is_suffix_mach_word (char *str, char *suffix);
void word_in_dict (char *noun_suffixes[], int noun_suffixes_len,
char *verb_suffixes[], int verb_suffixes_len,
char *adj_suffixes[], int adj_suffixes_len,char *str,
int *num_of_nouns, int *num_of_verbs, int *num_of_adjs );

/*lines 3
this function compare two char and return positive for a>b,negative for b>a
and 0 for equal*/
int compare_char(char letterA, char letterB)
{
    if (letterA==letterB)
        return 0;
    return letterA-letterB;
}
/*lines 4
this function return the string length */
int strlength(char *s)
{
    int i=0;
    while (s[i])
        i++;
    return i;
}
/*lines 7
this function get string and position and return the
 next letter in the string in format of small letter */
char get_next_letter_in_small(char *str,int *position)
{

    while(*position>=0)
    {
      if ((str[*position]>='a')&&(str[*position]<='z'))
        return str[*position];
      if ((str[*position]>='A')&&(str[*position]<='Z'))
        return str[*position]-('A'-'a');
      *position=*position-1;
    }
    return 0;
}
/*lines 11
this function compare string and suffix and return 0 if the suffix fit to
the word, positive if the string's suffix is bigger alphabetical order,
and negative for other*/
int is_suffix_mach_word (char *str, char *suffix)
{
    int i=0;
    int position=strlength(str)-1;
    int tempAnswerOfCompare=0;
    while (suffix[i])
    {
         tempAnswerOfCompare=compare_char(get_next_letter_in_small
                                          (str,&position),suffix[i]);
         if (tempAnswerOfCompare!=0)
            return tempAnswerOfCompare;
         position=position-1;
         i++;
    }
    return 0;
}
/*lines 14
this function check if there any suffix in the dictionary that is fit to
the word*/
bool is_suffix_in_dict(char *str, char *dict[], int n)
{
    int buttomSerch=0;
    int currentWord=0;
    int topSerch=n-1;
    int answer=0;
    while (buttomSerch<=topSerch)
    {
        currentWord=(buttomSerch+topSerch)/2;
        answer=is_suffix_mach_word (str,dict[currentWord]);
        if (answer==0)
            return true;
        if(answer<0)
            topSerch=currentWord-1;
        if(answer>0)
            buttomSerch=currentWord+1;
    }
    return false;
}
/*lines 6
this function get word and and update the counter of the word family*/
void word_in_dict (char *noun_suffixes[], int noun_suffixes_len,
char *verb_suffixes[], int verb_suffixes_len,
char *adj_suffixes[], int adj_suffixes_len,char *str,int *num_of_nouns,
 int *num_of_verbs, int *num_of_adjs )
{
    if (is_suffix_in_dict(str,noun_suffixes,noun_suffixes_len))
        *num_of_nouns=*num_of_nouns+1;
    if(is_suffix_in_dict(str,verb_suffixes,verb_suffixes_len))
        *num_of_verbs=*num_of_verbs+1;
    if(is_suffix_in_dict(str,adj_suffixes,adj_suffixes_len))
        *num_of_adjs=*num_of_adjs+1;
}
/*lines 21
this functions get sentence from the user and count the words family*/
bool read_sentence(char *noun_suffixes[], int noun_suffixes_len,
char *verb_suffixes[], int verb_suffixes_len,
char *adj_suffixes[], int adj_suffixes_len,
int *num_of_nouns, int *num_of_verbs, int *num_of_adjs)
{
    bool stop=false;
    char str[MAX_DIGITS]={0};
    int i=0;
    while((!stop))// gets letters until '.'
    {
        if ((scanf("%c",&str[i])!=EOF))//get for EOF
        {
            if(str[i]=='.')//if we get '.', we stop scanning
                stop=true;
            if ((str[i]=='.')||(str[i]=='\n')||(str[i]==' ')||
                (str[i]=='\t'))//if its end of
            {                  //word we check for suffix matching
                str[i]=0;//make the last digit \n
                if(i!=0)// for checking only when its real word
                {
                    word_in_dict(noun_suffixes,noun_suffixes_len,
                    verb_suffixes,verb_suffixes_len,adj_suffixes,
                    adj_suffixes_len,str,num_of_nouns,num_of_verbs,
                    num_of_adjs);
                }
                i=0;//start the next word from the begging of the array
            }
            else
                i++;
        }
        else
            return true;//return true if EOF
    }
        return !stop;
}
/*lines 15
this main functions get sentences from the user and count+print the
words family for each sentence*/
int main()
{
    char *noun_suffixes[] = {"msi", "re", "sci", "ssen", "tnem", "tsi"};
    char *verb_suffixes[] = {"de", "eta", "ezi", "gni", "yfi"};
    char *adj_suffixes[] = {"elba", "evi", "hsi", "la", "luf", "suo"};
    int num_of_nouns=0;
    int num_of_verbs=0;
    int num_of_adjs=0;
    printf("Enter text to analyze:\n");
    while (!read_sentence(noun_suffixes,N_NOUNS,verb_suffixes,N_VERBS,
            adj_suffixes,N_ADJS,&num_of_nouns,&num_of_verbs,&num_of_adjs))
    {
        printf("The sentence had %d nouns, ",num_of_nouns);
        printf("%d verbs and %d adjectives.\n",num_of_verbs,num_of_adjs);
        num_of_nouns=0;
        num_of_verbs=0;
        num_of_adjs=0;
    }
    return 0;
}
