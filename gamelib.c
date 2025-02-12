#include "gamelib.h"
#include <stdio.h>
#include <stdlib.h>


// Definizioni delle funzioni in gamelib.c.
// Piu altre funzioni di supporto.
// Le funzioni richiamabili in main.c non devono essere static.
// Le altre devono essere static (non visibili all'esterno).

// Funzioni statiche



// #regione Imposta 
    static struct Stanza* creaStanza (
            struct Stanza** mappa, struct Stanza* dx, struct Stanza* uw, struct Stanza* sx, struct Stanza* dw,
            int tipoStanza, int tipoTrabocchetto, int tipoTesoro) {

        struct Stanza* temp = (struct Stanza*)malloc(sizeof(struct Stanza));
        
        temp->porte[0] = dx;
        temp->porte[1] = uw;
        temp->porte[2] = sx;
        temp->porte[3] = dw;
        
        temp->tipoStanza = tipoStanza;
        temp->tipoTrabocchetto = tipoTrabocchetto;
        temp->tipoTesoro = tipoTesoro;

        int numStanze = getRoomCount(mappa);
        struct Stanza* ultimaStanza = *(mappa - 1 + numStanze);

        if(numStanze) {
            for (int i = 0; i < 4; i++){
                if(temp->porte[i] == ultimaStanza) {
                    ultimaStanza->porte[(i+2)%4] = temp;
                }
            }
            
        }

        mappa[numStanze] = temp;

        return temp;
    }

    static void inserisciStanza(struct Stanza** mappa) {
        struct Stanza* ultimaStanza = NULL;
        int numStanze = getRoomCount(mappa); 
        if (numStanze >= 15) {
            return;
        }

        // pick doors
        struct Stanza* porte [4] = {NULL, NULL, NULL, NULL}; 
        
        int porta = 5;

        while(1) { // selezione porta
        
            printf("Da quale porta si accede alla stanza?:\n"
            " 0) DESTRA\n 1) AVANTI\n 2) SINISTRA\n 3) INDIETRO\n");

            if ((scanf("%d", &porta) == 1) && porta >= 0 && porta <= 4) {
                // do nun
            } else {
                printf("Input non valido.\n");
                while (getchar() != '\n');
                continue;
            } 

            if (numStanze) {

                ultimaStanza = *(mappa - 1 + getRoomCount(mappa));
                if (ultimaStanza->porte[(porta + 2)%4] != NULL) {
                    printf("La porta corrispondente è già in uso.\n");
                    continue;
                }

                porte[porta] = ultimaStanza;
            }
            break;

        }


        // pick verythign else
        int contenuti [] = {0, 0, 0};

        while(1) { // selezione stanza
            printf("Inserisci tipo stanza:\n"
            " 0) CORRIDOIO\n 1) SCALA\n 2) SALA BANCHETTO\n 3) MAGAZZINO"
            "\n 4) POSTAZIONE DI GUARDIA\n 5) PRIGIONE\n 6) ARMERIA\n 7) MOSCHEA\n"
            " 8) TORRE\n 9) BAGNI\n");

            if ((scanf("%d", &contenuti[0]) == 1) && contenuti[0] >= 0 && contenuti[0] <= 9) {
                break;
            } else {
                printf("Input non valido.\n");
                while (getchar() != '\n');
                continue;
            } 
        }

        while(1) { // selezione trabocchetto
            printf("Inserisci tipo trabocchetto:\n"
            " 1) PIANOFORTE\n 2) LAME\n 3) BANANA\n 4) BURRONE\n 0) NESSUNO\n");

            if ((scanf("%d", &contenuti[1]) == 1) && contenuti[1] >= 0 && contenuti[1] <= 4) {
                break;
            } else {
                printf("Input is invalid.\n");
                while (getchar() != '\n');
                continue;
            } 
        }

        while(1) { // selezione tesoro
            printf("Inserisci tipo tesoro:\n"
            " 1) VELENO\n 2) GUARIGIONE\n 3) AUMENTA_HP\n 4) SPADA_TAGLIENTE\n"
            " 5) SCUDO\n 0) NESSUNO\n");

            if ((scanf("%d", &contenuti[2]) == 1) && contenuti[2] >= 0 && contenuti[2] <= 5) {
                break;
            } else {
                printf("Input is invalid.\n");
                while (getchar() != '\n');
                continue;
            } 
        }

        struct Stanza* nuovaStanza = creaStanza(mappa, porte[0], porte[1], porte[2], porte[3], contenuti[0], contenuti[1], contenuti[2]);
        
        

    return;
    
    }

    static void cancellaStanza(struct Stanza** mappa) {
        if (getRoomCount(mappa) > 1) {
                struct Stanza* penultimaStanza = *(mappa - 2 + getRoomCount(mappa));
                struct Stanza* ultimaStanza = *(mappa -1 + getRoomCount(mappa));
                for (int i = 0; i < 4; i++) {
                    if (penultimaStanza->porte[i] == ultimaStanza) {
                        penultimaStanza->porte[i] = NULL;
                    }
                }
            
            }
    }

    static void cancellaStanzaSelect(struct Stanza** mappa) {
        if (getRoomCount(mappa) == 0) {
            printf("Non ci sono stanze su questa mappa.\n");
            return;
        }

        printf("Ultima stanza creata:\n\n");
        struct Stanza* ultimaStanza = *(mappa - 1 + getRoomCount(mappa));
        stampaStanza(ultimaStanza, 1);
        printf("Vuoi davvero cancellare questa stanza?\n0) Annulla\n1) Conferma\n");
        int temp = 0;

        if ((scanf("%d", &temp) == 1) && temp <= 1 && temp >= 0) {
            if(temp == 0) {
                printf("Operazione annullata.\n");
                return;
            }


            cancellaStanza(mappa);

            *(mappa - 1 + getRoomCount(mappa)) = NULL;
            free(ultimaStanza);

            
            printf("Cancellazione completa!\n");
            
            } else {
                printf("Input non valido.\n");
                while (getchar() != '\n');
            } 

    }

    static void stampaStanze(struct Stanza** mappa) {
        printf("stampaStanze called.\n");
        int numStanze = getRoomCount(mappa);
        for(int i = 0; i < numStanze; i++) {
            stampaStanza(*(mappa + i), 1);
        }
    }

    static void generaRandom(struct Stanza** mappa) {
        printf("generaRandom called.\n");

        //Cancella tutte
        int temp = getRoomCount(mappa);
        for (int i = 0; i < temp; i++) {
            cancellaStanza(mappa);
        }

        //Genera Ex Novo
        for (int i = 0; i < 15; i++) {
            

            struct Stanza* porte[4] = {NULL, NULL, NULL, NULL};
            if(getRoomCount(mappa)) {
                porte[0] = *(mappa -1 + getRoomCount(mappa));
            }

            for (int j = 0; j < 4; j++) { //roll porta

            }

            int tipoStanza = 0; //roll stanza

            int tipoTrabocchetto = 0; //roll trabocchetto

            int tipoTesoro = 0; //roll tesoro

            creaStanza(mappa, porte[0], porte[1], porte[2], porte[3], tipoStanza, tipoTrabocchetto, tipoTesoro);
            printf("iterato\n");
        }

        printf("Se riesci a leggere questo, non hai segfaultato\n");
    }

    static int chiudiMappa(struct Stanza** mappa) {
        int temp = getRoomCount(mappa);
        if (temp != 15) {
            printf("La mappa ha %d stanze. Puoi salvare solo mappe con 15 stanze esatte.\n", temp);
            return 0;
        }

        return 1;
    }

// #endregion 


static void avanza() {
    printf("avanza called.\n");
}


// #region Combattimento 


    static void vinci() {
        printf("vinci called.\n");
    }

    static void scappa() {
        printf("scappa called.\n");
    }    

    static void combatti() {
        printf("combatti called.\n"); 
        while(1) {
            int choice = 0;
            printf("scegli un'azione pisé:\n1) Lotta!\n2) Vinci\n3) Scappa\n");
            if (scanf("%d", &choice) == 1) { 
                switch (choice) {
                    case 1: 
                        printf("Lotti per un turno intero!\n");
                        break;
                    case 2: 
                        printf("Sconfiggi l'avversario!\n");
                        vinci();
                        break;
                    case 3: 
                        printf("Riesci a fuggire per il rotto della cuffia...\n");
                        scappa();
                        break;
                    default: 
                        printf("Opzione non valida.\n");
                        break;
                }

            }
        }  
    }


// #endregion


static void stampaGiocatori() {
    printf("stampaGiocatori called.\n");
}

static void stampaZona() {
    printf("stampaZona called.\n");
}

static void prendiTesoro() {
    printf("prendiTesoro called.\n");
}

static void cercaPortaSegreta() {
    printf("cercaPortaSegreta called.\n");
}

static void passaTurno() {
    printf("passaTurno called.\n");
}

void impostaGioco(struct Stanza** mappa) {
    printf("impostaGioco called.\n");
    do {
        int temp = 0;
        printf("Seleziona opzione 1-5:\n 1) Inserisci\n 2) Cancella\n 3) Stampa\n 4) Generazione casuale\n 5) Indietro\n");
        if (scanf("%d", &temp) == 1) {
        switch (temp) {
            case 1:
                inserisciStanza(mappa); //DONE 
                break;
            case 2: 
                cancellaStanzaSelect(mappa); //DONE
                break;
            case 3: 
                stampaStanze(mappa); //DONE
                break;
            case 4: 
                generaRandom(mappa); //IN PROGRESS
                break;
            case 5:
                if (chiudiMappa(mappa)) {return;} //DONE
                break;
            default:
                break;
            } 
        } else {
            printf("Input is invalid.\n");
            
        }
            

    }
    while (1);
}

// #region Gioca

    void gioca() {
        int playerNum = 1;

        // selezione giocatori
        
        do {
            printf("Quanti giocatori ci sono? Max 4.\n");
            if (scanf("%d", &playerNum) == 1) {
                if (playerNum <= 4 && playerNum >= 1) {
                    printf("Preparo il gioco per %d giocatori.\n", playerNum);
                } else {
                    printf("Questa versione del gioco supporta un massimo di 4 giocatori.\n");       
                }
                
            } else {
                printf("Input non valido.\n");
            }  
            while (getchar() != '\n');
        } while(!(playerNum <= 4 && playerNum >= 1));

        //selezione classi


        
    } 

// #endregion

void crediti() {
    printf("crediti called.\n");
}

void terminaGioco() {
    printf("terminaGioco called.\n");
    exit(0);
}


struct Stanza* getFirstRoom (struct Stanza** mappa) {
    return *mappa;
}

struct Stanza* getlastRoom (struct Stanza** mappa) {
    return *(mappa + getRoomCount(mappa) - 1);
}

//Subroutines 
void stampaStanza(struct Stanza* room, int viewAll) {

    if(room == NULL) {
        printf(" Nessuna stanza selezionata.");
    }


    printf("_______________________________\n");
    printf(" Tipo stanza: ");
    printRoomType(room);
    printf("\n\n");
    
    printf(" Tipo trabocchetto: ");
    switch(room->tipoTrabocchetto) {
        case NESSUN_TRABOCCHETTO:
            printf("NESSUN_TRABOCCHETTO\n");
            break;
        case PIANOFORTE:
            printf("PIANOFORTE\n");
            break;
        case LAME: 
            printf("LAME\n");
            break;
        case CADUTA: 
            printf("CADUTA\n");
            break;
        case BURRONE: 
            printf("BURRONE\n");
            break;
        default: 
            printf("errore: tipo trabucchino non valido\n");
            break;
    }
    
    
    
    if(viewAll){
        printf(" Tipo tesoro: ");
        switch(room->tipoTesoro) {
            case NESSUN_TESORO:
                printf("NESSUN_TESORO\n");
                break;
            case VELENO:
                printf("VELENO\n");
                break;
            case GUARIGIONE: 
                printf("GUARIGIONE\n");
                break;
            case AUMENTA_HP: 
                printf("AUMENTA_HP\n");
                break;
            case SPADA_TAGLIENTE: 
                printf("SPADA_TAGLIENTE\n");
                break;
            case SCUDO: 
                printf("SCUDO\n");
                break;
            default: 
                printf("errore: tipo tesoro non valido\n");
                break;
        }
    } else { 
        if(room->tipoTesoro) {
            printf("La stanza contiente un tesoro sconosciuto...\n");
        } else {
            printf("La stanza non contiente un tesoro...\n");
        }
    }


    printf(" Porta destra: ");
    if(room->porte[0] == NULL) {
        printf("Chiusa\n");
    } else printRoomType(room->porte[0]);

    printf(" Porta sopra: ");
    if(room->porte[1] == NULL) {
        printf("Chiusa\n");
    } else printRoomType(room->porte[1]);

    printf(" Porta sinistra: ");
    if(room->porte[2] == NULL) {
        printf("Chiusa\n");
    } else printRoomType(room->porte[2]);

    printf(" Porta sotto: ");
    if(room->porte[3] == NULL) {
        printf("Chiusa\n");
    } else printRoomType(room->porte[3]);

    printf("_______________________________\n");

    return;
}

int getRoomCount(struct Stanza** mappa) { //COMPLETE
    int temp = 0;
    for (int i = 0; i < 15; i++) {
        if (*(mappa + i) == NULL) {
            break;
        } else {
            temp++;
        }
    }
    return temp;
}
    
// external save/load

void Debug(struct Stanza* last) {
    
}
/*
void writeToFile(const char *filename, struct Stanza *s) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return;
    }
    
    fprintf(file, "%d\n", s->tipoStanza);  
    fprintf(file, "%d\n", s->tipoTrabocchetto);
    fprintf(file, "%d\n", s->tipoTesoro);
    fprintf(file, "%p\n", s->stanzaSx);
    fprintf(file, "%p\n", s->stanzaDx);
    fprintf(file, "%p\n", s->stanzaSotto);
    fprintf(file, "%p\n", s->stanzaSopra);

    fclose(file);
}*/

void printRoomType(struct Stanza* stanza) {
    switch(stanza->tipoStanza) {
        case CORRIDOIO: 
            printf("CORRIDOIO\n");
            break;
        case SCALA:
            printf("SCALA\n");
            break;
        case SALA_BANCHETTO: 
            printf("SALA BANCHETTO\n");
            break;
        case MAGAZZINO: 
            printf("MAGAZZINO\n");
            break;
        case POSTO_GUARDIA: 
            printf("POSTO DI GUARDIA\n");
            break;
        case PRIGIONE: 
            printf("PRIGIONE\n");
            break;
        case ARMERIA: 
            printf("ARMERIA\n");
            break;
        case MOSCHEA: 
            printf("MOSCHEA\n");
            break;
        case TORRE: 
            printf("TORRE\n");
            break;
        case BAGNI: 
            printf("BAGNI\n");
            break;
        default: 
            printf("errore: tipo stanza non valido\n");
            break;
    }
    
}