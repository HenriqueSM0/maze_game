// Labirinto :

# include <stdio.h>
# include <stdlib.h>

typedef struct {
    char type;
} point;

typedef struct {
    point ** maze;
    int number_keys, number_movs, number_bomb;
} game;

int in_ice, only_one_way, switchair_i, switchair_j;

# define NEW_GAME 1
# define LOAD_GAME 2
# define EXIT 3

void new_game(FILE * arq) {
    arq = fopen("save_game", "w");
    fprintf(arq, "1\n");
    fflush(arq);
}

int load_game(FILE * arq) {
    int stage;
    arq = fopen("save_game", "r");
    fscanf(arq, "%d%*c", &stage);
    return stage;
}

FILE * stage_read(int stage) {
    FILE * arq = NULL;
    if (stage == 1) {
        arq = fopen("levels\\level_1", "r");
    } else if (stage == 2) {
        arq = fopen("levels\\level_2", "r");
    } else if (stage == 3) {
        arq = fopen("levels\\level_3", "r");
    } else if (stage == 4) {
        arq = fopen("levels\\level_4", "r");
    } else if (stage == 5) {
        arq = fopen("levels\\level_5", "r");
    }
    return arq;
}

void stage_intialize(game * Henrique, FILE * arq, int *height, int *widht) {
    int i, j, C_height, C_width;
    char pointer;
    fscanf(arq, "%dx%d %d\n", &C_width, &C_height, &Henrique->number_movs);
    Henrique->maze = (point**)malloc(C_height * sizeof(point*));
    for (i = 0; i < C_height; i++) {
        Henrique->maze[i] = (point*)malloc(C_width * sizeof(point));
    }
    for (i = 0; i < C_height; i++) {
        for (j = 0; j < C_width; j++) {
            fscanf(arq, "%c", &pointer);
            if (pointer != '\n') {
                Henrique->maze[i][j].type = pointer; 
                if (pointer == 'I') {
                    
                }          
            } else {
                j--;
            }
        }
    }
    *height = C_height;
    *widht = C_width;
    Henrique->number_keys = 0;
    Henrique->number_bomb = 0;
}

# define WALL 'w'
# define AIR 'o'
# define SWITCHAIR 'a'
# define ONLYUP '^'
# define ONLYDOWN 'v'
# define ONLYLEFT '<'
# define ONLYRIGHT '>'
# define ONLYUP_A '='
# define ONLYDOWN_A '_'
# define ONLYLEFT_A '['
# define ONLYRIGHT_A ']'
# define SWITCH 'S'
# define SWITCHWALL 's'
# define ICE 'i'
# define TRADE 't'
# define BOMB 'b'
# define WEAKWALL_1ST '&'
# define WEAKWALL_2ST '$'
# define KILL 'x'
# define DOOR 'd'
# define KEY 'k'
# define PLAYER 'p'
# define END 'e'

void stage_print(game * Henrique, int height, int width, int *player_i, int *player_j, int stage) {
   int i, j;
   for (i = 0; i < height; i++) {
        printf("\n");
    }
    printf("Level : %d\n", stage);
    printf("----------------------------------------------------------------------------------------\n");
   for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (Henrique->maze[i][j].type == WALL) {
                printf("o ");
            } else if ((Henrique->maze[i][j].type == AIR) || (Henrique->maze[i][j].type == SWITCHAIR)) {
                printf("  ");
            } else if (Henrique->maze[i][j].type == KILL) {
                printf("\033[31mx \033[0m");
            } else if (Henrique->maze[i][j].type == DOOR) {
                printf("\033[35md \033[0m");
            } else if (Henrique->maze[i][j].type == KEY) {
                printf("\033[33mk \033[0m");
            } else if (Henrique->maze[i][j].type == PLAYER) {
                printf("\033[1;34mP \033[0m");
                *player_i = i;
                *player_j = j;
            } else if (Henrique->maze[i][j].type == END) {
                printf("\033[32mE \033[0m");
            } else if (Henrique->maze[i][j].type == '+') {
                printf("\033[32m");
                if ((Henrique->maze[i][j + 2].type > 47) && (Henrique->maze[i][j + 2].type < 58)) {
                    printf("%c%c%c   ", Henrique->maze[i][j].type, Henrique->maze[i][j + 1].type, Henrique->maze[i][j + 2].type);
                } else {
                    printf("%c%c  ", Henrique->maze[i][j].type, Henrique->maze[i][j + 1].type);
                }
                printf("\033[0m");
            } else if (Henrique->maze[i][j].type == '-') {
                printf("\033[31m");
                if ((Henrique->maze[i][j + 2].type > 47) && (Henrique->maze[i][j + 2].type < 58)) {
                    printf("%c%c%c  ", Henrique->maze[i][j].type, Henrique->maze[i][j + 1].type, Henrique->maze[i][j + 2].type);
                } else {
                    printf("%c%c  ", Henrique->maze[i][j].type, Henrique->maze[i][j + 1].type);
                }
                printf("\033[0m");
            } else if (Henrique->maze[i][j].type == ICE) {
                printf("\033[34mi \033[0m");
            } else if (Henrique->maze[i][j].type == ONLYUP) {
                printf("\033[1;35m^ \033[0m");
            } else if (Henrique->maze[i][j].type == ONLYDOWN) {
                printf("\033[1;35mv \033[0m");
            } else if (Henrique->maze[i][j].type == ONLYLEFT) {
                printf("\033[1;35m< \033[0m");
            } else if (Henrique->maze[i][j].type == ONLYRIGHT) {
                printf("\033[1;35m> \033[0m");
            } else if (Henrique->maze[i][j].type == SWITCH) {
                printf("\033[1;35mS \033[0m");
            } else if (Henrique->maze[i][j].type == SWITCHWALL) {
                printf("\033[1;35mo \033[0m");
            } else if (Henrique->maze[i][j].type == TRADE) {
                printf("\033[1;31mt \033[0m");
            } else if (Henrique->maze[i][j].type == BOMB) {
                printf("\033[1;31mb \033[0m");
            } else if (Henrique->maze[i][j].type == WEAKWALL_1ST) {
                printf("\033[33mo \033[0m");
            } else if (Henrique->maze[i][j].type == WEAKWALL_2ST) {
                printf("\033[31mo \033[0m");
            } else if (Henrique->maze[i][j].type == ONLYUP_A) {
                printf("\033[1;32m^ \033[0m");
            } else if (Henrique->maze[i][j].type == ONLYDOWN_A) {
                printf("\033[1;32mv \033[0m");
            } else if (Henrique->maze[i][j].type == ONLYLEFT_A) {
                printf("\033[1;32m< \033[0m");
            } else if (Henrique->maze[i][j].type == ONLYRIGHT_A) {
                printf("\033[1;32m> \033[0m");
            } 
        }
        printf("\n");
    }
    printf("----------------------------------------------------------------------------------------\n");
    printf("\033[33mkeys\033[0m = %d              \033[34mmovs\033[0m = %d", Henrique->number_keys, Henrique->number_movs);
    if (Henrique->number_bomb > 0) {
        printf("              \033[31mbombs\033[0m = %d", Henrique->number_bomb);
    }   
    printf("\n");
}

# define UP 'w'
# define DOWN 's'
# define LEFT 'a'
# define RIGHT 'd'

int player_move(game * Henrique, int player_i , int player_j, int height, int width) {
    char key;   
    int recorder, selector, i, j, trade_tmp;
    int detector(int new_player_i, int new_player_j) {
        if ((Henrique->maze[new_player_i][new_player_j].type == WALL) || (Henrique->maze[new_player_i][new_player_j].type == SWITCHWALL)) {
            return 0;
        } else if ((Henrique->maze[new_player_i][new_player_j].type == AIR) || (Henrique->maze[new_player_i][new_player_j].type == SWITCHAIR)) {
            recorder = 1;
            if (Henrique->maze[new_player_i][new_player_j].type == SWITCHAIR) {
                switchair_i = new_player_i;
                switchair_j = new_player_j;
            }
            return 1;
        } else if (Henrique->maze[new_player_i][new_player_j].type == KILL) {
            return 2;
        } else if (Henrique->maze[new_player_i][new_player_j].type == DOOR) {
            if (Henrique->number_keys > 0) {
                Henrique->number_keys--;
                return 1;
            } else {
                return 0;
            }
        } else if (Henrique->maze[new_player_i][new_player_j].type == KEY) {
            Henrique->number_keys++;
            return 1;
        } else if (Henrique->maze[new_player_i][new_player_j].type == END) {
            return 3;
        } else if (Henrique->maze[new_player_i][new_player_j].type == '+') {
            if ((Henrique->maze[new_player_i][new_player_j + 2].type > 47) && (Henrique->maze[new_player_i][new_player_j + 2].type < 58)) {
                Henrique->number_movs = Henrique->number_movs + (Henrique->maze[new_player_i][new_player_j + 1].type - 48) * 10 + (Henrique->maze[new_player_i][new_player_j + 2].type - 48);
                Henrique->maze[new_player_i][new_player_j + 2].type = AIR;
            } else {
                Henrique->number_movs = Henrique->number_movs + (Henrique->maze[new_player_i][new_player_j + 1].type - 48);
            }
            Henrique->maze[new_player_i][new_player_j + 1].type = AIR;
            return 1;
        } else if (Henrique->maze[new_player_i][new_player_j].type == '-') {
            if ((Henrique->maze[new_player_i][new_player_j + 2].type > 47) && (Henrique->maze[new_player_i][new_player_j + 2].type < 58)) {
                Henrique->number_movs = Henrique->number_movs - (Henrique->maze[new_player_i][new_player_j + 1].type - 48) * 10 + (Henrique->maze[new_player_i][new_player_j + 2].type - 48);
                Henrique->maze[new_player_i][new_player_j + 2].type = AIR;
            } else {
                Henrique->number_movs = Henrique->number_movs - (Henrique->maze[new_player_i][new_player_j + 1].type - 48);
            }
            Henrique->maze[new_player_i][new_player_j + 1].type = AIR;
            return 1;
        } else if (Henrique->maze[new_player_i][new_player_j].type == ICE) {
            return -1;
        } else if (Henrique->maze[new_player_i][new_player_j].type == ONLYUP) {
            if (player_i > new_player_i) {
                only_one_way = 1;
                return 1;
            } else {
                return 0;
            }
        } else if (Henrique->maze[new_player_i][new_player_j].type == ONLYDOWN) {
            if (player_i < new_player_i) {
                only_one_way = 1;
                return 1;
            } else {
                return 0;
            }
        } else if (Henrique->maze[new_player_i][new_player_j].type == ONLYLEFT) {
            if (player_j > new_player_j) {
                only_one_way = 1;
                return 1;
            } else {
                return 0;
            }
        } else if (Henrique->maze[new_player_i][new_player_j].type == ONLYRIGHT) {
            if (player_j < new_player_j) {
                only_one_way = 1;
                return 1;
            } else {
                return 0;
            }
        } else if (Henrique->maze[new_player_i][new_player_j].type == SWITCH) {
            for (i = 0; i < height; i++) {
                for (j = 0; j < width; j++) {
                    if (Henrique->maze[i][j].type == ONLYUP) {
                        Henrique->maze[i][j].type = ONLYDOWN;
                    } else if (Henrique->maze[i][j].type == ONLYDOWN) {
                        Henrique->maze[i][j].type = ONLYUP;
                    } else if (Henrique->maze[i][j].type == ONLYLEFT) {
                        Henrique->maze[i][j].type = ONLYRIGHT;
                    } else if (Henrique->maze[i][j].type == ONLYRIGHT) {
                        Henrique->maze[i][j].type = ONLYLEFT;
                    } else if (Henrique->maze[i][j].type == SWITCHWALL) {
                        Henrique->maze[i][j].type = SWITCHAIR;
                    } else if (Henrique->maze[i][j].type == SWITCHAIR) {
                        Henrique->maze[i][j].type = SWITCHWALL;
                    }
                }
            }
            return 0;
        } else if (Henrique->maze[new_player_i][new_player_j].type == TRADE) {
            if (Henrique->number_keys > 0) {
                trade_tmp = Henrique->number_keys;
                Henrique->number_keys = Henrique->number_movs;
                Henrique->number_movs = trade_tmp;
            }
            return 1;
        } else if (Henrique->maze[new_player_i][new_player_j].type == BOMB) {
            Henrique->number_bomb++;
            return 1; 
        } else if (Henrique->maze[new_player_i][new_player_j].type == WEAKWALL_1ST) {
            return 0;
        } else if (Henrique->maze[new_player_i][new_player_j].type == WEAKWALL_2ST) {
            return 0;
        } else if (Henrique->maze[new_player_i][new_player_j].type == ONLYUP_A) {
            if (player_i > new_player_i) {
                only_one_way = 1;
                return 1;
            } else {
                return 0;
            }
        } else if (Henrique->maze[new_player_i][new_player_j].type == ONLYDOWN_A) {
            if (player_i < new_player_i) {
                only_one_way = 1;
                return 1;
            } else {
                return 0;
            }
        } else if (Henrique->maze[new_player_i][new_player_j].type == ONLYLEFT_A) {
            if (player_j > new_player_j) {
                only_one_way = 1;
                return 1;
            } else {
                return 0;
            }
        } else if (Henrique->maze[new_player_i][new_player_j].type == ONLYRIGHT_A) {
            if (player_j < new_player_j) {
                only_one_way = 1;
                return 1;
            } else {
                return 0;
            }
        }
    }
    scanf("%c", &key);
    if (key == UP) {
        selector = detector(player_i - 1, player_j);
        if ((selector == 1) && (in_ice == 0) && (only_one_way == 0))  {
            Henrique->maze[player_i][player_j].type = AIR;
            if ((switchair_i == player_i) && (switchair_j == player_j)) {
                Henrique->maze[player_i][player_j].type = SWITCHAIR;
                switchair_i = 0;
                switchair_j = 0;
            }
            Henrique->maze[player_i - 1][player_j].type = PLAYER;
            Henrique->number_movs--;
        } else if ((in_ice == 1) && (selector != 0)) {
            Henrique->maze[player_i][player_j].type = ICE;
            Henrique->maze[player_i - 1][player_j].type = PLAYER;
            if (recorder == 1) {
                in_ice = 0;
            }
        } else if ((selector == -1) && (in_ice == 0)) {
            Henrique->maze[player_i][player_j].type = AIR;
            if ((switchair_i == player_i) && (switchair_j == player_j)) {
                Henrique->maze[player_i][player_j].type = SWITCHAIR;
                switchair_i = 0;
                switchair_j = 0;
            }
            Henrique->maze[player_i - 1][player_j].type = PLAYER;
            in_ice = 1;
        } else if ((selector == 1) && (only_one_way == 1)) {
            Henrique->maze[player_i][player_j].type = AIR;
            if ((switchair_i == player_i) && (switchair_j == player_j)) {
                Henrique->maze[player_i][player_j].type = SWITCHAIR;
                switchair_i = 0;
                switchair_j = 0;
            }
            Henrique->maze[player_i - 2][player_j].type = PLAYER;
            only_one_way = 0;
        }
    } else if (key == DOWN) {
        selector = detector(player_i + 1, player_j);
        if ((selector == 1) && (in_ice == 0) && (only_one_way == 0))  {
            Henrique->maze[player_i][player_j].type = AIR;
            if ((switchair_i == player_i) && (switchair_j == player_j)) {
                Henrique->maze[player_i][player_j].type = SWITCHAIR;
                switchair_i = 0;
                switchair_j = 0;
            }
            Henrique->maze[player_i + 1][player_j].type = PLAYER;
            Henrique->number_movs--;
        } else if ((in_ice == 1) && (selector != 0)) {
            Henrique->maze[player_i][player_j].type = ICE;
            Henrique->maze[player_i + 1][player_j].type = PLAYER;
            if (recorder == 1) {
                in_ice = 0;
            }
        } else if ((selector == -1) && (in_ice == 0)) {
            Henrique->maze[player_i][player_j].type = AIR;
            if ((switchair_i == player_i) && (switchair_j == player_j)) {
                Henrique->maze[player_i][player_j].type = SWITCHAIR;
                switchair_i = 0;
                switchair_j = 0;
            }
            Henrique->maze[player_i + 1][player_j].type = PLAYER;
            in_ice = 1;
        } else if ((selector == 1) && (only_one_way == 1)) {
            Henrique->maze[player_i][player_j].type = AIR;
            if ((switchair_i == player_i) && (switchair_j == player_j)) {
                Henrique->maze[player_i][player_j].type = SWITCHAIR;
                switchair_i = 0;
                switchair_j = 0;
            }
            Henrique->maze[player_i + 2][player_j].type = PLAYER;
            only_one_way = 0;
        }
    } else if (key == LEFT) {
        selector = detector(player_i, player_j - 1);
        if ((selector == 1) && (in_ice == 0) && (only_one_way == 0)) {
            Henrique->maze[player_i][player_j].type = AIR;
            if ((switchair_i == player_i) && (switchair_j == player_j)) {
                Henrique->maze[player_i][player_j].type = SWITCHAIR;
                switchair_i = 0;
                switchair_j = 0;
            }
            Henrique->maze[player_i][player_j - 1].type = PLAYER;
            Henrique->number_movs--;
        } else if ((in_ice == 1) && (selector != 0)) {
            Henrique->maze[player_i][player_j].type = ICE;
            Henrique->maze[player_i][player_j - 1].type = PLAYER;
            if (recorder == 1) {
                in_ice = 0;
            }
        } else if ((selector == -1) && (in_ice == 0)) {
            Henrique->maze[player_i][player_j].type = AIR;
            if ((switchair_i == player_i) && (switchair_j == player_j)) {
                Henrique->maze[player_i][player_j].type = SWITCHAIR;
                switchair_i = 0;
                switchair_j = 0;
            }
            Henrique->maze[player_i][player_j - 1].type = PLAYER;
            in_ice = 1;
        } else if ((selector == 1) && (only_one_way == 1)) {
            Henrique->maze[player_i][player_j].type = AIR;
            if ((switchair_i == player_i) && (switchair_j == player_j)) {
                Henrique->maze[player_i][player_j].type = SWITCHAIR;
                switchair_i = 0;
                switchair_j = 0;
            }
            Henrique->maze[player_i][player_j - 2].type = PLAYER;
            only_one_way = 0;
        }
    } else if (key == RIGHT) {
        selector = detector(player_i, player_j + 1);
        if ((selector == 1) && (in_ice == 0) && (only_one_way == 0)) {
            Henrique->maze[player_i][player_j].type = AIR;
            if ((switchair_i == player_i) && (switchair_j == player_j)) {
                Henrique->maze[player_i][player_j].type = SWITCHAIR;
                switchair_i = 0;
                switchair_j = 0;
            }
            Henrique->maze[player_i][player_j + 1].type = PLAYER;
            Henrique->number_movs--;
        } else if ((in_ice == 1) && (selector != 0)) {
            Henrique->maze[player_i][player_j].type = ICE;
            Henrique->maze[player_i][player_j + 1].type = PLAYER;
            if (recorder == 1) {
                in_ice = 0;
            }
        } else if ((selector == -1) && (in_ice == 0)) {
            Henrique->maze[player_i][player_j].type = AIR;
            if ((switchair_i == player_i) && (switchair_j == player_j)) {
                Henrique->maze[player_i][player_j].type = SWITCHAIR;
                switchair_i = 0;
                switchair_j = 0;
            }
            Henrique->maze[player_i][player_j + 1].type = PLAYER;
            in_ice = 1;
        } else if ((selector == 1) && (only_one_way == 1)) {
            Henrique->maze[player_i][player_j].type = AIR;
            if ((switchair_i == player_i) && (switchair_j == player_j)) {
                Henrique->maze[player_i][player_j].type = SWITCHAIR;
                switchair_i = 0;
                switchair_j = 0;
            }
            Henrique->maze[player_i][player_j + 2].type = PLAYER;
            only_one_way = 0;
        }
    } else if ((key == 'b') && (Henrique->number_bomb > 0)) {
        for (i = player_i - 1; i <= player_i + 1; i++) {
            for (j = player_j - 1; j <= player_j + 1; j++) {
                if (Henrique->maze[i][j].type == WEAKWALL_1ST) {
                    Henrique->maze[i][j].type = WEAKWALL_2ST;
                } else if (Henrique->maze[i][j].type == WEAKWALL_2ST) {
                    Henrique->maze[i][j].type = AIR;
                }
            }
        }
        Henrique->number_bomb--;
    }
    if (Henrique->number_movs < 1) {
        selector = 2;
    }
    return selector;
}

void overwrite_game(FILE * arq, int current_stage) {
    arq = fopen("save_game", "w");
    fprintf(arq, "%d\n", current_stage + 1);
    fflush(arq);
}

void end_stage (game * Henrique, int height) {
    int i;
    for (i = 0; i < height; i++) {
        free(Henrique->maze[i]);
    }
    free(Henrique->maze);
    Henrique->number_keys = 0;
    Henrique->number_movs = 0;
    Henrique->number_bomb = 0;
}

int menu() {
    int key;
    printf("MAZE GAME :\n");
    printf("%d. NEW GAME\n", NEW_GAME);
    printf("%d. LOAD GAME\n", LOAD_GAME);
    printf("%d. EXIT\n", EXIT);
    scanf("%d", &key);
    return key;
}

int main() {
    game Henrique;
    FILE * arq = NULL;
    int selector, height, width, player_i, player_j, i, j, current_stage;
    while (1) {
        selector = menu();
        if (selector == NEW_GAME) {
            new_game(arq);
            selector = LOAD_GAME;
        } 
        if (selector == LOAD_GAME) {
            stage_intialize(&Henrique, stage_read(load_game(arq)), &height, &width);
            current_stage = load_game(arq);
            while (1) {
                stage_print(&Henrique, height, width, &player_i, &player_j, current_stage);
                selector = player_move(&Henrique, player_i, player_j, height, width);
                if (selector == 2) {
                    printf("VOCE FOI ELIMINADO!!\n");
                    end_stage(&Henrique, height);
                    break;
                } else if (selector == 3) {
                    printf("VOCE COMPLETOU A FASE %d\n", load_game(arq));
                    overwrite_game(arq, current_stage);
                    end_stage(&Henrique, height);
                    break;
                }
            }
        } else if (selector == EXIT) {
            return 0;
        }
    }
}