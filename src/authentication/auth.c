#include <termios.h>
#include "../header.h"

char *USERS = "./data/users.txt";

void loginMenu(char a[50], char pass[50])
{
    struct termios oflags, nflags;

    drawLoginMenu1();
    scanf("%s", a);

    // disabling echo
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }

    drawLoginMenu2();
    scanf("%s", pass);

    // restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
};

const char *getPassword(struct User u)
{
    FILE *fp;
    struct User userChecker;

    if ((fp = fopen("./data/users.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    while (fscanf(fp, "%d %s %s", &(userChecker.id), userChecker.name, userChecker.password) != EOF)
    {
        if (strcmp(userChecker.name, u.name) == 0)
        {
            u.id = userChecker.id;
            fclose(fp);
            char *buff = userChecker.password;
            return buff;
        }
    }

    fclose(fp);
    return "no user found";
}

const char *registerMenu()
{

    struct User registerData;
    struct User userChecker;

    drawRegisterMenu1();
    scanf("%s", registerData.name);

    FILE *fp;

    if ((fp = fopen("./data/users.txt", "a+")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    while (fscanf(fp, "%d %s %s", &(userChecker.id), userChecker.name, userChecker.password) != EOF)
    {
        if (strcmp(registerData.name, userChecker.name) == 0)
        {
            fclose(fp);
            char *answer = "false";
            return answer;
        }
    }

    drawRegisterMenu3();
    scanf("%s", registerData.password);

    registerData.id = getNextId();
    addUser(fp, &registerData);

    fclose(fp);
    char *answer = "true";
    return answer;

    /* registerData.id = getNextId(); */
}
