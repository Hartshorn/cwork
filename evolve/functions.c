

void simulate_day(animal amls[], plant plts[])
{
  add_plants();


}

void draw_world(animal amls[], plant plts[])
{
  int x, y, a, p;

  for (y = 0; y < HEIGHT; y++) {
    printf("\n");
    printf("|");
    for (x = 0; x < WIDTH; x++) {
      for (a = p = 0; p < plantc && a < animalc; p++, a++) {
        if (amls[a].alive && amls[a].x == x && amls[a].y == y)
          printf("M");
        else if (plts[p].)x == x && plts[p].y == y)
          printf("*");
        else
          printf(" ");
      }
    }
    printf("|");
  }
  printf("\n");
}
