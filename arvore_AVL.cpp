#include <iostream>
#include <stdlib.h>

using namespace std;

typedef struct tipo_item{
	int chave;
}item;

typedef struct tipo_no{
	struct tipo_item dado;
	struct tipo_no *esq, *dir;
	int altura;
}no;

typedef struct tipo_arvore{
	struct tipo_no *raiz;
}arvore;

void inicializa(arvore* a){
	a->raiz = NULL;
}

int vazia(arvore* a){
	return a->raiz == NULL;
}

no* cria_no(item x){
	no *novo = (no*)malloc(sizeof(no));
	novo->dado = x;
	novo->esq = NULL;
	novo->dir = NULL;

	return novo;
}

no* busca_no(no* ptr, int chave){
	if(ptr == NULL || ptr->dado.chave == chave)
		return ptr;
	if(ptr->dado.chave > chave)
		return busca_no(ptr->esq, chave);
	if(ptr->dado.chave < chave)
		return busca_no(ptr->dir, chave);
}

no* busca(arvore* a, int chave){
	return busca_no(a->raiz, chave);
}

no* maior(no* n){
	if(n->dir == NULL)
		return n;
	else return maior(n->dir);
}

int altura_no(no* n){
	int alt_esq, alt_dir;
	if(n != NULL){
		if(n->dir != NULL)
			alt_dir = n->dir->altura;
		else alt_dir = 0;

		if(n->esq != NULL)
			alt_esq = n->esq->altura;
		else alt_esq = 0;

		if(alt_dir > alt_esq)
			return alt_dir+1;
		else return alt_esq+1;
	}
	else return 0;
}

void rotaciona_esquerda(no** p){
	no *aux, *q;

	q = (*p)->dir;
	(*p)->dir = q->esq;
	q->esq = (*p);
	aux = *p;
	*p = q;
	q = aux;
	q->altura = altura_no(q);
	(*p)->altura = altura_no(*p);
}

void rotaciona_direita(no** p){
	no *aux, *q;

	q = (*p)->esq;
	(*p)->esq = q->dir;
	q->dir = (*p);
	aux = (*p);
	*p = q;
	q = aux;
	q->altura = altura_no(q);
	(*p)->altura = altura_no(*p);
}

int fator_balanceamento_altura(no* n){ //exercício 15a
	int alt_esq, alt_dir;

	if(n->dir == NULL)
		alt_dir = 0;
	else alt_dir = n->dir->altura;

	if(n->esq == NULL)
		alt_esq = 0;
	else alt_esq = n->esq->altura;

	return alt_dir - alt_esq;
}

int fator_balanceamento(no* n){ //exercício 15b
	return altura_no(n->dir) - altura_no(n->esq);
}

void balanceia(no** n){
	if(altura_no((*n)->dir) > altura_no((*n)->esq)+1){
		if(altura_no((*n)->dir->esq) > altura_no((*n)->dir->dir))
			rotaciona_direita(&((*n)->dir));
		rotaciona_esquerda(n);
	}
	else if(altura_no((*n)->esq) > altura_no((*n)->dir)+1){
		if(altura_no((*n)->esq->dir) > altura_no((*n)->esq->esq))
			rotaciona_esquerda(&((*n)->esq));
		rotaciona_direita(n);
	}
}

int insere_no(no** n, item x){
	int ret;
	if(*n == NULL){
		*n = cria_no(x);
		(*n)->altura = altura_no(*n);
		ret = 1;
	}
	else if((*n)->dado.chave < x.chave){
		ret = insere_no(&((*n)->dir), x);
	}
	else if((*n)->dado.chave > x.chave)
		ret = insere_no(&((*n)->esq), x);
	else ret = 0;

	(*n)->altura = altura_no((*n));
	balanceia(n);
	return ret;
	
}

int insere(arvore* a, item x){
	return insere_no(&(a->raiz), x);
}

int remove_no(no** n, int ch, item* retorno, int flag){
	no* aux;
	int ret;

	if(*n != NULL){
		if(ch > (*n)->dado.chave)
			ret = remove_no(&((*n)->dir), ch, retorno, flag);
		else if(ch < (*n)->dado.chave)
			ret = remove_no(&((*n)->esq), ch, retorno, flag);
		else if(ch == (*n)->dado.chave){
			if(!flag)
				*retorno = (*n)->dado;
			if((*n)->esq != NULL && (*n)->dir != NULL){
				aux = maior((*n)->esq);
				(*n)->dado = aux->dado;
				remove_no(&((*n)->esq), aux->dado.chave, retorno, 1);
			}
			else{
				aux = *n;
				if((*n)->esq == NULL)
					*n =(*n)->dir;
				else *n = (*n)->esq;
				free(aux);
			}
			ret = 1;
		}
		if(*n != NULL){
			(*n)->altura = altura_no(*n);
			balanceia(n);
		}
	}
	return ret;
}

int remove(arvore* a, int ch, item* retorno){
	return remove_no(&(a->raiz), ch, retorno, 0);
}

void escreve_nos(no* n, int nivel){
	if(n != NULL){
		for(int i=0; i<nivel*4; i++)
			cout << " ";
		cout << n->dado.chave << endl;
		escreve_nos(n->esq, ++nivel);
		escreve_nos(n->dir, nivel);
	}
}

void imprime(arvore* a){
	escreve_nos(a->raiz, 0);
	cout << endl;
}

void reinsere_lista(int lista[], int tam_lista, no* n, int* index){ //exercício 18 - percurso em-ordem
	if(n != NULL){
		reinsere_lista(lista, tam_lista, n->esq, index);
		lista[*index] = n->dado.chave;
		(*index)++;
		reinsere_lista(lista, tam_lista, n->dir, index);
	}
}

void organiza_lista(int lista[], int tam_lista){ //exercício 18
	arvore aux;
	item inserir;
	int index = 0;

	inicializa(&aux);
	for(int i=0; i<tam_lista; i++){ //inserindo dados na árvore auxiliar
		inserir.chave = lista[i];
		insere(&aux, inserir);
	}

	reinsere_lista(lista, tam_lista, aux.raiz, &index);
}

int main(){
	arvore A;
	int opt, remover, ele_busca;
	item inserir, removido;
	int tam = 6, lista[tam] = {50, 10, -9, 128, 60, 0} ;

	inicializa(&A);
	do{
		cout << "[1] Vazia?" << endl;
		cout << "[2] Insere elemento" << endl;
		cout << "[3] Imprime árvore" << endl;
		cout << "[4] Remove elemento" << endl;
		cout << "[5] Fator balanceamento" << endl;
		cout << "[6] Ordenar lista" << endl;
		cin >> opt;
		switch(opt){
			case 1:
				if(vazia(&A))
					cout << "ÁRVORE VAZIA" << endl;
				cout << endl;
			break;

			case 2:
				system("clear");
				cout << "Digite o elemento que deseja inserir: ";
				cin >> inserir.chave;
				if(insere(&A, inserir))
					cout << "ELEMENTO INSERIDO COM SUCESSO!" << endl;
				else cout << "ERRO NA OPERAÇÃO!" << endl;
				cout << endl;
			break;

			case 3:
				system("clear");
				imprime(&A);
				cout << endl;
			break;

			case 4:
				system("clear");
				cout << "Insira o elemento que deseja remover: ";
				cin >> remover;
				if(remove(&A, remover, &removido))
					cout << removido.chave << " REMOVIDO COM SUCESSO!" << endl;
				else cout << "ERRO NA OPERAÇÃO!" << endl;
				cout << endl;
			break;

			case 5:
				system("clear");
				cout << "Insira uma chave: ";
				cin >> ele_busca;
				cout << "Fator de balanceamento: " << fator_balanceamento(busca(&A, ele_busca)) << endl;
				cout << "Fator de balanceamento: " << fator_balanceamento_altura(busca(&A, ele_busca)) << endl;
				cout << endl;
			break;

			case 6:
				cout << "Lista original: ";
				for(int i=0; i<tam; i++){
					cout << lista[i] << " ";
				}
				cout << endl;
				organiza_lista(lista, tam);
				cout << "Lista organizada: ";
				for(int i=0; i<tam; i++){
					cout << lista[i] << " ";
				}
				cout << endl << endl;
			break;
		}	
	}while(opt != 0);
}