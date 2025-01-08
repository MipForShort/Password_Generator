#include <stdio.h>
#include <stdlib.h> // For arc4random_uniform and strtol
#include <errno.h> // For errno
#include <limits.h> // For INT_MAX, INT_MIN


void generate_password(int length);
void copy_to_clipboard(const char *password);
void write_to_file(const char *password);

int main(int argc, char *argv[])
{
    /* Check for invalid usage */
    if (argc != 2)
    {
        printf("Usage: ./pass_gen <password_length>\n");
        return 1;
    }

    /* Variables needed for storing password_length and the chars from argv[1] */
    char *p;
    int password_length;

    errno = 0; // Not int errno, that is already include with errno.h

    /* We set a long # with strtol using arvg[1], derefernce of *p and length 10 */
    long converter = strtol(argv[1], &p, 10);

    /* We check for errors on ernno, if the string is not digits or
    *if it doens't have the right size of an integer
    */
    if (errno != 0 || *p != '\0' || converter > INT_MAX || converter < INT_MIN)
    {
        printf("Usage: ./pass_gen <password_length>\n");
        return 2;
    }
    else
    {
        password_length = converter;
        printf("Length of password:\n%d\n", password_length);
    }

    /* The next lines are the typical scanf way to read a number,
    *use it if you don't want to use argc/argv
    */

    /* We set the password_length and then we ask for it to scan it */
    /*
    printf("Introduce the password length:\n");
    scanf("%d", &password_length);
    */

    /* If the password is less than 1, then we say we don't do that
    *in this place and we exit
    */
    if (password_length <= 0)
    {
        printf("The password length should be greater than 0.\n");
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

    char password[length + 1]; /* +1 to add '\0' at the end and it becomes a string */

    /* We do a for loop with the length and we use arc4random_uniform,
    *that function gives us a better quality random number than rand(), this from
    *the integer that we set before and adds it to index.
    *Next we set the password[i] to the index value that we got for charset
    */
    for (int i = 0; i < length; i++)
    {
        int index = arc4random_uniform(charset_size);
        password[i] = charset[index];
    }

    /* The next line creates the NUL that appears at the end of every string */
    password[length] = '\0';

    printf("Password:\n%s\n", password);

    /* Menu for copy_to_clipboard or write_to_file */
    int option;
    printf("Select an option:\n1. Copy to clipboard\n2. Write to file\n3. Exit\nOption:\n");
    scanf("%d", &option);

    /* The next while loop checks for option not being smaller than 0 or
    *greater than 3 and scan it again
    */
    while (option > 3 || option < 1)
    {
        printf("Invalid option\nInsert a new one\nOption:\n");
        scanf("%d", &option);
    }
    switch (option)
    {
        case 1:
            printf("To copy the password manually, select it and use Ctrl+Shift+C from console\n");
            copy_to_clipboard(password);
            break;
        case 2:
            write_to_file(password);
            break;
        case 3:
            printf("Goodbye!\n");
            break;
        default:
            printf("Invalid option\n");
            break;
    }
}


void copy_to_clipboard(const char *password)
{
    FILE *clipboard = popen("xclip -sel clip", "w"); // Use pbcopy for Mac
    if (clipboard == NULL)
    {
        printf("Error accessing clipboard\n");
        return;
    }
    fprintf(clipboard, "%s", password);
    pclose(clipboard);
    printf("Password copied to clipboard\n");
}


void write_to_file(const char *password)
{
    FILE *file = fopen("password.txt", "w");
    if (file == NULL)
    {
        printf("Error creating file\n");
        return;
    }
    fprintf(file, "%s", password);
    fclose(file);
    printf("Password saved to 'password.txt'\n");
}
