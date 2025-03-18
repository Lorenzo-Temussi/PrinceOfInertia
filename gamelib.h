// Dichiarazione delle funzioni da chiamare in main.c
//Funzions
typedef struct Stanza Stanza;
typedef struct Giocatore Giocatore;
typedef struct Nemico Nemico;
typedef struct Punteggio Punteggio;

//
// SEZIONE 1 - IMPOSTA
//
static void riceviInputStringa(char* buffer, int dimensione);
int riceviInputNumerico(int minimo, int massimo);

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
static Giocatore* popolaGiocatore(Giocatore* giocatore);
static void inserisciGiocatore(Giocatore* giocatore);
static void determinaOrdineTurno();
static Giocatore* ptrGiocatoreNumero(int indice);
static int ottieniNumeroGiocatori();

// Gioca_Turno

static void avanza(Giocatore* giocatore);
static void combatti(Giocatore* giocatore, int nemico);
static void vinciCombattimento(Giocatore* giocatore, int nemico);
static void muori(Giocatore* giocatore);
static void scappa(Giocatore* giocatore);
static void prendiTesoro(Giocatore* giocatore);
static int cercaPortaSegreta(Giocatore* giocatore);
static int passaTurno(int nemico);

static void innescaTrabocchetto(Giocatore* giocatore, Stanza* stanza);
static int generaRandomNemico();

//gameover
static void mostraPunteggio(Giocatore* giocatore);
static void pausaEsecuzione();

// Ipse
static void giocaTurno(Giocatore* giocatore);

// Finale 2

void gioca();

//
// SEZIONE 3 - CREDITI
//
void inizializzaTabellonePunteggi();
void stampaTabellonePunteggi();


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

//Enemies

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