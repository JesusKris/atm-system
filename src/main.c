#include "header.h"

void mainMenu(struct User u)
{
    int option;

mainMenu:
    drawMainMenu1();
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        createNewAcc(u);
        goto mainMenu;
    case 2:
        updateAccount(u);
        goto mainMenu;
    case 3:
        checkOneAccount(u);
        goto mainMenu;
    case 4:
        checkAllAccounts(u);
        goto mainMenu;
    case 5:
        makeTransaction(u);
        goto mainMenu;
    case 6:
        deleteAccount(u);
        goto mainMenu;
    case 7:
        transferAccount(u);
        goto mainMenu;
    case 8:
        exit(1);
    default:
        drawMainMenu2();
        system("sleep 1.5");
        goto mainMenu;
    }
};

void initMenu(struct User *u)
{
    int r = 0;
    int option;

initMenu:
    drawInitMenu();
    while (!r)
    {
        scanf("%d", &option);
        switch (option)
        {
        case 1:
        login:
            loginMenu(u->name, u->password);
            if (strcmp(u->password, getPassword(*u)) == 0)
            {
                drawLoginMenu3();
                getUserId(u);
                system("sleep 1.5");
            }
            else
            {
                drawLoginMenu4();
                system("sleep 1.5");
                goto login;
            }
            r = 1;
            break;
        case 2:
        regist:

            if (strcmp(registerMenu(), "true") == 0)
            {
                drawRegisterMenu4();
                system("sleep 1.5");
            }
            else
            {
                drawRegisterMenu2();
                system("sleep 1.5");
                goto regist;
            }

            goto initMenu;
        case 3:
            exit(1);
            break;
        default:
            goto initMenu;
        }
    }
};

int main()
{
    struct User u;

    initMenu(&u);
    mainMenu(u);
    return 0;
}
