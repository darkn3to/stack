#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#define gdec decoy=getc(stdin);

void lo_reg(char);                  
bool valid_user(char *, char *, FILE *);         //checks whether the entered password exists and corresponds to the entered username.

typedef struct data {                    //stores data of users in structure "det" when they register.
    char f_name[20];
    long int mob_no;
    char email[20];
}x;
x det[100];                   

void main() {
    char choice;
    printf("Welcome to JetLink Airlines!\n");
    printf("Enter A for login/Enter B for Regsitration\n");
    scanf("%c", &choice);
    lo_reg(choice);                       // login/register function called.
}


void lo_reg(char choice) {
    FILE *l, *r;
    int eval, i=0, rem_attempts=3;      //rem_attempts tracks the number of attempts left to successfully login when a user fails one.
    char user[30], pass[30], decoy;
    gdec
    eval=(choice == 'a' || choice == 'A');
    if (eval) {
        l=fopen("dbase.txt", "r");
        retry:
        while (rem_attempts>=1) {
            printf("Enter your username: ");
            scanf("%s", user);
            printf("Enter password: ");
            scanf("%s", pass);
            if (valid_user(user, pass, l)) {
                /*.
                .
                .*/printf("Login successful");
                break;
            }
            else {
                printf("Invalid credentials.\n"); --rem_attempts; goto retry;
            }
        }
        if (rem_attempts==0)
        printf("Too many failed login attempts. Try again later."); 
        goto br;
    }
    else {
        r=fopen("dbase.txt", "a");
        printf("Enter your full name: ");                              //user data stored in structs.
        scanf_s("%[^\n]s", (det+i)->f_name, sizeof((det+i)->f_name));
        gdec
        /*fprintf(r, "Name: %s |", (det+i)->f_name);*/
        printf("Enter your mobile number: ");
        scanf_s("%ld", &(det+i)->mob_no, sizeof((det+i)->mob_no));
        gdec
        /*fprintf(r, " Mob: %ld |", (det+i)->mob_no);*/
        printf("Enter your email id: ");
        scanf_s("%s", (det+i)->email, sizeof((det+i)->email));
        /*fprintf(r, " Email: %s |", (det+i)->email);*/
        printf("Enter your username: ");
        scanf_s("%s", user, sizeof(user));
        fprintf(r, "%s|", user);                             //username and password stored in dbase.txt
        printf("Enter your password: ");
        scanf_s("%s", pass, sizeof(pass));
        fprintf(r, "%s|", pass);
        i++;
        printf("User registered successfully.");
    }
    br:
    fclose(r);
}

bool valid_user(char *user, char *pass, FILE *fptr) {
    char line[100];
    char *token;

    while (fgets(line, sizeof(line), fptr)) {
        token = strtok(line, "|");
        if (strcmp(token, user) == 0) {
            token = strtok(NULL, "|");
            printf("%s\n", token);
            if (strcmp(token, pass) == 0) {
                rewind(fptr);         
                return true;
            }
        }
    }

    rewind(fptr); // Reset the file pointer to the beginning
    return false;
}






