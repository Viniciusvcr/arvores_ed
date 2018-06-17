#include <iostream>
#include <stdlib.h>
#include <cmath>

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

int altura_no(no* n){ //Exercício 1 e 13
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

void conta_no_nivel(no* n, int nivel, int nivel_atual, int* qntd){ //exercício 10;
	if(n != NULL){
		if(nivel_atual == nivel)
			(*qntd)++;
		nivel_atual++;
		conta_no_nivel(n->esq, nivel, nivel_atual, qntd);
		conta_no_nivel(n->dir, nivel, nivel_atual, qntd);
	}
}

int conta_nivel(arvore* a, int nivel){ //exercício 10 - protótipo
	int retorno = 0;
	
	conta_no_nivel(a->raiz, nivel, 0, &retorno);
	return retorno;
}

int* lista_nivel(arvore* a){ //exercício 11
	int altura_arvore = altura_no(a->raiz);
	int* lista = (int*)malloc(sizeof(int)*altura_arvore);

	for(int i=0; i<altura_arvore; i++){
		lista[i] = conta_nivel(a, i);
	}

	return lista;
}

void conta_no_folha(no* n, int* qntd){ //exercício 12
	if(n != NULL){
		if(n->esq == NULL && n->dir == NULL)
			(*qntd)++;
		conta_no_folha(n->esq, qntd);
		conta_no_folha(n->dir, qntd);
	}
}

int qntd_folha(arvore* a){ //exercício 12 - protótipo
	int retorno = 0;
	conta_no_folha(a->raiz, &retorno);
	return retorno;
}

int arvore_completa(arvore* a){ //exercício 14
	if(qntd_folha(a) == pow(2, altura_no(a->raiz)-1))
		return 1;
	else return 0;
}

int main(){
	arvore A;
	int opt, ele_busca, ele_remove, *lista;
	no *retorno;
	item ele_insere, *ret;

	inicializa(&A);
	do{
		cout << "[01] Vazia?" << endl;
		cout << "[02] Inserir elemento" << endl;
		cout << "[03] Buscar elemento" << endl;
		cout << "[04] Maior elemento" << endl;
		cout << "[05] Remover elemento" << endl;
		cout << "[06] Mostra árvore" << endl;
		cout << "[07] Menor elemento" << endl;
		cout << "[08] Altura de um nó" << endl;
		cout << "[09] Qntd em um nível" << endl;
		cout << "[10] Lista qntd de nós" << endl;
		cout << "[11] Qntd de nós folha" << endl;
		cout << "[12] Árvore Completa?" << endl;
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

			case 9:
				system("clear");
				cout << "Insira um nível: ";
				cin >> ele_busca;
				cout << "Qntd no nível: " << conta_nivel(&A, ele_busca) << endl;
				cout << endl;
			break;

			case 10:
				lista = lista_nivel(&A);
				cout << endl;
				for(int i=0; i<altura_no(A.raiz); i++){
					cout << i << ":" << lista[i] << endl;
				}
				cout << endl;
			break;

			case 11:
				cout << "QNTD NÓS FOLHA: " << qntd_folha(&A) << endl;
				cout << endl;
			break;

			case 12:
				if(arvore_completa(&A))
					cout << "ÁRVORE COMPLETA" << endl;
				else cout << "ÁRVORE NÃO COMPLETA" << endl;
				cout << endl;
			break;
		}
	}while(opt != 0);
}