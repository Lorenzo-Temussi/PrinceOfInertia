#include "gamelib.h"
#include <stdio.h>
#include <stdlib.h>

// Questo file continene solo la definizione della funzione main
// con il menu principale 1-2-3



int main( ) {

    int seed = 0;
    generaSeed(&seed);

    //allocazione memoria
    

    Giocatore** giocatori = (Giocatore**)malloc(__SIZEOF_POINTER__*4);

    Giocatore* giocatore_corrente = NULL;
    
    //Debug(lastRoom);

    int state = 0;
    do {
        printf("Selezione 1-4:\n 1) Imposta Partita\n 2) Inizia Partita\n 3) Chiudi Gioco\n 4) Crediti\n");
        if (scanf("%d", &state) == 1) {
            switch(state) {
            case 1:
                impostaGioco(); //DONE
                break;
            case 2:
                gioca(); //inputs firstRoom, lastRoom -> ()
                break;
            case 3:
                terminaGioco(); //DONE
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
