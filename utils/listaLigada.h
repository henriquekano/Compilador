#ifndef LISTALIGADA_H_INCLUDED
#define LISTALIGADA_H_INCLUDED

typedef char TipoDoElemento;

typedef struct No {
    TipoDoElemento info;
    struct No *prox;
} No;

typedef No * TipoDaPosicao;

typedef struct {
    int comp; /*componentes*/
    No *cabeca;
} Lista;

void constroi(Lista *l);
void destroi(Lista *l);
void leitura(Lista *l);
void imprime(No *c);

int comprimento(Lista *l);
int vazia(Lista *l);

TipoDaPosicao primeiro(Lista *l);
TipoDaPosicao proximo(TipoDaPosicao p, Lista *l);
TipoDaPosicao localizaAnterior(TipoDaPosicao p, Lista *l);
TipoDaPosicao localiza(TipoDoElemento x, Lista *l);
void insereInicio(TipoDoElemento x, Lista *l);
void insereFim(TipoDoElemento x, Lista *l);
void remova(TipoDaPosicao p, Lista *l);

TipoDoElemento acessa(TipoDaPosicao p, Lista *l);

void overflow(Lista *l);
void imprimeLista(Lista *l);

int ehPrimo(int numero);

char *toArray(Lista *l);

#endif // LISTALIGADA_H_INCLUDED
