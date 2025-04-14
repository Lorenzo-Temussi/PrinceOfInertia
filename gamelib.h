typedef struct Stanza Stanza;
typedef struct Giocatore Giocatore;
typedef struct Nemico Nemico;
typedef struct Punteggio Punteggio;


int riceviInputNumerico(int minimo, int massimo);

void inizializzaSeme();
extern void generaSeed();

void impostaGioco();

void gioca();

void inizializzaTabellonePunteggi();
void stampaTabellonePunteggi();

void crediti();

void terminaGioco();


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

enum tipo_nemico {
    NESSUN_NEMICO,
    SCHELETRO,
    GUARDIA,
    JAFFAR
};

struct Stanza {
    enum tipo_stanza tipoStanza;
    enum tipo_trabocchetto tipoTrabocchetto;
    enum tipo_tesoro tipoTesoro;

    Stanza* porte [4]; //Ordine: dx, uw, sx, dw (come la circ. goniometrica)
    int porteSegrete [4];
    char* direzionePorte [4];
    Stanza* successiva;
};

struct Giocatore{
    char* nome;
    enum tipo_giocatore classe;
    Stanza* posizione;
    int saluteMax;
    int saluteCorrente;
    int attacco;
    int difesa;

    int numEvadiTrabocchetto;
    int numFuga;

    Giocatore* successivo;
    int punteggio;

};



struct Nemico {
    
    int saluteMax;
    int saluteCorrente;
    int attacco;
    int difesa;
};

struct Punteggio {
    char* nome;
    int punteggio;  
};