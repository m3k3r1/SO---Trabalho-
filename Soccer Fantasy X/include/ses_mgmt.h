#ifndef _SESSION_MGMT_H_
#define  _SESSION_MGMT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

#define WIDTH 51
#define HEIGHT 21

typedef struct{
    int game_result[2];
    int run;
    int seconds, numPlayers;
} game_stat_t;

typedef struct game_control_t game_control_t;
struct game_control_t {
    int role, posX, posY, id;
    pthread_t tid;
    game_control_t * next, * head;
    //bool have_b all;
};

typedef struct client_data_t client_data_t;
struct client_data_t {
    int role, posX, posY;
    //bool have_b all;
};

int send_to_cli(game_control_t * head, int cli_fd, int numPlayers);
void set_game(game_stat_t * game, game_control_t ** head, int sec);
void movePlayer(game_control_t * player);
void * PlayerMovement(void * arg);
int moveCheck(int x, int y, game_control_t * head);
int randNum(int min, int max);
void initPlayers(game_stat_t * game, game_control_t ** head, int numDef, int numOff);

#endif
