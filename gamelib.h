// Dichiarazione delle funzioni da chiamare in main.c
//Funzions
typedef struct Stanza Stanza;
typedef struct Giocatore Giocatore;

void generaSeed(int* seed);

void impostaGioco();
void gioca();
void crediti();
void terminaGioco();


//Subroutines Inserisci

static void stampaStanze();
static void stampaStanza(Stanza* stanza, int showAll);
static void stampaTipoStanza(Stanza* stanza);
static void spingiStanza(Stanza* stanza);
static int getRoomCount();

// Definizione dei tipi necessari alla libreria

enum tipo_giocatore {
    PRINCIPE,
    DOPPELGANGER,
};

enum tipo_stanza {
    CORRIDOIO,
    SCALA,
    SALA_BANCHETTO,
    MAGAZZINO,
    POSTO_GUARDIA,
    PRIGIONE,
    ARMERIA,
    MOSCHEA,
    TORRE,
    BAGNI
};

enum tipo_trabocchetto {
    NESSUN_TRABOCCHETTO,
    PIANOFORTE,
    LAME,
    CADUTA,
    BURRONE
};

enum tipo_tesoro {
    NESSUN_TESORO,
    VELENO, 
    GUARIGIONE,
    AUMENTA_HP,
    SPADA_TAGLIENTE,
    SCUDO 
};

struct Stanza {
    enum tipo_stanza tipoStanza;
    enum tipo_trabocchetto tipoTrabocchetto;
    enum tipo_tesoro tipoTesoro;

    Stanza* porte [4]; //Ordine: dx, uw, sx, dw (come la circ. goniometrica)
    Stanza* successiva;
};

struct Giocatore{
    char* nome;
    enum tipo_giocatore classe;
    Stanza* posizione;
    int maxHp;
    int currentHp;
    int atk;
    int def;

};

//Enemies

struct Enemy {
    
    int maxHp;
    int currentHp;
    int atk;
    int def;
};