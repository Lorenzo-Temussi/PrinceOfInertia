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
            struct Stanza* sx, struct Stanza* dx, struct Stanza* uw, struct Stanza* dw,
            int tipoStanza, int tipoTrabocchetto, int tipoTesoro) {

        struct Stanza* temp = (struct Stanza*)malloc(sizeof(struct Stanza));
        
        temp->stanzaSx = sx;
        temp->stanzaDx = dx;
        temp->stanzaSopra = uw;
        temp->stanzaSotto = dw;
        
        temp->tipoStanza = tipoStanza;
        temp->tipoTrabocchetto = tipoTrabocchetto;
        temp->tipoTesoro = tipoTesoro;

        return temp;
    }

    static void inserisciStanza(struct Stanza** mappa) {
        // pick doors
        struct Stanza* porte [4] = {NULL, NULL, NULL, NULL}; 
        // pick verythign else
        int contenuti [] = {0, 0, 0};

        while(1) { // selezione stanza
            printf("Inserisci tipo stanza:\n"
            "1) CORRIDOIO\n2) SCALA\n3) SALA BANCHETTO\n4) MAGAZZINO\n"
            "5) POSTAZIONE DI GUARDIA\n 6) PRIGIONE\n 7) ARMERIA\n 8) MOSCHEA\n"
            "9) TORRE\n 0) BAGNI\n");

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
            "1) PIANOFORTE\n2) LAME\n3) BANANA\n4) BURRONE\n 0) NESSUNO\n");

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
            "1) VELENO\n2) GUARIGIONE\n3) AUMENTA_HP\n4) SPADA_TAGLIENTE\n"
            "5) SCUDO\n0) NESSUNO\n");

            if ((scanf("%d", &contenuti[2]) == 1) && contenuti[2] >= 0 && contenuti[2] <= 5) {
                break;
            } else {
                printf("Input is invalid.\n");
                while (getchar() != '\n');
                continue;
            } 
        }

        struct Stanza* nuovaStanza = creaStanza(porte[0], porte[1], porte[2], porte[3], contenuti[0], contenuti[1], contenuti[2]);
        

        int selectDir = 0;
        struct Stanza* ultimaStanza = *(mappa + getRoomCount(mappa) -1); 
        ultimaStanza = nuovaStanza;
    
    return;
    
    }


    static void cancellaStanza(struct Stanza** mappa) {
        printf("cancellaStanza called.\n");

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
    }

    static void chiudiMappa() {
        printf("chiudiMappa called.\n");
        
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
                inserisciStanza(mappa); //TODO 
                break;
            case 2: 
                cancellaStanza(mappa);
                break;
            case 3: 
                stampaStanze(mappa);
                break;
            case 4: 
                generaRandom(mappa);
                break;
            case 5:
                chiudiMappa();
                return;
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
        printf("Nessuna stanza selezionata.");
    }

    printf("Tipo stanza: ");
    printRoomType(room);
    
    printf("Tipo trabocchetto: ");
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
        printf("Tipo tesoro: ");
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

    printf("Porta sinistra: ");
    if(room->stanzaSx == NULL) {
        printf("Chiusa\n");
    } else printRoomType(room->stanzaSx);

    printf("Porta destra: ");
    if(room->stanzaDx == NULL) {
        printf("Chiusa\n");
    } else printRoomType(room->stanzaDx);

    printf("Porta sopra: ");
    if(room->stanzaSopra == NULL) {
        printf("Chiusa\n");
    } else printRoomType(room->stanzaSopra);

    printf("Porta sotto: ");
    if(room->stanzaSotto == NULL) {
        printf("Chiusa\n");
    } else printRoomType(room->stanzaSotto);

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
    last->stanzaDx = (struct Stanza*)malloc(sizeof(struct Stanza*));
    struct Stanza* newRoom = last->stanzaDx;

    newRoom->tipoStanza = BAGNI;
    newRoom->tipoTrabocchetto = LAME;
    newRoom->tipoTesoro = SCUDO;

    newRoom->stanzaSx = last;
    newRoom->stanzaDx = NULL;
    newRoom->stanzaSopra = NULL;
    newRoom->stanzaSotto = NULL;

    last = newRoom;
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
            printf("SALA_BANCHETTO\n");
            break;
        case MAGAZZINO: 
            printf("MAGAZZINO\n");
            break;
        case POSTO_GUARDIA: 
            printf("POSTO_GUARDIA\n");
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