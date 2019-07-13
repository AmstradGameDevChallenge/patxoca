/**
 * SUPER ULTRA RPG GAME
 * by patxoca
 * July 2019
 **/

#include <cpctelera.h>
#include <stdio.h>

/**************************************************************************/
/* MACROS                                                                 */
/**************************************************************************/

#define CMD_NONE 0
#define CMD_ATTACK 1
#define CMD_DEFEND 2


/**************************************************************************/
/* TYPES                                                                  */
/**************************************************************************/

typedef u8 command_t;

typedef struct {
   u8 energy;
   u8 attack;
   u8 defense;
   const char *name;
} entity_t;


/**************************************************************************/
/* PROTOTYPES                                                             */
/**************************************************************************/

void init_globals(void);
void display_stats(entity_t *entity);
command_t get_player_command(void);
command_t get_enemy_command(void);
void execute_turn(command_t command, entity_t *me, entity_t *opponent);


/**************************************************************************/
/* GLOBALS                                                                */
/**************************************************************************/

entity_t player;
entity_t enemy;


/**************************************************************************/
/* MAIN                                                                   */
/**************************************************************************/

void main(void) {

    init_globals();

    // Let's start!
    printf("RPG GAME\r\n");
    printf("\r\n");
    printf("PRESS ENTER TO START\r\n");

    // Is enter pressed?
    while (!cpct_isKeyPressed(Key_Enter)) {
        cpct_scanKeyboard();
    }

    while (1) {
        // CLS
        putchar(12);

        display_stats(&player);
        display_stats(&enemy);

        execute_turn(get_player_command(), &player, &enemy);
        execute_turn(get_enemy_command(), &enemy, &player);
    }
}


/**************************************************************************/
/* FUNCTIONS                                                              */
/**************************************************************************/

void init_globals(void) {
    player.energy = 100;
    player.attack = 30;
    player.defense = 15;
    player.name = "PLAYER";

    enemy.energy = 90;
    enemy.attack = 20;
    enemy.defense = 10;
    enemy.name = "ENEMY";
}

void display_stats(entity_t *entity) {
    printf("%s [%d] (a%d) (d%d)\r\n",
           entity->name,
           entity->energy,
           entity->attack,
           entity->defense
           );
}

command_t get_player_command(void) {
    command_t command;

    command = CMD_NONE;
    do {
        cpct_scanKeyboard();
        if (cpct_isKeyPressed(Key_A)) {
            command = CMD_ATTACK;
        } else if (cpct_isKeyPressed(Key_D)) {
            command = CMD_DEFEND;
        }
    } while (command == CMD_NONE);

    return command;
}

command_t get_enemy_command(void) {
    if (cpct_rand() < 64) {
        return CMD_DEFEND;
    } else {
        return CMD_ATTACK;
    }
}

void execute_turn(command_t command, entity_t *me, entity_t *opponent) {
    switch (command) {
    case CMD_ATTACK:
        opponent->energy -= me->attack;
        break;

    case CMD_DEFEND:
        me->energy += me->defense;
        break;
    }

}
