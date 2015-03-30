#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define WIDTH     90
#define HEIGHT    40
#define REPNRG    200
#define PLNTNRG   80
#define MAXBUF    WIDTH * HEIGHT

#include "animal.h"
#include "functions.h"

int main()
{
    srand(time(NULL));
    int i, in_nbr;

    plant plants[MAXBUF];
    animal animals[MAXBUF];
    animal animal_a;
    animal animal_b;
    animal animal_c;

    add_plants(plants);

    init_animal(&animal_a);
    add_animal(&animal_a, animals);

    reproduce_animal(&animal_a, REPNRG);
    animal_b = copy_animal(animal_a);
    add_animal(&animal_b, animals);

    scanf("%d", &in_nbr);
    for (i = 0; i < in_nbr; i++)
      simulate_day(animals, plants);
    draw_world(animals, plants);

    return 0;
}
