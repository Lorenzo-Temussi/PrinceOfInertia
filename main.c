#include "gamelib.h"
#include <stdio.h>
#include <stdlib.h>

// Questo file continene solo la definizione della funzione main
// con il menu principale 1-2-3



int main( ) {

    //allocazione memoria
    struct Stanza** mappa = (struct Stanza**)malloc(__SIZEOF_POINTER__* 15);
    for(int i = 1; i<=15; i++) {
        *(mappa - 1 + i) = NULL;
    }

    struct Giocatore** giocatori = (struct Giocatore**)malloc(__SIZEOF_POINTER__*4);

    struct Giocatore* giocatore_corrente = NULL;
    

    printf("%d", getRoomCount(mappa));

    //Debug(lastRoom);

    int state = 0;
    do {
        printf("Selezione 1-4:\n 1) Imposta Partita\n 2) Inizia Partita\n 3) Chiudi Gioco\n 4) Crediti\n");
        if (scanf("%d", &state) == 1) {
            switch(state) {
            case 1:
                impostaGioco(mappa); //inputs firstRoom, lastRoom -> ()
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
