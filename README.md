# Implementação de Transformações Básicas em OpenGL

- Este código em C demonstra a implementação de transformações básicas - translação, rotação e escala - em um ponto usando a biblioteca OpenGL. As transformações são executadas de forma interativa, permitindo ao usuário escolher o tipo de transformação a ser aplicada.

## Funções Implementadas

### Translação

A translação é o processo de mover um objeto de uma posição para outra em um sistema de coordenadas. A função `transladarPonto` implementa a translação de um ponto, permitindo que ele se mova horizontalmente (tx) e verticalmente (ty).

### Rotação

A rotação envolve girar um objeto em torno de um ponto específico. A função `rotacionarEmTornoDoPonto` realiza a rotação de um ponto em torno de um ponto central (cx, cy) e permite que o ponto gire de forma interativa.

### Escala

A escala envolve redimensionar um objeto em relação a um ponto específico. A função `escalarPonto` implementa a escala de um ponto, permitindo que ele seja redimensionado em relação a um ponto central.

## Fórmulas Geométricas

- **Translação**: Novo Ponto (px, py) = Ponto Original (px, py) + Deslocamento (tx, ty)

- **Rotação**: Novo Ponto (xf, yf) = (cx + (px - cx) * cos(theta) - (py - cy) * sin(theta), cy + (px - cx) * sin(theta) + (py - cy) * cos(theta)

- **Escala**: Novo Ponto (fx, fy) = (px * Fator de Escala Horizontal (sx), py * Fator de Escala Vertical (sy)

## Como Executar

Compile o código e execute o programa para escolher entre as opções de translação, rotação ou escala.

```bash
$ gcc -c translacao2D.c -lGL -lGLU -lglut -lm
$ gcc -o translacao2D translacao2D.c -lGL -lGLU -lglut -lm
$ ./translacao2D
```