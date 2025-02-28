#include "gamelib.h"
#include <bits/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>


Stanza* ptrPrimaStanza = NULL;
Stanza* ptrUltimaStanza = NULL;

Giocatore* ptrPrimoGiocatore = NULL;
Giocatore* giocatoreCorrente = NULL;

int seme = 0;
int* semePtr = &seme;


// Definizioni delle funzioni in gamelib.c.
// Piu altre funzioni di supporto.
// Le funzioni richiamabili in main.c non devono essere static.
// Le altre devono essere static (non visibili all'esterno).

// SEZIONE 1 - IMPOSTA

    void inizializzaSeme() {
        time_t t;
        unsigned int value = (unsigned int)time(&t);
        *semePtr = value % 1000000;
        
        srand(*semePtr);
        
        printf("seed is now %d", *semePtr);
        return;
    }

    extern void generaSeed() {
        *semePtr = rand() % 1000000;
        srand(*semePtr);
        printf("seed is now %d", *semePtr);
        return;
    }

    static void selezionaSeed () {
        int input = -1;
        while(1) {  
            printf("Seleziona un numero tra 000000 e 999999:\n");
            if((scanf("%d", &input) != 1) || input < 0 || input > 999999) {
                while(getchar() != '\n');
                continue;
            } 

            *semePtr = input;
            srand(*semePtr);
            printf("seed is now %d", *semePtr);
            break;
        }
        return;
    }

    static void modificaSemeSelect() {
        while(1) {
            printf("Modifica seme:\n1) Casuale\n2) Inserisci\n 0) Annulla\n\n");
            int choice = -1;
            if (scanf("%d", &choice) == 1) { 
                switch(choice) {
                    case 0:
                        return;
                    case 1:
                        generaSeed();
                        return;
                    case 2: 
                        selezionaSeed();
                        return;
                    default:
                        printf("Selezione non valida\n");
                }
            }
        }
    }

    static int generaRandomPorte(int ultimaPorta) {
        ultimaPorta = (ultimaPorta + 3 + rand() % 3) %4;
        return (ultimaPorta);
    }

    static int generaRandomStanza() {
        int tipoStanza = rand() % 10; //roll stanza
        return tipoStanza;
    }

    static int generaRandomTrabocchetto() {
                    
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

    static int generaRandomTesoro() {
                    
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

    static void stampaTipoStanza(Stanza* stanza) {
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

    static void stampaStanza (Stanza* stanza, int viewAll) {

    if(stanza == NULL) {
        printf(" Nessuna stanza selezionata.");
    }

    printf("_______________________________\n");
    printf(" Tipo stanza: ");
    stampaTipoStanza(stanza);
    printf("\n");

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
            printf(" La stanza contiente un tesoro sconosciuto...\n");
        } else {
            printf(" La stanza non contiente un tesoro...\n");
        }
    }

    for(int i = 0; i < 4; i++) {
        printf(" PORTA %s: ", stanza->direzionePorte[i]);
        if (stanza->porte[i] == NULL) {
            printf("Chiusa\n");
            continue;
        }
        stampaTipoStanza(stanza->porte[i]);
    }

    printf("_______________________________\n\n");

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

        char* stringa[10];

        for(int i = 0; i<4; i++) {
            temp->direzionePorte[0] = malloc(sizeof(stringa));
        }

        temp->direzionePorte[0] = "DESTRA";
        temp->direzionePorte[1] = "AVANTI";
        temp->direzionePorte[2] = "SINISTRA";
        temp->direzionePorte[3] = "INDIETRO";

        
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

    static int cancellaStanza() {
        
        Stanza* stanzaCorrente = ptrPrimaStanza;

        if (!getRoomCount()) {
            printf("Non ci sono stanze su questa mappa.\n");
            return 0;
        }

        if(stanzaCorrente == ptrUltimaStanza) {
            free(stanzaCorrente);
            ptrPrimaStanza = NULL;
            ptrUltimaStanza = NULL;
        }
        
        while(stanzaCorrente->successiva != ptrUltimaStanza) {
            stanzaCorrente = stanzaCorrente->successiva;
        }

        for(int i = 0; i < 4; i++) {
            if (stanzaCorrente->porte[i] == ptrUltimaStanza) {
                stanzaCorrente->porte[i] = NULL;
            }
        }

        free (stanzaCorrente->successiva);
        stanzaCorrente->successiva = NULL;
        ptrUltimaStanza = stanzaCorrente;
        printf("stanza deletata alla grande!\n");
        return 1;    
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
        
        while(cancellaStanza()) {
            continue;
        }

        //Genera Ex Novo
        int ultimaPorta = rand() %4;
        for (int i = 0; i < 15; i++) {
                    
            struct Stanza* porte[4] = {NULL, NULL, NULL, NULL};

            int tipoStanza = generaRandomStanza();

            int tipoTrabocchetto = generaRandomTrabocchetto();
            
            int tipoTesoro = generaRandomTesoro();

            ultimaPorta = generaRandomPorte(ultimaPorta);        

            Stanza* nuovaStanza = creaStanza (tipoStanza, tipoTrabocchetto, tipoTesoro);
            connettiStanza(nuovaStanza, ultimaPorta);
            spingiStanza(nuovaStanza);
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

    void impostaGioco() {
        printf("impostaGioco called.\n");
        do {
            int temp = -1;
            printf("Seleziona opzione 0-5:\n 0) Modifica seme\n 1) Inserisci\n 2) Cancella\n 3) Stampa\n 4) Generazione casuale\n 5) Indietro\n");
            if (scanf("%d", &temp) == 1) {
            switch (temp) {
                case 0:
                    modificaSemeSelect();
                    break;
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



// SEZIONE 2 - GIOCA

    static int haiSconfittoJaffar() {
        return 0;
    }

    static int partitaConclusa() {
        Giocatore* temp = ptrPrimoGiocatore;
            if (!temp) {
            printf("Errore: 0 giocatori nella lista\n");
            return -1;
        } 

        if(haiSconfittoJaffar()) {
            return 1;
        }
        for(int i = 0; i < ottieniNumeroGiocatori(); i++) {
            if (ptrGiocatoreNumero(i)->saluteCorrente != 0) {
                return 0;
            }
        }
        return 1;
    }

    static int ottieniNumeroGiocatori() {
        Giocatore* temp = ptrPrimoGiocatore;
        int numero = 0;

        while(temp && temp->successivo) {
            temp = temp->successivo;
            numero++;
        }

        return numero;
    }

    static int inserisciNumeroGiocatori() {
        int playerNum;
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

        Giocatore* listaGiocatori [playerNum];
        for (int i = 0; i < playerNum; i++) {
            listaGiocatori[i] = creaGiocatore();
            inserisciGiocatore(listaGiocatori[i]);

        }

        for (int i = 0; i < playerNum; i++) {
            popolaGiocatore(ptrGiocatoreNumero(i));
        }
        return playerNum;
    }

    static void inserisciGiocatore(Giocatore* giocatore) {
        Giocatore* temp = ptrPrimoGiocatore;

        if(temp == NULL) {
            ptrPrimoGiocatore = giocatore;
            return;
        }

        while(temp->successivo) {
            temp = temp->successivo;
        }
        temp->successivo = giocatore;
    }

    static Giocatore* ptrGiocatoreNumero(int indice) {
        Giocatore* temp = ptrPrimoGiocatore;

        while(indice > 0) {
            temp = temp->successivo;
            indice--;
        }
        return temp;
    }

    static Giocatore* creaGiocatore() {
        //printf("Crea giocatore chiamata\n");
        Giocatore* giocatore = (Giocatore*)malloc(sizeof(Giocatore));


        giocatore->attacco = 1;
        giocatore->classe = -1;
        giocatore->difesa = 1;
        giocatore->nome = "Giocatore X";
        giocatore->posizione = NULL;
        giocatore->saluteMax = 3;
        giocatore->saluteCorrente = 3;
        giocatore->numFuga = 2;
        giocatore->numEvadiTrabocchetto = 0;

        giocatore->successivo = NULL;


        return giocatore;
    }

    static void popolaGiocatore(Giocatore* giocatore) {
        int temp;
        Giocatore* tempGiocatore = ptrPrimoGiocatore;
        int numGiocatori = ottieniNumeroGiocatori();

        while(tempGiocatore != giocatore) {
            if(tempGiocatore->classe == PRINCIPE) {
                giocatore->classe = DOPPELGANGER;
                printf("Almeno 1 principe\n");
                break;
            }

            if(tempGiocatore->successivo->successivo == NULL) {

                giocatore->classe = PRINCIPE;
                break;
            }

            tempGiocatore = tempGiocatore->successivo;
        }


        while(giocatore->classe == -1) {
            printf("Seleziona la classe:\n 0) PRINCIPE\n 1) DOPPELGANGER\n");
            if(scanf("%d", &temp) != 0 && temp >= 0 && temp <= 1) {
                giocatore->classe = temp;
                break;
            } else {
                printf("Input non valido.\n");
            }  
            while (getchar() != '\n');
        
        }
        

        if(giocatore->classe == PRINCIPE) {
            printf("si nu principe\n");
            giocatore->numEvadiTrabocchetto = 1;
            giocatore->numFuga = 1;
        } else {
            printf("SI nu bucciott\n");
        }


        char string[100];
        while(1) {
            printf("Inserisci nome:\n ");
            if(scanf("%99s", string)) {
                giocatore->nome = malloc(strlen(string) + 1);
                break;
            } else {
                printf("Input non valido.\n");
            }  
            while (getchar() != '\n');
        }
            strcpy(giocatore->nome, string);  // Copy the string into the allocated memory
        
        giocatore->posizione = ptrPrimaStanza;
        
        return;
    }
        
    static void innescaTrabocchetto(Giocatore* giocatore, Stanza* stanza) {
        switch (stanza->tipoTrabocchetto) {
            case 0:
                printf("La stanza non contiene trappole, traboccheti, botole o cazzi analoghi.\n");
                break;
            case 1:
                printf("Un pianoforte cade dall'alto sulla testa di %s, spaccandone varie ossa\n", giocatore->nome);

                break;
            case 2:
                printf("Numerose lame vengono lanciate da apposite fessure nei muri, e si conficcano nelle carni di %s\n", giocatore->nome);

                break;
            case 3:
                printf("L'ignaro/a %s, scivola sul pavimento saponatissimo e sbatte lo zigomo su un tavolo\n", giocatore->nome);

                break;
            case 4:
                printf("Il pavimento si apre e %s cade in una botola piena di pezzi lego\n", giocatore->nome);

                break;
            default:
                printf("Non so come hai fatto ma sei riuscito a far buggare una variabile.\n");
                break;
        }
    }

    static int generaRandomNemico() {
        int temp = rand()%100;
        if (temp < 25){
            if (rand()%100 < 60) {
                printf("Dagli oscuri recessi del palazzo appare uno scheletro senza vita, mosso da un incantesimo!\n");
                return SCHELETRO;
            } else {
                printf("Il suono di una scimitarra che viene sguainata annuncia la presenza di una guardia nella stanza.\n");
                return GUARDIA;
            }
        }
            printf("L'odore dell'olio bruciato e l'unica compagnia in questa stanza.\n");
            return 0;

    }

    static void avanza(Giocatore* giocatore) {
        if(!giocatore->posizione->successiva) {
            printf("Debug: questa è l'ultima stanza, non è possibile avanzare ancora.\n");
            return;
        }

        printf("%s si muove verso ", giocatore->nome);
        stampaTipoStanza(giocatore->posizione->successiva);

        giocatore->posizione = giocatore->posizione->successiva;
    }
    
    // Blocco Combatti

        static int tiraDado () {
            return rand()%6;
        }

        static int valutaDado (int risultato) {
            if (risultato == 6) {
                return 2;
            }
            if (risultato >= 4) {
                return 1;
            }
            return 0;
        }

        static int infliggiDanni(int attacco, int difesa) {
            int attaccotemp = 0; 
            int difesatemp = 0;

            for (int i= 0; i <= attacco; i++) {
                attaccotemp += valutaDado(tiraDado());
            }

            for (int i = 0; i <= difesa; i++) {
                difesatemp += valutaDado(tiraDado());
            }

            if((attaccotemp - difesatemp) <= 0) {
                printf("Mancato! L'attacco non connette, e non infligge danni!\n");
                return 0;
            } else {
                printf("Attacco a segno! Infligge %d danni!\n", attaccotemp - difesatemp);
                return (attaccotemp - difesatemp);
            }
        }

        static Nemico* inizializzaNemico(int indice) {
            Nemico* temp = (Nemico*)malloc(sizeof(Nemico));

            switch(indice) {
                case SCHELETRO:
                    temp->saluteMax = 1;
                    temp->saluteCorrente = 1;
                    temp->attacco = 1;
                    temp->difesa = 1;
                    printf("Uno scheletro si avvicina scheletrando!\n");
                    break;
                case GUARDIA: 
                    temp->saluteMax = 2;
                    temp->saluteCorrente = 2;
                    temp->attacco = 2;
                    temp->difesa = 2;
                    printf("Una guardia ti guardia in cagnesco!\n");
                    break;
                case JAFFAR: 
                    temp->saluteMax = 3;
                    temp->saluteCorrente = 3;
                    temp->attacco = 3;
                    temp->difesa = 2;
                    printf("Il cattivissimo Jaffar e il suo pappagallo Iago"
                    ", doppiato da Gilbert Gottfried, ti sbarrano la strada!\n");
                    break;
                default: 
                    printf("In questa stanza non sembra esserci nessuno\n");
                    return NULL;
            }
            return temp;
        }

        static void vinciCombattimento(Giocatore* giocatore, int nemico) {
            printf("vinci called.\n");
            if(giocatore->saluteCorrente < giocatore->saluteMax) {
                giocatore->saluteCorrente++;
                printf("Ti riposi dopo la battaglia, e ti senti più in salute.\n");
            } else  {
            printf("Vittoria perfetta!");
            }
            
            return;
        } 
        
        static void muori (Giocatore* giocatore) {
            printf("Sei morto!\n");
            giocatore->saluteCorrente = 0;
            return;
        }

        static void combatti(Giocatore* giocatore, int indiceNemico) {
            printf("combatti called.\n"); 
            Nemico* nemico = inizializzaNemico(indiceNemico);
            while(giocatore->saluteCorrente > 0) { //TODO
                int choice = 0;
                printf("scegli un'azione pisé:\n1) Combatti!\n2) Vinci\n3) Perdi\n");
                if (scanf("%d", &choice) == 1) { 
                    switch (choice) {
                        case 1: 
                            if (rand()%2) {
                                nemico->saluteCorrente -= infliggiDanni(giocatore->attacco, nemico->difesa);
                                printf("(Debug: salute rimanente nemico = %d)", nemico->saluteCorrente);
                                if(nemico->saluteCorrente <= 0) {
                                    vinciCombattimento(giocatore, indiceNemico);
                                    return;
                                }

                                giocatore->saluteCorrente -= infliggiDanni(nemico->attacco, giocatore->difesa);
                                printf("(Debug: salute rimanente player = %d)", giocatore->saluteCorrente);

                                if (giocatore->saluteCorrente <= 0) {
                                    muori(giocatore);
                                    return;
                                }
                            } else {
                                giocatore->saluteCorrente -= infliggiDanni(nemico->attacco, giocatore->difesa);
                                printf("(Debug: salute rimanente player = %d)", giocatore->saluteCorrente);

                                if (giocatore->saluteCorrente <= 0) {
                                    muori(giocatore);
                                    return;
                                }

                                nemico->saluteCorrente -= infliggiDanni(giocatore->attacco, nemico->difesa);
                                printf("(Debug: salute rimanente nemico = %d)", nemico->saluteCorrente);

                                if(nemico->saluteCorrente <= 0) {
                                    vinciCombattimento(giocatore, indiceNemico);
                                    return;
                                }
                                
                            }
                            break;
                        case 2: 
                            printf("Sconfiggi l'avversario!\n");
                            vinciCombattimento(giocatore, indiceNemico);
                            return;
                        case 3:
                            printf("Le tue forze svaniscono e ritorni alle ombre...\n");
                            muori(giocatore);
                            return;
                        default: 
                            printf("Opzione non valida.\n");
                            break;
                    }
                }
            }  
        }

    // fine blocco

    static void scappa() {
        printf("scappa called.\n");
    }

    static void stampaGiocatore(Giocatore* giocatore) {
    printf("stampaGiocatore called.\n");
    }


    // stampaStanza definita in precedenza

    static void prendiTesoro(Giocatore* giocatore) {
        switch(giocatore->posizione->tipoTesoro) {
            case NESSUN_TESORO: 
                printf("La stanza non contiene un tesoro.\n");
                return;
            case VELENO:
                printf("Bevi il contenuto dell'ampolla.\n Un dolore terribile ti scuote da testa a piedi. Perdi 1 PS.\n");
                giocatore->saluteCorrente -= 1;
                if (giocatore->saluteCorrente <= 0) {
                    muori(giocatore);
                }
                break;
            case GUARIGIONE:
                printf("Bevi il contenuto dell'ampolla.\n Ti senti meglio. Recuperi 1 PS.\n");
                if(giocatore->saluteCorrente < giocatore->saluteMax) {
                    giocatore->saluteCorrente += 1;
                }
                break;
            case AUMENTA_HP:
                printf("Bevi il contenuto dell'ampolla.\n Ti senti invincibile. PS massimi aumentati!\n");
                giocatore->saluteMax += 1;
                giocatore->saluteCorrente += 1;
                break;
            case SPADA_TAGLIENTE:
                printf("Trovi un'arma più efficace di quella attuale! Guadagni 1 ATK.\n");
                giocatore->attacco += 1;
                break;
            case SCUDO:
                printf("Trovi uno scudo di fattura migliore di quello che stai brandendo! Guadagni 1 DEF.\n");
                giocatore->difesa += 1;
                break;
            default:
                printf("Se leggi questo hai fatto un macello.\n");
        }
        printf("La stanza non contiene più tesori.\n");
        giocatore->posizione->tipoTesoro = NESSUN_TESORO;

    }

    static void cercaPortaSegreta() {
        printf("cercaPortaSegreta called.\n");
    }

    static int passaTurno(int nemico) {
        if(nemico != 0) {
            printf("Non puoi passare il turno se un nemico ti incalza.\n");
            return 0;
        } else {
            printf("Giocatore passa il turno!\n");
            return 1;
        }
    }

    static void giocaTurno(Giocatore* giocatore) {
        
        int choice;
        int numAvanza = 1;
        int nemicoPresente = 0;
        int indiceNemico = 0; // qui rendere nemico un tipoNemico int e aggiustare il codeice di conseguenza

        while(giocatore->saluteCorrente > 0) {

            printf("scegli un'azione %s:\n 1) Avanza!\n 2) Combatti\n 3) Scappa\n"
            " 4) Stampa Giocatore\n 5) Stampa Zona\n 6) Prendi Tesoro\n"
            " 7) Cerca Porta Segreta\n 8) Passa Turno\n", giocatore->nome);
            if (scanf("%d", &choice) == 1) { 
                switch (choice) {
                    case 1: 
                        if(numAvanza > 0) {
                            printf("%d\n", numAvanza);
                            numAvanza = 0;
                            avanza(giocatore);
                            innescaTrabocchetto(giocatore, giocatore->posizione);
                            indiceNemico = (generaRandomNemico());
                        } else {
                            printf("Hai finito i piedi.\n");
                        }
                        break;
                    case 2: 
                        if(!indiceNemico) {
                            printf("Assumi una posizione di combattimento, ma non ci sono nemici.\n");
                            break;
                        }
                        combatti(giocatore, indiceNemico);
                        indiceNemico = 0;
                        break;
                    case 3:
                        scappa();
                        indiceNemico = 0;
                        break;
                    case 4: 
                        stampaGiocatore(giocatore);
                        break;
                    case 5:
                        stampaStanza(giocatore->posizione, 0);
                        break;
                    case 6:
                        prendiTesoro(giocatore);
                        break;
                    case 7: 
                        cercaPortaSegreta();
                        break;
                    case 8: 
                        if (passaTurno(indiceNemico)) {
                            return;
                        } else {
                            break;
                        }
                        
                    default: 
                        printf("Opzione non valida.\n");
                        break;
                }
            }
        }
    }
    
    void gioca() {

        int numGiocatori = inserisciNumeroGiocatori();  //selezione num. giocatori
        Giocatore* giocatoriTurnati[numGiocatori];

        for(int i = 0; i < numGiocatori; i++) {     // creazione giocatori
        inserisciGiocatore(creaGiocatore());
        }


        while (partitaConclusa() == 0) {                
            int temp;
            // genera un giocatore non turnato
            for(int i = 0; i < numGiocatori; i++) {
                giocaTurno(ptrGiocatoreNumero(i));
                if (i == numGiocatori) 
                {i = -1;}
            }
        }

        
        return;
    } 

// #endregion




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
