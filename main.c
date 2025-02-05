#include "gamelib.h"
#include <stdio.h>
#include <stdlib.h>

// Questo file continene solo la definizione della funzione main
// con il menu principale 1-2-3

static struct Stanza* mappa = NULL;

static struct Stanza* firstRoom = NULL;
static struct Stanza* lastRoom = NULL;

int main( ) {

    Debug(lastRoom);
    Debug(lastRoom);
    Debug(lastRoom);

    

    
    int state = 0;
    do {
        printf("Selezione 1-4:\n 1) Imposta Partita\n 2) Inizia Partita\n 3) Chiudi Gioco\n 4) Crediti\n");
        if (scanf("%d", &state) == 1) {
            switch(state) {
            case 1:
                impostaGioco(firstRoom, lastRoom);
                break;
            case 2:
                gioca();
                break;
            case 3:
                terminaGioco();
                break;
            case 4: 
                crediti();
                break;
            default:
                printf("Input is ivalid.\n");
                break;
            }
        } else {
            printf("Input is invalid.\n");
            while (getchar() != '\n');
        }        
    } 
    while(1);

}
