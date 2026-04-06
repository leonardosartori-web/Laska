#include "laska.h"

/**
 * @file main.c
 * @authors Leonardo Sartori, Mattia Dei Rossi, Agostino Calabrò
 * @date 19 Gen 2021
 * @brief main
 *
 * @see relazione.pdf
 */

int main() {
    char chessboard[3 * N_ELEMENT][N_ELEMENT];
    coord_t mossa, pedina;
    char col_pedina, col_mossa;
    ped_t *squadra1;
    ped_t *squadra2;
    short int len_chessboard, type_of_game, END_OF_GAME = 1, valido, type_mossa, data, offset_verticale, offset_orizzontale, gioca;
    short int i, iesimo;
    char fine;
    char* turno;
    char* turno_opposto;
    short int k, N_PEDINE, priorita_pedina_squadra1, mosse_totali_possibili_squadra1, mosse_mangia_squadra1, priorita_pedina_squadra2, mosse_totali_possibili_squadra2, mosse_mangia_squadra2;
    short int colore_squadra1, colore_squadra2, zona_non_legale = 0;
    short int ultima_pedina_squadra1 = 0, ultima_pedina_squadra2 = 3;
    bool obbligatorio = true;
    short int n_mosse = 1;


    N_PEDINE = calcola_n_pedine(N_ELEMENT);

    squadra1 = (ped_t*) malloc(N_PEDINE * sizeof(ped_t));
    squadra2 = (ped_t*) malloc(N_PEDINE * sizeof(ped_t));

    turno = up;
    len_chessboard = LEN;
    offset_verticale = 3;

    offset_orizzontale = (181 - N_ELEMENT*len_chessboard) / 2;                  /* Visualizzazione a schermo intero */

    presentazione_menu(offset_orizzontale, offset_verticale, &gioca);
    if (gioca == 0) {
        come_si_gioca(offset_orizzontale, offset_verticale, &gioca);
    }
    type_of_game = tipo_gioco(offset_orizzontale);

    scegli_impostazioni(&colore_squadra1, &colore_squadra2, &len_chessboard, offset_orizzontale);
    offset_orizzontale = (181 - N_ELEMENT*len_chessboard) / 2;

    while (zona_non_legale == colore_squadra1 || zona_non_legale == colore_squadra2 || zona_non_legale == 0) {                        /* cerca colore a caso per la zona non legale */
        srand(time(0));
        zona_non_legale = rand() % 8;
        if (zona_non_legale != colore_squadra1 && zona_non_legale != colore_squadra2 && zona_non_legale != 0) {
            break;
        }
    }

    mosse_totali_possibili_squadra1 = 1;
    mosse_totali_possibili_squadra2 = 1;


    for(i=0; i < N_PEDINE ;i++)
    {
        squadra1[i].colore = up[0];
        squadra2[i].colore = down[0];
        squadra1[i].promozione = 0;
        squadra2[i].promozione = 0;
        squadra1[i].conquistato = 0;
        squadra2[i].conquistato = 0;
    }

    posizionamento_iniziale(chessboard,squadra1,squadra2);


    printer_che(chessboard,3*N_ELEMENT, N_ELEMENT, len_chessboard, offset_verticale, offset_orizzontale, colore_squadra1, colore_squadra2, zona_non_legale);

    for (k = 0; k < N_PEDINE; ++k) {
        verifica_mosse_possibili(chessboard, squadra1, k, turno);
    }
    mosse_mangia_squadra1 = ha_mosse_mangia(squadra1);
    for (k = 0; k < N_PEDINE; ++k) {
        print_database(squadra1, k, 0, offset_orizzontale + 2, mosse_mangia_squadra1);
    }
    mosse_totali_possibili_squadra1 = calcola_mosse_totali(squadra1, 0);

    while (END_OF_GAME != 0) {
        offset_orizzontale_f(offset_orizzontale + 2);
        printf("Mossa della partita numero: [%hd] \n", n_mosse);
        offset_orizzontale_f(offset_orizzontale + 2);
        if (turno == up) {
            printf("Il turno e' di ( Squadra1 ) \n");

            printf("\nMosse possibili squadra1: [%hd]; squadra2: [%hd].\n", mosse_totali_possibili_squadra1, mosse_totali_possibili_squadra2);
        }
        else {
            printf("Il turno e' di ( Squadra2 ) \n");

            printf("\nMosse possibili squadra1: [%hd]; squadra2: [%hd].\n", mosse_totali_possibili_squadra1, mosse_totali_possibili_squadra2);
        }

        turno_opposto = dimmi_turno_opposto(turno);
        if ((type_of_game == 1 && turno == down) || (type_of_game == 2 && turno == down)) {
            priorita_pedina_squadra2 = calcola_priorita_pedina(squadra2, &ultima_pedina_squadra2);
            data = strategia(squadra2, priorita_pedina_squadra2);
            pedina.pos_y = (squadra2[priorita_pedina_squadra2].posizione.pos_y) / 3;
            pedina.pos_x = squadra2[priorita_pedina_squadra2].posizione.pos_x;
            mossa.pos_y = squadra2[priorita_pedina_squadra2].database[data].mossa.pos_y;
            mossa.pos_x = squadra2[priorita_pedina_squadra2].database[data].mossa.pos_x;
        }
        else if (type_of_game == 2 && turno == up) {
            priorita_pedina_squadra1 = calcola_priorita_pedina(squadra1, &ultima_pedina_squadra1);
            data = strategia(squadra1, priorita_pedina_squadra1);
            pedina.pos_y = (squadra1[priorita_pedina_squadra1].posizione.pos_y) / 3;
            pedina.pos_x = squadra1[priorita_pedina_squadra1].posizione.pos_x;
            mossa.pos_y = squadra1[priorita_pedina_squadra1].database[data].mossa.pos_y;
            mossa.pos_x = squadra1[priorita_pedina_squadra1].database[data].mossa.pos_x;
        }
        else {

            if (turno == up)
                priorita_pedina_squadra1 = calcola_priorita_pedina(squadra1, &ultima_pedina_squadra1);
            else priorita_pedina_squadra2 = calcola_priorita_pedina(squadra2, &ultima_pedina_squadra2);

            offset_orizzontale_f(offset_orizzontale + 2);
            printf("Inserisci coordinate pedina da spostare: \n");
            offset_orizzontale_f(offset_orizzontale + 2);
            scanf(" %c", &col_pedina);
            pedina.pos_x = differenza_tra_char(col_pedina, 'a');
            scanf(" %hd", &pedina.pos_y);

            offset_orizzontale_f(offset_orizzontale + 2);
            printf("Inserisci coordinate mossa: \n");
            offset_orizzontale_f(offset_orizzontale + 2);
            scanf(" %c", &col_mossa);
            getchar();
            scanf("%hd", &mossa.pos_y);
            mossa.pos_x = differenza_tra_char(col_mossa, 'a');


        }

        offset_orizzontale_f(offset_orizzontale);
        printf("(%hd, %hd) -> [%hd, %hd]\n", pedina.pos_x, pedina.pos_y, mossa.pos_x, mossa.pos_y);

        type_mossa = mossa_type(pedina.pos_y, pedina.pos_x, mossa.pos_y, mossa.pos_x);


        /* validità mossa */
        if (turno == up) {
            iesimo = dimmi_come_si_chiama(squadra1, pedina.pos_y, pedina.pos_x, verified_ped(chessboard, pedina, turno));

            valido = correct(chessboard, squadra1 + iesimo, mossa, turno);
            if (obbligatorio) {
                if (mosse_mangia_squadra1 && type_mossa != 2)
                    valido = 0;
            }
        } else {
            iesimo = dimmi_come_si_chiama(squadra2, pedina.pos_y, pedina.pos_x, verified_ped(chessboard, pedina, turno));
            valido = correct(chessboard, squadra2 + iesimo, mossa, turno);
            if (obbligatorio) {
                if (mosse_mangia_squadra2 && type_mossa != 2)
                    valido = 0;
            }
        }

        if (valido)       {                /* Se la mossa è valida continua nell'if, altrimenti continua a capo del while (non cambia il turno !) */
            n_mosse++;
            if (turno == up)
                mossa_f(chessboard, mossa, pedina, turno, turno_opposto, squadra1, squadra2, type_mossa);
            else mossa_f(chessboard, mossa, pedina, turno, turno_opposto, squadra2, squadra1, type_mossa);

            printer_che(chessboard,N_ELEMENT*3,N_ELEMENT, len_chessboard, offset_verticale, offset_orizzontale, colore_squadra1, colore_squadra2, zona_non_legale);

            if (type_of_game == 2 || (turno == down && type_of_game == 1))
                frase(offset_orizzontale + 2);

            if (turno == up) {
                turno = down;
                for (k = 0; k < N_PEDINE; ++k) {
                    verifica_mosse_possibili(chessboard, squadra2, k, turno);
                }
                mosse_mangia_squadra2 = ha_mosse_mangia(squadra2);
                for (k = 0; k < N_PEDINE; ++k) {
                    print_database(squadra2, k, 0, offset_orizzontale + 2, mosse_mangia_squadra2);
                }
                mosse_totali_possibili_squadra2 = calcola_mosse_totali(squadra2, mosse_mangia_squadra2);
            } else {
                turno = up;
                    for (k = 0; k < N_PEDINE; ++k) {
                    verifica_mosse_possibili(chessboard, squadra1, k, turno);
                }
                mosse_mangia_squadra1 = ha_mosse_mangia(squadra1);
                for (k = 0; k < N_PEDINE; ++k) {
                    print_database(squadra1, k, 0, offset_orizzontale + 2, mosse_mangia_squadra1);
                }
                mosse_totali_possibili_squadra1 = calcola_mosse_totali(squadra1, mosse_mangia_squadra1);
            }

            END_OF_GAME = verifica_fine_gioco(mosse_totali_possibili_squadra1, mosse_totali_possibili_squadra2);

            if (END_OF_GAME == 0){
                offset_orizzontale_f(offset_orizzontale + 2);
                printf("Game Over \n");
                break;
            }
        }
    }
    offset_orizzontale_f(offset_orizzontale + 2);
    if (turno == down)                                /* Attenzione turno già cambiato. Essendo che il nuovo turno non ha mosse disponibili, si considera turno opposto*/
        printf("Ha vinto: Squadra1 \n");
    else printf("Ha vinto: Squadra2 \n");
    n_mosse--;
    offset_orizzontale_f(offset_orizzontale + 2);
    printf("La partita e' terminata in %hd mosse \n", n_mosse);
    elimina_squadra(squadra1);
    elimina_squadra(squadra2);
    offset_orizzontale_f(offset_orizzontale + 2);
    system("pause");
    return 0;
}
