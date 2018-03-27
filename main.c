#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_PONTOS 50
#define NOME_ARQUIVO "ArqGrav.txt" 

// prototipos das funcoes
void init(void);
void display(void);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void desenhaPontos(float *x, float *y, int qtdPontos);
void desenhaPoligono(float *x, float *y, int qtdPontos);
void desenhaPoligonoPreenchido(float *x, float *y, int qtdPontos);
void lerPontos(float *x, float *y, int *qtdPontos);


// funcao principal
int main(int argc, char** argv){

  glutInit(&argc, argv);                                  // inicializa o glut
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);           // especifica o uso de cores e buffers
  glutInitWindowSize (256, 256);                          // especifica as dimensoes da janela
  glutInitWindowPosition (100, 100);                      // especifica aonde a janela aparece na tela
  glutCreateWindow ("Desenhando uma linha");              // cria a janela
  init();
  glutDisplayFunc(display);                               // funcao que sera redesenhada pelo GLUT
  glutKeyboardFunc(keyboard);                             // funcoes de teclado
  glutMouseFunc(mouse);                                   // clique do mouse
  glutMainLoop();                                         // mostra todas as janelas criadas
  return 0;
}

// definicao de cada funcao

void init(void){
  glClearColor(1.0, 1.0, 1.0, 1.0);    // cor de fundo
  glOrtho (0, 256, 0, 256, -1 ,1);     // modo de projecao ortogonal
}

void display(void){

  float x[MAX_PONTOS], y[MAX_PONTOS];
  int qtdPontos = 0;
  lerPontos(x, y, &qtdPontos);

  glClear(GL_COLOR_BUFFER_BIT);               // limpa a janela
  glColor3f (0.0, 0.0, 0.0);                  // cor da linha

  desenhaPontos(x,y, qtdPontos);
  desenhaPoligono(x,y, qtdPontos);
  desenhaPoligonoPreenchido(x,y, qtdPontos);  
  
  glFlush();
}

void desenhaPontos(float *x, float *y, int qtdPontos){
  glBegin(GL_POINTS);

  for(int i = 0; i < qtdPontos; i++){
    glVertex2i(x[i],y[i]);
  }      

  glEnd();
}

void desenhaPoligono(float *x, float *y, int qtdPontos){
  glPolygonMode(GL_BACK, GL_LINE);
  glBegin(GL_POLYGON);
  
  for(int i = 0; i < qtdPontos; i++){
    glVertex2i(x[i],y[i]-80);
  }

//   128-190
// 128-240

  glEnd();
}

void desenhaPoligonoPreenchido(float *x, float *y, int qtdPontos){
  glPolygonMode(GL_BACK, GL_FILL);
  glColor3f(1, 0, 1);
  glBegin(GL_POLYGON);

  for(int i = 0; i < qtdPontos; i++){
    glVertex2i(x[i],y[i]-160);
  }

  glEnd();
}

void keyboard(unsigned char key, int x, int y){
  switch (key) {
    case 27:                                         // tecla Esc (encerra o programa)
    exit(0);
    break;
  }
}

void mouse(int button, int state, int x, int y) { 
 
    if(button == GLUT_LEFT_BUTTON){
      if (state == GLUT_DOWN){ 
        printf("Pressionado na posição: ");  
        printf("(%d, %d)\n", x,y);
      } 
    }
} 

void lerPontos(float *x, float *y, int *qtdPontos){
  
  FILE *arq;
  int i=0, result;

  arq = fopen(NOME_ARQUIVO, "r");

  if (arq == NULL)  {
    printf("Problemas na abertura do arquivo\n");
    return;
  }

  result = fscanf(arq, "%f-%f", &x[i], &y[i]);

  while (result!=EOF){

    // if (result)  // Se foi possível ler
    //   printf("X: %.2f Y: %.2f\n", x[i], y[i]);
  
    i++;
    // Lê uma linha (inclusive com o '\n')
    result = fscanf(arq, "%f-%f", &x[i], &y[i]); 
  }

  *qtdPontos = i;

  fclose(arq);
}