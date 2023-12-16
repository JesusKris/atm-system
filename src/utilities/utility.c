#include "../header.h"
#include <stdlib.h>

void getUserId(struct User *u)
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
        if (strcmp(userChecker.name, u->name) == 0)
        {
            u->id = userChecker.id;
            fclose(fp);
        }
    }

    fclose(fp);
}

char *checkUser(char name[50])
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
        if (strcmp(userChecker.name, name) == 0)
        {

            fclose(fp);
            char *answer = "true";
            return answer;
        }
    }

    fclose(fp);
    char *answer = "false";
    return answer;
}

int getNextId()
{
    struct User lastUser;
    FILE *fp;

    if ((fp = fopen("./data/users.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    while (fscanf(fp, "%d %s %s", &(lastUser.id), lastUser.name, lastUser.password) != EOF)
        ;

    fclose(fp);
    if (lastUser.id == 0)
    {
        return lastUser.id + 1;
    }
    else if (lastUser.id > 0 && lastUser.id < 100)
    {
        return lastUser.id + 1;
    }
    else
    {
        return 0;
    }
}

void markingID(struct Record *r, char name[50])
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
        if (strcmp(userChecker.name, name) == 0)
        {
            r->userId = userChecker.id;
        }
    }

    fclose(fp);
}

int getNextRecordsId()
{
    struct Record r;
    FILE *fp;

    if ((fp = fopen("./data/records.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    while (fscanf(fp, "%d %d %s %d %d/%d/%d %s %d %lf %s", &r.id, &r.userId, r.name, &r.accountNbr, &r.deposit.month, &r.deposit.day, &r.deposit.year, r.country, &r.phone, &r.amount, r.accountType) != EOF)
        ;

    fclose(fp);
    return r.id;
}

void getAllAccounts(struct User u)
{
    char userName[100];
    struct Record r;
    const char *RECORDS = "./data/records.txt";
    FILE *pf = fopen(RECORDS, "r");

    system("clear");
    printf("\t\t==================================== All accounts from user, %s =====================================\n\n", u.name);
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
}

char *checkAccountOwner(int id, char name[50])
{
    char userName[100];
    struct Record r;
    const char *RECORDS = "./data/records.txt";
    FILE *pf = fopen(RECORDS, "r");

    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, name) == 0 && r.id == id)
        {
            char *answer = "true";
            return answer;
        }
    }
    fclose(pf);
    char *answer = "false";
    return answer;
}

double calculateInterest(char type[50], double amount)
{
    int interest;
    if (strcmp(type, "saving") == 0)
    {
        interest = (amount * 0.07) / 12;
        return interest;
    }
    if (strcmp(type, "current") == 0)
    {
        interest = 0;
        return interest;
    }
    if (strcmp(type, "fixed01") == 0)
    {
        interest = (amount * 0.04);
        return interest;
    }
    if (strcmp(type, "fixed02") == 0)
    {
        interest = (amount * 0.05 * 2);
        return interest;
    }
    if (strcmp(type, "fixed03") == 0)
    {
        interest = (amount * 0.08 * 3);
        return interest;
    }
}