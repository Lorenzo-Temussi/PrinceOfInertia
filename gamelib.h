// Dichiarazione delle funzioni da chiamare in main.c
//Funzions
typedef struct Stanza Stanza;
typedef struct Giocatore Giocatore;

int getRoomCount();
void generaSeed(int* seed);

void impostaGioco();
void gioca();
void crediti();
void terminaGioco();

void stampaStanza(Stanza* stanza, int showAll);
void printRoomType(Stanza* stanza);



// Definizione dei tipi necessari alla libreria

enum tipo_giocatore {
    PRINCIPE,
    DOPPELGANGER,
};

enum tipo_nemico {
    MELMA,
    SCHELETRO,
    GUARDIA,
    JAFFAR
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

    struct Stanza* porte [4]; //Ordine: dx, uw, sx, dw (come la circ. goniometrica)
};

struct Giocatore{
    char* nome;
    enum tipo_giocatore classe;
    struct Stanza* posizione;
    int maxHp;
    int currentHp;
    int atk;
    int def;

};

//Enemies

struct Enemy {
    enum tipo_nemico tipoNemico;
    int maxHp;
    int currentHp;
    int atk;
    int def;
};