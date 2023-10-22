#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

int escolhaUsuario = 0; // Variável para a escolha do usuário
int tipoTransformacao = 0; // Variável para o tipo de transformação

double pontoFixo[2] = {0.0, 0.0}; // Ponto fixo no centro
double vertices[4][2] = {{-1, -1}, {1, -1}, {1, 1}, {-1, 1}}; // Coordenadas dos vértices para escalação e translação

// Função de inicialização para configurar a janela
void inicializacao() {
    glClearColor(1, 1, 1, 1); // Define a cor de fundo como branco
    gluOrtho2D(-5, 5, -5, 5); // Define as coordenadas da janela
}

// Função para desenhar um quadrado
void desenharQuadrado() {
    glBegin(GL_QUADS);
    glVertex2f(vertices[0][0], vertices[0][1]);
    glVertex2f(vertices[1][0], vertices[1][1]);
    glVertex2f(vertices[2][0], vertices[2][1]);
    glVertex2f(vertices[3][0], vertices[3][1]);
    glEnd();
}

// Função para desenhar pontos (ponto fixo em verde e ponto rotacionado em vermelho)
void desenharPontos() {
    // Desenhar o ponto fixo (em verde)
    glColor3f(0, 1, 0);
    glPointSize(20.0);
    glBegin(GL_POINTS);
    glVertex2f(pontoFixo[0], pontoFixo[1]);
    glEnd();

    // Desenhar o ponto rotacionado (em vermelho)
    glColor3f(1, 0, 0);
    glPointSize(20.0);
    glBegin(GL_POINTS);
    glVertex2f(vertices[0][0], vertices[0][1]);
    glEnd();
}

// Função para aplicar escalação ao quadrado
void aplicarEscala() {
    printf("Digite 1 para aumentar a figura em 3 vezes\nDigite 2 para aumentar a figura em um terço\nDigite 3 para alterar a direção X 4 vezes, e a direção Y inalterada.\n");
    scanf("%d%*c", &escolhaUsuario);

    switch (escolhaUsuario) {
        case 1:  // a figura fica 3 vezes maior
            for (int i = 0; i < 4; i++) {
                vertices[i][0] *= 3;
                vertices[i][1] *= 3;
            }
            break;
        case 2:  // a figura fica um terço maior
            for (int i = 0; i < 4; i++) {
                vertices[i][0] *= 1.0 / 3;
                vertices[i][1] *= 1.0 / 3;
            }
            break;
        case 3:  // a direção X fica 4 vezes maior, a direção Y inalterada
            for (int i = 0; i < 4; i++) {
                vertices[i][0] *= 4;
            }
            break;
        default:
            break;
    }
}

// Função para aplicar rotação a um ponto em torno do ponto fixo
void aplicarRotacao(double* ponto, double angulo) {
    double cosA = cos(angulo);
    double sinA = sin(angulo);

    double x = ponto[0] - pontoFixo[0]; // Deslocamento em X em relação ao ponto fixo
    double y = ponto[1] - pontoFixo[1]; // Deslocamento em Y em relação ao ponto fixo
    
    // Aplicar rotação em torno do ponto fixo
    ponto[0] = pontoFixo[0] + x * cosA - y * sinA;
    ponto[1] = pontoFixo[1] + x * sinA + y * cosA;
}

// Função para aplicar translação ao quadrado
void aplicarTranslacao() {
    printf("Digite 1 para deslocar o objeto 3 unidades para a direita\nDigite 2 para deslocar o objeto 2 unidades para cima\nDigite 3 para mover o objeto para baixo ½ unidade e para direita uma unidade\nDigite 4 para mover o objeto para baixo 2/3 unidade e para a esquerda 4 unidades.\n");
    scanf("%d%*c", &escolhaUsuario);

    switch (escolhaUsuario) {
        case 1:  // deslocar o objeto 3 unidades para a direita
            for (int i = 0; i < 4; i++) {
                vertices[i][0] += 3;
            }
            break;
        case 2:  // deslocar o objeto 2 unidades para cima
            for (int i = 0; i < 4; i++) {
                vertices[i][1] += 2;
            }
            break;
        case 3:  // mover o objeto para baixo ½ unidade e para direita uma unidade
            for (int i = 0; i < 4; i++) {
                vertices[i][0] += 1;
                vertices[i][1] -= 0.5;
            }
            break;
        case 4:  // mover o objeto para baixo 2/3 unidade e para a esquerda 4 unidades
            for (int i = 0; i < 4; i++) {
                vertices[i][0] -= 4;
                vertices[i][1] -= 2.0 / 3;
            }
            break;
        default:
            break;
    }
}

// Função para exibir o desenho na janela
void exibir() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (tipoTransformacao == 2) { // Se a escolha for rotação
        desenharPontos();
    } else {
        // Desenhar um quadrado vermelho
        glColor3f(1, 0, 0);
        desenharQuadrado();
    }

    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(10, 50);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Transformacoes");
    inicializacao();
    glutDisplayFunc(exibir);

    printf("Escolha a transformacao:\n");
    printf("1 - Escalar\n");
    printf("2 - Rotacionar\n");
    printf("3 - Transladar\n");
    scanf("%d%*c", &tipoTransformacao);

    if (tipoTransformacao == 2) { // Se a escolha for rotação
        printf("Digite o ângulo de rotação em graus: ");
        double angulo;

        scanf("%lf%*c", &angulo);
        angulo = (angulo + 135) * M_PI / 180.0; // Converter para radianos e ajustar para o ponto vermelho ficar à direita do ponto verde

        aplicarRotacao(vertices[0], angulo);
    } else if (tipoTransformacao == 1) { // Se a escolha for escala
        aplicarEscala();
    } else if (tipoTransformacao == 3) { // Se a escolha for translação
        aplicarTranslacao();
    }

    glutMainLoop();
    return 0;
}
