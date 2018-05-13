#include "deklaracije.h"
#include <GL/glut.h>
#include <math.h>

extern Blok blokovi[];
extern int i;
extern float blokR, blokG, blokB;
extern float pravacNarednog, verovatnocaPravca;

extern float loptaX, loptaY, loptaZ;
extern float padanjeX, padanjeY, padanjeZ;
extern float loptaR, loptaG, loptaB;

extern int animationParameter;


void crtajBlokove(){ 
        
        /*
         * Crtamo prvi blok.
         */
        
	blokovi[0].pravac = -1;
	blokovi[0].x = blokovi[0].z = 0;
        
	glPushMatrix();
		glColor3f(blokR, blokG, blokB);
		glTranslatef(blokovi[0].x, constBlokY, blokovi[0].z);
		glScalef(1, -2, 1);
		glutSolidCube(1);
	glPopMatrix();
        
        
        /*
         * Pomocna promenljiva kojom osiguravamo da ce prva 2 bloka biti na X osi,
         * posto po njoj pocinje da se krece lopta.
         */
	int pravacPrvog = 1;
        
        
	while(i<MAXBLOKOVA){                
                /*
                 * Na svakih 50 blokova povecavamo verovatnocu cikcak blokova,
                 * i tako otezavamo igricu.
                 */
                if(i % 50 == 0)
                    verovatnocaPravca += 0.02;
                
                
                /*
                 * U slucaju da je pravacNarednog upao u verovatnocu promene - menjamo pravac bloka.
                 */
                
		pravacNarednog = nasumicniBroj(0, 1);
                
		if(pravacNarednog < verovatnocaPravca)
			blokovi[i].pravac = blokovi[i-1].pravac * -1;
		else
			blokovi[i].pravac = blokovi[i-1].pravac;
		
                
                /*
                 * Blokovi smeju da odstupaju do 7. podeoka po obe ose - da ne bi izlazili iz kadra kamere.
                 */
		if ((blokovi[i].pravac == 1 && fabs(blokovi[i-1].z+1-blokovi[i-1].x) > 7) || pravacPrvog == 1){
			blokovi[i].pravac = -1;
                        pravacPrvog = 0;
		}
		
		if (blokovi[i].pravac == -1 && fabs(blokovi[i-1].z-(blokovi[i-1].x+1)) > 7){
			blokovi[i].pravac = 1;
		}
		
		/*
                 * Pravimo novi blok u nastavku poslednjeg napravljenog, u odnosu na pravac.
                 */
		
		if(blokovi[i].pravac == 1){
                    
			blokovi[i].x = blokovi[i-1].x;
			blokovi[i].z = blokovi[i-1].z+1;
			
		}
		else{
                    
			blokovi[i].x = blokovi[i-1].x+1;
			blokovi[i].z = blokovi[i-1].z;
			
		}
		
		i++;
                
        }
                /*
                 * Crtamo blokove koje smo napravili u nizu.
                 */
		for(i = 1; i<MAXBLOKOVA; i++){
                    
			glPushMatrix();
                        glColor3f(blokR, blokG, blokB);
				glTranslatef(blokovi[i].x, constBlokY, blokovi[i].z);
				glScalef(1, -2, 1);
				glutSolidCube(1);
			glPopMatrix();	
                        
		}
		
		/*
                 * Crtamo poslednji (pobednicki) blok isto kao i prethodne samo druge boje.
                 */
                
                if(blokovi[i].pravac == 1){
                    
			blokovi[i].x = blokovi[i-1].x;
			blokovi[i].z = blokovi[i-1].z+1;
			
		}
		else{
                    
			blokovi[i].x = blokovi[i-1].x+1;
			blokovi[i].z = blokovi[i-1].z;
			
		}
		
                glPushMatrix();
                        glColor3f(1, 1, 1);
                        glTranslatef(blokovi[i].x, constBlokY, blokovi[i].z);
                        glScalef(1, -2, 1);
                        glutSolidCube(1);
                glPopMatrix();	
                
}


void crtajLoptu(){
    
        /*
         * Ako lopta ne pada crtamo nju i njenu senku po loptaXYZ koordinatama.
         */
        if(animationParameter != 2){
            
	glPushMatrix();
		glColor3f(loptaR, loptaG, loptaB);
		glTranslatef(loptaX, loptaY, loptaZ);
		glutSolidSphere(0.2, 50, 50);
	glPopMatrix();
        
        
        /*
         * Crtamo senku ('lazemo' igraca).
         */
        glPushMatrix();
                    glColor3f(0.1, 0.1, 0.1);
                    glTranslatef(loptaX, loptaY-0.2, loptaZ);
                    glScalef(1, 0.1, 1);
                    glutSolidSphere(0.2, 50, 50);
        glPopMatrix();
        
        }
        
        /*
         * Kada krene da pada iscrtavamo je pomocu padanjeXYZ koordinata, bez senke.
         */
        else{
            
            glPushMatrix();
		glColor3f(loptaR, loptaG, loptaB);
		glTranslatef(padanjeX, padanjeY, padanjeZ);
		glutSolidSphere(0.2, 50, 50);
            glPopMatrix();
        
        }
        
}
