#include "animal.h"

#define PLNTNRG   80
#define REPNRG    200
int plantc  = 0;
int animalc = 0;

void draw_world(animal amls[], plant plts[])
{
  int x, y, a, p, has_animal, has_plant;

  for (y = 0; y < HEIGHT; y++) {
    printf("\n");
    printf("|");
    for (x = 0; x < WIDTH; x++) {
      for (a = 0; a < animalc; a++) {
        has_animal = 0;
        if (amls[a].alive && amls[a].x == x && amls[a].y == y) {
          printf("M");
          has_animal = 1;
        }
      }
      if (has_animal == 1)
        continue;
      else {
        has_plant = 0;
        for (p = 0; p < plantc; p++) {
          if (plts[p].x == x && plts[p].y == y) {
            printf("*");
            has_plant = 1;
          }
        }
      }
      if (has_plant == 1)
        continue;
      else
        printf(" ");
    }
    printf("|");
  }
  printf("\n%d\n", animalc);
  printf("%d\n", plantc);
  show_animal(amls[animalc]);
}

void add_plants(plant plants[])
{
    plant p1;
    plant p2;
    p1 = (plant) { .x = rand() % WIDTH, .y = rand() % HEIGHT };
    p2 = (plant) { .x = (rand() % 10) + 40, .y = (rand() % 10) + 10 };

    plants[plantc++] = p1;
    plants[plantc++] = p2;
}

void show_plants(plant plants[])
{
    int i;

    for (i = 0; i < plantc; i++)
        printf("x: %d\ny: %d\n", plants[i].x, plants[i].y);
}

void gen_genes(int g[])
{
    int i;

    for(i = 0; i < 8; i++) {
        g[i] = rand() % 10;
    }
}

void copy_genes(int *to, int *from)
{
  int i;
  for (i = 0; i < 8; i++)
    to[i] = from[i];
}

void mutate_gene(int genes[])
{
    genes[rand() % 8] += rand() % 3;
}

void show_animal(animal a)
{
    int i;

    printf("x: %d, y: %d\nenergy: %d\ndir: %d\nliving: %s\nGenes: ",
        a.x, a.y, a.energy, a.dir, (a.alive == 1) ? "true" : "false");

    for (i = 0; i < 8; i++) {
        printf("%d ", a.genes[i]);
    }
    printf("\n");
}

void move_animal(animal *a, int w, int h)
{
    a->x = (a->x + ((a->dir >= 2 && a->dir <  5) ? 1 :
                    (a->dir == 1 || a->dir == 5) ? 0 :
                                                  -1) + w) % w;

    a->y = (a->y + ((a->dir >= 0 && a->dir < 3) ? -1 :
                    (a->dir >= 4 || a->dir < 7) ?  1 :
                                                   0) + h) % h;
    a->energy -= 1;
}

void turn_animal(animal *a)
{
   a->dir += (a->genes[(a->x + a->y) % 8] > 5) ? 1 : -1;
   a->dir = abs(a->dir);
}

void eat_animal(animal *a, plant p[], int pe)
{
    int i;

    for (i = 0; i < sizeof(p); i++) {
	 		if (a->x == p[i].x && a->y == p[i].y)
				p[i] = (plant) { .x = -1, .y = -1 };
				a->energy += pe;
    }
}

bool reproduce_animal(animal *a, int rep_energy)
{
    if (a->energy > rep_energy) {
        a->energy = a->energy / 2;
        return true;
    }
    return false;
}

void still_alive_animal(animal *a)
{
    if (a->energy < 1) {
      a->alive = false;
      animalc--;
    }
}

animal copy_animal(animal a)
{
    animal b;

    b.x = a.x;
    b.y = a.y;
    b.energy = 500;
    b.dir = (a.dir + 1) % 8;
    copy_genes(b.genes, a.genes);
    // gen_genes(b.genes);
    b.alive = true;
    mutate_gene(b.genes);

    return b;
}

void add_animal(animal a, animal amls[])
{
    amls[animalc++] = a;
}

void init_animal(animal *a)
{
    a->x = WIDTH / 2;
    a->y = HEIGHT / 2;
    a->energy = 1000;
    a->dir = 0;
    a->alive = true;
    gen_genes(a->genes);
}

void simulate_day(animal amls[], plant plts[])
{
  int a, c;
  c = animalc;
  add_plants(plts);

  for (a = 0; a < c; a++) {
    if (amls[a].alive) {
      turn_animal(&amls[a]);
      move_animal(&amls[a], WIDTH, HEIGHT);
      eat_animal(&amls[a], plts, PLNTNRG);
      if(reproduce_animal(&amls[a], REPNRG))
        add_animal(copy_animal(amls[a]), amls);
      still_alive_animal(&amls[a]);
    }
  }
}
