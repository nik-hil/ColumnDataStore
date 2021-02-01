//strtok.h

/*

 strTok is same as the standard strtok function. You need to implement the functionality without
 using strtok function itself.
 The usage is as given below

 1) to start with the strTok is called with the string that needs to be tokenised
    ex: char str[] ="this is a sample text"
        char *tok=strTok(str," ");
    here the function tokenises the given string and returns just the string from
    the given string till it finds the 2nd parameter(its a string not char)
    ex: it returns a char * which has the contents "this\0". \0 is null which marks the
    end of the string. The string that is passed as the 1st argument is unchanged

 2) to get the consequent tokens the 1st parameter is passed as NULL, which means use the
    string that has been passed earlier.
    ex: char *newtok=strTok(NULL," ");
    This returns the next token

 3) If the strTok does not find the separator string in the given string, it returns the given string
    ex: strTok("this is a full token",":")   returns "this is a full token"

 4) If the strTok gets a NULL as 1st argument and it has finished tokeninsing the previous string then
    it returns NULL
    ex: strTok("this is a full token",":")   returns "this is a full token"
        strTok(NULL,":")  if called will return NULL as there was no more string to tokenize

 A full example of the function is given



 * strTok example by mind@metalshell.com
 *
 * This is an example on string tokenizing
 *
 * 02/19/2002
 *
 * http://www.metalshell.com
 *


#include <stdio.h>
#include <string.h>
#include "strtok.h"

int main(int argc, char *argv[])
{
        int x = 1;
        char str[]="this:is:a:test:of:string:tokenizing";
        char *str1;

        // print what we have so far
        printf("String: %s\n", str);

        // extract first string from string sequence
        str1 = strTok(str, ":");

        // print first string after tokenized
        printf("%i: %s\n", x, str1);

        // loop until finishied
        while (1)
        {
                // extract string from string sequence
                str1 = strTok(NULL, ":");

                // check if there is nothing else to extract
                if (str1 == NULL)
                {
                        printf("Tokenizing complete\n");
                        exit(0);
                }

                // print string after tokenized
                printf("%i: %s\n", x, str1);
                x++;
        }

        return 0;

}



Note: you will have to use a static variable inorder to store the remaining string.

*/

char *strTok(char *string, char *delimiter);