#include "gamelib.h"
#include <bits/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

//Funzioni Statiche

static void pausaEsecuzione();
static void muori(Giocatore* giocatore);
static void mostraPunteggio(Giocatore* giocatore);



Stanza* ptrPrimaStanza = NULL;
Stanza* ptrUltimaStanza = NULL;

Punteggio* tabellonePunteggi[5];

void inizializzaTabellonePunteggi() {
    for (int i = 0; i <5; i++) {
        tabellonePunteggi[i] =(Punteggio*)malloc(sizeof(Punteggio));
    }

    tabellonePunteggi[0]->nome = "Ali_Baba";
    tabellonePunteggi[0]->punteggio = 1000;

    tabellonePunteggi[1]->nome = "Aladdin";
    tabellonePunteggi[1]->punteggio = 900;

    tabellonePunteggi[2]->nome = "Corto_Maltese";
    tabellonePunteggi[2]->punteggio = 800;

    tabellonePunteggi[3]->nome = "Papa_Francesco";
    tabellonePunteggi[3]->punteggio = 700;

    tabellonePunteggi[4]->nome = "Mister_Rogers";
    tabellonePunteggi[4]->punteggio = 400;
    
}

static void ordinaTabellonePunteggi() {
    for (int i = 0; i < 5; i ++) {
        for (int j = 1; j < 5 - i; j++) {
         if((tabellonePunteggi[i]->punteggio < (tabellonePunteggi[i + j]->punteggio))) {
            Punteggio* temp = tabellonePunteggi[i + j];
            tabellonePunteggi[i + j] = tabellonePunteggi[i];
            tabellonePunteggi[i] = temp;
            }
            
        }
    }
}

static int valutaPunteggio (Giocatore* giocatore) {
    if (giocatore->punteggio > tabellonePunteggi[4]->punteggio) {
        tabellonePunteggi[4]->nome = giocatore->nome;
        tabellonePunteggi[4]->punteggio = giocatore->punteggio;
        ordinaTabellonePunteggi();
        return 1;
    } else {
        return 0;
    }
}

void stampaTabellonePunteggi () {
    printf("****SALA DEI RECORD****\n\n");
    for (int i = 0; i < 5; i++) {
        printf("%d): %s ............. %d\n", i + 1, tabellonePunteggi[i]->nome, tabellonePunteggi[i]->punteggio);
    }
    printf("\n");
    pausaEsecuzione();
}


int JaffarSconfitto = 0;

int seme = 0;
int* semePtr = &seme;


    static void riceviInputStringa(char* buffer, int dimensione) {
        if (fgets(buffer, dimensione, stdin) && !(strchr(buffer, '\n'))) {
            char c;
            while((c = getchar()) != '\n' && c != EOF);
        }
    }

    int riceviInputNumerico (int minimo, int massimo) {
        int temp = -1;
        char buffer [8];
        riceviInputStringa(buffer, 8);
        if(!sscanf(buffer, "%d", &temp)) {
            return -1;
        }

        if (temp < minimo || temp > massimo) {
            return -1;
        }

        return temp;
    }

// SEZIONE 1 - IMPOSTA

    void inizializzaSeme() {
        time_t t;
        unsigned int value = (unsigned int)time(&t);
        *semePtr = value % 1000000;
        
        srand(*semePtr);
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
            input = riceviInputNumerico(0, 999999);
            if (input == -1) {
                continue;
            } 

            *semePtr = input;
            srand(*semePtr);
            printf("Seme impostato: %d.\n", *semePtr);
            break;
        }
        return;
    }

    static void modificaSemeSelect() {
        int temp = -1;
        while(1) {
            printf(" 1) Genera Seed casuale\n 2) Seleziona Seed\n 0) Indietro\n");
            temp = riceviInputNumerico(0, 2);
            switch(temp) {
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
                    break;
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

    /*static void aggiornaUltimaStanza() { //COMPLETA - LL
        struct Stanza* stanzaCorrente = ptrPrimaStanza;
        if (stanzaCorrente == NULL)  {
            ptrUltimaStanza = NULL;
            return;
        }

        while (stanzaCorrente->successiva != NULL) {       
            stanzaCorrente = stanzaCorrente->successiva;     
        }
        
        ptrUltimaStanza = stanzaCorrente;
    }*/

    static int selezionaPorta() {
        while(1) { // selezione porta
        
            printf("Da quale porta si accede alla stanza?:\n"
            " 0) DESTRA\n 1) AVANTI\n 2) SINISTRA\n 3) INDIETRO\n");
            int porta;
            porta = riceviInputNumerico(0, 3);

            

            if (porta != -1) {
                // do nun
            } else {
                printf("Input non valido.\n");
                continue;
            } 

            if (getRoomCount()) {

                if (ptrUltimaStanza->porte[(porta + 2)%4] != NULL) {
                    printf("La porta corrispondente è già in uso.\n");
                    continue;
                }
            }   
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
            tipoStanza = riceviInputNumerico(0, 9);
            if (tipoStanza != -1) {
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

            trabocchetto = riceviInputNumerico(0, 4);
            if (trabocchetto != -1) {
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

            tesoro = riceviInputNumerico(0, 5);
            if (tesoro != -1) {
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
        Stanza* temp = (Stanza*)malloc(sizeof(Stanza));
        
        temp->porte[0] = NULL;
        temp->porte[1] = NULL;
        temp->porte[2] = NULL;
        temp->porte[3] = NULL;
        temp->successiva = NULL;

        temp->porteSegrete[0] = 0;
        temp->porteSegrete[1] = 0;
        temp->porteSegrete[2] = 0;
        temp->porteSegrete[3] = 0;

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

        stanza->porte[indicePorta] = ptrUltimaStanza;
        
        ptrUltimaStanza->porte[(indicePorta + 2) %4] = stanza;
        ptrUltimaStanza->porteSegrete[(indicePorta + 2) %4] = -1;
        ptrUltimaStanza->successiva = stanza;
    }

    static void spingiStanza(Stanza* stanza) {
        if(!getRoomCount()) { 
            ptrPrimaStanza = stanza;
            ptrUltimaStanza = stanza;
        } else {
            ptrUltimaStanza = stanza;
        }
    }

    static void creaStanzaMain() {

        //DEBUG struct Stanza* porte [4] = {NULL, NULL, NULL, NULL}; 
        
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
        printf("La stanza è stata cancellata con successo!\n");
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
        int temp = -1;

        temp = riceviInputNumerico(0, 1);
        if (temp != -1) {
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
        
        while(cancellaStanza()) {
            continue;
        }

        int ultimaPorta = rand() %4;
        for (int i = 0; i < 15; i++) {
                    
            //DEBUG struct Stanza* porte[4] = {NULL, NULL, NULL, NULL};

            int tipoStanza = generaRandomStanza();

            int tipoTrabocchetto = generaRandomTrabocchetto();
            
            int tipoTesoro = generaRandomTesoro();

            ultimaPorta = generaRandomPorte(ultimaPorta);        

            Stanza* nuovaStanza = creaStanza (tipoStanza, tipoTrabocchetto, tipoTesoro);
            connettiStanza(nuovaStanza, ultimaPorta);
            spingiStanza(nuovaStanza);
        }
        printf("Sono state create 15 stanze casuali.\n");
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
        int temp = -1;
        do {
            printf("Seleziona opzione 0-5:\n 0) Modifica seme\n 1) Inserisci\n 2) Cancella\n 3) Stampa\n 4) Generazione casuale\n 5) Indietro\n");
            temp = riceviInputNumerico(0, 5);
            
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
                    printf("Input is invalid.\n");
                    continue;
                }                 
        }
        while (1);
    }

// SEZIONE 2 - GIOCA

    static int inserisciNumeroGiocatori() {
        int playerNum;
        do {
            printf("Quanti giocatori ci sono? Max 4.\n");
            playerNum = riceviInputNumerico(1, 4);
            if (playerNum != -1) {
                    printf("Preparo il gioco per %d giocatori.\n", playerNum);   
                    return playerNum;      
            } else {
                printf("Input non valido.\n");
            }  
            while (getchar() != '\n');
        } while(1);
    }

    static Giocatore* creaGiocatore() {
        //printf("Crea giocatore chiamata\n");
        Giocatore* giocatore = (Giocatore*)malloc(sizeof(Giocatore));


        giocatore->attacco = 1;
        giocatore->classe = -1;
        giocatore->difesa = 1;
        giocatore->nome = "Giocatore X";
        giocatore->posizione = NULL;
        giocatore->saluteMax = 100;
        giocatore->saluteCorrente = 100;
        giocatore->numFuga = 2;
        giocatore->numEvadiTrabocchetto = 0;

        giocatore->successivo = NULL;


        return giocatore;
    }

    static Giocatore* popolaGiocatore(Giocatore* giocatore, int indice) {
        int temp;

        while(giocatore->classe == -1) {
            printf("\n\nSeleziona la classe, giocatore %d:\n 0) PRINCIPE\n 1) DOPPELGANGER\n", indice);
            if(scanf("%d", &temp) != 0 && temp >= 0 && temp <= 1) {
                giocatore->classe = temp;
                break;
            } else {
                printf("Input non valido.\n");
            }  
            while (getchar() != '\n');
        
        }
        

        if(giocatore->classe == PRINCIPE) {
            printf("\nIl giocatore %d è il PRINCIPE\n", indice);
            giocatore->numEvadiTrabocchetto = 1;
            giocatore->numFuga = 1;
        } else {
            printf("\nIl giocatore %d è un DOPPELGANGER\n", indice);
        }

        
        char inputName[100];
        printf("Inserisci nome:\n ");
        while (1) {
            riceviInputStringa(inputName, 99);
        
            size_t len = strlen(inputName);
        
            if (len == 0) {
                printf("L'input non contiene assolutamente nulla(molto strano...)\nInserisci nome valido:\n");
                continue;
            }
        
            if (inputName[len - 1] == '\n') {
                inputName[len - 1] = '\0';
                len--;
            }
        
            if (len == 0) {
                
                continue;
            }
        
            giocatore->nome = malloc(len + 1);
            if (!giocatore->nome) {
                printf("Errore allocazione memoria.\n");
                exit(1);
            }
        
            strcpy(giocatore->nome, inputName);
            break;
        }         
        
        //strcpy(giocatore->nome, inputName);  // Copy the string into the allocated memory
        giocatore->posizione = ptrPrimaStanza;

        giocatore->attacco = 2;
        giocatore->difesa = 2;
        
        return giocatore;
    }
        
    static void innescaTrabocchetto(Giocatore* giocatore, Stanza* stanza) {
        if ((giocatore->numEvadiTrabocchetto > 0) && (stanza->tipoTrabocchetto > 0)) {
            printf("I sensi di persiano di %s lo avvisano che il pericolo è imminente!\n"
            "Con un salto, una schivata e un ruzzolone, %s evade la trappola in questa stanza!\n",
            giocatore->nome, giocatore->nome);
            giocatore->numEvadiTrabocchetto --;
            giocatore->punteggio += 50;
            return;
        }
        switch (stanza->tipoTrabocchetto) {
            case 0:
                printf("La stanza non contiene trappole, trabocchetti o tranelli di sorta.\n");
                break;
            case 1:
                printf("Un pianoforte cade dall'alto sulla testa di %s, spaccandone varie ossa\nPerde 2 PS.\n", giocatore->nome);
                giocatore->saluteCorrente -=2;
                giocatore->punteggio += 200;
                break;
            case 2:
                printf("Numerose lame vengono lanciate da apposite fessure nei muri, e si conficcano nelle carni di %s\nPerde 1 PS.\n", giocatore->nome);
                giocatore->saluteCorrente -= 1;
                giocatore->punteggio += 70;
                break;
            case 3:
                printf("L'ignaro/a %s, scivola sul pavimento saponatissimo e sbatte lo zigomo su un tavolo\nNon riesce più a rotolare come prima.\n", giocatore->nome);
                if (giocatore->numEvadiTrabocchetto > 0) {
                    giocatore->numEvadiTrabocchetto -= 1;
                    }
                    
                break;
            case 4:
                printf("Il pavimento si apre e %s cade in una botola piena di pezzi lego\nNon riesce più a correre come prima.\n", giocatore->nome);
                if (giocatore->numFuga > 0) {
                    giocatore->numFuga -= 1;
                    }
                break;
            default:
                printf("Non so come hai fatto ma sei riuscito a far buggare una variabile dura.\n");
                break;
        }
        if (giocatore->saluteCorrente <= 0) {
            muori(giocatore);
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
        if(giocatore->posizione->successiva == NULL) {
            printf("Questa è l'ultima stanza, non è possibile avanzare ancora.\n");
            return;
        }

        printf("%s si muove verso ", giocatore->nome);
        stampaTipoStanza(giocatore->posizione->successiva);

        giocatore->posizione = giocatore->posizione->successiva;
        giocatore->punteggio += 40;
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
                    printf("In questa stanza sembra non esserci nessuno\n");
                    return NULL;
            }
            return temp;
        }

        static void vinciCombattimento(Giocatore* giocatore, int nemico) {
            giocatore->punteggio += nemico * 100;
            if(nemico == 3) {
                JaffarSconfitto = 1;
                printf("Il perfido Jaffar si accascia a terra, la sua pelle si tramuta in sabbia e le sue ossa ESPLODONO."
                "Il suo pappagallo, travolto dall'esplosione, diventa un pacchetto da sei pezzi di chicken nuggets, che "
                "%s e la principessa mangiano sulla via per casa.\n", giocatore->nome);
                pausaEsecuzione();
                return;
            }

            if(giocatore->saluteCorrente < giocatore->saluteMax) {
                giocatore->saluteCorrente++;
                printf("Ti riposi dopo la battaglia, e ti senti più in salute.\n");
            } else  {
            printf("Vittoria perfetta!\n");
            }
            pausaEsecuzione();
            return;
        } 
        
        static void muori (Giocatore* giocatore) {
            printf("Sei morto!\n");
            giocatore->saluteCorrente = 0;
            pausaEsecuzione();
            return;
        }

        static void combatti(Giocatore* giocatore, int indiceNemico) {
            printf("Inzia la battaglia!\n");
            Nemico* nemico = inizializzaNemico(indiceNemico);
            while(giocatore->saluteCorrente > 0) { 
                if (rand()%2) {
                    printf("%s attacca! ", giocatore->nome);
                    nemico->saluteCorrente -= infliggiDanni(giocatore->attacco, nemico->difesa);
                    printf("Salute nemico: %d\n", nemico->saluteCorrente);
                    
                    if(nemico->saluteCorrente <= 0) {
                        vinciCombattimento(giocatore, indiceNemico);
                        free(nemico);
                        nemico = NULL;
                        return;
                    }

                    printf("Il nemico attacca! ");
                    giocatore->saluteCorrente -= infliggiDanni(nemico->attacco, giocatore->difesa);
                    printf("Salute %s: %d\n", giocatore->nome, giocatore->saluteCorrente);
                    
                    if (giocatore->saluteCorrente <= 0) {
                        muori(giocatore);
                        free(nemico);
                        nemico = NULL;
                        return;
                    }
                    pausaEsecuzione();
                } else {
                    printf("Il nemico attacca! ");
                    giocatore->saluteCorrente -= infliggiDanni(nemico->attacco, giocatore->difesa);
                    printf("Salute %s: %d\n", giocatore->nome, giocatore->saluteCorrente);

                    if (giocatore->saluteCorrente <= 0) {
                        muori(giocatore);
                        free(nemico);
                        nemico = NULL;
                        return;
                    }

                    printf("%s attacca! ", giocatore->nome);
                    nemico->saluteCorrente -= infliggiDanni(giocatore->attacco, nemico->difesa);
                    printf("Salute nemico: %d\n", nemico->saluteCorrente);

                    if(nemico->saluteCorrente <= 0) {
                        vinciCombattimento(giocatore, indiceNemico);
                        free(nemico);
                        nemico = NULL;
                        return;
                    }
                    pausaEsecuzione();                    
                }
            }  
        }

    // fine blocco

    static void scappa(Giocatore* giocatore) {
        if (giocatore->numFuga > 0) {
            giocatore->numFuga --;
        } else {
            printf("Non riesci a correre ancora, devi lottare!\n");
        }
        for (int i = 0; i <= 3; i++) {
            if (giocatore->posizione->porte[i] && giocatore->posizione->porte[i] != giocatore->posizione->successiva) {
                giocatore->posizione = giocatore->posizione->porte[i];
                break;
            }
        }
        printf("Riesci a far perdere le tue tracce tornando nella stanza precedente.\n"
        "Il nemico insegue una falsa pista nelle profondità del palazzo.\n");
        return;

    }

    static void stampaGiocatore(Giocatore* giocatore) {
        printf("***************************\n");
        printf("NOME GIOCATORE: %s\n\n", giocatore->nome);

        printf("CLASSE: %s\n", giocatore->classe?"Doppelganger":"Principe");

        printf("SALUTE: %d/%d\n", giocatore->saluteCorrente, giocatore->saluteMax);

        printf("ATTACCO: %d\n", giocatore->attacco);
        printf("DIFESA: %d\n", giocatore->difesa);

        printf("%s può ancora fuggire da %d nemici e schivare %d trabocchetti.\n", giocatore->nome, 
        giocatore->numFuga, giocatore->numEvadiTrabocchetto);
        printf("***************************\n");
        return;
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
                giocatore->punteggio += 50;
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

    static Stanza* creaStanzaSegreta() {
        return creaStanza(generaRandomStanza(), generaRandomTrabocchetto(), generaRandomTesoro());
    }

    static int cercaPortaSegreta(Giocatore* giocatore) {
        int scan = -1;
        int stanzeSegretePotenziali = 4;

        for(int i = 0; i <= 3; i++) {
            if(giocatore->posizione->porteSegrete[i] != 0) {
                stanzeSegretePotenziali --;
            }
        }

        if(stanzeSegretePotenziali == 0) {
            printf("Hai cercato ovunque, qui non ci sono porte segrete da nessuna parte.\n");
            return -1;
        }
        
        while(scan < 0 || scan > 3) {
            for (int i = 0; i <= 3; i++) {
                if (giocatore->posizione->porteSegrete[i] == 0) {
                    printf(" %d) Cerca stanza segreta a %s.\n", i, giocatore->posizione->direzionePorte[i]);
                }
            }

            scan = riceviInputNumerico(0, 3);
            if (scan != -1 && (giocatore->posizione->porteSegrete[scan] == 0)) {
                break;
            }
        }

        

        switch (stanzeSegretePotenziali) {
            case 3:
                if (!(rand()%100 < 33)) {
                    printf("Dopo un'attenta investigazione, concludi che non c'è alcuna stanza segreta verso %s.\n", giocatore->posizione->direzionePorte[scan]);
                    giocatore->posizione->porteSegrete[scan] = -1;
                    return scan;
                }
                break;
            case 2:
                if (!(rand()%100 < 20)) {
                    printf("Dopo un'attenta investigazione, concludi che non c'è alcuna stanza segreta verso %s.\n", giocatore->posizione->direzionePorte[scan]);
                    giocatore->posizione->porteSegrete[scan] = -1;                    
                    return scan;
                }
                break;
            case 1:
                if (!(rand()%100 < 15)) {
                    printf("Dopo un'attenta investigazione, concludi che non c'è alcuna stanza segreta verso %s.\n", giocatore->posizione->direzionePorte[scan]);
                    giocatore->posizione->porteSegrete[scan] = -1;                    
                    return scan;
                }
                break;
            default:
                printf("Non ci sono altre stanze segrete...\n");
                return -1;
        }

        //TODO this doesnt run for unknown reasons
        Stanza* stanzaSegreta = creaStanzaSegreta();
        Stanza* prev = giocatore->posizione;

        printf("%s esplora la stanza segreta.\n", giocatore->nome);
        giocatore->posizione = stanzaSegreta;
        innescaTrabocchetto(giocatore,  stanzaSegreta);
        prendiTesoro(giocatore);

        giocatore->posizione = prev;
        giocatore->posizione->porteSegrete[scan] = 1;
        return scan;

    }

    static void giocaTurno(Giocatore* giocatore) {
        
        int choice = -1;
        int numAvanza = 1;
        int indiceNemico = 0; 

        while(giocatore->saluteCorrente > 0 && !JaffarSconfitto) {

            printf("scegli un'azione %s:\n 1) Avanza!\n 2) Combatti\n 3) Scappa\n"
            " 4) Stampa Giocatore\n 5) Stampa Zona\n 6) Prendi Tesoro\n"
            " 7) Cerca Porta Segreta\n 8) Passa Turno\n", giocatore->nome);
            choice = riceviInputNumerico(1, 8);
            switch (choice) {
                case 1: 
                    if(numAvanza > 0) {
                        printf("%d\n", numAvanza);
                        numAvanza = 0;
                        avanza(giocatore);
                        innescaTrabocchetto(giocatore, giocatore->posizione);
                        if(giocatore->posizione->successiva == NULL) {
                            printf("Nella stanza è presente la principessa, incatenata al muro!\n"
                            "%s si avvicina per liberarla, ma dalle ombre una risata pretenziosa annuncia la presenza di qualcuno...\n", giocatore->nome);
                            indiceNemico = 3;
                            break;
                        }
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
                    if(!indiceNemico) {
                        printf("Una paura inspiegabile ti filtra nelle ossa, vuoi fuggire!\n"
                        "Ma ti riprendi in tempo: nella stanza con te non c'è nessuno...\n");
                        break;
                    }
                    scappa(giocatore);
                    indiceNemico = 0;
                    break;
                case 4: 
                    stampaGiocatore(giocatore);
                    break;
                case 5:
                    stampaStanza(giocatore->posizione, 0);
                    break;
                case 6:
                    if (!indiceNemico) {
                        prendiTesoro(giocatore);
                    } else {
                        printf("Non è il momento di saccheggiare il palazzo!\n");
                    }
                    break;
                case 7:
                {
                    int temp = -1;
                    if (numAvanza <= 0) {
                        printf("Non puoi trovare stanze segrete senza i piedi!\n");
                        break;
                        }
                    temp = cercaPortaSegreta(giocatore);
                    if (temp < 0 || temp >= 4) {
                        break;
                    } else {
                        numAvanza --;
                        for(int i = 0; i <= 4; i++) {
                            if (giocatore->posizione->porteSegrete[i] == 0) {
                                break;
                            }
                        }
                    }
                    break;
                }
                case 8: 
                    if (!indiceNemico) {
                        printf("%s conclude il suo turno.\n", giocatore->nome);
                        return;
                    } else {
                        printf("Un nemico ti sbarra la strada.\n");
                        break;
                    }
                default: 
                    printf("Opzione non valida.\n");
                    break;
                }
            }
        }
    
    void gioca() {

        if(getRoomCount() < 15) {
            printf("Imposta la mappa (15 stanze) prima di iniziare un round!\n");
            return;
        }

        JaffarSconfitto = 0;
        int numGiocatori = inserisciNumeroGiocatori();  //selezione num. giocatori
        Giocatore* listaGiocatori[numGiocatori];
        int ordineGiocatori[numGiocatori];
        int principeSelezionato = 0;

        for(int i = 0; i < numGiocatori; i++) {     // creazione giocatori
        listaGiocatori[i] = creaGiocatore();
        if (principeSelezionato) {
            listaGiocatori[i]->classe = DOPPELGANGER;
        } else if (!(principeSelezionato) && (i == (numGiocatori - 1))) {
            listaGiocatori[i]->classe = PRINCIPE;
        }

        listaGiocatori[i] = popolaGiocatore(listaGiocatori[i], i + 1);
        if (listaGiocatori[i]->classe == PRINCIPE) {
            principeSelezionato = 1;
        }
        ordineGiocatori[i] = i;
        }

        while (JaffarSconfitto == 0) { 
            
            for (int i = 0; i < 30; i++) {
                int rand1 = rand() % numGiocatori;
                int rand2 = rand() % numGiocatori;
                int var = 0;
                var = ordineGiocatori[rand1];
                ordineGiocatori[rand1] = ordineGiocatori[rand2];
                ordineGiocatori[rand2] = var;
            }


            for(int i = 0; i < numGiocatori; i++) {
                giocaTurno(listaGiocatori[ordineGiocatori[i]]);

                if (i == numGiocatori) {i = -1;}
            }
        }

        printf("PUNTEGGI: \n\n");

        for (int i = 0; i < numGiocatori; i++) {

            //here
            if(valutaPunteggio(listaGiocatori[i])) {
                printf("Nuovo Record!");
            }

            mostraPunteggio(listaGiocatori[i]);
        }
        pausaEsecuzione();

        return;
    } 

// #endregion

    void pausaEsecuzione() {
        printf("Premi Enter per continuare.\n");
        while(getchar() != '\n');
    }

    static void mostraPunteggio(Giocatore* giocatore) {
        printf("%s: .............. %d punti\n\n", giocatore->nome, giocatore->punteggio);
        return;
    }

// #endregion


void crediti() {
    printf("  Una produzione di: Il Tecnotrespolo con Corax Crowe\n"
    "  Lead Designer: Lorenzo Temussi\n  Lead Artist: Lorenzo Temussi\n  Level Designer: Lorenzo Temussi\n"
    "  Ringrazio un collega anonimo per il feedback eccezionale che ha offerto, e Luca, Luca, Antonio"
    "   , Bedetta e Tiziano per aver playtestato questo prodotto quando ancora era tutto tranne che completo.\n"
    "  Inoltre, Tommaso, per aver offerto feedback avanzato (insulti) sulla qualità del codice.\n"
    "\n  Liberamente ispirato da uno script di Francesco Santini e da un videogame di Jordan Mechner.\n\n");
}

void terminaGioco() {
    printf("Fine sessione\n");
    exit(0);
}


