## Projeto 04 - TExtra - RGB Color Guess Game

The fourth project of Trybe's 5th module.

### What was proposed here

As a literal copy/paste of the instructions:

---
### 1 - O seu site deve possuir um título com o nome do seu jogo

- O **id** do seu título deve ser `title`

### 2 - A página deve possuir o texto RGB a ser adivinhado

- O seu **id** deve ser `rgb-color`
- Esse texto deve conter os três números das cores RGB a ser adivinhada, no seguinte formato: `(168, 34, 1)`

### 3 - A página deve conter opções de cores para serem adivinhadas

- Deve conter 6 bolas como opção de cor de adivinhação
- A **class** de todas as bolas deve ser `ball`

### 4 - Ao clicar em uma bola, deve ser mostrado um texto

- Quando o jogo é iniciado, o texto exibido deve ser `"Escolha uma cor"`
- Se a bola clicada for a **correta**, deve ser exibido o texto `"Acertou!"`
- Se a bola clicada for a **incorreta**, deve ser exibido o texto `"Errou! Tente novamente!"`
- O seu **id** deve ser `answer`

### 5 - As cores das bolas devem ser geradas

- Ao carregar a página, as cores devem ser geradas via JavaScript

### 6 - Crie um botão para iniciar/reiniciar o jogo

- O elemento deve ter o **id** `reset-game`.
- Ao clicar no botão, novas cores devem ser geradas via JavaScript e o elemento `rgb-color` deve ser atualizado
- Ao clicar no botão, o elemento `answer` deve voltar ao estado inicial, exibindo o texto `"Escolha uma cor"`

## BÔNUS

### 7 - Crie um placar que incremente 3 pontos para cada acerto no jogo

- O elemento deve ter o **id** `score`.
- O valor inicial dele deve ser 0.
- A cada acerto, é incrementado 3 pontos ao placar
- Ao clicar no botão reiniciar, o placar **NÃO** deve ser resetado

---

### Grade

This project got a **100%/100%** grade and can be checkout entirely on [here](https://github.com/tryber/sd-06-project-color-guess/pull/28)

#### Comments

On this project i challenged myself to keep all the constraints given when uploading the project to my repository, but still had to come up with new ideais and increase how complex the game is.

To do that, i decided to create a 'hard mode', in which the used only has 3 lives (showed on screen) and every consecutive hit, creating a *streak* increases the amount of points gained per hit. Hard mode is enabled with a checkbox, and can be disabled with the reset button.

One other challenge i proposed to myself was to **not use any while loop** during the development and execution of the project. The reasoning being most courses or videos always uses the while loop as an example of 'game mechanic' or associates it with that. Obviously is a correct association, since a lot of games do, in fact, use while loops to work. But the idea here is to show the power of **events**, topic of the module.

The application is also fully responsive on smaller screens.

###### Feedback

As always, any feedback or suggestion is welcomed.
