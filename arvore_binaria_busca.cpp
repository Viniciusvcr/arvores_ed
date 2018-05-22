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
	novo->item = x;
	novo->esq = NULL;
	novo->dir = NULL;

	return novo;
}

no* inserir_no(no* r, item x){
	if(r == NULL)
		r = cria_no(x);
	else if(r->dado.chave > x.chave)
		r->esq = inserir_no(r->esq, x);
	else if(r->dado.chave < x.chave)
		r->dir = inserir_no(r->dir, x);

	return r;
}

void insere(arvore* a, item x){
	a->raiz = inserir_no(a->raiz, x);
}

