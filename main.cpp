#include <GL/glew.h>
#include<windows.h>
#include<iostream>
#include <stdio.h>
#include<stdlib.h>
#include <GL/glut.h>
#define M_PI 3.14159265358979323846
#include <math.h>


float velocity = 0;
unsigned char myString[] = "The quick god jumps over the lazy brown fox.";
int w = glutBitmapLength(GLUT_BITMAP_8_BY_13, myString);
float cubex = rand() % 700 - 200;
float cubez = rand() % 700 - 200;
float angle = 30;
float carRot = 90;
void init(void);
float carDiagonal = 100;
float carPos = 400;
void display(void);
void keyboard(unsigned char key, int x, int y);

// funcao principal
int main(int argc, char** argv){
  std::cout << "Comandos: \n\n\tw - acelerar\n\ts - retroceder\n\ta - virar para a esquerda\n\ts - virar para a direita\n\tr - resetar o carro para a posicao inicial\n\n\tcolete os cubos roxos";
  glutInit(&argc, argv);                              // inicializa o glut
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);           // especifica o uso de cores e buffers
  glutInitWindowSize (800, 600);                          // especifica as dimensoes da janela
  glutInitWindowPosition (100, 100);                      // especifica aonde a janela aparece na tela
  glutCreateWindow ("Exemplo projeçoes");              // cria a janela
  init();
  glutDisplayFunc(display);                               // funcao que sera redesenhada pelo GLUT
  glutKeyboardFunc(keyboard);                             // funcoes de teclado
  glutMainLoop();                                         // mostra todas as janelas criadas
  return 0;
}

// definicao de cada funcao

void init(void){
  glClearColor(0.0, 0.0, 0.0,0.0);    // cor de fundo
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  glOrtho (0, 800, 0, 600, -1200.0 ,1200.0);     // modo de projecao ortogonal
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  glRotatef(angle, 1.0, 1.0, 0.0);

}


void display(void){
    glClear(GL_COLOR_BUFFER_BIT);               // limpa a janela
    glColor3f (0.0, 0.0, 0.0);




    glPushMatrix();
    glTranslatef(200.0,250.0,0.0);

    glBegin(GL_QUADS);
    glColor3f(0.0,0.2,0.0);
    glVertex3f(-600.0,0.0,-1200.0);
    glVertex3f(1000.0,0.0,-1200.0);
    glVertex3f(1000.0,0.0,1200.0);
    glVertex3f(-600.0,0.0,1200.0);
    glEnd();

    glColor3f(0.10,0.10,0.10);
    glBegin(GL_QUADS);
    glVertex3f(50.0,0.0,-1200.0);
    glVertex3f(50.0,0.0,1200.0);
    glVertex3f(225.0,0.0,1200.0);
    glVertex3f(225.0,0.0,-1200.0);
    glEnd();

    glColor3f(1.0,1.0,1.0);
    glPushMatrix();
    glTranslatef(137.5,0.0,-1200.0);
    glPushMatrix();
    glScalef(3.0,1.0,20.0);
    glutSolidCube(2);
    glPopMatrix();

    int i;
    for(i=0;i<22;i++){
    glPushMatrix();
    glTranslatef(0.0,0.0,i*100.0);
    glScalef(3.0,1.0,20.0);
    glutSolidCube(2);
    glPopMatrix();
    }

    glPopMatrix();

     glPushMatrix();
    glTranslatef(carDiagonal,0.0,carPos);
    glRotatef(carRot,0.0,1.0,0.0);
    glColor3f(0.8,0.8,0.8);
    glPushMatrix();
    glScalef(10,1,5);
    glutSolidCube(10);
    glPopMatrix();
    glPushMatrix();
    glScalef(2,1,2);
    glTranslatef(0.0,10.0,0.0);
    glColor3f(0.5,0.9,0.5);
    glutSolidCube(20);
    glPopMatrix();
    glPopMatrix();




    glPushMatrix();
    glTranslatef(100.0,0.0,0.0);
    glPushMatrix();
    glScalef(1,5,1);
    glColor3f(0.0,0.0,0.0);
    glutSolidCube(25);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(200.0,0.0,0.0);
    glScalef(1,5,1);
    glutSolidCube(25);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(cubex,10.0,cubez);
    glColor3f(0.3,0.1,0.7);
    glutSolidCube(40);
    glPopMatrix();

    glPushMatrix();
    if(carPos<90 && carDiagonal > 50 && carDiagonal < 200){
      glColor3f(0.0,1.0,0.0);
    }
    else{
    glColor3f(1.0,0.0,0.0);
    }
    glTranslatef(200,75,0.0);
    glScalef(10,1,2);
    glutSolidCube(25);

    glPopMatrix();
    glPopMatrix();

    Sleep(10);
    if(velocity>0 || velocity < 0){
        if(carPos<cubez+50 && carPos > cubez-50 && carDiagonal > cubex-50 && carDiagonal < cubex+50){
            cubex = rand() % 700 - 200;
            cubez = rand() % 700 - 200;
            while(cubex<-100 && cubez<-100){
                cubex = rand() % 700 - 200;
                cubez = rand() % 700 - 200;
            }
        }

        if(velocity>0){
            carPos = carPos - velocity *sin((carRot*M_PI)/180);
            carDiagonal = carDiagonal + velocity*cos((carRot*M_PI)/180);
            velocity = velocity - 1;
        }
        else{
            carPos = carPos - velocity *sin((carRot*M_PI)/180);
            carDiagonal = carDiagonal + velocity*cos((carRot*M_PI)/180);
            velocity = velocity + 1;
        }
    glutPostRedisplay();
    }


  glFlush();
}

void keyboard(unsigned char key, int x, int y){

  switch (key) {

    case 27:                                         // tecla Esc (encerra o programa)
        exit(0);
        break;

    case 97:
        if(carRot == 360){
            carRot = 0;
        }
        carRot = carRot + 15;
        glutPostRedisplay();
        break;
    case 114:
        carRot = 90;
        carDiagonal = 100;
        carPos = 400;
        velocity = 0;
        glutPostRedisplay();
     break;


    case 100:
        if(carRot == 0){
            carRot = 360;
        }
        carRot = carRot - 15;
        glutPostRedisplay();
     break;

    case 119:
        velocity = velocity + 15;
        glutPostRedisplay();

        break;

    case 115:
        velocity = velocity - 5;
             glutPostRedisplay();
        break;
  }
}
