#include "laska.h"

/**
 * @file laska.c
 * @authors Leonardo Sartori, Mattia Dei Rossi, Agostino Calabrò
 * @date 19 Gen 2021
 * @brief Implementazione delle funzioni utilizzate per costruire il gioco miniLaska
 *
 * @see index.html
 */

const char EMPTY = ' ';
const char OUTCAST = '#';
char up[2] = {'r', 'R'};
char down[2] = {'y', 'Y'};
char* Frase[5] = {"Bella mossa ...", "Mossa astuta ...", "Attento! Potrei vincere facilmente...", "Cosi' vinco facile...", "Non ti lascero' vincere facilmente"};
short int mosse[4] = {-2, -1 , 1, 2};

short int controllo_risposta(short int n_risposte, short int risposta) {
    if (risposta >= 0 && risposta < n_risposte) return 0;
    else return 1;
}

short int dimmi_riga(short int y, short int sottocasella) {
    return (3 * y) + sottocasella;
}

short int differenza_tra_char(char a, char b) {
    return (short int) a - (short int) b;
}

void offset_verticale_f(short int len) {
    int i;
    for (i = 0; i < len; ++i) {
        printf("\n");
    }
}

void offset_orizzontale_f(short int len) {
    int i;
    for (i = 0; i < len; ++i) {
        printf(" ");
    }
}

void prima_ultima_riga(short int len) {
    int i;
    for (i = 0; i < len; ++i) {
        printf("#");
    }
    printf("\n");
}

void riga_vuota(short int len) {
    int i;
    printf("#");
    for (i = 0; i < len - 2; ++i) {
        printf(" ");
    }
    printf("#");
    printf("\n");
}

void presentazione_menu(short int offset_o, short int offset_v, short int* gioco) {
    short int i, len = 22, controllo = 1;
    while (controllo) {
        offset_verticale_f(offset_v);
        offset_orizzontale_f(offset_o);
        prima_ultima_riga(len);
        for (i = 0; i < 2; ++i) {
            offset_orizzontale_f(offset_o);
            riga_vuota(len);
        }
        offset_orizzontale_f(offset_o);
        printf("# Benvenuti su Lasca #");
        printf("\n");
        for (i = 0; i < 2; ++i) {
            offset_orizzontale_f(offset_o);
            riga_vuota(len);
        }
        offset_orizzontale_f(offset_o);
        prima_ultima_riga(len);
        printf("\n\n");
        offset_orizzontale_f(offset_o);
        printf("[0]: Aiuto \n");
        offset_orizzontale_f(offset_o);
        printf("[1]: Gioca \n");
        offset_orizzontale_f(offset_o);
        scanf("%hd", gioco);
        controllo = controllo_risposta(2, *gioco);
    }
}

void posizionamento_iniziale(char (*chessboard)[N_ELEMENT], ped_t *squadra1, ped_t *squadra2) {
    short int r,c,count=0,count2=0;


    for (r = 0; r < 3*N_ELEMENT; r++)
    {
        /* scorri colonne */
        for (c = 0; c < N_ELEMENT; c++)
        {
            if ((r/3+c) % 2 == 0)
            {
                if (r%3 == 2)
                {
                    /* usa le pedine della squadra1 */
                    if(r<=dimmi_riga((N_ELEMENT/2 - 1), 2)){
                        chessboard[r][c] = squadra1[count].colore;
                        squadra1[count].posizione.pos_y = r;
                        squadra1[count].posizione.pos_x = c;
                        count++;
                    }
                    else if(r>=dimmi_riga((N_ELEMENT/2), 0) && r<=dimmi_riga((N_ELEMENT/2), 2)){
                        chessboard[r][c] = EMPTY;
                    }
                    /* usa le pedine della squadra2 */
                    if(r>=dimmi_riga((N_ELEMENT/2 + 1), 2)){
                        chessboard[r][c] = squadra2[count2].colore;
                        squadra2[count2].posizione.pos_y = r;
                        squadra2[count2].posizione.pos_x = c;
                        count2++;
                    }
                }
                else
                    chessboard[r][c] = EMPTY;
            } else
                chessboard[r][c] = OUTCAST;
        }
    }

}

short int dimmi_come_si_chiama(ped_t* squadra, short int casella_y, short int casella_x, short int sottocasella) {
    short int i;
    short int posizione_y = dimmi_riga(casella_y, sottocasella);
    for (i = 0; i < calcola_n_pedine(N_ELEMENT); ++i) {
        if (squadra[i].posizione.pos_y == posizione_y && squadra[i].posizione.pos_x == casella_x) {
            return i;
        }
    }
    return 0;
}

void come_si_gioca(short int offset_o, short int offset_v, short int *gioco) {
    printf("Come utilizzare il gioco : \n");
    printf("Ogni input dell'utente, a eccezione delle coordinate, deve essere uguale alle proposte visualizzate tra [] sullo schermo.\n");
    printf("A ogni input seguire le indicazioni visualizzate a schermo e per confermare premere 'invio'. \n");
    printf("Per le coordinate inserire la lettera seguita dallo 'spazio' e del numero della riga. Premere infine 'invio'.\n");
    printf("E' consigliato utilizzare lo schrmo intero. \n");
    system("pause");
    system("cls");
    presentazione_menu(offset_o, offset_v, gioco);
}

short int calcola_n_pedine(short int n) {
    return (n * (n - 1) + 2) / 4;
}


void printer_color(char* string, short int color) {
    printf("\033[0;3%hdm", color);
    printf("%s", string);
    printf("\033[0;37m");
}

void printer_che(char (*chessboard)[N_ELEMENT], short int row, short int col, short int length, short int offset_v, short int offset_o, short int c1, short int c2, short int znl) {
    short int i, j, k, act_row=0, l, m;

    system("cls");
    offset_verticale_f(offset_v);
    /* stampa colonne */
    offset_orizzontale_f(offset_o + 3 + length / 2);
    for (j = 0; j < col; j++) {
        printf("%c", 'a'+j);
        offset_orizzontale_f(length);
    }
    printf("\n");

    offset_orizzontale_f(offset_o + 2);
    for (l = 0; l < N_ELEMENT; ++l) {
        printf("|");
        for (m = 0; m < length; ++m) {
            printf("-");
        }
    }
    printf("|");
    printf("\n");

    /* scrorri righe */
    for (i = 0; i <row; i++) {
        /* stampa righe */
        offset_orizzontale_f(offset_o);
        if (i % 3 == 2) {
            printf("%d ",act_row++);
        } else
            printf("  ");
        /* scorri colonne */
        for (j = 0; j <= col; j++) {
            printf("|");
            if (j < col) {
                switch(chessboard[i][j])
                {
                    case '#':
                        for(k=0; k < length; k++)
                            printer_color("\260", znl);
                        break;
                    case 'r':
                        for(k=0; k < length; k++)
                            printer_color("\261", c1);
                        break;
                    case 'y':
                        for(k=0; k < length; k++)
                            printer_color("\261", c2);
                        break;
                    case 'R':
                        for(k=0; k < length; k++)
                            printer_color("\262", c1);
                        break;
                    case 'Y':
                        for(k=0; k < length; k++)
                            printer_color("\262", c2);
                        break;
                    case ' ':
                        for(k=0; k < length; k++)
                            printf(" ");
                        break;
                }
            }
        }
        /*offset_orizzontale_f(offset_o);*/
        printf("\n");
        if (i%3 == 2) {
            offset_orizzontale_f(offset_o + 2);
            for (l = 0; l < N_ELEMENT; ++l) {
                printf("|");
                for (m = 0; m < length; ++m) {
                    printf("-");
                }
            }
            printf("|");
            printf("\n");
        }
    }
}

short int verified_ped(char (*chessboard)[N_ELEMENT], coord_t pedina, const char* turno) {
    short int pedina_y = pedina.pos_y, pedina_x = pedina.pos_x;

    int act_row_ped = dimmi_riga(pedina_y, 2);
    int i;
    /*controlla da sopra la pedina*/
    /*controlla se � vuota*/
    for(i=2; i>=0; i--)
    {
        /*printf("casella %c riga %d e colonna  %d\n", chessboard[y_media-i][x_media], y_media-i, x_media);*/
        if (chessboard[act_row_ped-i][pedina_x] != EMPTY ) {
            /*printf("Non vuota...");*/
            /*controlla la squadra*/
            if (chessboard[act_row_ped-i][pedina_x] == turno[0] || chessboard[act_row_ped-i][pedina_x] == turno[1]) {
                return 2-i;
            }
            else {
                /*printf("Error, pedina della squadra avversaria\n");*/
                return -1;
            }
        }
        /*se � vuota, procedi con l'iterazione successiva*/
    }
    return -1;
}


short int mossa_type(short int pedina_y, short int pedina_x, short int mossa_y, short int mossa_x){
    /*printf("%hd - %hd, %hd - %hd \n", pedina_y, pedina_x, mossa_y, mossa_x);*/
    if((pedina_y+1 == mossa_y || pedina_y-1 == mossa_y) && (pedina_x+1 == mossa_x || pedina_x-1 == mossa_x)) {
        return 1; /*mossa_f sposta*/
    }
    else if((pedina_y+2 == mossa_y || pedina_y-2 == mossa_y) && (pedina_x+2 == mossa_x || pedina_x-2 == mossa_x)) {
        return 2; /*mossa_f mangia*/
    }
    else
        return 0; /*altrimenti*/
}

short int verso(short int pedina_y, short int mossa_y){
    if(pedina_y > mossa_y)
        return 1; /*dal basso verso l'alto*/
    else
        return -1; /*dall'alto verso il basso*/
}


short int coordinata_media(short int pedina, short int mossa) {
    return (pedina + mossa) / 2;
}


void modifica_pos_y_e_pos_x(ped_t* squadra_a, short int casella_y, short int casella_x, short int casella_pedina_y, short int casella_pedina_x, short int sottocasella_pedina, short int sottocasella_mossa) {
    short int a = dimmi_come_si_chiama(squadra_a, casella_pedina_y, casella_pedina_x, sottocasella_pedina);
    squadra_a[a].posizione.pos_y = dimmi_riga(casella_y, sottocasella_mossa);
    squadra_a[a].posizione.pos_x = casella_x;
}

char* dimmi_turno_opposto(const char* turno) {
    if (turno == up)
        return down;
    else return up;
}

void modifica_colore_chessboard(char (*chessboard)[N_ELEMENT], ped_t* squadra, short int casella_y, short int casella_x, short int sottocasella, const char* turno) {
    short int a = dimmi_come_si_chiama(squadra, casella_y, casella_x, sottocasella);
    casella_y = dimmi_riga(casella_y, sottocasella);
    if (squadra[a].promozione == 1) {
        squadra[a].colore = turno[1];
    }
    chessboard[casella_y][casella_x] = squadra[a].colore;
}

void promossa(char (*chessboard)[N_ELEMENT], ped_t* squadra, const char* turno, short int mossa_y, short int mossa_x) {
    short int i, a;
    for (i = 0; i < 3; ++i) {
        if (chessboard[dimmi_riga(mossa_y, i)][mossa_x] == turno[0]) {
            a = dimmi_come_si_chiama(squadra, mossa_y, mossa_x, i);
            squadra[a].promozione = 1;
            modifica_colore_chessboard(chessboard, squadra, mossa_y, mossa_x, i, turno);
        }
    }
}

void mossa_f(char (*chessboard)[N_ELEMENT], coord_t mossa, coord_t pedina, char* turno, const char* turno_opposto, ped_t* squadra_turno, ped_t* squadra_opposta, short int mossa_type) {
    char sottocasella_pedina;
    char turno_promosso, turno_opposto_promosso, turno_non_promosso, turno_opposto_non_promosso;
    short int mossa_y, mossa_x, pedina_y, pedina_x;
    mossa_y = mossa.pos_y, mossa_x = mossa.pos_x, pedina_y = pedina.pos_y, pedina_x = pedina.pos_x;
    turno_promosso = turno[1];
    turno_opposto_promosso = turno_opposto[1];
    turno_non_promosso = turno[0];
    turno_opposto_non_promosso = turno_opposto[0];

    /* Se il tipo di mossa_f mi indica che la mossa mangia */
    if (mossa_type== 2) {
        short int i, conta_pedine_casella_pedina = 0, sottocaselle_disponibili;
        short int casella_da_mangiare_x, casella_da_mangiare_y, conta_pedine_casella_da_mangiare, posizione_ultima_pedina_da_mangiare;
        short int conta_pedine_che_riempiono_mossa, posizione_ultima_pedina_pedina;
        short int j, k, l;
        char sottocasella_da_mangiare;
        short int pedina_da_togliere;
        coord_t out_zone;

        for (i = 0; i < 3; ++i) {                                                       /* Conto le pedine nella casella pedina */
            sottocasella_pedina = chessboard[dimmi_riga(pedina_y, i)][pedina_x];
            if (sottocasella_pedina != EMPTY) {
                conta_pedine_casella_pedina++;
            }
        }

        sottocaselle_disponibili = 3 - conta_pedine_casella_pedina;                     /* Conto quante sottocaselle sono disponibili */
        casella_da_mangiare_x = coordinata_media(pedina_x, mossa_x);
        casella_da_mangiare_y = coordinata_media(pedina_y, mossa_y);

        conta_pedine_casella_da_mangiare = 0;

        for (j = 0; j < 3; ++j) {                                                       /* Conto le pedine opposte nella casella_da_mangiare */
            sottocasella_da_mangiare = chessboard[dimmi_riga(casella_da_mangiare_y, j)][casella_da_mangiare_x];
            if (sottocasella_da_mangiare != EMPTY) {
                if (conta_pedine_casella_da_mangiare < sottocaselle_disponibili) {
                    if (sottocasella_da_mangiare == turno_opposto_non_promosso || sottocasella_da_mangiare == turno_opposto_promosso) {
                        conta_pedine_casella_da_mangiare++;
                        posizione_ultima_pedina_da_mangiare = j;                            /* Ritorno la posizione dell'ultima pedina */
                    }
                }
                else {
                    pedina_da_togliere = dimmi_come_si_chiama(squadra_opposta, casella_da_mangiare_y, casella_da_mangiare_x, j);
                    out_zone.pos_y = squadra_opposta[pedina_da_togliere].posizione.pos_y + 3 * N_ELEMENT;
                    out_zone.pos_x = squadra_opposta[pedina_da_togliere].posizione.pos_x + N_ELEMENT;
                    modifica_pos_y_e_pos_x(squadra_opposta, out_zone.pos_y/3, out_zone.pos_x, casella_da_mangiare_y, casella_da_mangiare_x, j, 0);
                    squadra_opposta[pedina_da_togliere].conquistato = 1;
                }
            }
        }

        conta_pedine_che_riempiono_mossa = 0, posizione_ultima_pedina_pedina = 2;

        for (k = 2; k >= 0; --k) {                                                      /* Entro nella casella mossa e riempio dal basso verso l'alto */
            if (conta_pedine_che_riempiono_mossa < conta_pedine_casella_da_mangiare) {  /* Riempio con le pedine della casella_da_mangiare */
                modifica_pos_y_e_pos_x(squadra_opposta, mossa_y, mossa_x, casella_da_mangiare_y, casella_da_mangiare_x, posizione_ultima_pedina_da_mangiare, k);
                modifica_colore_chessboard(chessboard, squadra_opposta, mossa_y, mossa_x, k, turno_opposto);
                squadra_opposta[dimmi_come_si_chiama(squadra_opposta, mossa_y, mossa_x, k)].conquistato = 1;
                conta_pedine_che_riempiono_mossa++;
                posizione_ultima_pedina_da_mangiare--;
            }

            else {
                sottocasella_pedina = chessboard[dimmi_riga(pedina_y, posizione_ultima_pedina_pedina)][pedina_x];
                if (sottocasella_pedina == turno_non_promosso || sottocasella_pedina == turno_promosso){                                      /* Riempio con le pedine della casella pedina */
                    modifica_pos_y_e_pos_x(squadra_turno, mossa_y, mossa_x, pedina_y, pedina_x, posizione_ultima_pedina_pedina, k);
                    modifica_colore_chessboard(chessboard, squadra_turno, mossa_y, mossa_x, k, turno);
                    if (turno == up) {
                        if (mossa_y == N_ELEMENT - 1)
                            promossa(chessboard, squadra_turno, turno, mossa_y, mossa_x);
                    }
                    else if (turno == down){
                        if (mossa_y == 0)
                            promossa(chessboard, squadra_turno, turno, mossa_y, mossa_x);
                    }
                    conta_pedine_che_riempiono_mossa++;
                    posizione_ultima_pedina_pedina--;
                } else if (sottocasella_pedina == turno_opposto_non_promosso || sottocasella_pedina == turno_opposto_promosso) {
                    modifica_pos_y_e_pos_x(squadra_opposta, mossa_y, mossa_x, pedina_y, pedina_x, posizione_ultima_pedina_pedina, k);
                    modifica_colore_chessboard(chessboard, squadra_opposta, mossa_y, mossa_x, k, turno_opposto);
                    conta_pedine_che_riempiono_mossa++;
                    posizione_ultima_pedina_pedina--;
                } else chessboard[dimmi_riga(mossa_y, k)][mossa_x] = EMPTY;
            }
        }


        for (l = 0; l < 3; ++l) {                                                       /* Svuoto le caselle pedina e, dove possibile, casella_da_mangiare */
            chessboard[dimmi_riga(pedina_y, l)][pedina_x] = EMPTY;
            sottocasella_da_mangiare = chessboard[dimmi_riga(casella_da_mangiare_y, l)][casella_da_mangiare_x];
            if (sottocasella_da_mangiare == turno_opposto_non_promosso || sottocasella_da_mangiare == turno_opposto_promosso)
                chessboard[dimmi_riga(casella_da_mangiare_y, l)][casella_da_mangiare_x] = EMPTY;
            else if (sottocasella_da_mangiare == turno_non_promosso || sottocasella_da_mangiare == turno_promosso)                                 /* Libero le pedine prigioniere del turno */
                squadra_turno[dimmi_come_si_chiama(squadra_turno, casella_da_mangiare_y, casella_da_mangiare_x, l)].conquistato = 0;
        }
    }

        /* Se la pedina si sposta solamente */
    else {
        short int i;
        for (i = 0; i < 3; ++i) {
            sottocasella_pedina = chessboard[dimmi_riga(pedina_y, i)][pedina_x];
            if (sottocasella_pedina == turno_non_promosso || sottocasella_pedina == turno_promosso) {                                         /* Sposto le pedine del turno dalla pedina alla mossa_f */
                modifica_pos_y_e_pos_x(squadra_turno, mossa_y, mossa_x, pedina_y, pedina_x, i, i);
                modifica_colore_chessboard(chessboard, squadra_turno, mossa_y, mossa_x, i, turno);
                if (turno == up) {
                    if (mossa_y == N_ELEMENT - 1)
                        promossa(chessboard, squadra_turno, turno, mossa_y, mossa_x);
                }
                else if (turno == down){
                    if (mossa_y == 0)
                        promossa(chessboard, squadra_turno, turno, mossa_y, mossa_x);
                }
            } else if (sottocasella_pedina == turno_opposto_non_promosso || sottocasella_pedina == turno_opposto_promosso) {                        /* Sposto le pedine opposte dalla pedina alla mossa_f */
                modifica_pos_y_e_pos_x(squadra_opposta, mossa_y, mossa_x, pedina_y, pedina_x, i, i);
                modifica_colore_chessboard(chessboard, squadra_opposta, mossa_y, mossa_x, i, turno_opposto);
            } else chessboard[dimmi_riga(mossa_y, i)][mossa_x] = EMPTY;
            chessboard[dimmi_riga(pedina_y, i)][pedina_x] = EMPTY;                      /* Svuoto la casella da cui si � spostata la pedina */
        }
    }
}

void print_posizioni_pedine(ped_t* squadra) {
    short int i;
    for (i = 0; i < calcola_n_pedine(N_ELEMENT); ++i) {
        printf("Pedina [%hd]: {%hd, %hd} \n", i, squadra[i].posizione.pos_x, squadra[i].posizione.pos_y);
    }
}

short int calcola_mosse_totali(ped_t* squadra, short int mangia) {
    short int i, sum = 0;
    for (i = 0; i < calcola_n_pedine(N_ELEMENT); ++i) {
        if (mangia) {
            sum = sum + squadra[i].mosse_mangia_possibili;
        }
        else sum = sum + squadra[i].mosse_possibili;
    }
    return sum;
}

bool correct(char (*chessboard)[N_ELEMENT], ped_t* pedina, coord_t mossa, const char* turno) {
    short int act_row, i, act_row_ped, verso_teorico=0, type_mossa, x_media, y_media, verso_reale;
    short int pedina_y = (pedina->posizione.pos_y) / 3, pedina_x = pedina->posizione.pos_x;
    short int mossa_y = mossa.pos_y, mossa_x =  mossa.pos_x;
    char casella_media;

    if (mossa_y > N_ELEMENT - 1 || mossa_x > N_ELEMENT - 1) return 0;
    if (pedina_y > N_ELEMENT - 1 || pedina_x > N_ELEMENT - 1) return 0;
    if (pedina->conquistato == 1) return 0;
    if (mossa_y == -1 && mossa_x == -1) return 0;

    /*verso teorico quando il mio turno � r o y (non promosso)*/
    if(turno[0] == up[0])
        verso_teorico = -1;
    else
        verso_teorico = 1;
    /*se � promosso verso_teorico =0*/
    if(pedina->promozione)
        verso_teorico =0;
    /*printf("verso: %d \n",verso_teorico);*/

    /*verso reale, se il turno � promosso -> verso_reale= verso_teroico*/
    if(verso_teorico!=0)
        verso_reale = verso(pedina_y, mossa_y);
    else
        verso_reale = verso_teorico;

    /*type mossa_f*/
    type_mossa = mossa_type(pedina_y,pedina_x,mossa_y,mossa_x);

    /*riga attuale*/
    act_row_ped = dimmi_riga(pedina_y, 2);
    act_row = dimmi_riga(mossa_y, 2);

    /*SPOSTA*/
    if(type_mossa == 1) {
        /*controlla se la mossa_f indicata � all'interno del campo*/
        if (chessboard[act_row][mossa_x] == OUTCAST) {
            /*printf("Mossa non valida, mossa_f fuori dal campo di gioco \n");*/
            return 0;
        }
        /*controlla se � vuota e il verso della mossa_f*/
        if (chessboard[act_row][mossa_x] == EMPTY && verso_reale == verso_teorico){
            /*printf("Mossa valida -> la pedina adiacente nel verso corretto e' vuota \n");*/
            return 1;
        }
        else
            return 0;
    }
        /*MANGIA*/
    else if(type_mossa == 2){
        /*coordinate medie*/
        y_media = coordinata_media(act_row_ped, act_row);
        x_media = coordinata_media(pedina_x, mossa_x);
        /*controlla se la mossa_f indicata � all'interno del campo*/
        if (chessboard[act_row][mossa_x] == OUTCAST) {
            /*printf("Mossa non valida, mossa_f fuori dal campo di gioco \n");*/
            return 0;
        }
        /*controlla la pedina finale se � vuota*/
        if(chessboard[act_row][mossa_x] == EMPTY && verso_reale == verso_teorico) {
            /*controlla la casella intermedia*/
            casella_media = chessboard[y_media][x_media];
            if (casella_media == EMPTY) {
                /*printf("la casella intermedia e' vuota, spostamento di una posizione consentito alla casella (%d,%d)\n",x_media, y_media);*/
                return 0;
            }
            else
            {
                /*controlla se la casella intermedia � conquistata*/
                /*controlla da sopra la pedina*/
                /*controlla se � vuota*/
                for(i=2; i>=0; i--)
                {
                    /*printf("casella %c riga %d e colonna  %d\n", chessboard[y_media-i][x_media], y_media-i, x_media);*/
                    if (chessboard[y_media-i][x_media] != EMPTY ) {
                        /*printf("Non vuota...");*/
                        /*controlla la squadra*/
                        if (chessboard[y_media-i][x_media] == turno[0] || chessboard[y_media-i][x_media] == turno[1]) {
                            /*printf("Mossa non valida, pedina da mangiare della stessa squadra del turno \n");*/
                            return 0;
                        }
                        else{
                            /*printf("Mossa valida, pedina da mangiare della squadra avversaria  \n");
                            printf("e' possibile conquistare la pedina intermedia (%d,%d)\n", x_media,y_media);*/
                            return 1;
                        }
                    }
                    /*se � vuota, procedi con l'iterazione successiva*/
                }
            }
        }
        else{
            /*printf("Mossa non valida, la casella indicata e' occupata\n");*/
            return 0;
        }


    }
        /*ALTRIMENTI*/
    else if(type_mossa == 0){
        /*printf("Mossa non valida\n");*/
        return 0;
    }
    return 0;
}

short int verifica_fine_gioco(short int a, short int b){
    if (a > 0 && b > 0)
        return 1;
    else return 0;
}

void verifica_mosse_possibili(char (*chessboard)[N_ELEMENT], ped_t *squadra, short int pedina, const char* turno) {
    coord_t mossa, p;
    short int k;
    squadra[pedina].mosse_possibili = 0;
    squadra[pedina].mosse_mangia_possibili = 0;

    p.pos_y = (squadra[pedina].posizione.pos_y) / 3;      /* Attenzione posizione gi� reale */
    p.pos_x = squadra[pedina].posizione.pos_x;
    /*printf(" ( %hd, %hd )", p.pos_y, p.pos_x);*/

    for (k = 0; k < 8; ++k) {
        if (k<4) {
            mossa.pos_y = p.pos_y + mosse[k];
            mossa.pos_x = p.pos_x + mosse[k];
            /*printf(" ( %hd, %hd )", mossa.pos_y, mossa.pos_x);*/
        }
        else {
            mossa.pos_y = p.pos_y + mosse[k-4];             /* fa la stessa cosa di prima ma 4 pi� avanti */
            mossa.pos_x = p.pos_x + mosse[7-k];             /* 3-(k-4) */
            /*printf(" ( %hd, %hd )", mossa.pos_y, mossa.pos_x);*/
        }
        if (correct(chessboard, squadra + pedina, mossa, turno)) {
            squadra[pedina].database[k].mossa.pos_y = mossa.pos_y;
            squadra[pedina].database[k].mossa.pos_x = mossa.pos_x;
            squadra[pedina].mosse_possibili++;
            squadra[pedina].database[k].mossa_type = mossa_type(p.pos_y, p.pos_x, mossa.pos_y, mossa.pos_x);
            if (squadra[pedina].database[k].mossa_type == 2)
                squadra[pedina].mosse_mangia_possibili++;
        } else {
            squadra[pedina].database[k].mossa.pos_y = -1;
            squadra[pedina].database[k].mossa.pos_x = -1;
            squadra[pedina].database[k].mossa_type = 0;
        }
    }
}

void print_database(ped_t* squadra, short int pedina, short int non_disponibili, short int offset_o, bool mangia) {
    int i;

    if (mangia) {
        if (squadra[pedina].mosse_mangia_possibili > 0) {
            offset_orizzontale_f(offset_o);
            printf("Pedina [%hd]:", pedina);
            for (i = 0; i < 8; ++i) {
                if (non_disponibili == 0) {
                    if (squadra[pedina].database[i].mossa_type == 2)
                        printf("Tipo: %hd - {%c; %hd} -", squadra[pedina].database[i].mossa_type, 'a' + squadra[pedina].database[i].mossa.pos_x, squadra[pedina].database[i].mossa.pos_y);
                }
                else printf(" {%c; %hd} -", 'a' + squadra[pedina].database[i].mossa.pos_x, squadra[pedina].database[i].mossa.pos_y);
            }
            printf("\b\b");
            printf("\n");
        }
    }
    if (!mangia) {
        if (squadra[pedina].mosse_possibili > 0) {
            offset_orizzontale_f(offset_o);
            printf("Pedina [%hd]:", pedina);
            for (i = 0; i < 8; ++i) {
                if (non_disponibili == 0) {
                    if (squadra[pedina].database[i].mossa_type == 1)
                        printf("Tipo: %hd - {%c; %hd} -", squadra[pedina].database[i].mossa_type, 'a' + squadra[pedina].database[i].mossa.pos_x, squadra[pedina].database[i].mossa.pos_y);
                } else
                    printf(" {%c; %hd} -", 'a' + squadra[pedina].database[i].mossa.pos_x, squadra[pedina].database[i].mossa.pos_y);
            }
            printf("\b\b");
            printf("\n");
        }
    }
}

short int strategia(ped_t* squadra, short int pedina) {
    short int i, j, mosse_totali_mangia;
    mosse_totali_mangia = calcola_mosse_totali(squadra, 1);
    if (mosse_totali_mangia > 0) {
        for (i = 0; i < 8; ++i) {
            if (squadra[pedina].database[i].mossa_type == 2)
                return i;
        }
    }
    else {
        for (j = 0; j < 8; ++j) {
            if (squadra[pedina].database[j].mossa_type == 1)
                return j;
        }
    }
    return -1;
}

short int calcola_score_pedina(ped_t* squadra, short int pedina) {
    short int score, score_posizione_x;
    if (squadra[pedina].conquistato) return 0;
    score_posizione_x = N_ELEMENT / 2 - abs(squadra[pedina].posizione.pos_x - N_ELEMENT / 2);       /*3 - |x - 3| */
    score = 5*squadra[pedina].mosse_mangia_possibili + 3*squadra[pedina].mosse_possibili + score_posizione_x;
    /* 3 * (mosse che mangiano) + mosse normali(1) ->
     * 3 * (mosse che mangiano) + (mosse possibili - mosse che mangiano) */
    return score;
}

short int ha_mosse_mangia(ped_t *squadra) {
    if (calcola_mosse_totali(squadra, 1) > 0) return 1;
    else return 0;
}

short int calcola_priorita_pedina(ped_t* squadra, short int* ultima_pedina) {
    short int i, max_score, i_score;
    bool mosse_mangia;
    max_score = 0;
    mosse_mangia = ha_mosse_mangia(squadra);
    for (i = 0; i < calcola_n_pedine(N_ELEMENT); ++i) {
        if (mosse_mangia && squadra[i].mosse_mangia_possibili) {
            squadra[i].score = calcola_score_pedina(squadra, i);
            if (calcola_mosse_totali(squadra, 1) == 1) {
                i_score = i;
                max_score = squadra[i].score;
                break;
            }
            else if (i == *ultima_pedina) continue;
            else {
                *ultima_pedina = i;
                i_score = i;
                max_score = squadra[i].score;
                break;
            }
        }
        else {
            squadra[i].score = calcola_score_pedina(squadra, i);
            if (squadra[i].score > max_score) {
                max_score = squadra[i].score;
                i_score = i;
            }
        }
    }
    printf("\nScore massimo: [%hd]\n", max_score);
    printf("I_score: [%hd] \n", i_score);
    printf("Pedina top score: {%c, %hd} \n", 'a'+squadra[i_score].posizione.pos_x, squadra[i_score].posizione.pos_y/3);
    return i_score;
}

void frase(short int offset_o) {
    short int a;
    srand(time(0));
    a = rand()%5;
    printf("\n");
    offset_orizzontale_f(offset_o + 2);
    printf("%s\n\n", Frase[a]);
}

short int tipo_gioco(short int offset_o){
    short int a, controllo = 1;
    while (controllo) {
        offset_orizzontale_f(offset_o);
        printf("Inserisci tipo di gioco:\n");
        offset_orizzontale_f(offset_o);
        printf("[0]: Utente vs. Utente\n");
        offset_orizzontale_f(offset_o);
        printf("[1]: Utente vs. Computer\n");
        offset_orizzontale_f(offset_o);
        printf("[2]: Computer vs. Computer\n");
        offset_orizzontale_f(offset_o);
        scanf("%hd", &a);
        controllo = controllo_risposta(3, a);
    }
    return a;
}

void scegli_colore(short int *color, short int offset_o) {
    short int controllo = 1;
    while (controllo) {
        offset_orizzontale_f(offset_o);
        printf("Scegli il colore: \n");
        offset_orizzontale_f(offset_o);
        printf("[0]: Nero\n");
        offset_orizzontale_f(offset_o);
        printf("[1]: Rosso\n");
        offset_orizzontale_f(offset_o);
        printf("[2]: Verde\n");
        offset_orizzontale_f(offset_o);
        printf("[3]: Giallo\n");
        offset_orizzontale_f(offset_o);
        printf("[4]: Blu\n");
        offset_orizzontale_f(offset_o);
        printf("[5]: Magenta\n");
        offset_orizzontale_f(offset_o);
        printf("[6]: Ciano\n");
        offset_orizzontale_f(offset_o);
        printf("[7]: Bianco\n");
        offset_orizzontale_f(offset_o);
        scanf("%hd", color);
        controllo = controllo_risposta(8, *color);
    }
}

void scegli_impostazioni(short int* s1_color, short int* s2_color, short int* len, short int offset_o) {
    short int controllo = 1;
    while (controllo) {
        offset_orizzontale_f(offset_o);
        printf("Squadra1: \n");
        scegli_colore(s1_color, offset_o);
        offset_orizzontale_f(offset_o);
        printf("Squadra2: \n");
        scegli_colore(s2_color, offset_o);
        offset_orizzontale_f(offset_o);
        printf("Inserire larghezza scacchiera\n");
        offset_orizzontale_f(offset_o);
        scanf("%hd", len);
        controllo = controllo_risposta(15, *len);
    }
}

void elimina_squadra(ped_t* squadra) {
    free(squadra);
}
