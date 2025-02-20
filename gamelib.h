// Dichiarazione delle funzioni da chiamare in main.c
//Funzions
typedef struct Stanza Stanza;
typedef struct Giocatore Giocatore;

//
// SEZIONE 1 - IMPOSTA
//

void inizializzaSeme();
static void modificaSemeSelect();
extern void generaSeed();
static void selezionaSeed();

static int getRoomCount();
static void aggiornaUltimaStanza();

//1 - Crea
static int selezionaPorta();
static int selezionaTipoStanza();
static int selezionaTrabocchetto();
static int selezionaTesoro();

static Stanza* creaStanza(int tipoStanza, int tipo_trabocchetto, int tipo_tesoro);
static void connettiStanza(Stanza* stanza, int indicePorta);
static void spingiStanza(Stanza* stanza);

static void creaStanzaMain();

//2 - Cancella
static int cancellaStanza();
static void cancellaStanzaSelect();

//3 - Stampa
static void stampaTipoStanza(Stanza* stanza);
static void stampaStanza(Stanza* stanza, int showAll);
static void stampaStanze();

//4 - Genera
static int generaRandomPorte(int ultimaPorta);
static int generaRandomStanza();
static int generaRandomTrabocchetto();
static int generaRandomTesoro();
static void generaRandom();

//5 - Chiudi
static int chiudiMappa();

// Finale 1

void impostaGioco();

//
// SEZIONE 2 - GIOCA
//

// Inizializzazione

static int inserisciNumeroGiocatori();
static Giocatore* creaGiocatore();
static void popolaGiocatore(Giocatore* giocatore);
static void inserisciGiocatore(Giocatore* giocatore);
static void determinaOrdineTurno();
static Giocatore* ptrGiocatoreNumero(int indice);
static int ottieniNumeroGiocatori();

// Gioca_Turno

static void avanza(Giocatore* giocatore);
static void combatti();
static void scappa();
static void prendiTesoro();
static void cercaPortaSegreta();
static void passaTurno();

// Ipse
static void giocaTurno(Giocatore* giocatore);

// Finale 2

void gioca();

//
// SEZIONE 3 - CREDITI
//

void crediti();

//
// SEZIONE 4 - EXPORT/IMPORT
//

//
// SEZIONE 5 - TERMINA GIOCO
//
void terminaGioco();


//Subroutines Inserisci

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
    Giocatore* punteggio;

};

//Enemies

struct Enemy {
    
    int maxHp;
    int currentHp;
    int atk;
    int def;
};