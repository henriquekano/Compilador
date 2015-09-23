#include<stdio.h>
#include<stdlib.h>

#include "listaLigada.h"

void constroi(Lista *l)
{
    l->comp = 0;
    l->cabeca = NULL;
}

void destroi(Lista *l)
{
    No *p = l->cabeca;
    No *paux;
    while (p != NULL) {
        paux = p;
        p = p->prox;
        /*Se eu der free antes de eu pegar o proximo, eu perco a referencia pro proximo*/
        free(paux);
    }
    l->comp = 0;
}

/*
Apontador apontando para um apontador
cabeca foi declarada como ponteiro
e foi passada como parametro do tipo
ponteiro para o metodo leitura
*/

void leitura(Lista *l)
{
    int num;

    printf("Digite uma sequencia de inteiros\n");
    scanf("%d", &num);

    while(num != 0) {
        insereInicio(num, l);
        scanf("%d", &num);
    }
}

void imprimeLista(Lista *l)
{
    No *z = primeiro(l);
    if (vazia(l))
        printf("Lista vazia");
    else {
        printf("\n\n");
        while (z != NULL) {
            printf("\t%d\n", acessa(z, l));
            z = proximo(z, l);
        }
    }
}

int comprimento(Lista *l)
{
    return l->comp;
}

int vazia (Lista *l)
{
    return l->comp == 0;
}

void insereInicio(TipoDoElemento x, Lista *l)
{
    No *paux = NULL;
    paux = (No *)malloc(sizeof(No));
    if (paux != NULL) {
        paux->info = x;
        paux->prox = l->cabeca;
        l->cabeca = paux;
        l->comp++;
    } else
        overflow(l);
}

TipoDaPosicao localiza(TipoDoElemento x, Lista *l)
{
    No *p = l->cabeca;
    while (p != NULL) {
        if (p->info == x)
            return p;
        p = p->prox;
    }
    return NULL;
}

TipoDaPosicao localizaAnterior(TipoDaPosicao p, Lista *l)
{
    No *i = l->cabeca;
    while (i != NULL && i->prox != p) {
        i = i->prox;
    }
    return i;
}

void remova(TipoDaPosicao p, Lista *l)
{
    No *a = localizaAnterior(p, l);
    if (a == NULL) {
        l->cabeca = p->prox;
    }
    else {
        a->prox = p->prox;
    }
    l->comp--;
    free(p);
}

void overflow(Lista *l)
{
    printf("OVERFLOW!!!");
}

TipoDaPosicao primeiro(Lista *l)
{
    if(!vazia(l))
        return l->cabeca;
}

TipoDaPosicao proximo(TipoDaPosicao p, Lista *l)
{
    No *i = l->cabeca;
    i = p;
    return i->prox;
}

TipoDoElemento acessa(TipoDaPosicao p, Lista *l)
{
    No *b = l->cabeca;
    b = p;
    return b->info;
}

int ehPrimo(int numero)
{
    int i, primo = 1;
    if (numero == 1)
        return 0;
    for (i = 2; i < numero; i++) {
        if (numero%i == 0)
            primo = 0;
    }
    return primo;
}
