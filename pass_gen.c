#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_password(int length)
{
    /* We set the char array that includes all letters, digits & spec. symbols */
    charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz"
                "0123456789"
                "!@#$%^&*()-_+";

    /* We set an integer sizeof our char array - 1
        so it excludes the '\0' at the end of the string charset
    */
    int charset_size = sizeof(charset) - 1;

    char password[length + 1]; /* +1 to add '\0' at the end */

    /* We do a for loop with the length and we use arc4random_uniform,
        that function gives us a better quality random number from
        the integer that we set before and adds it to index.
        Next we set the password[i] to the index that we got for charset
    */
    for (int i = 0; i < length; i++)
    {
        int index = arc4random_uniform(charset_size);
        password[i] = charset[index];
    }

    /* The next line create the NUL that appears at the endof every string */
    password[length] = '\0';

    printf("Password:\n%s", password);
}
