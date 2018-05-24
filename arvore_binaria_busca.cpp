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
	no *aux = n;
	while(aux->dir != NULL)
		aux = aux->dir;
	return aux;
}

no* maior_rec(no* n){
	if(n->dir == NULL)
		return n;
	else return maior_rec(n->dir);
}

int main(){
	arvore A;
	int opt, ele_busca;
	no *retorno;
	item ele_insere;

	inicializa(&A);
	do{
		cout << "[1] Vazia?" << endl;
		cout << "[2] Inserir elemento" << endl;
		cout << "[3] Buscar elemento" << endl;
		cout << "[4] Maior elemento" << endl;
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
				retorno = maior_rec(A.raiz);
				cout << retorno->dado.chave << endl;
				cout << endl;
			break; 
		}
	}while(opt != 0);
}