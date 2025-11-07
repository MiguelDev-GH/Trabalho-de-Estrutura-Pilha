# Trabalho de Estrutura de Dados sobre Pilha 🔋

### 👤 Integrantes: 
- João Victor Martins Teixeira
- Isabela Arques Mota Ferreira
- Miguel Chagas Maciel *(Líder)*
- Roberto Righetti Neto
- Pedro Henrique Nobre Formiga Chaves
___

### 🧑‍💻 Estrutura de Dados Implementada: Pilha (Stack)

O código implementa a estrutura de dados fundamental Pilha (Stack), usando a técnica de Lista Ligada Simples (Singly Linked List).

### Como foi implementada?

* **`struct No`:** Cada Elemeno da sua pilha é um "Nó" (`struct No`). Este nó é o bloco de construção da lista.
* **`prox`:** é o ponteiro **`struct No* prox`**. Cada nó "sabe" quem é o próximo nó abaixo dele na pilha. Isso conecta a lista.
* **`Pilha`:** A pilha é na verdade um ponteiro que aponta sempre para o nó que está no topo. Se a pilha está vazia, ela aponta para `NULL`.
* **`push`** e **`push_simb`:** Quando "empilha" (dá push) um novo item, cria um novo **`No`**, faz o **`prox`** dele apontar para o antigo topo, e depois atualiza a **`Pilha`** para apontar para este novo nó.
* **`pop`:** Quando "desempilha" (dá pop) pega o nó do topo, atualiza a **`Pilha`** para apontar para o **`prox`** daquele nó (item que está abaixo dele) e libera o nó removido.

### Por que `No` tem `valor`, `simb` e `valor_simb`?

Foi realizado uma otimização para que em vez de criar dois tipos de pilhas (um para números e outra para símbolos), utilizamos um nó "híbrido". **`valor_simb`** permite que a mesma pilha armazene tanto os números (**`int valor`**) quanto os operadores (**`char simb`**) da calculadora.

---

### 🧮 Aplicação Prática: Calculadora de Expressões

A utilidade deste código é uma Calculadora de Expressões Matemáticas Infixas.

Ela foi projetada para resolver expressões como: `(10 + 2) * 5` ou `100 / (5 * (3 + 1))` e encontrar o resultado correto, respeitando parênteses e a ordem das operações.

### Fluxo do Programa

1.  **Entrada:** O **`main.c`** lê uma expressão inteira do usuário (ex: `10 + 5 * 2`).
2.  **Processamento (Pilha `pi`):** O código percorre a string de entrada:
    * **Números:** Se encontra um número (como "10"), a função `addnum` (que é muito útil) lê todos os dígitos e empilha o número inteiro (10) na pilha `pi`.
    * **Símbolos:** Se encontra um operador (`+`, `*`, `(`), ele simplesmente o empilha em `pi`.
3.  **`(Pilha pi_calc)`** É um "gatilho" quando o código encontra um parêntese de fechamento ou quando chega ao fim da expressão.
4.  **Função (`InserirPiCalc`):**
    * Quando um `)` é encontrado, o código move todos os itens da pilha **`pi`** para a pilha **`pi_calc`** até encontrar o **`(`**. Se for o fim da linha ele também move tudo.
5.  **Resolvendo a Expressão (Função `calcularPiCalc`):**
    * A função recebe a pilha **`pi_calc`** (que agora contém uma expressão).
    * **Ordem de Operações:** Ela primeiro varre a pilha e resolve todas as multiplicações e divisões que encontrar.
    * **Segunda Passagem:** Depois que todas as multiplicações e divisões foram resolvidas, ela varre a pilha novamente e resolve adições e subtrações.
    * Isso garante que "`5 + 2 * 3`" seja calculado como "`5 + 6 (11)`" e não "`7 * 3 (21)`".
6.  **Resultado:** Após o **`calcularPiCalc`** terminar, a **`pi_calc`** terá apenas um nó (o resultado). Este resultado é então empilhado de volta na pilha **`pi`**.
7.  **Finalização:** O processo se repete até que toda a expressão de entrada tenha sido processada. No final, a pilha **`pi`** conterá apenas um item: o resultado final da expressão inteira, que é impresso na tela.
___

### ➡️ Instruções claras sobre como compilar e executar o projeto:
- Abra o diretório de onde o projeto está localizado na sua máquina e compile o *main.c*

```
gcc main.c -o main
```

- Agora execute o novo executável, o *main*

```
./main
```
# Usando a aplicação:

- Quando aberto a aplicação, é apenas necessário escrevar a operação, exemplo:

```
10 + 5 * (1 + 1)
```

E então o output será:
```
>>> 10 + 5 * (1 + 1)
Expressao escrita de forma CORRETA!

Resultado = 20
```
<br>

<img src="https://github.com/user-attachments/assets/78658b04-cfba-49f2-95f4-b0deb8fa9525" width='100px'>

⚠️**OBS:** O tratamento de ```()```, ```[]``` e ```{}``` é feito de forma igual, independente se abre usando 1, se pode fechar usando outro dos 3, **por exemplo**:

```
>>> 1 + [1 - (1])
Expressao escrita de forma CORRETA!

Resultado = 1
```

### Algumas entradas irão ser **INVÁLIDADAS** com os seguintes critérios:

- Se tiver o use de caracteres que o programa não reconhece:

| Exemplo:
```
>>> 10 vezes 2 dividido por 5
EXPRESSAO INVALIDA - Caractere invalido identificado
```

___

- Se houver 2 operações básicas seguidas

| Exemplo:
```
>>> 10 +- 2
EXPRESSAO INVALIDA! - Dois simbolos em sequencia
```

___

- Se houver 2 números posicionados seguidamente sem uma operação no meio:

| Exemplo:
```
>>> 10 20 + 2
EXPRESSAO INVALIDA! - Dois numeros em sequencia
```

___

- Se houver um parêntes, colchetes ou chaves abertos ou fechados de forma incorreta:

| Exemplo:
```
>>> 10 (+ 2
EXPRESSAO INVALIDA - Operacao nao fechada corretamente
```

ou

```
>>> 10) - 2
EXPRESSAO INVALIDA - Operacao aberta incorretamente
```

___

- Se estiver dividindo com 0:

| Exemplo:
```
>>> 10 / 0
EXPRESSAO INVALIDA - Nao exite divisao por 0 (Zero)
```
