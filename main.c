#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "deklaracije.h"

/*
 * Koordinate pomocu kojih upravljamo loptom kada se krece ili kada pada, i menjamo joj pravac.
 */
float loptaX, loptaY, loptaZ;
float padanjeX, padanjeZ , padanjeY;
int znak;

/*
 * Brzina kretanja loptice, i uslov nakon kog se ubrzava.
 */
float korakTranslacije;
int uslovTranslacije;

/*
 * Pocetna brzina padanja loptice i njeno ubrzanje dok pada.
 */
float padanje, ubrzanjePadanja;

/*
 * Promenljive kojima se bira pravac crtanja blokova, 
 * verovatnoca promene pravca, 
 * i brojac koji prolazi kroz blokove.
 */
float pravacNarednog;
float verovatnocaPravca;
int i;

/*
 * Promenljiva koja nam govori da li je igrica u toku, i da li je igrac presao igricu.
 */
int animationParameter; 
int krajIgre;

/*
 * RGB promenljive za loptu i blokove, i promenljiva koja bira jednu od kombinacija.
 */
float blokR, blokG, blokB, loptaR, loptaG, loptaB;
int nasumicnaBoja;

/*
 * Promenljive za ispis rezultata, i jedna dodatna za slucaj da igrac predje igricu.
 */
float ispisX, ispisY, ispisZ, ispisRegX;

/*
 * Promenljive u kojima pamtimo rezultat, najboljiRezultat,
 * za koliko ce se uvecavati isti na svakom cikcak-u.
 */
int rezultat;
int korakRezultat;
int najboljiRezultat = 0;

/*
 * Sluzi nam da bismo znali na koje parametre da vratimo igricu kada se restartuje,
 * u slucaju da je igrac uneo tezinu koja nije podrazumevajuca.
 */
int indikatorTezine = 0;

/*
 * U slucaju da se stigne do MAXBLOKOVA - igrica je predjena,
 * dodatni blok je poslednji, 'pobednicki'.
 */
Blok blokovi[MAXBLOKOVA + 1];


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    
    srand(time(NULL));
    
    /*
     * Podrazumevana je tezina '1', stoga proveravamo i slucaj da li ima 2 argumenta,
     * ako je unesena pogresna vrednost argumenta, ili ih ima vise - obavestavamo igraca i izlazimo.
     */
    if(argc == 2){
        
        if(!strcmp(argv[1], "1")){
            
            verovatnocaPravca = 0.3;
            korakTranslacije = 0.2;
            
        }
        else if(!strcmp(argv[1], "2")){
            
            verovatnocaPravca = 0.4;
            korakTranslacije = 0.22;
            indikatorTezine = 1;
            
        }
        else{
            
            printf("\nGRESKA: Unesite ./cikcak ['1' ili '2' za tezinu]\n\n");
            exit(EXIT_FAILURE);
            
        }
    }
    else if(argc > 2){
        
        printf("\nGRESKA: Unesite ./cikcak ['1' ili '2' za tezinu]\n\n");
        exit(EXIT_FAILURE);
        
    }
    
    
    inicijalizacija();
    
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_NORMALIZE);

    glutMainLoop();

    return 0;
}
