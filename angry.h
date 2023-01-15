/* Copyright 2022 Neil Kirby */

/* Angry Bits Library code.  Not for disclosure without permission */

void ab_angle(int degrees);
void ab_beep();
int ab_bird(int type, double X, double Y);
void ab_clear();
void ab_flash();
void ab_force(int force);
int ab_getch();
int ab_initialize();
int ab_mark(double X, double Y);
void ab_refresh();
void ab_score(int score);
void ab_status(const char *statstr);
void ab_teardown();
void ab_time(int milliseconds);
/* Copyright 2022 Neil Kirby */

/* Angry Bits Library code.  Not for disclosure without permission */

int microsleep(unsigned int microseconds);
int millisleep(unsigned int milliseconds);
double now();
