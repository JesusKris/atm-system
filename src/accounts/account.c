#include "../header.h"
#include <stdlib.h>

const char *RECORDS = "./data/records.txt";

int getAccountFromFile(FILE *ptr, char name[50], struct Record *r)
{
    return fscanf(ptr, "%d %d %s %d %d/%d/%d %s %d %lf %s",
                  &r->id,
                  &r->userId,
                  name,
                  &r->accountNbr,
                  &r->deposit.month,
                  &r->deposit.day,
                  &r->deposit.year,
                  r->country,
                  &r->phone,
                  &r->amount,
                  r->accountType) != EOF;
}

void success(struct User u)
{
    int option;
    drawSucces1();
invalid:
    scanf("%d", &option);
    system("clear");
    if (option == 1)
    {
        mainMenu(u);
    }
    else if (option == 0)
    {
        exit(1);
    }
    else
    {
        drawSucces2();
        goto invalid;
    }
}

void saveAccountToFile(FILE *ptr, struct User u, struct Record *r)
{
    fprintf(ptr, "\n");
    fprintf(ptr, "%d %d %s %d %d/%d/%d %s %d %lf %s",
            r->id,
            u.id,
            u.name,
            r->accountNbr,
            r->deposit.month,
            r->deposit.day,
            r->deposit.year,
            r->country,
            r->phone,
            r->amount,
            r->accountType);
}

void createNewAcc(struct User u)
{
    struct Record r;
    struct Record cr;
    char userName[50];
    FILE *pf = fopen(RECORDS, "a+");

noAccount:
    drawCreateAcc1();
    scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year);

    drawCreateAcc2();
    scanf("%d", &r.accountNbr);

    while (getAccountFromFile(pf, userName, &cr))
    {
        if (strcmp(userName, u.name) == 0 && cr.accountNbr == r.accountNbr)
        {
            drawCreateAcc3();
            goto noAccount;
        }
    }

    drawCreateAcc4();
    scanf("%s", r.country);

    drawCreateAcc5();
    scanf("%d", &r.phone);

    drawCreateAcc6();
    scanf("%lf", &r.amount);

    drawCreateAcc7();
    scanf("%s", r.accountType);

    r.id = getNextRecordsId() + 1;

    fclose(fopen(RECORDS, "a+"));

    pf = fopen(RECORDS, "a+");
    saveAccountToFile(pf, u, &r);

    fclose(pf);
    success(u);
}

void checkAllAccounts(struct User u)
{
    char userName[100];
    struct Record r;

    FILE *pf = fopen(RECORDS, "r");

    system("clear");
    printf("\t\t==================================== All accounts from user, %s ====================================\n\n", u.name);
    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0)
        {
            printf("\t\t\t_____________________\n");
            printf("\n\t\t\tAccount ID: %d\n\t\t\tAccount number: %d\n\t\t\tDeposit Date: %d/%d/%d \n\t\t\tCountry: %s \n\t\t\tPhone number: %d \n\t\t\tAmount deposited: $%.2f \n\t\t\tType Of Account: %s\n",
                   r.id,
                   r.accountNbr,
                   r.deposit.day,
                   r.deposit.month,
                   r.deposit.year,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType);
        }
    }
    fclose(pf);
    success(u);
}

void stayOrReturn(int notGood, void f(struct User u), struct User u)
{
    int option;
    if (notGood == 0)
    {
        system("clear");
        printf("\n✖ Record not found!!\n");
    invalid:
        printf("\nEnter 0 to try again, 1 to return to main menu and 2 to exit:");
        scanf("%d", &option);
        if (option == 0)
            f(u);
        else if (option == 1)
            mainMenu(u);
        else if (option == 2)
            exit(0);
        else
        {
            printf("Insert a valid operation!\n");
            goto invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &option);
    }
    if (option == 1)
    {
        system("clear");
        mainMenu(u);
    }
    else
    {
        system("clear");
        exit(1);
    }
}

void save1AccountToFile(FILE *ptr, char name[50], struct Record r)
{
    fprintf(ptr, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n",
            r.id,
            r.userId,
            name,
            r.accountNbr,
            r.deposit.month,
            r.deposit.day,
            r.deposit.year,
            r.country,
            r.phone,
            r.amount,
            r.accountType);
}

void save2AccountToFile(FILE *ptr, char name[50], struct Record r)
{
    markingID(&r, name);
    fprintf(ptr, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n",
            r.id,
            r.userId,
            name,
            r.accountNbr,
            r.deposit.month,
            r.deposit.day,
            r.deposit.year,
            r.country,
            r.phone,
            r.amount,
            r.accountType);
}

void updateAccount(struct User u)
{
    char userName[100];
    struct Record accounts[128];
    struct Record r;
    int choice;
    int i = 0;
    bool changed;

    FILE *pf = fopen(RECORDS, "r");

    getAllAccounts(u);
    drawUpdateMenu8();
    scanf("%d", &choice);
    fclose(fopen(RECORDS, "r"));

    pf = fopen(RECORDS, "r");

    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0 && choice == r.id)
        {

            getAllAccounts(u);
            drawUpdateMenu3(r.id);
            scanf("%d", &choice);
            if (choice == 1)
            {
                drawUpdateMenu5();
                scanf("%d", &r.phone);
            }
            else if (choice == 2)
            {
                drawUpdateMenu6();
                scanf("%s", r.country);
            }
            changed = true;
        }
        strcpy(r.name, userName);
        accounts[i] = r;
        i++;
    }

    fclose(pf);

    if (changed)
    {

        fclose(fopen(RECORDS, "w"));

        pf = fopen(RECORDS, "a+");

        for (int j = 0; j < i; j++)
        {
            save1AccountToFile(pf, accounts[j].name, accounts[j]);
        }
        fclose(pf);
        drawUpdateMenu7();
        system("sleep 1.5");
        return;
    }
    else
    {
        drawUpdateMenu2();
        system("sleep 1.5");
        return;
    }
}

void checkOneAccount(struct User u)
{

    int choice, choice2;

start:
    getAllAccounts(u);
    drawOneAccountMenu1(u);
    scanf("%d", &choice);
    if (choice == 1111)
    {
        return;
    }
    if (strcmp(checkAccountOwner(choice, u.name), "false") == 0)
    {
        drawUpdateMenu2();
        system("sleep 1.5");
        goto start;
    }
middle:
    getAllAccounts(u);
    drawOneAccountMenu2(u, choice);
    scanf("%d", &choice2);
    if (choice2 == 0)
    {
        return;
    }
    else if (choice2 == 1)
    {
        goto start;
    }
    else
    {
        goto middle;
    }
}

void transferAccount(struct User u)
{
    char userName[100];
    struct Record accounts[128];
    struct Record r;
    int i = 0;
    bool changed;
    int id;
    char selectedP[100];

    FILE *pf = fopen(RECORDS, "r");

    getAllAccounts(u);
    drawTransferMenu1();
    scanf("%d", &id);
    fclose(fopen(RECORDS, "r"));

    pf = fopen(RECORDS, "r");

    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0 && id == r.id)
        {
        middle:
            getAllAccounts(u);
            drawTransferMenu2();
            scanf("%s", selectedP);
            if (strcmp(checkUser(selectedP), "false") == 0)
            {
                drawTransferMenu3();
                system("sleep 1.5");
                goto middle;
            }
            strcpy(r.name, selectedP);
            changed = true;
        }
        else
        {
            strcpy(r.name, userName);
        }
        accounts[i] = r;
        i++;
    }

    fclose(pf);

    if (changed)
    {

        fclose(fopen(RECORDS, "w"));

        pf = fopen(RECORDS, "a+");

        for (int j = 0; j < i; j++)
        {
            save2AccountToFile(pf, accounts[j].name, accounts[j]);
        }
        fclose(pf);
        drawUpdateMenu7();
        system("sleep 1.5");
        return;
    }
    else
    {
        drawUpdateMenu2();
        system("sleep 1.5");
        return;
    }
}

void deleteAccount(struct User u)
{
    char userName[100];
    struct Record accounts[128];
    struct Record r;
    int choice;
    int i = 0;
    bool changed;

    FILE *pf = fopen(RECORDS, "r");

    getAllAccounts(u);
    drawDeleteMenu1();
    scanf("%d", &choice);
    fclose(fopen(RECORDS, "r"));

    pf = fopen(RECORDS, "r");

    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0 && choice == r.id)
        {
            changed = true;
        }
        else
        {
            strcpy(r.name, userName);
            accounts[i] = r;
            i++;
        }
    }

    fclose(pf);

    if (changed)
    {

        fclose(fopen(RECORDS, "w"));

        pf = fopen(RECORDS, "a+");

        for (int j = 0; j < i; j++)
        {
            save1AccountToFile(pf, accounts[j].name, accounts[j]);
        }
        fclose(pf);
        drawDeleteMenu2();
        system("sleep 1.5");
        return;
    }
    else
    {
        drawDeleteMenu3();
        system("sleep 1.5");
        return;
    }
}

void makeTransaction(struct User u)
{
    char userName[100];
    struct Record accounts[128];
    struct Record r;
    int choice;
    int i = 0;
    double amount;
    int methodChoice;
    bool changed;

    FILE *pf = fopen(RECORDS, "r");

    getAllAccounts(u);
    drawTransMenu1();
    scanf("%d", &choice);
    fclose(fopen(RECORDS, "r"));

    pf = fopen(RECORDS, "r");

    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0 && choice == r.id)
        {
        middle:
            drawTransMenu3();
            scanf("%lf", &amount);
            if (amount <= 0)
            {
                drawTransMenu4();
                system("sleep 1.5");
                goto middle;
            }
            drawTransMenu2();
            scanf("%d", &methodChoice);
            if (methodChoice == 1)
            {
                if (amount > r.amount)
                {
                    drawTransMenu5();
                    system("sleep 1.5");
                    goto middle;
                }
                drawTransMenu6(amount);
                r.amount -= amount;
            }
            else if (methodChoice == 2)
            {
                drawTransMenu7(amount);
                r.amount += amount;
            }
            changed = true;
        }
        strcpy(r.name, userName);
        accounts[i] = r;
        i++;
    }

    fclose(pf);

    if (changed)
    {

        fclose(fopen(RECORDS, "w"));

        pf = fopen(RECORDS, "a+");

        for (int j = 0; j < i; j++)
        {
            save1AccountToFile(pf, accounts[j].name, accounts[j]);
        }
        fclose(pf);
        system("sleep 1.5");
        return;
    }
    else
    {
        drawTransMenu8();
        system("sleep 1.5");
        return;
    }
}