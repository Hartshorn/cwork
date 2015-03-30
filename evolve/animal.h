#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define WIDTH   90
#define HEIGHT  40
#define MAXBUF  WIDTH * HEIGHT

typedef struct {
    bool alive;
    int x, y, energy, dir;
    int genes[8];
} animal;

typedef struct {
    int x;
    int y;
} plant;

void gen_genes(int g[]);
void add_animal(animal *a, animal amls[]);
void copy_genes(int *to, int *from);
void mutate_gene(int genes[]);
void show_animal(animal a);
void move_animal(animal *a, int w, int h);
void turn_animal(animal *a);
void eat_animal(animal *a, plant p[], int pe);
bool reproduce_animal(animal *a, int rep_energy);
void still_alive_animal(animal *a);
animal copy_animal(animal a);
void init_animal(animal *a);

void add_plants(plant p[]);
void show_plants(plant p[]);

void simulate_day(animal a[], plant p[]);
void remove_dead(animal a[]);
void str_cpy(char *to, char *from);
void draw_world(animal amls[], plant plts[]);
