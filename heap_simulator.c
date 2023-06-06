#include <stdio.h>
#include <stdlib.h>
// SIMULADOR DE HEAP: Nesse programa � feito um simulador do funcionamento da mem�ria no HEAP atraves de um vetor,
// este possui dois valores poss�veis: 0(espa�o livre) e 1(espa�o ocupado). Com a op��o inserir � poss�vel
// atribuir um espa�o do nosso vetor(HEAP) para o ponteiro especificado com id, podendo ser essa inser��o:
// first-fit(no primeiro espa�o livre encontrado), next-fit(no pr�ximo espa�o livre encontrado do ponto atual), 
// best-fit(no espa�o livre com menor tamanho encontrado), worst-fit(no espa�o livre com maior tamanho encontrado). 
// A op��o deletar simula o free, onde o espa�o apontado pelo ponteiro especificado com id � liberado. Existe
// a op��o exibir que exibe o HEAP, assim sendo vis�vel, em tempo de execu��o, os espa�os livres e ocupados.
// A �ltima op��o � atribuir, onde � poss�vel fazer um ponteiro 'a' apontar para o espa�o apontado por um ponteiro 
// 'b', ou para NULL. Dessa forma, teremos o espa�o anteriormente apontado por 'a' como um lixo no nosso HEAP, 
//sem a possibilidade de elimin�-lo de forma simples.

// Lista de registros livres no heap(vetor), possui o endere�o inicial do espa�o livre e o tamanho desse espa�o.
typedef struct vazio{
	int* endereco;
	int tamanhoLivre;
	struct vazio* prox;
} Registro;

// Lista de registros dos ponteiros(id) no heap(vetor), possui endereco incial e tamanho(total de espa�os).
typedef struct ponteiro{
	char id;
	int* endereco;
	int tamanho;
	struct ponteiro* prox;
} Ponteiro;

// Fun��o que faz uma atribui��o, ou seja, passados 'a' e 'b'(a=b), o ponteiro 'a' agora aponta para o espa�o 
//apontado por 'b'.
Ponteiro* atribuir(Ponteiro* p, char id, char id2){
	Ponteiro* aux;
	Ponteiro* aux2;
	aux=p;
	aux2=p;
	while(aux->id!=id){
		aux=aux->prox;
	}
	while(aux2->id!=id2){
		aux2=aux2->prox;
	}
	aux->endereco=aux2->endereco;
	aux->tamanho=aux2->tamanho;
	return p;
}

// Fun��o que serve para atualizar a lista de registros, � sempre ativada quando inserimos ou removemos novos 
// elementos.
Registro* atualizarRegistros(int* vet, Registro* r, int posicao, int tamanho){
	if(posicao<tamanho){
		if(vet[posicao]==0){
			int cont=0;
			r=(Registro*)malloc(sizeof(Registro));
			r->endereco=&vet[posicao];
			while(vet[posicao]==0 && posicao < tamanho){
				cont++;
				posicao++;
			}
			r->tamanhoLivre=cont;
			r->prox=atualizarRegistros(vet, r->prox, posicao, tamanho);
			return r;
		} else{
			r=atualizarRegistros(vet, r, posicao+1, tamanho);
			return r;
		}
	} else{
		return NULL;
	}
	return r;
}

// Fun��o que inicializa o vetor(heap) com 0, 0 significa espa�o vazio.
void inicializa(int* vet, int tamanho){
	int i;
	for(i=0; i<tamanho; i++){
		vet[i]=0;
	}
}

// Fun��o insere com o algoritmo first-fit, no primeiro espa�o livre encontrado.
Ponteiro* inserirFirst(int* vet, char id, int tamanho, Registro* r, Ponteiro* p, int** posicao){
	if(r==NULL){
		printf("\nNao foi possivel inserir, o heap nao tem espaco.\n");
		return p;
	} else {
		if(r->tamanhoLivre>=tamanho){
			Ponteiro* novo=(Ponteiro*)malloc(sizeof(Ponteiro));
			novo->endereco=r->endereco;
			novo->tamanho = tamanho;
			novo->id=id;
			novo->prox=p;
			int i=1;
			while(i<=tamanho){
				*(r->endereco)=1;
				r->endereco++;
				i++;
			}
			*posicao=r->endereco;
			return novo;
		} else{
			p=inserirFirst(vet, id, tamanho, r->prox, p, posicao);
			return p;
		}	
	}
}

// Fun��o insere com o algoritmo next-fit, no pr�ximo espa�o livre partindo da �ltima inser��o.
Ponteiro* inserirNext(int* vet, char id, int tamanho, Registro* r, Ponteiro* p, int** posicao, int total){
	Registro* aux = NULL;
	int i=0;
	while(&(vet[i])!=*posicao){
		i++;
	}
	aux = atualizarRegistros(vet, aux, i, total);
	p=inserirFirst(vet, id, tamanho, aux, p, posicao);
	return p;
}

// Fun��o insere com o algoritmo worst-fit, no maior espa�o livre encontrado.
Ponteiro* inserirWorst(int* vet, char id, int tamanho, Registro* r, Ponteiro* p, int** posicao){
	if(r!=NULL){
		int i=1;
		Registro* maior;
		Registro* atual;
		maior=r;
		atual=r->prox;
		if(maior!=NULL && atual!=NULL){
			while(maior->tamanhoLivre<tamanho && maior!=NULL && atual!=NULL){
				maior=maior->prox;
				atual=atual->prox;
			}
		}
		
		if(maior->tamanhoLivre>=tamanho && maior!=NULL){
			while(atual!=NULL){
				if(atual->tamanhoLivre>maior->tamanhoLivre && atual->tamanhoLivre>=tamanho){
					maior=atual;
				}
				atual=atual->prox;
			}
			Ponteiro* novo=(Ponteiro*)malloc(sizeof(Ponteiro));
			novo->endereco=maior->endereco;
			novo->tamanho = tamanho;
			novo->id=id;
			novo->prox=p;
			while(i<=tamanho){
				*(maior->endereco)=1;
				maior->endereco++;
				i++;
			}
			*posicao=maior->endereco;
			return novo;
		} else{
			printf("\nNao foi possivel inserir, o heap nao tem espaco.\n");
			return p;
		}
	} else{
		printf("\nNao foi possivel inserir, o heap nao tem espaco.\n");
		return p;
	}
} 

// Fun��o insere com o algoritmo best-fit, no menor espa�o livre encontrado.
Ponteiro* inserirBest(int* vet, char id, int tamanho, Registro* r, Ponteiro* p, int** posicao){
	if(r!=NULL){
		int i=1;
		Registro* menor;
		Registro* atual;
		menor=r;
		atual=r->prox;
		if(menor!=NULL && atual!=NULL){
			while(menor->tamanhoLivre<tamanho && menor!=NULL && atual!=NULL){
				menor=menor->prox;
				atual=atual->prox;
			}
		}
		
		if(menor->tamanhoLivre>=tamanho && menor!=NULL){
			while(atual!=NULL){
				if(atual->tamanhoLivre<menor->tamanhoLivre && atual->tamanhoLivre>=tamanho){
					menor=atual;
				}
				atual=atual->prox;
			}
			Ponteiro* novo=(Ponteiro*)malloc(sizeof(Ponteiro));
			novo->endereco=menor->endereco;
			novo->tamanho = tamanho;
			novo->id=id;
			novo->prox=p;
			while(i<=tamanho){
				*(menor->endereco)=1;
				menor->endereco++;
				i++;
			}
			*posicao=menor->endereco;
			return novo;
		} else{
			printf("\nNao foi possivel inserir, o heap nao tem espaco.\n");
			return p;
		}
	} else{
		printf("\nNao foi possivel inserir, o heap nao tem espaco.\n");
		return p;
	}
} 

// Fun��o simula o free e libera o espa�o que o ponteiro(id) aponta, colocando o 0(vazio) no lugar.
Ponteiro* deletar(int* vet, char id, Ponteiro* p){
	if(p == NULL){
		printf("Ponteiro nao encontrado.\n");
		return NULL;
	} else{
		if(p->id==id){
			if(p->endereco!=NULL){
				int i=0;
				while(&vet[i]!=p->endereco){
					i++;
				}
				while(p->tamanho!=0){
					vet[i]=0;
					p->tamanho--;
					i++;
				}	
			}
			Ponteiro* aux;
			aux=p;
			p=p->prox;
			free(aux);
			printf("Valor deletado do Heap.\n");
			return p;
		} else{
			p->prox=deletar(vet, id, p->prox);
		}
	}
}

// Fun��o exibe o vetor que simula o heap.
void exibir(int* vet, int tamanho){
	int i;
	for(i=0; i<tamanho; i++){
		printf("%d ", vet[i]);
	}
	printf("\n");
}

int main(){
	int opc, tamanho, espaco;
	char id, id2;
	
	printf("Digite o tamanho maximo do heap: \n");
	scanf("%d", &tamanho);
	int vet[tamanho];
	inicializa(vet, tamanho);
	
	Registro* r = NULL;
	r = atualizarRegistros(vet, r, 0, tamanho);
	
	Ponteiro* p = NULL;
	
	int* atual=&vet[0];  // Ponteiro que segura a posi��o atual do nosso heap, serve para usarmos na next-fit.
	
	do{
		printf("\nDigite a opcao desejada: \n");
		printf("0 - sair\n1 - inserir\n2 - deletar\n3 - exibir\n4 - atribuir\n");
		scanf("%d", &opc);
		switch(opc){
			case 0: {
				printf("Saindo...");
				break;
			}
			case 1: {
				int x;
				printf("\nDigite a opc de insercao no heap desejada: \n");
				printf("0 - voltar\n1 - first\n2 - next\n3 - worst\n4 - best\n");
				scanf("%d", &x);
				switch(x){
					case 0:{
						printf("Voltando...\n");
						break;
					}
					case 1: {
						printf("Digite a id do novo espaco: \n");
						while (getchar() != '\n');
						scanf("%c", &id);
						printf("Digite o tamanho de espaco desejado: \n");
						scanf("%d", &espaco);
						if(espaco<=tamanho){
							p=inserirFirst(vet, id, espaco, r, p, &atual);
							r=atualizarRegistros(vet, r, 0, tamanho);
						} else{
							printf("Nao foi possivel inserir esse valor, ele excede o tamanho do heap.\n");
						}
						break;
					}
					case 2: {
						printf("Digite a id do novo espaco: \n");
						while (getchar() != '\n');
						scanf("%c", &id);
						printf("Digite o tamanho de espaco desejado: \n");
						scanf("%d", &espaco);
						p=inserirNext(vet, id, espaco, r, p, &atual, tamanho);
						r=atualizarRegistros(vet, r, 0, tamanho);
						break;
					}
					case 3: {
						printf("Digite a id do novo espaco: \n");
						while (getchar() != '\n');
						scanf("%c", &id);
						printf("Digite o tamanho de espaco desejado: \n");
						scanf("%d", &espaco);
						if(espaco<=tamanho){
							p=inserirWorst(vet, id, espaco, r, p, &atual);
							r=atualizarRegistros(vet, r, 0, tamanho);
						} else{
							printf("Nao foi possivel inserir esse valor, ele excede o tamanho do heap.\n");
						}
						break;
					}
					case 4: {
						printf("Digite a id do novo espaco: \n");
						while (getchar() != '\n');
						scanf("%c", &id);
						printf("Digite o tamanho de espaco desejado: \n");
						scanf("%d", &espaco);
						if(espaco<=tamanho){
							p=inserirBest(vet, id, espaco, r, p, &atual);
							r=atualizarRegistros(vet, r, 0, tamanho);
						} else{
							printf("Nao foi possivel inserir esse valor, ele excede o tamanho do heap.\n");
						}
						break;
					}
					default:{
						printf("opc invalida.\n");
						break;
					}
				}
				break;
			}
			case 2:{
				printf("Digite a id para deletar: \n");
				while (getchar() != '\n');
				scanf("%c", &id);
				p=deletar(vet, id, p);
				r=atualizarRegistros(vet, r, 0, tamanho);
				break;
			}
			case 3:{
				printf("Heap: \n");
				exibir(vet, tamanho);
				break;
			}
			case 4:{
				printf("Digite o primeiro valor da atribuicao: \n");
				while (getchar() != '\n');
				scanf("%c", &id);
				printf("Digite o segundo valor da atribuicao: \n");
				printf("Caso o objetivo seja atribuir para NULL basta digitar '.'\n");
				while (getchar() != '\n');
				scanf("%c", &id2);
				if(id2=='.'){
					Ponteiro* aux;
					aux=p;
					while(aux->id!=id){
						aux=aux->prox;
					}
					aux->endereco=NULL;
					aux->tamanho=0;				
				} else{
					p=atribuir(p, id, id2);
				}
				break;
			}
			default:{
				printf("opc invalida.\n");
				break;
			}
		}
	} while(opc!=0);
	return 0;
}

