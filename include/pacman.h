#ifndef PACMAN_H
#define PACMAN_H

#include <termios.h>

#define R 15
#define C 30
#define G 4

extern int rowMove[4];
extern int colMove[4];

// Functions
void makeRaw();
int keyReady();
int inPart(int g, int r, int c);

#endif
