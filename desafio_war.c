
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_TERRITORIES 10
#define MAX_MISSIONS 3

typedef struct {
    char name[MAX_NAME];
    char color[MAX_NAME];
    int troops;
} Territory;

typedef struct {
    char description[100];
    int completed;
} Mission;

// Function to create a territory
Territory* createTerritory(const char* name, const char* color, int troops) {
    Territory* t = (Territory*)malloc(sizeof(Territory));
    strncpy(t->name, name, MAX_NAME);
    strncpy(t->color, color, MAX_NAME);
    t->troops = troops;
    return t;
}

// Function to simulate an attack
void attack(Territory* attacker, Territory* defender) {
    if (attacker->troops > 1) {
        int attackTroops = attacker->troops / 2;
        int defenseTroops = defender->troops;

        printf("Attack from %s to %s\n", attacker->name, defender->name);
        printf("Attacker troops: %d, Defender troops: %d\n", attackTroops, defenseTroops);

        if (attackTroops > defenseTroops) {
            printf("%s conquered %s!\n", attacker->name, defender->name);
            defender->troops = attackTroops - defenseTroops;
            attacker->troops -= attackTroops;
        } else {
            printf("Attack failed.\n");
            attacker->troops -= attackTroops;
        }
    } else {
        printf("Not enough troops to attack.\n");
    }
}

// Function to check mission completion
void checkMissions(Mission* missions, int numMissions, Territory* territories, int numTerritories) {
    for (int i = 0; i < numMissions; i++) {
        if (strstr(missions[i].description, "Ásia") || strstr(missions[i].description, "América do Sul")) {
            for (int j = 0; j < numTerritories; j++) {
                if ((strstr(territories[j].name, "Ásia") || strstr(territories[j].name, "América do Sul")) && territories[j].troops > 0) {
                    missions[i].completed = 1;
                    printf("Missão '%s' completada!\n", missions[i].description);
                    break;
                }
            }
        }
    }
}

int main() {
    Territory* territories[MAX_TERRITORIES];
    territories[0] = createTerritory("Território Ásia", "Vermelho", 10);
    territories[1] = createTerritory("Território América do Sul", "Azul", 8);

    Mission missions[MAX_MISSIONS] = {
        {"Conquistar Ásia", 0},
        {"Conquistar América do Sul", 0},
        {"Dominar 2 territórios", 0}
    };

    attack(territories[0], territories[1]);
    checkMissions(missions, MAX_MISSIONS, *territories, 2);

    for (int i = 0; i < 2; i++) {
        free(territories[i]);
    }

    return 0;
}
