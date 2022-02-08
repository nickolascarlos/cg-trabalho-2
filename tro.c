// Traçado de Retas Otimizado
#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

#include <unistd.h>


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

  // Desenha uma linha do ponto (5, 10) até (400, 300)
  tracarLinha(5, 10, 400, 300);

  usleep(10000);
  glFlush();
}

// Retorna:
// 0, se o pixel E for escolhido
// 1, se o NE for escolhido
int EorNE(int x, int y, float dy, float dx, float b) {
  float d = dy*(x+1) - dx*(y+0.5) + b*dx; // Variável de decisão
  return d > 0 ? 1 : 0;
}

void tracarLinha(int x1, int y1, int x2, int y2) {
    // Conversões
    float x_1 = (float) x1;
    float x_2 = (float) x2;
    float y_1 = (float) y1;
    float y_2 = (float) y2;

    // Cálculos iniciais para a determinação da reta
    float dy = y_2 - y_1; // Variação de Y
    float dx = x_2 - x_1; // Variação de X
    float dy_dx = dy/dx;  // Derivada de Y em função de X
    float b = y_1 - dy_dx*x_1; // Constante B

    if (dy_dx > 1) {
      printf("Não é possível traçar essa linha pois seu ângulo é maior que 45º");
      return;
    }

    glBegin(GL_POINTS);

      int c_x = x1, c_y = y1; // Ponto atual
      while(c_x <= x2) {
        // Pintamos o ponto atual
        glVertex2i(c_x, c_y);

        // Calculamos o próximo
        // Primeiro, decidimos se pegaremos o ponto E ou NE
        int d = EorNE(c_x, c_y, dy, dx, b); // Passamos o ponto atual (e outros coeficientes)
        c_x = c_x + 1; // Incrementamos c_x em 1
        c_y = d == 0 ? c_y : c_y + 1; // Se o ponto E for escolhido, não mudamos c_y;
                                      // Se o ponto NE for escolhido, incrementamos em 1.
      }

    glEnd();
}