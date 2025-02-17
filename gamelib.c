#include "gamelib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


Stanza* ptrPrimaStanza = NULL;
Stanza* ptrUltimaStanza = NULL;

// Definizioni delle funzioni in gamelib.c.
// Piu altre funzioni di supporto.
// Le funzioni richiamabili in main.c non devono essere static.
// Le altre devono essere static (non visibili all'esterno).

// Funzioni statiche

    void generaSeed(int* seed) {
        time_t t;
        srand((unsigned) time(&t));
        printf("seed is now %d", *seed);
    }

    void selezionaSeed (int* seed, int input) {
        *seed = input;
        printf("seed is now %d", input);
    }


    int generaRandomStanza() {
        int tipoStanza = rand() % 10; //roll stanza
        return tipoStanza;
    }

    int generaRandomTrabocchetto() {
                    
        int tipoTrabocchettoRand = rand() % 100;
        if (tipoTrabocchettoRand <= 64) {
            return 0;
        } else if (tipoTrabocchettoRand <= 74) {
            return 1;
        } else if (tipoTrabocchettoRand <= 83) {
            return 2;
        } else if (tipoTrabocchettoRand <= 91) {
            return 3;
        } else if (tipoTrabocchettoRand <= 99) {
            return 4;
        }
        return 0;
    }

    int generaRandomTesoro() {
                    
        int tipoTesoroRand = rand() % 100;
        if (tipoTesoroRand <= 19) {
            return 0;
        } else if (tipoTesoroRand <= 39) {
            return 1;
        } else if (tipoTesoroRand <= 59) {
            return 2;
        } else if (tipoTesoroRand <= 74) {
            return 3;
        } else if (tipoTesoroRand <= 89) {
            return 4;
        } else if (tipoTesoroRand <= 99) {
            return 5;
        }
        return 0;
    }

    int generaRandomPorte(int ultimaPorta) {
        ultimaPorta = (ultimaPorta + 3 + rand() % 3) %4;
        return (ultimaPorta);
}

// subroutines Imposta 
static int getRoomCount() { //COMPLETE - LL
    int stanzeTotali = 0;
    Stanza* stanzaCorrente = ptrPrimaStanza;
    while (stanzaCorrente != NULL) {       
        stanzeTotali++;
        stanzaCorrente = stanzaCorrente->successiva;
        }        
    return stanzeTotali;
    }
    


static void aggiornaUltimaStanza() { //COMPLETA - LL
    struct Stanza* stanzaCorrente = ptrPrimaStanza;
    if (stanzaCorrente == NULL)  {
        ptrUltimaStanza = NULL;
        return;
    }

    while (stanzaCorrente->successiva != NULL) {       
        stanzaCorrente = stanzaCorrente->successiva;     
    }
    
    ptrUltimaStanza = stanzaCorrente;
}

static void stampaStanza (Stanza* stanza, int viewAll) {

if(stanza == NULL) {
    printf(" Nessuna stanza selezionata.");
}


printf("_______________________________\n");
printf(" Tipo stanza: ");
stampaTipoStanza(stanza);
printf("\n\n");

printf(" Tipo trabocchetto: ");
switch(stanza->tipoTrabocchetto) {
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
    switch(stanza->tipoTesoro) {
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
    if(stanza->tipoTesoro) {
        printf("La stanza contiente un tesoro sconosciuto...\n");
    } else {
        printf("La stanza non contiente un tesoro...\n");
    }
}


printf(" Porta destra: ");
if(stanza->porte[0] == NULL) {
    printf("Chiusa\n");
} else stampaTipoStanza(stanza->porte[0]);

printf(" Porta sopra: ");
if(stanza->porte[1] == NULL) {
    printf("Chiusa\n");
} else stampaTipoStanza(stanza->porte[1]);

printf(" Porta sinistra: ");
if(stanza->porte[2] == NULL) {
    printf("Chiusa\n");
} else stampaTipoStanza(stanza->porte[2]);

printf(" Porta sotto: ");
if(stanza->porte[3] == NULL) {
    printf("Chiusa\n");
} else stampaTipoStanza(stanza->porte[3]);

printf("_______________________________\n");

return;
}

static void stampaStanze() {
    printf("stampaStanze called.\n");
    Stanza* stanzaCorrente = ptrPrimaStanza;
    
    if(!stanzaCorrente) { //caso 0 stanze
        printf("Nessuna stanza selezionata. Ji Nio.\n");
    }

    while (stanzaCorrente != NULL) { //iteratore
        stampaStanza(stanzaCorrente, 1);
        stanzaCorrente = stanzaCorrente->successiva;
    }
    return;        
}

static Stanza* creaStanza(int tipoStanza, int tipoTrabocchetto, int tipoTesoro) {
    printf("creaStanza called!\n");
    Stanza* temp = (Stanza*)malloc(sizeof(Stanza));
    
    temp->porte[0] = NULL;
    temp->porte[1] = NULL;
    temp->porte[2] = NULL;
    temp->porte[3] = NULL;
    temp->successiva = NULL;
    
    temp->tipoStanza = tipoStanza;
    temp->tipoTrabocchetto = tipoTrabocchetto;
    temp->tipoTesoro = tipoTesoro;
    
    return temp;
}

static void connettiStanza(Stanza* stanza, int indicePorta) {
    if(!getRoomCount()) {
        return;
    }

    printf("connettiStanza called!\n");
    stanza->porte[indicePorta] = ptrUltimaStanza;
    
    ptrUltimaStanza->porte[(indicePorta + 2) %4] = stanza;
    ptrUltimaStanza->successiva = stanza;
}

static void spingiStanza(Stanza* stanza) {
    printf("getRoomsCount: %d \n", getRoomCount());
    stampaStanze();
    printf("spingiStanza called!\n");
    if(!getRoomCount()) { //caso prima stanza
        ptrPrimaStanza = stanza;
        ptrUltimaStanza = stanza;
    } else {
        ptrUltimaStanza = stanza;
    }
}

static int selezionaPorta() {
    while(1) { // selezione porta
    
        int porta;
        printf("Da quale porta si accede alla stanza?:\n"
        " 0) DESTRA\n 1) AVANTI\n 2) SINISTRA\n 3) INDIETRO\n");

        if ((scanf("%d", &porta) == 1) && porta >= 0 && porta < 4) {
            // do nun
        } else {
            printf("Input non valido.\n");
            while (getchar() != '\n');
            continue;
        } 

        if (getRoomCount()) {

            if (ptrUltimaStanza->porte[(porta + 2)%4] != NULL) {
                printf("La porta corrispondente è già in uso.\n");
                continue;
            }
        }   
        printf("ptrUltimaStanza non è NULL\n");
        return porta;
    }
}

static int selezionaTipoStanza() {
    int tipoStanza = -1;
    while(1) { 
        
        printf("Inserisci tipo stanza:\n"
        " 0) CORRIDOIO\n 1) SCALA\n 2) SALA BANCHETTO\n 3) MAGAZZINO"
        "\n 4) POSTAZIONE DI GUARDIA\n 5) PRIGIONE\n 6) ARMERIA\n 7) MOSCHEA\n"
        " 8) TORRE\n 9) BAGNI\n");

        if ((scanf("%d", &tipoStanza) == 1) && tipoStanza >= 0 && tipoStanza <= 9) {
            break;
        } else {
            printf("Input non valido.\n");
            while (getchar() != '\n');
            continue;
        } 
    }
    return tipoStanza;
}

static int selezionaTrabocchetto() {
    int trabocchetto = -1;
    while(1) { // selezione trabocchetto
        printf("Inserisci tipo trabocchetto:\n"
        " 1) PIANOFORTE\n 2) LAME\n 3) BANANA\n 4) BURRONE\n 0) NESSUNO\n");

        if ((scanf("%d", &trabocchetto) == 1) && trabocchetto >= 0 && trabocchetto <= 4) {
            break;
        } else {
            printf("Input is invalid.\n");
            while (getchar() != '\n');
            continue;
        } 
    }
    return trabocchetto;
}

static int selezionaTesoro() {
    int tesoro = -1;
    while(1) { // selezione tesoro
        printf("Inserisci tipo tesoro:\n"
        " 1) VELENO\n 2) GUARIGIONE\n 3) AUMENTA_HP\n 4) SPADA_TAGLIENTE\n"
        " 5) SCUDO\n 0) NESSUNO\n");

        if ((scanf("%d", &tesoro) == 1) && tesoro >= 0 && tesoro <= 5) {
            break;
        } else {
            printf("Input is invalid.\n");
            while (getchar() != '\n');
            continue;
        } 
    }
    return tesoro;
}

static void creaStanzaMain() {

    struct Stanza* porte [4] = {NULL, NULL, NULL, NULL}; 
    
    if (getRoomCount()  >= 15) {
        printf("Numero massimo di stanze raggiunto.\n");
        return;
    }

    Stanza* nuovaStanza = creaStanza(selezionaTipoStanza(), selezionaTrabocchetto(), selezionaTesoro());
    
    connettiStanza(nuovaStanza, selezionaPorta());
    spingiStanza(nuovaStanza);
    
    return;
}

static void cancellaStanza() {
    
    Stanza* stanzaCorrente = ptrPrimaStanza;

    if(stanzaCorrente == ptrUltimaStanza) {
        free(stanzaCorrente);
        ptrPrimaStanza = NULL;
        ptrUltimaStanza = NULL;
    }
    
    while(stanzaCorrente->successiva != ptrUltimaStanza) {
        stanzaCorrente = stanzaCorrente->successiva;
    }

    free (stanzaCorrente->successiva);
    stanzaCorrente->successiva = NULL;
    ptrUltimaStanza = stanzaCorrente;
    printf("stanza deletata alla grande!\n");
    return;    
}

void stampaTipoStanza(Stanza* stanza) {
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



static void cancellaStanzaSelect() {
    if (!getRoomCount()) {
        printf("Non ci sono stanze su questa mappa.\n");
        return;
    }

    printf("Ultima stanza creata:\n\n");
    stampaStanza(ptrUltimaStanza, 1);
    printf("Vuoi davvero cancellare questa stanza?\n0) Annulla\n1) Conferma\n");
    int temp = 0;

    if ((scanf("%d", &temp) == 1) && temp <= 1 && temp >= 0) {
        if(temp == 0) {
            printf("Operazione annullata.\n");
            return;
        }


        cancellaStanza();
        
        printf("Cancellazione completa!\n");
        
        } else {
            printf("Input non valido.\n");
            while (getchar() != '\n');
        } 

}

static void generaRandom() {
    printf("generaRandom called.\n");

    //Cancella tutte
    int temp = getRoomCount();
    for (int i = 0; i < temp; i++) {
        cancellaStanza();
    }

    //Genera Ex Novo
    int ultimaPorta = rand() %4;
    for (int i = 0; i < 15; i++) {
                
        struct Stanza* porte[4] = {NULL, NULL, NULL, NULL};

        int tipoStanza = generaRandomStanza();

        int tipoTrabocchetto = generaRandomTrabocchetto();
        
        int tipoTesoro = generaRandomTesoro();

        ultimaPorta = generaRandomPorte(ultimaPorta);
        porte[ultimaPorta] = ptrUltimaStanza;
        

        creaStanza (tipoStanza, tipoTrabocchetto, tipoTesoro);
        printf("iterato\n");
    }

    printf("Se riesci a leggere questo, non hai segfaultato\n");
}

static int chiudiMappa() {
    int temp = getRoomCount();
    if (temp != 15) {
        printf("La mappa ha %d stanze. Puoi salvare solo mappe con 15 stanze esatte.\n", temp);
        return 0;
    }

    return 1;
}



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

void impostaGioco() {
    printf("impostaGioco called.\n");
    do {
        int temp = 0;
        printf("Seleziona opzione 1-5:\n 1) Inserisci\n 2) Cancella\n 3) Stampa\n 4) Generazione casuale\n 5) Indietro\n");
        if (scanf("%d", &temp) == 1) {
        switch (temp) {
            case 1:
                creaStanzaMain(); //DONE 
                break;
            case 2: 
                cancellaStanzaSelect(); //DONE
                break;
            case 3: 
                stampaStanze(); //DONEa
                break;
            case 4: 
                generaRandom(); //IN PROGRESS
                break;
            case 5:
                if (chiudiMappa()) {return;} //DONE
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
