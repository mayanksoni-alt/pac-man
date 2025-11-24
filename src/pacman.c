#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>
#include <time.h>

#define R 15
#define C 30
#define G 4

int rowMove[4] = {-1, 1, 0, 0};
int colMove[4] = {0, 0, -1, 1};

void makeRaw()
{
    struct termios t;
    tcgetattr(0, &t);
    t.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &t);
}

int keyReady()
{
    fd_set f;
    FD_ZERO(&f);
    FD_SET(0, &f);
    struct timeval tv = {0, 0};
    return select(1, &f, NULL, NULL, &tv);
}

int inPart(int g, int r, int c)
{
    if (g == 0) return (r < 7 && c < 15);
    if (g == 1) return (r < 7 && c >= 15);
    if (g == 2) return (r >= 7 && c < 15);
    return (r >= 7 && c >= 15);
}

int main()
{
    srand(time(NULL));

    char board[R][C+1] = {
        "##############################",
        "#............##..............#",
        "#.####.######..######.####...#",
        "#o....#................#....o#",
        "#.####.#.####.##.####.#.####.#",
        "#......#......##......#......#",
        "######.######.##.######.######",
        "#............P...............#",
        "######.######.##.######.######",
        "#......#......##......#......#",
        "#.#####.####..##..####.#####.#",
        "#o....#................#....o#",
        "#.####.######..######.####...#",
        "#.............##.............#",
        "##############################"
    };

    int px = 7, py = 14;
    int pdir = -1;
    int score = 0;

    int leftDots = 0;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            if (board[i][j] == '.' || board[i][j] == 'o')
                leftDots++;

    int gx[G] = {3, 3, 10, 10};
    int gy[G] = {5, 24, 5, 24};
    int gdir[G] = {3, 2, 3, 2};
    char under[G];

    for (int i = 0; i < G; i++)
        under[i] = ' ';

    makeRaw();

    int pStep = 0;
    int gStep = 0;

    while (1)
    {
        system("clear");

        for (int i = 0; i < R; i++)
            printf("%s\n", board[i]);

        printf("Score: %d\n", score);

        if (keyReady())
        {
            char ch = getchar();
            if (ch == 'w') pdir = 0;
            else if (ch == 's') pdir = 1;
            else if (ch == 'a') pdir = 2;
            else if (ch == 'd') pdir = 3;
            else if (ch == 'q') return 0;
        }

        board[px][py] = ' ';

        pStep++;
        if (pStep >= 2)
        {
            pStep = 0;
            int nx = px + rowMove[pdir];
            int ny = py + colMove[pdir];

            if (pdir != -1 && board[nx][ny] != '#')
            {
                px = nx;
                py = ny;
            }
        }

        if (board[px][py] == '.') {
            score += 10;
            leftDots--;
        }
        else if (board[px][py] == 'o') {
            score += 50;
            leftDots--;
        }

        if (leftDots == 0)
        {
            system("clear");
            printf("YOU WIN!\nScore: %d\n", score);
            return 0;
        }

        board[px][py] = 'P';

        gStep++;

        if (gStep >= 3)
        {
            gStep = 0;

            for (int gID = 0; gID < G; gID++)
            {
                board[gx[gID]][gy[gID]] = under[gID];

                int nx = gx[gID] + rowMove[gdir[gID]];
                int ny = gy[gID] + colMove[gdir[gID]];

                if (board[nx][ny] == '#' || !inPart(gID, nx, ny))
                {
                    int ok = 0;
                    while (!ok)
                    {
                        int nd = rand() % 4;
                        int tx = gx[gID] + rowMove[nd];
                        int ty = gy[gID] + colMove[nd];

                        if (board[tx][ty] != '#' && inPart(gID, tx, ty))
                        {
                            gdir[gID] = nd;
                            nx = tx;
                            ny = ty;
                            ok = 1;
                        }
                    }
                }

                gx[gID] = nx;
                gy[gID] = ny;

                char tile = board[gx[gID]][gy[gID]];
                if (tile == 'G') tile = ' ';
                under[gID] = tile;

                if (gx[gID] == px && gy[gID] == py)
                {
                    printf("GAME OVER!\n");
                    return 0;
                }

                board[gx[gID]][gy[gID]] = 'G';
            }
        }

        usleep(85000);
    }

    return 0;
}
