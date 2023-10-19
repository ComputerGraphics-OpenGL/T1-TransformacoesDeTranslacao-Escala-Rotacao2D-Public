// Código C para implementar transformações básicas no OPENGL
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <GL/glut.h>

// Tamanho da janela
#define maxLargura 640
#define maxAltura 480

// Velocidade de rotação
#define velocidadeTheta 0.005

// Isso cria um atraso entre duas ações
void atraso(unsigned int msegundos) {
    clock_t objetivo = msegundos + clock();
    while (objetivo > clock());
}

// Esta é uma inicialização básica para a janela glut
void minhaInicializacao(void){
    glClearColor(1.0, 1.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, maxLargura, 0.0, maxAltura);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

// Esta função apenas desenha um ponto
void desenharPonto(int x, int y) {
    glPointSize(10.0);
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void rotacionarEmTornoDoPonto(int px, int py, int cx, int cy) {
    float theta = 0.0;
    while (1) {
        glClear(GL_COLOR_BUFFER_BIT);
        int xf, yf;

        // Atualiza theta rotação anti-horária
        theta = theta + velocidadeTheta;

        // Verifica overflow
        if (theta >= (2.0 * 3.14159))
            theta = theta - (2.0 * 3.14159);

        // cálculos reais..
        xf = (cx + (int)((float)(px - cx) *
            cos(theta)) - ((float)(py - cy) *
            sin(theta)));
        yf = (cy + (int)((float)(px - cx) *
            sin(theta)) + ((float)(py - cy) *
            cos(theta)));

        // Desenhando o ponto central
        desenharPonto(cx, cy);

        // Desenhando o ponto rotacionado
        desenharPonto(xf, yf);
        glFlush();

        // Criando um atraso para que o ponto possa ser notado
        atraso(100);
    }
}

// Esta função irá transladar o ponto
void transladarPonto(int px, int py, int tx, int ty) {
    int tempx = px;
    int tempy = py;
    int fx = px, fy = py;
    while (1)  {
        glClear(GL_COLOR_BUFFER_BIT);

// Desenhando o ponto
        desenharPonto(px, py);

        // Atualizar
        px = px + tx;
        py = py + ty;

        // Verificar overflow para manter o ponto na tela
        if (px > maxLargura || px < 0 ||
            py > maxAltura || py < 0) {
            px = fx;
            py = fy;
        }

        glFlush();

        // Criando um atraso para que o ponto possa ser notado
        atraso(1000000);
    }
}

// Esta função desenha 
void escalarPonto(int px, int py, int sx, int sy) {
    int fx, fy;
   
    while (1) {
        glClear(GL_COLOR_BUFFER_BIT);

        // Atualizar 
        fx = px * sx;
        fy = py * sy;

        // Desenhando o ponto 
        desenharPonto(fx, fy);

        glFlush();

        // Criando um atraso para que o ponto possa ser notado 
        atraso(500);

        glClear(GL_COLOR_BUFFER_BIT);

        // Atualizar 
        fx = px;
        fy = py;

        // Desenhando o ponto 
        desenharPonto(fx, fy);
        
		glFlush();

		// Criando um atraso para que o ponto possa ser notado 
		atraso(500);
	}
}

// Função de exibição real 
void minhaExibicao(void) {
	int opt;
	printf("\nDigite\n\t<1> para translação"
		   "\n\t<2> para rotação"
		   "\n\t<3> para escala\n\t:");
	scanf("%d", &opt);
	printf("\nVá para a janela...");

	switch (opt){
	case 1:
		transladarPonto(0, 0, 100, 100);
		break;
	case 2:
		rotacionarEmTornoDoPonto(200, 200, maxLargura / 2,
								  maxAltura / 2);

		// O ponto irá circular em torno do centro da janela 
		break;
	case 3:
		escalarPonto(10, 20, 2, 3);
		break;
	}
}

// Código principal 
void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(maxLargura, maxAltura);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Transformando ponto");
	glutDisplayFunc(minhaExibicao);
	minhaInicializacao();
	glutMainLoop();
}