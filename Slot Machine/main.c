#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define ESC 27
#define MAX 255

int check() {
    int i, temp, number;
    char check[MAX];
    do {
        temp = 0;
        fpurge(stdin);
        gets(check);
        if (strlen(check) < 1 || strlen(check) > 10)
            temp = 1;
        else {
            for (i = 0; i < strlen(check); i++) {
                if (check[i] > '9' || check[i] < '0')
                    temp = 1;
            }
        }
    } while (temp == 1);
    number = atoi(check);
    return number;
}

double playSlotMachine(double money){
    int number, i;
    int a[3];
    if(money <= 0){
        return 0;
    }
    money -= 0.25;
    srand(time(NULL));
    a[0] = rand() % 10;
    a[1] = rand() % 10;
    a[2] = rand() % 10;
//    number = rand() % 900 + 100;
    printf("\nSlot has roll: ");
    for(i = 0; i < 3; i++){
        printf("| %d | ",a[i]);
    }
//    printf("%d",number);
//    i = 2;
//    do {
//        a[i] = number % 10;
//        i--;
//        number /= 10;
//    }while(number > 0);
    if(a[0] == a[1] && a[1] == a[2]){
        money += 10;
        printf("\nWin! 10$ 3 match");
        printf("\nNow you have: %.2lf",money);
        return money;
    }else if(a[0] == a[1] || a[0] == a[2] || a[1] == a[2]){
        money += 0.5;
        printf("\nWin! 0.5$ 2 match");
        printf("\nNow you have: %.2lf",money);
        return money;
    }
    printf("\nNow you have: %.2lf",money);
    return money;
}

double openFILE(){
   double num;
   FILE *fptr;
   
   fptr = fopen("playSlotMachine.txt","r");
   if(fptr == NULL){
       fptr = fopen("playSlotMachine.txt","w");
       num = 10;
       fprintf(fptr,"%lf",num);
       fclose(fptr);
       return num;
   }

   fscanf(fptr,"%lf",&num);
   fclose(fptr); 
  
   return num;
}

double writeFILE(double num){
   FILE *fptr;
   fptr = fopen("playSlotMachine.txt","w");
   if(fptr == NULL)
   {
      printf("Error!");   
      exit(1);             
   }
   fprintf(fptr,"%lf",num);
   fclose(fptr);
   return num;
}

int main(){
    int choice;
    double money = openFILE();
    printf("\nYou having %.2lf", money);
    do{
        printf("\n1. Play the slot machine");
        printf("\n2. Save game");
        printf("\n3. Cash out");
        printf("\nEnter your choice: ");
        fpurge(stdin);
        choice = check();
        switch(choice){
            case 1:
                money = playSlotMachine(money);
                if(money == 0){
                    printf("\nYou don't have enough money to play. Bye! :) ");
                    return EXIT_SUCCESS;
                }
                break;
            case 2:
                writeFILE(money);
                return EXIT_SUCCESS;
                break;
            case 3:
                printf("Thank for playing you end with %.2lf", money);
                money = 10;
                writeFILE(money);
                return EXIT_SUCCESS;
                break;
        }
    }while(choice != 3);
}