#include "deklaracije.h"
#include <GL/glut.h>

extern int animationParameter, krajIgre;
extern int rezultat, korakRezultat;

extern int znak, i;
extern float loptaX, loptaY, loptaZ;
extern float padanjeX, padanjeY, padanjeZ;
extern float padanje, ubrzanjePadanja;
extern int uslovTranslacije;

extern float korakTranslacije, verovatnocaPravca;
extern int indikatorTezine;


void on_keyboard(unsigned char key, int x, int y){
    switch (key) {
        
        /*
         * Pritiskom 'ESC' gasimo igricu.
         */
    case 27:
        exit(0);
        break;
        
        /*
         * Pomocu 'space' menjamo pravac kretanja lopte,
         * u slucaju da pada - nista se ne desava da igrac ne bi varao sa poenima,
         * ili je pomerao levo desno dok pada.
         */
    case 32:
            if(animationParameter != 2){
                
                if(znak == 0)
                        znak = 1;
                else
                        znak *= -1;
                
            }
            
            /*
             * Ne zelimo da korisnik vara ni sa stajanjem-kretanjem loptice,
             * pa uvecavamo rezultat samo ako se ona zaista kretala pri promeni pravca.
             */
            if(animationParameter == 1)
                    rezultat += korakRezultat;
                
            if(!animationParameter && !krajIgre){
                
                    znak = 1;
                    glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
                    animationParameter = 1;
                    
            }
            break;
            
            /*
             * Igrica se pauzira,
             * onemoguceno pauziranje u slucaju da loptica pada.
             */
    case 's':
    case 'S':
            if(animationParameter != 2)
                animationParameter = 0;
            break;
            
            /*
             * Restartujemo igricu, vracamo sve parametre na pocetne vrednosti,
             * iscrtavamo novu putanju.
             */
    case 'r':
    case 'R':
            /* Vracamo parametre na pocetne vrednosti,
             * i iscrtavamo novu putanju.
             */
            inicijalizacija();
            
            crtajBlokove();
            
            glutPostRedisplay();
            break;
    }
}


void on_reshape(int width, int height){
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 1, 10000);
}


void on_display(void){
    GLfloat light_position[] = { 1, 1, 0, 0 };
    GLfloat light_ambient[]  = { 0.1, 0.1, 0.1, 1 };
    GLfloat light_diffuse[]  = { 0.8, 0.8, 0.8, 1 };
    GLfloat light_specular[] = { 0.5, 0.5, 0.5, 1 };

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	
    /*
     * Kamera prati brzinu loptice i krece se dijagonalno po XZ ravni,
     * po kojoj i pravimo blokove.
     */
    
    gluLookAt(-7+(loptaX+loptaZ)/2, 7+loptaY, -7+(loptaX+loptaZ)/2, 
                (loptaX+loptaZ)/2, loptaY, (loptaX+loptaZ)/2, 
                0, 1, 0);


    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    
    glEnable(GL_COLOR_MATERIAL); 
    
    /*
     * Iscrtavamo blokove i loptu, i ispisujemo rezultat.
     */
    crtajBlokove();
    crtajLoptu();
    ispisRezultata();

    glutSwapBuffers();
}


void on_timer(int value){
    if (value != TIMER_ID) return;
	
    /*
     * Bez uslova za animationParameter - restart ne vraca (svaki put) lopticu na sam pocetak putanje,
     * jer se doda jedan korakTranslacije pa mora opet da se restartuje da bi se skroz vratila,
     * stoga proveravamo da li je animationParameter razlicit nule,
     * i ako nije - ne dodajemo korakTranslacije.
     */
    if(znak == 1 && animationParameter != 0)        
        loptaX += korakTranslacije;
    else if(znak == -1)
        loptaZ += korakTranslacije;

    /*
     * Govori nam da li je igrac pao sa blokova ili dosao do kraja igrice.
     */
    proveraGranica();
    
    glutPostRedisplay();
    
    if(animationParameter == 1)
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
        
}


/*
 * Pomocni tajmer kojim simuliramo padanje lopte
 */
void on_timer2(int value){
    if (value != TIMER_ID2) return;
	
	/*
         * U slucaju padanja koristimo -x^2 ili -z^2 funkcije sa malim modifikacijama,
         * da bi pad izgledao prirodnije u zavisnosti od brzine loptice.
         */
        if(znak == 1){
            padanjeX += 0.4472 - korakTranslacije/2;
            padanjeY -= padanje - korakTranslacije/5;
        }
        else if(znak == -1){
            padanjeZ += 0.4472 - korakTranslacije/2;
            padanjeY -= padanje - korakTranslacije/5;
        }
    

        padanje += ubrzanjePadanja;
        
    
        glutPostRedisplay();
	
        if(animationParameter == 2 && padanjeY > -50){
            glutTimerFunc(TIMER_INTERVAL2, on_timer2, TIMER_ID2);
        }
}