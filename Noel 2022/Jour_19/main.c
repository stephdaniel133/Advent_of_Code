#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BLUEPRINTS 10
#define MAX_RESOURCES 10
#define MAX_ROBOTS 10

// Structure to represent a blueprint
typedef struct {
  int ore_cost[MAX_ROBOTS];
  int clay_cost[MAX_ROBOTS];
  int obsidian_cost[MAX_ROBOTS];
  int geode_production[MAX_ROBOTS];
} Blueprint;

// Parse the input and create a list of blueprints
int parse_input(char* input, Blueprint* blueprints) {
  char* line = strtok(input, "\n");
  int num_blueprints = 0;

  while (line != NULL) {
    sscanf(line, "Each ore robot costs %d ore. Each clay robot costs %d ore. Each obsidian robot costs %d ore and %d clay. Each geode robot costs %d ore and %d obsidian.",
           &blueprints[num_blueprints].ore_cost[0],
           &blueprints[num_blueprints].ore_cost[1],
           &blueprints[num_blueprints].ore_cost[2],
           &blueprints[num_blueprints].clay_cost[2],
           &blueprints[num_blueprints].ore_cost[3],
           &blueprints[num_blueprints].obsidian_cost[3]);
    line = strtok(NULL, "\n");
    num_blueprints++;
  }

  return num_blueprints;
}

// Simulate the building of robots for a given blueprint
int simulate(Blueprint blueprint, int* ore, int* clay, int* obsidian, int* robots) {
  int minutes = 0;
  int geodes = 0;
  int i;

  while (minutes < 24) {
    // Calculate the number of geodes that can be produced in the next minute
    int max_geodes = 0;
    int chosen_robot = -1;

    for (i = 0; i < MAX_ROBOTS; i++) {
      if (ore[0] >= blueprint.ore_cost[i] && clay[1] >= blueprint.clay_cost[i] && obsidian[2] >= blueprint.obsidian_cost[i]) {
        int geodes_per_minute = robots[i] * blueprint.geode_production[i];
        if (geodes_per_minute > max_geodes) {
          max_geodes = geodes_per_minute;
          chosen_robot = i;
        }
      }
    }

    // Build the chosen robot, if any
    if (chosen_robot != -1) {
      ore[0] -= blueprint.ore_cost[chosen_robot];
      clay[1] -= blueprint.clay_cost[chosen_robot];
      obsidian[2] -= blueprint.obsidian_cost[chosen_robot];
      robots[chosen_robot]++;
    }
  }
}
