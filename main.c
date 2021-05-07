#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "functions.h"

void menu(int *width, int *height, int *cellsize)
{
    printf("Please enter the width of window : ");
    scanf("%d",width);
    printf("Please enter the height of window : ");
    scanf("%d",height);
    printf("Please enter the size of maze cells : ");
    scanf("%d",cellsize);
}

int main(int argc, char* args[])
{
    int choice=0, width,height,cellsize;
    printf("----------------------- MENU -----------------------\n");
    printf("Please choose an option : \n");
    printf("\t1. Generate maze.\n");
    printf("\t2. Exit.\n");
    scanf("%d",&choice);
    if(choice == 1)
    {
        menu(&width,&height,&cellsize);
        createWindow(width,height,cellsize);
    }
    else if (choice == 2)    exit(0);
    return EXIT_SUCCESS;
}
