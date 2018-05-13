#ifndef _DEKLARACIJE_H_
#define _DEKLARACIJE_H_

#define TIMER_ID 0
#define TIMER_INTERVAL 50
#define TIMER_ID2 1
#define TIMER_INTERVAL2 50

#define constLoptaY 1
#define constBlokY (-0.2)
#define MAXBLOKOVA 500

/*
 * Struktura po kojoj nam se krece lopta, 
 * sadrzi koordinate i pravac svakog bloka,
 * ako je pravac -1 = x | 1 = z.
 */
typedef struct{
	float x, z; 
	int pravac;
} Blok;

void on_keyboard(unsigned char key, int x, int y);
void on_reshape(int width, int height);
void on_display(void);
void on_timer(int value);
void on_timer2(int value);


void crtajBlokove(void);
void crtajLoptu(void);
void proveraGranica(void);
void ispisRezultata(void);
void inicijalizacija(void);

float nasumicniBroj(float minimum, float maximum);

#endif