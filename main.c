#include "gamelib.h"
#include <stdio.h>
#include <stdlib.h>

// Questo file continene solo la definizione della funzione main
// con il menu principale 1-2-3-4



int main( ) {

    inizializzaSeme();
    inizializzaTabellonePunteggi();

    
    //Debug(lastRoom);

    int state = -1;
    do {
        printf("Selezione 1-4:\n 1) Imposta Partita\n 2) Inizia Partita\n 3) Chiudi Gioco\n 4) Crediti\n");
        state = riceviInputNumerico(1, 4);
            switch(state) {
            case 1:
                impostaGioco(); //COMPLETA!
                break;
            case 2:
                gioca(); //WIP
                break;
            case 3:
                terminaGioco(); //COMPLETA
                break;
            case 4: 
                crediti(); //WIP
                stampaTabellonePunteggi();
                break;
            default:
                printf("Input is invalid.\n");
                while (getchar() != '\n');
                break;
            } 
    } 
    while(1);
}
