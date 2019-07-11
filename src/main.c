/**
 * SUPER ULTRA RPG GAME
 * by patxoca
 * July 2019
 **/

#include <cpctelera.h>
#include <stdio.h>


void main(void) {
    // Init variables
    u8 energy    = 100;
    u8 attack    = 30;
    u8 defense   = 15;
    u8 energyen  = 90;
    u8 attacken  = 20;
    u8 defenseen = 10;

    cpct_keyID key_pressed = 0;

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

        // Print stats
        printf("PLAYER [%d] (a%d) (d%d)\r\n", energy,   attack,   defense);
        printf("ENEMY  [%d] (a%d) (d%d)\r\n", energyen, attacken, defenseen);

        key_pressed = 0;
        do {
            cpct_scanKeyboard();
            if (cpct_isKeyPressed(Key_A)) {
                key_pressed = Key_A;
            } else if (cpct_isKeyPressed(Key_D)) {
                key_pressed = Key_D;
            }
        } while (key_pressed == 0);

        switch (key_pressed) {
        case Key_A:
            // PLAYER ATTACKS!
            energyen -= attack;
            break;

        case Key_D:
            energy += defense;
            break;
        }

        // ENEMY DECIDE
        if (cpct_rand() < 64) {
            energyen += defenseen;
        } else {
            energy -= attacken;
        }
    }

}
