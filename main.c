#include "gamelib.h"
#include <stdio.h>
#include <stdlib.h>

// Questo file continene solo la definizione della funzione main
// con il menu principale 1-2-3



int main( ) {

    struct Stanza** mappa = (struct Stanza**)malloc(__SIZEOF_POINTER__* 15);
    
    struct Stanza* firstRoom = NULL;
    struct Stanza* lastRoom = NULL;

    printf("%d", getRoomCount(mappa));

    //Debug(lastRoom);

    int state = 0;
    do {
        printf("Selezione 1-4:\n 1) Imposta Partita\n 2) Inizia Partita\n 3) Chiudi Gioco\n 4) Crediti\n");
        if (scanf("%d", &state) == 1) {
            switch(state) {
            case 1:
                impostaGioco(firstRoom, lastRoom); //inputs firstRoom, lastRoom -> ()
                break;
            case 2:
                gioca(); //inputs firstRoom, lastRoom -> ()
                break;
            case 3:
                terminaGioco(); //inputs - -> create savefile ()
                break;
            case 4: 
                crediti(); // - -> printf()
                break;
            default:
                printf("Input is invalid.\n");
                break;
            }
        } else {
            printf("Input is invalid.\n");
            while (getchar() != '\n');
        }        
    } 
    while(1);

}
