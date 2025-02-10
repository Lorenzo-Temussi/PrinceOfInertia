// Dichiarazione delle funzioni da chiamare in main.c
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

    struct Stanza* stanzaSx;
    struct Stanza* stanzaDx;
    struct Stanza* stanzaSopra;
    struct Stanza* stanzaSotto;
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

struct gameConfig {};

//Funzions

int getRoomCount(struct Stanza** mappa);

void impostaGioco(struct Stanza** mappa);
void gioca();
void crediti();
void terminaGioco();

void stampaStanza(struct Stanza* stanza, int showAll);
void printRoomType(struct Stanza* stanza);

void writeToFile();
void Debug(struct Stanza* stanza);

//Enemies

struct Enemy {
    enum tipo_nemico tipoNemico;
    int maxHp;
    int currentHp;
    int atk;
    int def;
};