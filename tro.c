// Traçado de Retas Otimizado
#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>


void init();
void display();
void tracarLinha(int x1, int y1, int x2, int y2);

int main(int argc, char** argv) {
    glutInit(&argc, argv);                              
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (512, 512);                      
    glutInitWindowPosition (100, 100);                  
    glutCreateWindow ("Tracado de Linhas Otimizado");  
    init();
    glutDisplayFunc(display);
    glutMainLoop();   
}

void init() {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glOrtho (0, 512, 0, 512, -1 ,1);
}

void display(){
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f (0.0, 0.0, 0.0);
  tracarLinha(5, 10, 500, 50);
  glFlush();
}

void tracarLinha(int x1, int y1, int x2, int y2) {
    // Cálculos iniciais
    float dy = ((float)y2-(float)y1)/((float)x2-(float)x1);
    printf("dy/dx = %f\n", dy);
    
    float dx = ((float)x2-(float)x1)/((float)y2-(float)y1);
    printf("dx/dy = %f / %f = %f\n", ((float)x2-(float)x1), ((float)y2-(float)y1), dx);

    glBegin(GL_POINTS);
    // Traça em função de X
    for (int i = x1; i < x2; i++) {
        glVertex2i(i,i*dy);
    }
    // ---
    // Traça em função de Y
    for (int i = y1; i < y2; i++) {
        glVertex2i(i*dx, i);
    }
    glEnd();
}