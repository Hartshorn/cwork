#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXPLT  10

typedef struct {
    int x;
    int y;
} plant;



int plantc = 0;

void str_cpy(char *to, char *from);
void plant_two(plant plants[]);
void show();
void init_plant(plant *p);

int main()
{
    srand(time(NULL));
    
    plant plants[MAXPLT];

    plant_two(plants);
    show(plants);
    
    return 0;
}

// might be useful somewhere - copy one array over to another 
// void array_cpy(type *to, type *from) { while(*to++ = *from++); }

void plant_two(plant plants[])
{
    plant p1;
    plant p2;
    p1 = (plant) { .x = rand() % 10, .y = rand() % 10 };
    p2 = (plant) { .x = rand() % 10, .y = rand() % 10 };
    
    plants[plantc++] = p1;
    plants[plantc++] = p2;
}

void show(plant plants[])
{
    int i;
    
    for (i = 0; i < plantc; i++)
        printf("x: %d\ny: %d\n", plants[i].x, plants[i].y);
}

void init_plant(plant *p)
{
    p->x = 1;
    p->y = 1;
}