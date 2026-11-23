#include <stdio.h>
#include <string.h>

#define ROWS 9
#define COLS 15

typedef struct {
    int row;
    int col;
    int hasKey;
    int moveCount;
} Player;

char maze[ROWS][COLS + 1] = {
    "###############",
    "#P....#......E#",
    "#.#.#.#.#######",
    "#.#.#...#.....#",
    "#.#.#####.###.#",
    "#.#.....#...#.#",
    "#.#####.#.#.#.#",
    "#K......#.....#",
    "###############"
};

void printMaze(Player player);
int movePlayer(Player* player, char command);
int checkGameClear(Player player);

int main(void) {
    Player player = { 1, 1, 0, 0 };

    char input[100];
    char command;

    printf("=== MAZE ESCAPE ===\n");
    printf("W: up  A: left  S: down  D: right\n");
    printf("Find the K(key), then reach the E(End).\n");

    while (1) {
        printMaze(player);

        if (checkGameClear(player)) {
            printf("Success! Moved: %d\n", player.moveCount);
            break;
        }

        printf("W/A/S/D: move, Q: exit: ");

        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        command = input[0];

        if (command == 'q' || command == 'Q') {
            printf("게임을 종료합니다.\n");
            break;
        }

        if (movePlayer(&player, command)) {
            player.moveCount++;
        }
        else {
            printf("이동할 수 없습니다. 벽이거나 잘못된 입력입니다.\n");
        }
    }

    return 0;
}

void printMaze(Player player) {
    int row;
    int col;

    printf("\n열쇠: %s | 이동 횟수: %d\n", player.hasKey ? "획득" : "미획득", player.moveCount);

    for (row = 0; row < ROWS; row++) {
        for (col = 0; col < COLS; col++) {
            if (row == player.row && col == player.col) {
                printf("P");
            }
            else {
                printf("%c", maze[row][col]);
            }
        }
        printf("\n");
    }
}

int movePlayer(Player* player, char command) {
    int nextRow = player->row;
    int nextCol = player->col;

    switch (command) {
    case 'w':
    case 'W':
        nextRow--;
        break;
    case 's':
    case 'S':
        nextRow++;
        break;
    case 'a':
    case 'A':
        nextCol--;
        break;
    case 'd':
    case 'D':
        nextCol++;
        break;
    default:
        return 0;
    }

    if (maze[nextRow][nextCol] == '#') {
        return 0;
    }

    if (maze[nextRow][nextCol] == 'E' && !player->hasKey) {
        printf("You can't exit because you don't have a key.\n");
        return 0;
    }

    if (maze[nextRow][nextCol] == 'K') {
        player->hasKey = 1;
        maze[nextRow][nextCol] = '.';
        printf("Key collected!\n");
    }

    player->row = nextRow;
    player->col = nextCol;

    return 1;
}

int checkGameClear(Player player) {
    return maze[player.row][player.col] == 'E' && player.hasKey;
}