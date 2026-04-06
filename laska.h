/*
 * @mainpage
 * Developers & Mainteners
 *  Gruppo 38 IaP:
 *   Leonardo Sartori @email 886069@stud.unive.it
 *   Mattia Dei Rossi @email 885768@stud.unive.it
 *   Agostino Calabrò @email 974519@stud.unive.it
 *
 * Descrizione del progetto miniLaska
 *  Abbiamo chiamato mini-Laska una variante del gioco originale @site http://www.lasca.org/.
 *  Rispetto al gioco originale miniLaska prevede le seguenti limitazioni:
 *   • si può mangiare/conquistare una sola volta per mossa
 *   • le torri possono essere alte al massimo 3 pedine, superato questo limite, la pedina più in basso viene rimossa dalla scacchiera
 * Tutti i dettagli del gioco sono disponibli qui: @site http://www.lasca.org/.
*/

/**
 * @file laska.h
 * @authors Leonardo Sartori, Mattia Dei Rossi, Agostino Calabrò
 * @date 19 Gen 2021
 * @brief Descrizioni delle funzioni utilizzate per costruire il gioco miniLaska
 *
 * @see index.html
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#ifndef GRUPPO_38_LASKA_LASKA_H
#define GRUPPO_38_LASKA_LASKA_H

/**
 * Dimensioni effettive della scacchiera
 */
#define N_ELEMENT (7)

/**
 * Dimensione standard di visualizzazione della casella
 */
#define LEN (3)

/**
 *Carattere vuoto (' ') - Spazio legale della scacchiera dove si possono posizionare le pedine
 */
const char EMPTY;

/**
 * Carattere (\270) - Area non legale della scacchiera
 */
const char OUTCAST;

/**
 * Simboli promossi e non, squadra superiore
 */
char up[2];

/**
 * Simboli promossi e non, squadra inferiore
 */
char down[2];

/**
 * Array di frasi che commentano la mossa dell'utente
 */
char* Frase[5];

/**
 * Distanze possibili delle pedine
 */
short int mosse[4];

/**
 * Coordinate x,y
 */
typedef struct coord {
    short int pos_x; /**< Coordinata x */
    short int pos_y; /**< Coordinata y */
} coord_t;

/**
 * Mossa e relativo tipo
 */
typedef struct mossa_con_tipo {
    coord_t mossa; /**< Mossa da effettuare */
    short int mossa_type;  /**< Tipo di mossa da effettuare*/
} mossa_con_tipo_t;

/**
 * Pedina
 */
typedef
struct pedina{
    coord_t posizione; /**< Origine della pedina */
    char colore; /**< Squadra della pedina */
    bool promozione; /**< Promozione */
    bool conquistato; /**< Conquistato */
    mossa_con_tipo_t database[8]; /**< Database mosse possibili */
    short int mosse_possibili; /**<  Numero mosse possibili */
    short int mosse_mangia_possibili; /**< Mosse per conquistare altre pedine possibili */
    short int score; /**< Punteggio */
} ped_t;

/**
 * Controlla se il numero "risposta" è corretto o meno
 * @param n_risposte - Risposte massime possibili
 * @param risposta - Risposta data
 * @return  - True se  0 <= risposta < n_risposte
 */
short int controllo_risposta(short int n_risposte, short int risposta);

/**
 * Restituisce la riga corrispondente alla sottocasella della coordinata y della pedina selezionata
 * @param y - Coordinata della pedina y
 * @param sottocasella - Sottocasella della pedina
 * @return - Riga corrispondente
 */
short int dimmi_riga(short int y, short int sottocasella);

/**
 * Restituisce la quantità (numerica) tra due char
 * @param a - Char
 * @param b - Char
 * @return Differenza in short int tra i due char
 */
short int differenza_tra_char(char a, char b);

/**
 * Scrive tanti caratteri vuoti quanti "len" in verticale
 * @param len - Numero di caratteri vuoti
 */
void offset_verticale_f(short int len);

/**
 * Scrive tanti caratteri vuoti quanti "len" in orizzontale
 * @param len - Numero di caratteri vuoti
 */
void offset_orizzontale_f(short int len);

/**
 * Scrive una la prima o l'ultima riga vuota
 * @param len - Numero di caratteri vuoti
 */
void prima_ultima_riga(short int len);

/**
 * Scrive una riga vuota
 * @param len - Lunghezza riga, numero di caratteri vuoti
 */
void riga_vuota(short int len);

/**
 * Presentazione del menù
 * @param offset_o - Offset orizzontale
 * @param offset_v - Offset verticale
 * @param gioco - Tipo di gioco
 */
void presentazione_menu(short int offset_o, short int offset_v, short int* gioco);

/**
 * Posizionamento iniziale delle due squadre sulla scacchiera
 * @param chessboard - Scacchiera, array bidimensionale ( matrice)
 * @param squadra1 - Array di pedine
 * @param squadra2 - Array di pedine
 */
void posizionamento_iniziale(char (*chessboard)[N_ELEMENT], ped_t *squadra1, ped_t *squadra2);

/**
 * Restituisci l'indice della pedina nella squadra
 * @param squadra - Array di pedine
 * @param casella_y - Coordinata y della casella
 * @param casella_x - Coordinata x della casella
 * @param sottocasella - Sottocasella relativa alla pedina indicata (posizione nella torre di pedine)
 * @return - Indice della pedina nella squadra
 */
short int dimmi_come_si_chiama(ped_t* squadra, short int casella_y, short int casella_x, short int sottocasella);

/**
 * Stapa guida
 * @param ffset_o - Offset orizzontale
 * @param offset_v - Offset verticale
 * @param gioco - Tipo di gioco
 */
void come_si_gioca(short int offset_o, short int offset_v, short int *gioco);

/**
 * Ritorna il numero di pedine del gioco
 * @param n - N_colonne
 * @return - Numero di pedine che servono ad una squadra
 */
short int calcola_n_pedine(short int n);

/**
 * Funzione ausiliaria che stampa un simbolo (string) del colore scelto (color)
 * @param string - Simbolo da stampare
 * @param color - Colore di stampa
 */
void printer_color(char* string, short int color);

/**
 * Funzione che si occupa di gestire la visualizzazione a schermo della scacchiera
 * @param chessboard - Puntatore all'array bi-dimensionale della scacchiera
 * @param row - Numero righe
 * @param col - Numero colonne
 * @param length - Larghezza di visualizzazione della pedina
 * @param offset_v - Distanza schermo dall'alto al basso
 * @param offset_o - Distanza schermo da sinistra a destra
 * @param c1 - Pedina squadra 1
 * @param c2 - Pedina squadra 2
 * @param znl - Zona non legale della scacchiera
 */
void printer_che(char (*chessboard)[N_ELEMENT], short int row, short int col, short int length, short int offset_v, short int offset_o, short int c1, short int c2, short int znl);

/**
 * Verifica qual è la sottocasella più in alto della pedina
 * @param chessboard - Puntatore all'array bi-dimensionale della scacchiera
 * @param pedina - Area che contiene le sottocaselle
 * @param turno - Giocatore che muove
 * @return - Altezza pedina
 */
short int verified_ped(char (*chessboard)[N_ELEMENT], coord_t pedina, const char* turno);

/**
 * Indica il tipo di mossa che sta per essere eseguita
 * @param pedina_y - Coordinata y della pedina
 * @param pedina_x - Coordinata x della pedina
 * @param mossa_y - Coordinata y della mossa
 * @param mossa_x - Coordinate x della mossa
 * @return - Near, mangia, zero, altrimenti verifica se mossa non valida
 */
short int mossa_type(short int pedina_y, short int pedina_x, short int mossa_y, short int mossa_x);

/**
 * Indica se la mossa viene eseguita verso l'alto o verso il basso
 * @param pedina_y - Altezza pedina
 * @param mossa_y - Altezza mossa
 * @return - Direzione mossa (1:verso l'alto, -1: verso il basso)
 */
short int verso(short int pedina_y, short int mossa_y);

/**
 * indica le coordinate della casella media fra due date in input
 * @param pedina - Coordinate della pedina
 * @param mossa - Coordinate della mossa
 * @return - Casella media
 */
short int coordinata_media(short int pedina, short int mossa);

/**
 * funzione ausiliaria che modifica le coordinate di una precisa pedina data la sua posizione
 * @param squadra_a - Squadra a cui appartiene la pedina
 * @param casella_y - Posizione di destinazione
 * @param casella_x - Posizione di destinazione
 * @param casella_pedina_y - Posizione di partenza
 * @param casella_pedina_x - Posizione di partenza
 * @param sottocasella_pedina - Sottocasella di partenza
 * @param sottocasella_mossa - Sottocasella di destinazione
 */
void modifica_pos_y_e_pos_x(ped_t* squadra_a, short int casella_y, short int casella_x, short int casella_pedina_y, short int casella_pedina_x, short int sottocasella_pedina, short int sottocasella_mossa);

/**
 * Dato il turno di un giocatore, ritorna quello opposto
 * @param turno - Giocatore attuale
 * @return - Turno prossimo giocatore
 */
char* dimmi_turno_opposto(const char* turno);

/**
 * Funzione ausiliaria che va a modificare il colore della squadra nella scacchiera
 * @param chessboard - Puntatore all'array bi-dimensionale della scacchiera
 * @param squadra - Lista delle pedine della squadra
 * @param casella_y - Coordinata y della casella
 * @param casella_x - Coordinata x della casella
 * @param sottocasella - Altezza della casella
 * @param turno - Turno attuale
 */
void modifica_colore_chessboard(char (*chessboard)[N_ELEMENT], ped_t* squadra, short int casella_y, short int casella_x, short int sottocasella, const char* turno);

/**
 * Si occupa di promuovere la pedina, possibile quindi muoversi in tutte le direzioni
 * @param chessboard - Puntatore all'array bi-dimensionale della scacchiera
 * @param squadra - Lista delle pedine della squadra
 * @param turno - Turno attuale
 * @param mossa_y - Coordinata y della mossa
 * @param mossa_x - Coordinata x della mossa
 */
void promossa(char (*chessboard)[N_ELEMENT], ped_t* squadra, const char* turno, short int mossa_y, short int mossa_x);

/**
 * Cerca, modifica colore in chessboard, conquista  e spostamento posizione di una pedina
 * @param chessboard - Puntatore all'array bi-dimensionale della scacchiera
 * @param mossa - Coordinate destinazione
 * @param pedina - Coordinate pedina da muovere
 * @param turno - Turno attuale
 * @param turno_opposto - Prossimo turno
 * @param squadra_turno - Squadra del turno attuale
 * @param squadra_opposta - Squadra del prossimo turno
 * @param mossa_type - Tipo di mossa eseguita
 */
void mossa_f(char (*chessboard)[N_ELEMENT], coord_t mossa, coord_t pedina, char* turno, const char* turno_opposto, ped_t* squadra_turno, ped_t* squadra_opposta, short int mossa_type);

/**
 * Funzione ausiliaria che stampa la posizione delle pedine di una squadra
 * @param squadra - Puntatore all'array della squadra
 */
void print_posizioni_pedine(ped_t* squadra);

/**
 * Funzione che calcola le mosse possibili di una squadra
 * @param squadra - Puntatore all'array della squadra
 * @param mangia - 1 somma le mosse che mangiano, 0 altrimenti
 * @return - Somma delle mosse
 */
short int calcola_mosse_totali(ped_t* squadra, short int mangia);

/**
 * Controlla se la pedina può effettuare la mossa scelta
 * @param chessboard - Puntatore all'array bi-dimensionale della scacchiera
 * @param pedina - Puntatore ad una determinata Struct pedina
 * @param mossa - Coordinate di destinazione della pedina
 * @param turno - Puntatore all'array turno
 * @return - True se la pedina può effettuare la mossa, False altrimenti
 */
bool correct(char (*chessboard)[N_ELEMENT], ped_t* pedina, coord_t mossa, const char* turno);

/**
 * Funzione che verifica se le pedina di una squadra non hanno mosse legali a disposizioen
 * @param a - Mosse possibili squadra1
 * @param b - Mosse possibili squadra2
 * @return - 1 se gioco finito, altrimenti 0
 */
short int verifica_fine_gioco(short int a, short int b);

/**
 * La funzione popola l'array database di una pedina
 * @param chessboard - Puntatore all'array bi-dimensionale della scacchiera
 * @param squadra - Puntatore all'array della squadra.
 * @param pedina - Pedina i-esima dell'array squadra
 * @param turno - Puntatore all'array turno
 */
void verifica_mosse_possibili(char (*chessboard)[N_ELEMENT], ped_t *squadra, short int pedina, const char* turno);

/**
 * La funzione stampa le mosse possibili e il tipo di mossa di una pedina
 * @param squadra - Puntatore all'array della squadra.
 * @param pedina - Pedina i-esima dell'array squadra
 * @param non_disponibili - Consente di visualizzare anche le mosse non legali
 * @param offset_o - Offset orizziontale di stampa
 * @param mangia - 1 se la squadra ha pedine che possono conquistare pedine, 0 altrimenti
 */
void print_database(ped_t* squadra, short int pedina, short int non_disponibili, short int offset_o, bool mangia);

/**
 * La funzione cerca la miglior mossa di una pedina
 * @param squadra - Puntatore all'array della squadra.
 * @param pedina - Pedina i-esima dell'array squadra
 * @return - Restituisce una j-esima posizione dell'array del database della pedina
 */
short int strategia(ped_t* squadra, short int pedina);

/**
 * La funzione calcola lo score di una pedina in base alla posizione e il numero di mosse possibili della pedina.
 * @param squadra - Puntatore all'array della squadra.
 * @param pedina - Pedina i-esima dell'array squadra
 * @return Ritorna lo score della pedina
 */
short int calcola_score_pedina(ped_t* squadra, short int pedina);

/**
 * La funzione controlla la possibilità di mossa di una squadra
 * @param squadra - Puntatore all'array della squadra.
 * @return  - Restituisce 1 o 0
 */
short int ha_mosse_mangia(ped_t *squadra);

/**
 * La funzione scorre l'array di pedine di una squadra e cerca la pedina con lo score migliore, esclusa l'ultima pedina utilizzata
 * @param squadra - Puntatore all'array della squadra.
 * @param ultima_pedina - Puntatore all'ultima pedina utilizzata da quella squadra
 * @return - Restituisce una i pedina di una squadra
 */
short int calcola_priorita_pedina(ped_t* squadra, short int* ultima_pedina);

/**
 * La funzione stampa una frase casuale dall'array globale di frasi
 * @param offset_o - Offset orizziontale di stampa
 */
void frase(short int offset_o);

/**
 * La funzione stampa messaggi domanda/risposta restituendo il tipo di gioco
 * @param offset_o - Offset orizziontale di stampa
 * @return - Restituisce il tipo di gioco
 */
short int tipo_gioco(short int offset_o);

/**
 * La funzione stampa messaggi domanda/risposta modificando il contenuto della variabile colore
 * @param color - Puntatore alla variabile colore
 * @param offset_o - Offset orizziontale di stampa
 */
void scegli_colore(short int *color, short int offset_o);

/**
 * La funzione stampa messaggi domanda/risposta per definire le impostazioni di gioco
 * @param s1_color - Puntatore del colore della squadra1
 * @param s2_color - Puntatore del colore della squadra2
 * @param len - Puntatore della lunghezza della scacchiera
 * @param offset_o - Offset orizziontale di stampa
 */
void scegli_impostazioni(short int* s1_color, short int* s2_color, short int* len, short int offset_o);

/**
 * La funzione elimina dalla memoria la squadra presa come parametro
 * @param squadra - Puntatore all'array della squadra.
 */
void elimina_squadra(ped_t* squadra);

#endif //GRUPPO_38_LASKA_LASKA_H