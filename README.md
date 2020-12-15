# ST7920
Tutorial para uso do display ST7920 em modo paralelo com mBed e Keil uVision.

# Objetivo
Ensinar a importar a biblioteca em ambos compiladores (Keil uVision e mBed), e então escrever caracteres e linhas gráficas no display de cristal líquido (GLCD ST7920).

# Importação - mBed
Há duas maneiras de importar no mBed:
* Importando o código disponível no repositório do mBed neste [link](https://os.mbed.com/users/Marcelocostanzo/code/ST7920_TEST_sem_lib_2/)
* Dentro de seu projeto, criar 2 arquivos com a mesma estrutura presente na pasta "mbed-> biblioteca" deste repositório

# Importação - Keil
Crie normalmente seu projeto no cubeMX seguindo a pinagem escolhida para conexão do display, e tambem selecione o Timer1 com seu prescaler de 64-1 para uso da função delay_us. No diretório do projeto vá até a pasta Inc e copie os arquivos ST7920.h e delay.h disponiveis na pasta "Keil-> biblioteca" deste repositório, faça o mesmo com os arquivo ST7920.c e delay.c porem cole este na pasta Src do projeto.
Abra o projeto no Keil, na arvore do projeto clique direito com o mouse na pasta "Application/User" e então "Add Existing Files to Group Application/User", escolha os arquivos ST7920.c e delay.c copiados anteriormente na pasta Src.

# Programando
Para utilizar a biblioteca devemos incluir ela em nosso arquivo principal, o main. Para isso devemos escrever #include "ST7920.h", com isso o código já estará apto a utilizar as funções da biblioteca. As funções são as seguintes:

```javascript
void ST7920_Init (void)
```
- Inicializa o display, enviando uma sequência de dados necessários 

```javascript
void ST7920_DisplayString(int Row,int Column,unsigned char *ptr,int length);
```
- Escreve uma string no display (ou um vetor de caracteres)  

```javascript
void ST7920_Clear (void)  
```
- Limpa o display
    
```javascript
void ST7920_SetGraphicsMode(void)
```
- Entra em modo gráfico no display

```javascript
void ST7920_SetTextMode(void)
```
- Entra em modo texto no display

```javascript
void ST7920_DrawHorizontalLine(uint8_t X, uint8_t Y,  uint8_t LEN);
```
- Desenha uma linha horizontal no display

```javascript
void ST7920_DrawVerticalLine(uint8_t X, uint8_t Y,  uint8_t LEN);
```
- Desenha uma linha vertical no display
