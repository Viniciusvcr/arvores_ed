#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

typedef struct tipo_item{
	int chave;
}item;

typedef struct tipo_no{
	struct tipo_item item;
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

no* insere_raiz(arvore* a, item x){
	no* novo;

	if(vazia(a)){
		novo = cria_no(x);
		a->raiz = novo;
		return novo;
	}
	return NULL;
}

no* insere_dir(no* n, item x){
	no *novo;

	if(n->dir == NULL){
		novo = cria_no(x);
		n->dir = novo;
		return novo;
	}
	return NULL;
}

no* insere_esq(no* n, item x){
	no *novo;

	if(n->esq == NULL){
		novo = cria_no(x);
		n->esq = novo;
		return novo;
	}
	return NULL;
}

void escreve_nos(no* n, int nivel){
	if(n != NULL){
		for(int i=0; i<nivel*4; i++)
			cout << " ";
		cout << n->item.chave << endl;
		escreve_nos(n->esq, ++nivel);
		escreve_nos(n->dir, nivel);
	}
}

void escreve_nos_pre(no* n){
	if(n != NULL){
		cout << n->item.chave << " ";
		escreve_nos_pre(n->esq);
		escreve_nos_pre(n->dir);
	}
}

void escreve_nos_ordem(no* n){
	if(n != NULL){
		escreve_nos_ordem(n->esq);
		cout << n->item.chave << " ";
		escreve_nos_ordem(n->dir);
	}
}

void escreve_nos_pos(no* n){
	if(n != NULL){
		escreve_nos_pos(n->esq);
		escreve_nos_pos(n->dir);
		cout << n->item.chave << " ";
	}
}

void escreve_arvore(arvore* a){
	escreve_nos(a->raiz, 0);
}

no* busca_chave(no* ptr, int chave){
	if(ptr == NULL || ptr->item.chave == chave)
		return ptr;
	if(ptr->item.chave > chave)
		return busca_chave(ptr->esq, chave);
	if(ptr->item.chave < chave)
		return busca_chave(ptr->dir, chave);
}

no* acha_lugar(no* ptr, no* ant, int chave){
	if(ptr == NULL)
		return ant;
	if(chave < ptr->item.chave)
		return acha_lugar(ptr->esq, ptr, chave);
	if(chave > ptr->item.chave)
		return acha_lugar(ptr->dir, ptr, chave);
}

int main(){
	arvore A;
	no *retornos, *lugar;
	item insere;
	int opt, busca;

	inicializa(&A);

	do{
		cout << endl;
		cout << "[1] Vazia?" << endl;
		cout << "[2] Insere raiz" << endl;
		cout << "[3] Insere elemento" << endl;
		cout << "[4] Escreve arvore" << endl;
		cout << "[5] Percursos" << endl;
		cout << "[6] Busca chave" << endl;
		cin >> opt;
		switch(opt){
			case 1:
				if(vazia(&A))
					cout << "Arvore Vazia!" << endl;
				else cout << "Arvore nao vazia!" << endl;
			break;

			case 2:
				system("clear");
				cout << "Insira o elemento: ";
				cin >> insere.chave;
				retornos = insere_raiz(&A, insere);
				if(retornos == NULL)
					cout << "RAIZ PREVIAMENTE INSERIDA!" << endl;
				else cout << retornos->item.chave << " INSERIDO COMO RAIZ!" << endl;
			break;

			case 3:
				system("clear");
				cout << "Insira o elemento: ";
				cin >> insere.chave;
				lugar = acha_lugar(A.raiz, A.raiz, insere.chave);
				if(insere.chave < lugar->item.chave)
					retornos = insere_esq(lugar, insere);
				else retornos = insere_dir(lugar, insere);
				cout << retornos->item.chave << " INSERIDO COM SUCESSO!" << endl;
			break;

			case 4:
				system("clear");
				escreve_arvore(&A);
			break;

			case 5:
				cout << endl;
				escreve_nos_pre(A.raiz);
				cout << endl;
				escreve_nos_ordem(A.raiz);
				cout << endl;
				escreve_nos_pos(A.raiz);
				cout << endl;
			break;

			case 6:
				cout << "Insira a chave a buscar: ";
				cin >> busca;
				retornos = busca_chave(A.raiz, busca);
				if(retornos == NULL)
					cout << "NAO FOI ENCONTRADO" << endl;
				else cout << retornos << endl;
			break;
		}
	}while(opt != 0);
}
