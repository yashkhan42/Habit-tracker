#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <windows.h>
#include <time.h>


void genUser(void);
void editInfo(int);
void storeInfo(void);
void firstPage(void);
void addhabit(int);
void searchHabit(char*, int);
void editName(int, int);
void second_page(int);
void showHabits(int);
void habitLog(int);
void progressBar(int, int);
void ranQ(void);
void ranWQ(void);
void Welcome(void);
void skull(void);
void back(void);
void congrats(void);

int totalusers = 3;

typedef struct habit{
    char habitName[250];
    int totalDays;
    int daysCompleted;
    int streaks;
} hbbb;


void deleteHabit(int, int, int, struct habit *);
void completeHabit(int, int, int, struct habit *);

struct userData{
    char userName[250];
    char userPass[250];
    int habitNumber;
    struct habit habits[10];
};


struct userData ud[20];


int main(void){
    genUser();
    firstPage();
    storeInfo();
    return 0;
}


void storeInfo(void){
    FILE* fptr;
    FILE *data;

    fptr = fopen("test.txt", "w");
    data = fopen("data.txt", "w");

    fprintf(data, "%d\n", totalusers);

    for(int i = 0; i < totalusers; i++){
        fputs(ud[i].userName, fptr);
        fputs(ud[i].userPass, fptr);
        fprintf(data, "%d\n", ud[i].habitNumber);
        for(int j = 0; j < ud[i].habitNumber; j++){
            fputs(ud[i].habits[j].habitName, fptr);
            fprintf(data, "%d\n", ud[i].habits[j].totalDays);
            fprintf(data, "%d\n", ud[i].habits[j].daysCompleted);
            fprintf(data, "%d\n", ud[i].habits[j].streaks);
        }
    }
    fclose(fptr);
    fclose(data);
}


void editInfo(int un){

    printf("\n\n\n");
    printf("\n\n\n\n\t\t\t\t\t\t1. Change Username");
    printf("\n\n\t\t\t\t\t\t2. Change Password");
    printf("\n\n\t\t\t\t\t\t> ");
    int ans; scanf("%d", &ans);
    fflush(stdin);
    if(ans == 1){
        printf("\n\n\t\t\t\t\t\tEnter New Username: ");
        fgets(ud[un].userName, 250, stdin);
        printf("\t\t\t\t\t\tUsername Updated!");
        printf("\n\n\n\t\t\tPress any key to return to menu");
        getch();
        system("cls");
    } else {
        printf("\n\n\t\t\t\t\t\tEnter New Password: ");
        fgets(ud[un].userPass, 250, stdin);
        printf("\t\t\t\t\t\tPassword Updated!");
        printf("\n\n\n\t\t\tPress any key to return to menu");
        getch();
        system("cls");
    }
    fflush(stdin);
}


void genUser(void){
    FILE *fptr;
    FILE *data;
    fptr = fopen("test.txt", "r");
    data = fopen("data.txt", "r");
    int i = 0;
    fscanf(data, "%d", &totalusers);

    while(i<totalusers){
        fgets(ud[i].userName, 250, fptr);
        fgets(ud[i].userPass, 250, fptr);
        fflush(stdin);
        fscanf(data, "%d", &ud[i].habitNumber);
        for(int j = 0; j < ud[i].habitNumber; j++){
            fgets(ud[i].habits[j].habitName, 250, fptr);
            fflush(stdin);
            fscanf(data, "%d", &ud[i].habits[j].totalDays);
            fscanf(data, "%d", &ud[i].habits[j].daysCompleted);
            fscanf(data, "%d", &ud[i].habits[j].streaks);
            fflush(stdin);
        }
        i++;
    }
    fclose(fptr);
    fclose(data);
}


void firstPage(void){


    Welcome();
    ranWQ();
    printf("\n\t\t\t\t\t\t\t ~ WELCOME TO HABIT TRACKER ~\n");
    printf("\n\n\n");
    printf("\t\t\t\t\t1: New User\n\n");
    printf("\t\t\t\t\t2: Returning User\n\n");
    printf("\t\t\t\t\t3: Close Tracker\n");
    printf("\n\n\t\t\t\t\t> ");
    int choice;
    scanf("%d", &choice);
    system("cls");
    fflush(stdin);
    if(choice == 1){

        printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tREGISTRATION\n\n\n\n");
        printf("\t\t\t\t\t\tUSERNAME: ");
        fgets(ud[totalusers].userName, 250, stdin);
        printf("\n\n\t\t\t\t\t\tPASSWORD: ");
        fgets(ud[totalusers].userPass, 250, stdin);
        for(int i =0; i< totalusers; i++){
                if(strcmp(ud[totalusers].userName, ud[i].userName) == 0 || strcmp(ud[totalusers].userName, "\n")== 0){
            printf("\n\n\n\t\t\t\t\tThis username is already taken!! :( Try a different username~");
            printf("\n\n\n\n\n\t\t\t\t\tPress any key to return to menu");
            getch();
            fflush(stdin);
            system("cls");
            firstPage();
            }
        }
        system("cls");
        fflush(stdin);
        printf("\n\t\t\t\t\t\t\t\t~~WELCOME~~\n\n\n");
        ud[totalusers].habitNumber = 0;
        int nidx = totalusers;
        totalusers++;
        storeInfo();
        second_page(nidx);

    } else if(choice  == 2){

        printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tLOGIN\n\n\n");
        printf("\n\n");
        printf("\t\t\t\t\t\tEnter your Username and Password\n\n\n");
        char un[250];
        char pass[250];
        int match = 0;

        printf("\t\t\t\t\t\tUSERNAME: ");
        fgets(un, 250, stdin);
        printf("\n\n\t\t\t\t\t\tPASSWORD: ");
        fgets(pass, 250, stdin);
        system("cls");
        int idx = -1;
        for(int i = 0; i < totalusers; i++){
            if(strcmp(ud[i].userName, un) == 0){
                if(strcmp(ud[i].userPass, pass) == 0) {
                    match = 1;
                    idx = i;
                    break;
                }
            }
        }

        while(match == 0){
            fflush(stdin);

            printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\tYour username or Password is incorrect. Please try again!\n\n\n\n");
            printf("\t\t\t\t\tUSERNAME: ");
            fgets(un, 250, stdin);
            printf("\n\n\t\t\t\t\tPASSWORD: ");
            fgets(pass, 250, stdin);
            system("cls");
            for(int i = 0; i < totalusers; i++){
                if(strcmp(ud[i].userName, un) == 0){
                    if(strcmp(ud[i].userPass, pass) == 0) {
                        match = 1;
                        idx = i;
                        break;
                    }
                }
            }
        }


        printf("\n\n\n\n\n\n\t\t\t\t\t\t\t  Welcome Back %s\n", un);
        second_page(idx);
    } else if (choice == 3) {
        printf("\n\n\n\n\n\n\n\n");
        printf("\n\n\n\t\t\t\t\t\t\tSee You Again~~\n\n\n\n");
        fflush(stdin);
            return;

    } else{

        printf("\n\n\n\n\n\n\n\n");
        printf("\n\n\t\t\t\t\t\t\t\tUndefined Choice\n\n");
        printf("\n\n\n\n\n\t\t\t\tPress any key to return to menu");
        getch();
        fflush(stdin);
        system("cls");
        firstPage();
    }
}


void addhabit(int idx){

    printf("\n\n\n\n\n\n\n\n");
    printf("\n\n\n\n\t\t\tEnter the name of the Habit you want to build: ");
    fgets(ud[idx].habits[ud[idx].habitNumber].habitName, 250, stdin);
    fflush(stdin);
    int habitno = ud[idx].habitNumber;
    ud[idx].habitNumber++;
    printf("\n\n\t\t\tEnter the number of days you want to continue the habit for: ");
    scanf("%d", &ud[idx].habits[habitno].totalDays);
    ud[idx].habits[habitno].daysCompleted = 0;
    ud[idx].habits[habitno].streaks = 0;
    fflush(stdin);

    printf("\n\n\t\t\tDo you want to add another habit? (y/n): ");
    char ans;
    scanf(" %c", &ans);
    fflush(stdin);
    system("cls");
    if(ans == 'y'){
        addhabit(idx);

    }

}

void searchHabit(char* habit, int idx){

    printf("\n\n\t\t\t\t\tYour Search Results:\n\n");
    int j = 0;
    int hi[10];
    for(int i = 0; i < ud[idx].habitNumber; i++){
        char hn2[250];
        strcpy(hn2, ud[idx].habits[i].habitName);
        if(habit[0] == hn2[0] && habit[1] == hn2[1]){
            printf("\t\t\t\t\t%d: %s", j+1, hn2);
            hi[j] = i;
            j++;
        }
    }

        if(j == 0){
            printf("\t\t\t\t\tNo Habits Found!\n");
            fflush(stdin);
            printf("\n\n\n\n\n\t\t\t\tPress any key to return to menu");
            getchar();
            system("cls");
            return;
        }
        printf("\n\t\t\t\t\t> ");
        int input;
        scanf("%d", &input);
        fflush(stdin);
        input--;

        system("cls");
        printf("\n\n\n\n\n\n");
        printf("\n\n\t\t\t\t\t: Edit Habit name.\n\n\t\t\t\t\t2: See Your Progress.\n\n\t\t\t\t\t3: Delete this Habit.\n\n\t\
               \t\t\t> ");
        int a;
        scanf("%d", &a);
        if(a == 1)
            editName(idx, hi[input]);
        else if(a==2){
            printf("\n\n\n\n\t\t\t\t\tHabit %d Name: %s\n", hi[input]+1, ud[idx].habits[hi[input]].habitName);
            printf("\t\t\t\t\tTarget Days: %d\n", ud[idx].habits[hi[input]].totalDays);
            printf("\t\t\t\t\tDays Completed: %d\n", ud[idx].habits[hi[input]].daysCompleted);
            printf("\t\t\t\t\tStreaks: %d\n", ud[idx].habits[hi[input]].streaks);
            progressBar(ud[idx].habits[hi[input]].totalDays, ud[idx].habits[hi[input]].daysCompleted);
            printf("\n\n");
            printf("\n\n\n\t\t\t\tPress any key to return to menu");
            getch();
            system("cls");
        } else if(a == 3){
            deleteHabit(idx, hi[input], 10, ud[idx].habits);
        }
        else printf("\t\t\tInvalid Choice\n");

}


void editName(int i, int j){
    fflush(stdin);
    printf("\n\n\t\t\t\t\tEnter New Name: ");
    fgets(ud[i].habits[j].habitName, 250, stdin);
    printf("\n\t\t\t\t\tHabit Name Updated!\n\n");
    printf("\n\n\n\n\n\t\t\t\tPress any key to return to menu");
    getch();
    system("cls");
}


void second_page(int un){
    fflush(stdin);
    back();
    printf("\n\n");
    int option;
    printf("\t\t\t\t\t\tChoose from the following options\n\n\n\t\t\t\t1. Add Habit \n\n\t\t\
        \t2. See All Habit Info\n\n\t\t\t\t3. Log Your Daily Habits\n\n\t\t\
        \t4. Search Habit\n\n\t\t\t\t5. Edit Log-in Information\n\n\t\t\t\t6. Log Out\n\n\t\t\t\t> ");
    scanf("%d", &option);
    system("cls");
    fflush(stdin);
    switch(option)
    {
        case 1:
            addhabit(un);
            fflush(stdin);
            printf("\n\n\n\n\n\n\n\n");
            printf("\n\n\n\n\n\t\t\t\tPress any key to return to menu");
            getchar();
            system("cls");
            second_page(un);
            fflush(stdin);
            return;
        case 2:
            showHabits(un);
            second_page(un);
            fflush(stdin);
            return;
        case 3:
            habitLog(un);
            second_page(un);
            fflush(stdin);
            return;
        case 4:
            printf("\n\n\n\n\n\n\n\n");
            printf("\t\t\t\t\tEnter The habit Name: ");
            char hn[250];
            fgets(hn, 250, stdin);
            searchHabit(hn, un);
            second_page(un);
            fflush(stdin);
        case 5:
            editInfo(un);
            second_page(un);
            fflush(stdin);
            return;
        case 6:
            system("cls");
            firstPage();
            fflush(stdin);
            return;
        default:
            printf("\x1b[31m");
            printf("\n\n\n\n\n\n\n\n");
            printf("\t\t\t\t\t\tERROR!!!\n");
            printf("\x1b[0m");
            printf("\n\n\n\n\n\t\t\t\tPress any key to return to menu");
            getch();
            system("cls");
            second_page(un);
            fflush(stdin);
            return;
        }

}


void showHabits(int un){


    printf("\n\n\n\n");
    printf("\t\t\t\t\tActive Habits you have right now: %d\n\n\n", ud[un].habitNumber);

    for(int i = 0; i < ud[un].habitNumber; i++){
        printf("\n\t\t\t\t\tHabit %d Name: %s", i+1, ud[un].habits[i].habitName);
        printf("\t\t\t\t\tTarget Days: %d\n", ud[un].habits[i].totalDays);
        printf("\t\t\t\t\tDays Completed: %d\n", ud[un].habits[i].daysCompleted);
        progressBar(ud[un].habits[i].totalDays, ud[un].habits[i].daysCompleted);
        printf("\n");
        printf("\t\t\t\t\tStreaks: %d\n", ud[un].habits[i].streaks);
        printf("\n");

    }
    printf("\n\n\n\n\n\t\t\t\tPress any key to return to menu");
    getch();
    system("cls");
}


void progressBar(int TD, int DC){
    float r = DC/(float)TD;
    printf("\t\t\t\t\tProgress\n\t\t\t\t\t");
    char a = 178, b = 219;
    for (int i = 0; i < 26; i++){
        printf("%c", a);
        }
    printf("\t\t\t\t\t\r\t\t\t\t\t");
    for (int i = 0; i < r*26; i++) {
        printf("%c", b);
        }
}


void habitLog(int un){

    printf("\n\n\n\n\n\n\n\t");
    for(int i = 0; i < ud[un].habitNumber; i++){
        printf("\n\t\t\t\t\t%d. %s", i+1, ud[un].habits[i].habitName);

    }
    printf("\n\t\t\t\t\t> ");
    int input;
    scanf("%d", &input);
    fflush(stdin);
    input--;
    printf("\n\n\t\t\t\t\t%s\n", ud[un].habits[input].habitName);
    printf("\t\t\t\t\tDid you complete it?(y/n): ");
    char ans;
    scanf(" %c", &ans);
    system("cls");
    if(ans == 'y'){
        ud[un].habits[input].daysCompleted++;
        ud[un].habits[input].streaks++;
        if(ud[un].habits[input].daysCompleted == ud[un].habits[input].totalDays){
            completeHabit(un, input, 10, ud[un].habits);
            return;
        } else {
            ranQ();
            congrats();
            printf("\n\n\t\t\t\t\tStreaks Count: %d", ud[un].habits[input].streaks);
            printf("\n\n\t\t\t\t\tonly %d more days left!", (ud[un].habits[input].totalDays - ud[un].habits[input].daysCompleted));
        }
    } else {
        ud[un].habits[input].streaks = 0;
        printf("\n\n\n\t\t\t\t\t:( You lost your streaks\a\n");
        skull();
    }
    fflush(stdin);
    printf("\n\n\n\n\n\t\t\t\tPress any key to return to menu");
    getch();
    system("cls");

}


void deleteHabit(int idx, int pos, int size, struct habit * hb){
    printf("\t\tAre you sure you want to delete this habit? (y/n): ");
    char ans;
    scanf(" %c", &ans);
    if(ans == 'y'){
        for(int i = pos; i < size-1; i++){
            *(hb + i) = *(hb + i+1);
        }
        ud[idx].habitNumber--;
        printf("\n\t\tHabit deleted successfully.");
        fflush(stdin);
        skull();
        printf("\n\n\n\n\n\t\t\t\tPress any key to return to menu");
        getch();
        system("cls");
    }else{
        printf("\n\n\n\n\n\t\t\t\tPress any key to return to menu");
        getch();
        system("cls");
    }
}

void completeHabit(int idx, int pos, int size, struct habit * hb){

    system("cls");
    printf("\n\n\n\t\t\t\tCongratulations!\n\t\t\t\tYou Have Completed This Habit!\n\t\t\t\tYou are one step closer to the person you are meant to be!");

    for(int i = pos; i < size-1; i++){
            *(hb + i) = *(hb + i+1);
        }
        ud[idx].habitNumber--;
        fflush(stdin);
        printf("\n\n\n\n\n\t\t\t\tPress any key to return to menu");
        getch();
        system("cls");
}

void ranQ(void){

    char enQ[20][1000];

    FILE* fptr;
    fptr = fopen("Quotes.txt", "r");


    for(int i = 0; i < 20; i++){
        fgets(enQ[i], 1000, fptr);
    }
    fclose(fptr);


    time_t t;
    srand((unsigned) time(&t));
    int idx = rand() % 20;
    printf("\x1b[33m");
    printf("\n\n\t\t\t%s\n", enQ[idx]);
    printf("\x1b[0m");


}
void Welcome(void)
{
     char line[256];
    FILE *file;


    file = fopen("welcome.txt", "r");



    while (fgets(line, sizeof(line), file) != NULL) {
        fprintf(stdout, "%s", line);
    }


    fclose(file);

}
void ranWQ(void)
{
    char enQ[20][1000];

    FILE* fptr;
    fptr = fopen("Welcome_Quotes.txt", "r");


    for(int i = 0; i < 20; i++){
        fgets(enQ[i], 1000, fptr);
    }

    fclose(fptr);


    time_t t;
    srand((unsigned) time(&t));
    int idx = rand() % 15;
    printf("\x1b[33m");
    printf("\n\n\t\t\t\t\t%s\n\n", enQ[idx]);
    printf("\x1b[0m");
}
void skull(void)
{
    char line[256];
    FILE *file;


    file = fopen("Skull.txt", "r");


    printf("\x1b[31m");
    while (fgets(line, sizeof(line), file) != NULL) {
        fprintf(stdout, "%s", line);
}
    printf("\x1b[0m");
}
void back(void)
{
    char line[256];
    FILE *file;


    file = fopen("Back.txt", "r");
        printf("");
    while (fgets(line, sizeof(line), file) != NULL) {
        fprintf(stdout, "%s", line);
}
printf("\n");

}

void congrats(void)
{
    char line[256];
    FILE *file;


    file = fopen("CONGRATS.txt", "r");


    printf("\x1b[32m");
    while (fgets(line, sizeof(line), file) != NULL) {
        fprintf(stdout, "%s", line);
}
    printf("\x1b[0m");
}



