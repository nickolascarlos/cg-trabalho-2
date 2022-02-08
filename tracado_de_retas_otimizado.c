// Traçado de Retas Otimizado
#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

void init();
void display();
void drawLine(int x1, int y1, int x2, int y2);

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

    // Desenha uma linha preta do ponto (5, 10) até (400, 300)
    glColor3f (0.0, 0.0, 0.0);
    drawLine(5, 10, 400, 300);

    // Desenha uma linha vermelha do ponto (0, 0) até (300, 200)
    glColor3f (1.0, 0.0, 0.0);
    drawLine(0, 0, 300, 200);

    // Desenha uma linha azul do ponto (50, 50) até (400, 450)
    glColor3f (0.0, 0.0, 1.0);
    drawLine(50, 50, 400, 450);

    // Desenha uma linha verde do ponto (10, 10) até (20, 250)
    glColor3f (0.2, 0.7, 0.2);
    drawLine(10, 10, 20, 250);

    glFlush();
}

// Troca os pontos
void swapPoints(int* x1, int* y1, int* x2, int* y2) {
    int px2 = *x2;
    int py2 = *y2;

    *x2 = *x1;
    *y2 = *y1;

    *x1 = px2;
    *y1 = py2;
}

// Retorna:
// 0, se o pixel E for escolhido
// 1, se o NE for escolhido
int EorNE(int x, int y, float dy, float dx, float b) {
  float d = dy*(x+1) - dx*(y+0.5) + b*dx; // Variável de decisão
  return d > 0 ? 1 : 0;
}

// Desenha linhas de 0º a 90º
void drawLine(int x1, int y1, int x2, int y2) {
    // Se o ponto 1 estiver à esquerda
    // do ponto 2, troca os pontos
    if (x1 >= x2)
      swapPoints(&x1, &y1, &x2, &y2);

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

    // Espelhamento (eixo x = y)
    // Se a inclinação da reta for maior que 45º, calcula pela linha espelhada
    // E pinta a linha original pelo "reespelhamento"
    int espelhada = dy_dx > 1;
    if (espelhada) {
      int px1 = x1;
      x1 = y1;
      y1 = px1;

      int px2 = x2;
      x2 = y2;
      y2 = px2;

      // Recalcula os coeficientes da linha, agora espelhada
      x_1 = (float) x1;
      x_2 = (float) x2;
      y_1 = (float) y1;
      y_2 = (float) y2;

      dy = y_2 - y_1;
      dx = x_2 - x_1;
      dy_dx = dy/dx;
      b = y_1 - dy_dx*x_1;
    }

    printf("DERIVADA: %f\n", dy_dx);
    printf("LINHA CALCULADA: (%d, %d) -> (%d, %d)\n\n", x1, y1, x2, y2);

    glBegin(GL_POINTS);

      int c_x = x1, c_y = y1; // Ponto atual
      while(c_x <= x2) {
        // Pintamos o ponto atual
        if (espelhada) // Se a linha tiver sido espelhada, reespelhamos
          glVertex2i(c_y, c_x);
        else 
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