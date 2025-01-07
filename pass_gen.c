#include <stdio.h>
#include <stdlib.h>


void generate_password(int length);

int main ()
{
    /* We set the password_length and then we ask for it to scan it */
    int password_length;

    printf("Introduce the password length:\n");
    scanf("%d", &password_length);

    /* If the password is less than 1, then we say we don't do that
    *in this place and we exit
    */
    if (password_length <= 0)
    {
        printf("The password length should be greater than 0\n");
        return 1;
    }

    /* We call what is truly the main funct */
    generate_password(password_length);

    return 0;
}

void generate_password(int length)
{
    /* We set the char array that includes all letters, digits & spec. symbols */
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz"
                "0123456789"
                "!@#$%^&*()-_+";

    /* We set an integer sizeof our char array - 1
    *so it excludes the '\0' at the end of the string charset
    */
    int charset_size = sizeof(charset) - 1;

    char password[length + 1]; /* +1 to add '\0' at the end */

    /* We do a for loop with the length and we use arc4random_uniform,
    *that function gives us a better quality random number from
    *the integer that we set before and adds it to index.
    *Next we set the password[i] to the index that we got for charset
    */
    for (int i = 0; i < length; i++)
    {
        int index = arc4random_uniform(charset_size);
        password[i] = charset[index];
    }

    /* The next line create the NUL that appears at the endof every string */
    password[length] = '\0';

    printf("Password:\n%s\n", password);
}
