#include "deklaracije.h"
#include <GL/glut.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

extern Blok blokovi[];
extern float blokR, blokG, blokB;
extern float verovatnocaPravca;
extern int i;

extern float loptaX, loptaY, loptaZ;
extern float loptaR, loptaG, loptaB;
extern float korakTranslacije;
extern int uslovTranslacije, znak;

extern float padanjeX, padanjeY, padanjeZ;
extern float padanje, ubrzanjePadanja;

extern int animationParameter, krajIgre, indikatorTezine;
extern int rezultat, najboljiRezultat, korakRezultat;
extern int nasumicnaBoja;
extern float ispisX, ispisY, ispisZ, ispisRegX;


void inicijalizacija(void){
    
        /*
         * Postavljamo pocetne parametre svih promenljivih.
         */
        loptaX  = loptaZ = 0;
        loptaY = constLoptaY;
        
        padanje = 0.2;
        ubrzanjePadanja = 0.022;
        
        rezultat = 0;
        krajIgre = 0;
        
        animationParameter = 0;
        i = 1;
        
        if(indikatorTezine){
            
            korakTranslacije = 0.22;
            verovatnocaPravca = 0.4;
            korakRezultat = 2;
            
        }
        else{
            
            korakTranslacije = 0.2;
            verovatnocaPravca = 0.3;
            korakRezultat = 1;
            
        }
        
        uslovTranslacije = 200;
        
        znak = 0;
        
        /*
         * Biramo nasumicno jednu od paleta boja.
         */
        nasumicnaBoja = nasumicniBroj(1, 4);
        
        switch(nasumicnaBoja){
            
            /*
             * Narandzasto-plava.
             */
            case 1:
                blokR = 0.0;
                blokG = 0.5;
                blokB = 1.0;
                loptaR = 1.0;
                loptaG = 0.5;
                loptaB = 0.0;
                break;
                
            /*
             * Zeleno-narandzasta.
             */
            case 2: 
                blokR = 1.0;
                blokG = 0.6;
                blokB = 0.4;
                loptaR = 0.0;
                loptaG = 0.93;
                loptaB = 0.0;
                break;
                
            /*
             * Crveno-zuta.
             */
            case 3:
                blokR = 0.86;
                blokG = 0.75;
                blokB = 0.22;
                loptaR = 1;
                loptaG = 0.3;
                loptaB = 0;
                break;
        }
        
}

void proveraGranica(void){
    /*
     * Promenljiva kojom proveravamo da li se bar na jednom bloku nalazi lopta,
     * u slucaju da ga nadjemo - iskacemo iz petlje.
     */
    int k = 0;
    
    for(int i = 0; i<MAXBLOKOVA; i++){
	if(fabs(loptaX - blokovi[i].x) < 0.5 && fabs(loptaZ - blokovi[i].z) < 0.5){
            k++;
            break; 
        }
    }
    
    /*
     * U slucaju da lopta nije ni na jednom bloku.
     */
    if( k == 0 ){
        
        /*
         * Menjamo najbolji rezultat ako je potrebno.
         */
        if(rezultat > najboljiRezultat)
            najboljiRezultat = rezultat;
                                            
        /*
         * U slucaju da je lopta presla sve blokove - igrica je gotova,
         * zaustavljamo loptu i cestitamo igracu.
         */
        if(loptaX + loptaZ >= MAXBLOKOVA - 1){
            
            krajIgre = 1;
            animationParameter = 0;
            
        }
        
        /*
        * U slucaju padanja menjamo animationParameter, pozivamo odgovarajuci tajmer,
        * i postavljamo pocetne koordinate za padanje na koordinate sa kojih pocinje isto.
        */
        else{
             
            animationParameter = 2;
            padanjeX = loptaX;
            padanjeZ = loptaZ;
            padanjeY = loptaY;
            glutTimerFunc(TIMER_INTERVAL2, on_timer2, TIMER_ID2);
            
        }
            
    }
    
    /*
     * Ako lopta ispunjava uslovTranslacije koji je odredjeni broj blokova,
     * ubrzavamo je do neke granice, uvecavamo uslov za iduce ubrzavanje,
     * povecavamo broj poena koji se dodaje po cikcaku.
     */
    if(loptaX > uslovTranslacije && loptaZ > uslovTranslacije && korakTranslacije < 0.22){
        
        korakTranslacije += 0.01;
        uslovTranslacije += 200;
        korakRezultat += 1;
        
    }
}

void ispisRezultata(void){ 
        /*
         * Karakter kojim prolazimo kroz tekst u kom nam se nalaze rezultati,
         * i koordinate u odnosu na koje ispisujemo rezultate u prozoru.
         */
	char *c, tekst[32];
        ispisX = (loptaX+loptaZ)/2;
        ispisY = loptaY + 4.7;
        ispisZ = (loptaX+loptaZ)/2 + 5;
        
        
        /*
         * Koordinata koja se menja u slucaju prelazenja igrice,
         * da bi bilo lepo poravnanje sa najboljim rezultatom i da ne bismo poremetili pisanje istog.
         */
        ispisRegX = ispisX;
        
        if(krajIgre){
            
            sprintf(tekst, "Svaka cast, presli ste igricu!");
            ispisRegX += 2;
            
        }
        else
            sprintf(tekst, "Rezultat je: %d", rezultat);
        
        glDisable(GL_LIGHTING);
        
        /*
         * Ako pada lopta ispisujemo rezultat crvenom bojom, inace zelenom.
         */
        if(animationParameter != 2)
            glColor3f(1, 1, 1);
        else
            glColor3f(1, 0, 0);
        
	glRasterPos3f(ispisRegX, ispisY, ispisZ);
        
	for (c=tekst; *c != '\0'; c++) 
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
        
        /*
         * Ispis najboljeg rezultata je isti samo drugom bojom i pozicioniran iznad rezultata.
         */
        
        sprintf(tekst, "Najbolji rezultat je: %d", najboljiRezultat);
	
        glColor3f(0, 1, 0);
        
	glRasterPos3f(ispisX + 1, ispisY + 0.6, ispisZ);
        
        
	for (c=tekst; *c != '\0'; c++) 
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
        
        glEnable(GL_LIGHTING);
}

/*
 * Funkcija kojom se bira nasumicni broj.
 */
float nasumicniBroj(float minimum, float maximum){
    float koeficijent = rand() / (float) RAND_MAX;
    return minimum + koeficijent * (maximum - minimum);
}
