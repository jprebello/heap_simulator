# Heap Simulator
Simulador do funcionamento da memória no HEAP. Feito em C para a disciplina de Linguagens de Programação, na faculdade de Ciência da Computação.

## Funcionamento
Nesse programa é feito um simulador do funcionamento da memória no HEAP atraves de um vetor, este possui dois valores possíveis: 0(espaço livre) e 1(espaço ocupado). Com a opção inserir é possível atribuir um espaço do nosso vetor(HEAP) para o ponteiro especificado com id, podendo ser essa inserção: first-fit(no primeiro espaço livre encontrado), next-fit(no próximo espaço livre encontrado do ponto atual),  best-fit(no espaço livre com menor tamanho encontrado), worst-fit(no espaço livre com maior tamanho encontrado).  A opção deletar simula o free, onde o espaço apontado pelo ponteiro especificado com id é liberado. Existe a opção exibir que exibe o HEAP, assim sendo visível, em tempo de execução, os espaços livres e ocupados. A última opção é atribuir, onde é possível fazer um ponteiro 'a' apontar para o espaço apontado por um ponteiro  'b', ou para NULL. Dessa forma, teremos o espaço anteriormente apontado por 'a' como um lixo no nosso HEAP,  sem a possibilidade de eliminá-lo, simulando o que seria um lixo de memória.


