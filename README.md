 Implementação de Transformações Básicas em OpenGL

```markdown
Universidade Federal de Goiás - Instituto de Informática
Disciplina: Computação Gráfica
Prof.ª: DELLER JAMES FERREIRA
Alunos: 	Matheus Lázaro Honório da Silva
            Gabriel Crispim de Siqueira
            Guilherme Araújo França
            Thais Gonçalves da Silva
```

- Este código em C demonstra a implementação de transformações básicas - translação, rotação e escala - usando a biblioteca OpenGL. As transformações são executadas de forma interativa, permitindo ao usuário escolher o tipo de transformação a ser aplicada.

## Conteúdo
1. [Introdução](#introdução)
2. [Compilação](#compilação)
4. [Conceitos-chave](#conceitos-chave)
5. [Fórmulas](#fórmulas)

## Introdução

O projeto demonstra transformações geométricas em uma figura 2D representada como um quadrado. As transformações incluem:
- **Escalação**: Aumenta ou diminui o tamanho da figura.
- **Rotação**: Gira a figura em torno de um ponto fixo.
- **Translação**: Move a figura em uma direção.

## Compilação

```shell
gcc -c transformacoes2D.c -lGL -lGLU -lglut -lm
gcc -o transformacoes2D transformacoes2D.c -lGL -lGLU -lglut -lm
./transformacoes2D
```

## Conceitos-chave

- **OpenGL**: Uma API gráfica de código aberto usada para renderizar gráficos 2D e 3D.
- **Transformações Geométricas**: São operações que alteram a posição, escala ou orientação de objetos gráficos.

## Fórmulas

### Escala

A escala aumenta ou diminui o tamanho da figura usando a fórmula:

novo_valor = valor_original * fator


### Rotação

A rotação gira a figura em torno de um ponto fixo usando as fórmulas:

x_novo = x_centro + (x_original - x_centro) * cos(ângulo) - (y_original - y_centro) * sin(ângulo)
y_novo = y_centro + (x_original - x_centro) * sin(ângulo) + (y_original - y_centro) * cos(ângulo)

### Translação

A translação move a figura em uma direção usando a fórmula:

novo_valor = valor_original + deslocamento
