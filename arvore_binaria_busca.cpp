#include <iostream>
#include <stdlib.h>

using namespace std;

typedef struct tipo_item{
	int chave;
}item;

typedef struct tipo_no{
	struct tipo_item dado;
	struct tipo_no *esq, *dir;
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

no* insere_no(no* r, item x){
	if(r == NULL)
		r = cria_no(x);
	else if(r->dado.chave > x.chave)
		r->esq = insere_no(r->esq, x);
	else if(r->dado.chave < x.chave)
		r->dir = insere_no(r->dir, x);

	return r;
}

int insere_no_pont(no** n, item x){
	if(*n == NULL){
		*n = cria_no(x);
		return 1;
	}
	else if((*n)->dado.chave < x.chave)
		return insere_no_pont(&((*n)->dir), x);
	else if((*n)->dado.chave > x.chave)
		return insere_no_pont(&((*n)->esq), x);
	else return 0;
}

int insere(arvore* a, item x){
	return insere_no_pont(&(a->raiz), x);
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

int remove_no(no** n, int ch, item* x, int flag){
	no* aux;

	if(*n != NULL){
		if(ch > (*n)->dado.chave)
			return remove_no(&((*n)->dir), ch, x, flag);
		else if(ch < (*n)->dado.chave)
			return remove_no(&((*n)->esq), ch, x, flag);
		else if(ch == (*n)->dado.chave){
			if(!flag){
				*x = (*n)->dado;
			}
			if((*n)->esq != NULL && (*n)->dir != NULL){
				aux = maior((*n)->esq);
				(*n)->dado = aux->dado;
				remove_no(&((*n)->esq), aux->dado.chave, x, 1);
			}
			else{
				aux = *n;
				if((*n)->esq == NULL)
					*n = (*n)->dir;
				else *n = (*n)->esq;
				free(aux);
			}
			return 1;
		}
	}
	return 0;
}

int remove(arvore* a, int chave, item* x){
	return remove_no(&(a->raiz), chave, x, 0);
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

int altura_no(no* n){ //Exercício 1
	int h_esq, h_dir;
    if(n == NULL) 
    	return 0;
    h_esq = altura_no(n->esq);
    h_dir = altura_no(n->dir);
    if(h_esq > h_dir) return h_esq+1;
    else return h_dir+1;
}

no* menor_elemento(no* n){ //Exercício 2
	if(n->esq != NULL)
		return menor_elemento(n->esq);
	else return n;
}

int main(){
	arvore A;
	int opt, ele_busca, ele_remove;
	no *retorno;
	item ele_insere, *ret;

	inicializa(&A);
	do{
		cout << "[1] Vazia?" << endl;
		cout << "[2] Inserir elemento" << endl;
		cout << "[3] Buscar elemento" << endl;
		cout << "[4] Maior elemento" << endl;
		cout << "[5] Remover elemento" << endl;
		cout << "[6] Mostra árvore" << endl;
		cout << "[7] Menor elemento" << endl;
		cout << "[8] Altura de um nó" << endl;
		cin >> opt;
		switch(opt){
			case 1:
				if(vazia(&A))
					cout << "ÁRVORE VAZIA!" << endl;
				else cout << "ÁRVORE NÃO VAZIA" << endl;
				cout << endl;
			break;

			case 2:
				system("clear");
				cout << "Insira o elemento que deseja inserir: ";
				cin >> ele_insere.chave;
				if(insere(&A, ele_insere))
					cout << "ELEMENTO INSERIDO COM SUCESSO" << endl;
				else cout << "ERRO NA OPERAÇÃO" << endl;
				cout << endl;
			break;

			case 3:
				system("clear");
				cout << "Insira o elemento que deseja buscar: ";
				cin >> ele_busca;
				if(busca(&A, ele_busca) != NULL)
					cout << "ELEMENTO ENCONTRADO!" << endl;
				else cout << "ELEMENTO INEXISTENTE" << endl;
				cout << endl;
			break;

			case 4:
				retorno = maior(A.raiz);
				cout << retorno->dado.chave << endl;
				cout << endl;
			break;

			case 5:
				system("clear");
				cout << "Insira o elemento que deseja remover: ";
				cin >> ele_remove;
				if(remove(&A, ele_remove, ret))
					cout << "ELEMENTO " << ret->chave << " REMOVIDO COM SUCESSO" << endl;
				else cout << "ERRO NA OPERAÇÃO" << endl;
				cout << endl;
			break;

			case 6:
				system("clear");
				imprime(&A);
			break;

			case 7:
				retorno = menor_elemento(A.raiz);
				cout << "MENOR ELEMENTO: " << retorno->dado.chave << endl;
				cout << endl;
			break;

			case 8:
				system("clear");
				cout << "Insira um elemento: ";
				cin >> ele_busca;
				retorno = busca(&A, ele_busca);
				if(retorno != NULL)
					cout << "Altura: " << altura_no(retorno) << endl;
				else cout << "ELEMENTO NÃO ENCONTRADO" << endl;
				cout << endl;
			break;
		}
	}while(opt != 0);
}