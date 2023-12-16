#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Date
{
    int month, day, year;
};

// all fields for each record of an account
struct Record
{
    int id;
    int userId;
    char name[100];
    char country[100];
    int phone;
    char accountType[10];
    int accountNbr;
    double amount;
    struct Date deposit;
    struct Date withdraw;
};

struct User
{
    int id;
    char name[50];
    char password[50];
};

//accounts functions
void createNewAcc(struct User u);
void checkAllAccounts(struct User u);
void updateAccount(struct User u);
int getAccountFromFile(FILE *ptr, char name[50], struct Record *r);
void checkOneAccount(struct User u);
void transferAccount(struct User u);
void deleteAccount(struct User u);
void makeTransaction(struct User u);

// authentication functions
void loginMenu(char a[50], char pass[50]);
const char* registerMenu();
const char *getPassword(struct User u);

// main functions
void mainMenu(struct User u);

// users functions
void addUser(FILE *ptr, struct User *registerData);

//utility functions
void getUserId(struct User *u);
int getNextId();
int getNextRecordsId();
void getAllAccounts(struct User u);
char *checkAccountOwner(int id, char name[50]);
double calculateInterest(char type[50], double amount);
void markingID(struct Record *r,char name[50]);
char *checkUser(char name[50]);


//drawing functions
void drawMainMenu1();
void drawMainMenu2();
void drawInitMenu();
void drawCreateAcc1();
void drawCreateAcc2();
void drawCreateAcc3();
void drawCreateAcc4();
void drawCreateAcc5();
void drawCreateAcc6();
void drawCreateAcc7();
void drawSucces1();
void drawSucces2();
void drawLoginMenu1();
void drawLoginMenu2();
void drawLoginMenu3();
void drawLoginMenu4();
void drawRegisterMenu1();
void drawRegisterMenu2();
void drawRegisterMenu3();
void drawRegisterMenu4();
void drawUpdateMenu1();
void drawUpdateMenu2();
void drawUpdateMenu3(int id);
void drawUpdateMenu4(int id);
void drawUpdateMenu5();
void drawUpdateMenu6();
void drawUpdateMenu7();
void drawUpdateMenu8();
void drawOneAccountMenu1();
void drawOneAccountMenu2(struct User u, int id);
void drawTransferMenu1();
void drawTransferMenu2();
void drawTransferMenu3();
void drawDeleteMenu2();
void drawDeleteMenu3();
void drawDeleteMenu1();
void drawTransMenu1();
void drawTransMenu2();
void drawTransMenu3();
void drawTransMenu4();
void drawTransMenu5();
void drawTransMenu6(double amount);
void drawTransMenu7(double amount);
void drawTransMenu8();