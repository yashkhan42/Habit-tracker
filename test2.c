#include<stdio.h>
void skull(void)
{
        char line[256];
    FILE *file;


    file = fopen("CONGRATS.txt", "r");



    while (fgets(line, sizeof(line), file) != NULL) {
        fprintf(stdout, "%s", line);
    }


    fclose(file);
}
int main()
{
    skull();
}
