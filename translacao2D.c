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
void atraso(unsigned int msegundos)
{
    clock_t objetivo = msegundos + clock();
    while (objetivo > clock());
}

// Esta é uma inicialização básica para a janela glut
void minhaInicializacao(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, maxLargura, 0.0, maxAltura);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

// Esta função apenas desenha um ponto
void desenharPonto(int x, int y)
{
    glPointSize(7.0);
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void rotacionarEmTornoDoPonto(int px, int py, int cx, int cy)
{
    float theta = 0.0;
    while (1)
    {
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
        atraso(10);
    }
}

// Esta função irá transladar o ponto
void transladarPonto(int px, int py, int tx, int ty)
{
    int fx = px, fy = py;
    while (1)
    {
        glClear(GL_COLOR_BUFFER_BIT);

        // Atualizar
        px = px + tx;
        py = py + ty;

        // Verificar overflow para manter o ponto na tela
        if (px > maxLargura || px < 0 ||
            py > maxAltura || py < 0)
        {
            px = fx;
            py = fy;
        }

        // Desenhando o ponto
        desenharPonto(px, py);

        glFlush();

        // Criando um atraso para que o ponto possa ser notado
        atraso(10);
    }
}

// Esta função desenha 
void escalarPonto(int px, int py,
                  int sx, int sy)
{
    int fx, fy;
    while (1)
    {
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
void minhaExibicao(void)
{
	int opt;
	printf("\nDigite\n\t<1> para translação"
		   "\n\t<2> para rotação"
		   "\n\t<3> para escala\n\t:");
	scanf("%d", &opt);
	printf("\nVá para a janela...");
	switch (opt){
	case 1:
		transladarPonto(100, 200, 1, 5);
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
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(maxLargura, maxAltura);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Transformando ponto");
	glutDisplayFunc(minhaExibicao);
	minhaInicializacao();
	glutMainLoop();
}


/*#include <GL/glut.h>
#include <string.h>

// Função que desenha um quadrado vermelho
void desenhaQuadrado() {
    glColor3f(1.0, 0.0, 0.0); // Define a cor vermelha
    glBegin(GL_QUADS); // Inicia o modo de desenho de quadriláteros
        glVertex2f(-0.5, -0.5); // Define o primeiro vértice
        glVertex2f(-0.5, 0.5); // Define o segundo vértice
        glVertex2f(0.5, 0.5); // Define o terceiro vértice
        glVertex2f(0.5, -0.5); // Define o quarto vértice
    glEnd(); // Termina o modo de desenho
}

// Função que aplica uma transformação de translação 2D
void transladar(float tx, float ty) {
    // Calcula a matriz de translação
    float m[3][3] = {
        { 1, 0, tx },
        { 0, 1, ty },
        { 0, 0, 1 }
    };

    // Converte o ponteiro para a matriz m para um ponteiro para uma matriz de 4x4
    float m4x4[4][4] = {
        { m[0][0], m[0][1], 0, m[0][2] },
        { m[1][0], m[1][1], 0, m[1][2] },
        { 0      , 0      , 1, 0       },
        { m[2][0], m[2][1], 0, m[2][2] }
    };

    // Multiplica a matriz de transformação atual pela matriz de translação
    glMultMatrixf(&m4x4[0][0]);
}

// Função que desenha a cena
void display() {
    // Limpa a tela com a cor de fundo
    glClear(GL_COLOR_BUFFER_BIT);

    // Seleciona a matriz de modelagem
    glMatrixMode(GL_MODELVIEW);

    // Carrega a matriz identidade
    glLoadIdentity();

    // Aplica uma translação de (0.5, 0.5) no eixo x e y
    transladar(10, 10);

    // Desenha o quadrado vermelho
    desenhaQuadrado();

    // Força o desenho na tela
    glFlush();
}

// Função principal
int main(int argc, char** argv) {
    glutInit(&argc, argv); // Inicializa o GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Define o modo de exibição
    glutInitWindowSize(500, 500); // Define o tamanho da janela
    glutInitWindowPosition(100, 100); // Define a posição inicial da janela
    glutCreateWindow("Translacao 2D"); // Cria a janela com o título dado
    glClearColor(1.0, 1.0, 1.0, 1.0); // Define a cor de fundo como branca
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Define o sistema de coordenadas ortogonal 2D

    // Declara a função de desenho da cena
    glutDisplayFunc(display);

    // Entra no loop principal do GLUT
    glutMainLoop();
    
    return 0;
}
*/