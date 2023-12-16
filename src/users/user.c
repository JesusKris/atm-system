#include "../header.h"

void addUser(FILE *ptr, struct User *registerData)
{
    fprintf(ptr, "\n");
    fprintf(ptr, "%d %s %s",
            registerData ->id,
            registerData ->name,
            registerData ->password);
}