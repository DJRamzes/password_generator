#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum {SIZE = 7};

void supplement(char **agrv){
    int check;
    int len = 0;
    int i = 0;
    len = strlen(*(agrv + 2));
    if(len > SIZE - 1){
        printf("Too long password\n");
        return;
    } else if(len == SIZE - 1){
        printf("Maximum password offered\n");
        return;
    } else{
        printf("%s", *(agrv + 2));
        do{
            check = rand() % 2;
            if(check){
                fputc(65 + rand() % (90 - 65 + 1), stdout);
            } else
                fputc(97 + rand() % (122 - 97 + 1), stdout);
        } while(i++ < SIZE - len - 2);
        printf("\n");
    }
}


void new_password(){
    int check;
    int i = 0;
    int str[SIZE];
    do{
        check = rand() % 2;
        if(check){
            if(i == SIZE - 1)
                str[i] = '\0';
            else
                str[i] = 65 + rand() % (90 - 65 + 1);
        } else{
            if(i == SIZE - 1)
                str[i] = '\0';
            else
                str[i] = 97 + rand() % (122 - 97 + 1);
        }
    } while(str[i++] != '\0');
    i = 0;
    while(str[i] != '\0'){
        fputc(str[i], stdout);
        ++i;
    }
    printf("\n");
}

void documentation(){
    printf("-sup require third parametr started password's string\n-new give you new 6-values password third paramet doesn't require\n");
}


int main(int agrc, char **agrv){

    if(agrc < 2){
        printf("Say -help\n");
        return 1;
    }

    if(agrc > 3){
        printf("Too much arguments");
        return 1;
    }
    
    if ((strcmp(*(agrv + 1), "-new") == 0) && (agrc > 2)){
        printf("-new doesn't need argument\n");
        return 1;
    }
    
    if ((strcmp(*(agrv + 1), "-sup") == 0) && (agrc < 3)){
        printf("-sup needs third argument\n");
        return 1;
    }
    
    if ((strcmp(*(agrv + 1), "-help") == 0) && (agrc > 2)){
        printf("-help doesn't need argument\n");
        return 1;
    }

    srand(time(NULL));

    FILE *fl1, *fl2;
    
    if((fl1 = fopen("arrSource", "r")) == NULL || (fl2 = fopen("arrSource2", "r")) == NULL){
        fprintf(stderr, "File didn't open\n");
        return 2; 
    }
    
    if (strcmp(*(agrv + 1), "-new") == 0)
        new_password();
    else if (strcmp(*(agrv + 1), "-sup") == 0)
        supplement(agrv);
    else if (strcmp(*(agrv + 1), "-help") == 0)
        documentation();
    else
        printf("Error\n");
    
    if(fclose(fl1) < 0 || fclose(fl2) < 0){
        fprintf(stderr, "Error\n");
        return 2;
    }
    
    return 0;	
}