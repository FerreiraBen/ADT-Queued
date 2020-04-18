#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef void (*TImpressora)(void*);
typedef struct lista TLista;
TLista *criarLista();
void inserirInicioLSE(TLista *lst, void *e_carganova);
void inserirFinalLSE(TLista *lst, void *e_carganova);
void* removerInicioLSE(TLista *lst);
void* removerFinalLSE(TLista *lst);
void imprimirLSE(TLista *lst, TImpressora impressora);
typedef struct fila TFila;
TFila *criarFila();
void enfileirar(TFila *f, void *novoElem);
void *desenfileirar(TFila *f);


typedef struct elemento{
  void *carga; // carga util
  struct elemento *prox; // ponteiro proximo
} TElemento;

struct lista{
  int nroElementos;
  TElemento *inicio;
  TElemento *final;
};

TLista *criarLista(){
  TLista *e_lista = malloc(sizeof(TLista));

  e_lista->nroElementos = 0;
  e_lista->inicio=NULL;
  e_lista->final = NULL;

  return e_lista;
}

void inserirInicioLSE(TLista *lst, void *e_carganova){
  // lista vazia
  if (lst->inicio == NULL){
    TElemento *elem = malloc(sizeof(TElemento));
    elem->carga = e_carganova;
    elem->prox = NULL;

    lst->inicio = elem;
    lst->final = elem;
    lst->nroElementos = 1;
  }else{
    // trocar o inicio da Lista
    TElemento *elem = malloc(sizeof(TElemento));
    elem->prox = lst->inicio;
    elem->carga = e_carganova;
    lst->inicio = elem;
    lst->nroElementos++;
  }
}

void inserirFinalLSE(TLista *lst, void *e_carganova){
  // lista vazia
  if (lst->inicio == NULL){
    TElemento *elem = malloc(sizeof(TElemento));
    elem->carga = e_carganova;
    elem->prox = NULL;

    lst->inicio = elem;
    lst->final = elem;
    lst->nroElementos = 1;
  }else{
    // trocar o final da Lista
    TElemento *elem = malloc(sizeof(TElemento));

    lst->final->prox = elem;
    elem->carga = e_carganova;
    elem->prox = NULL;

    lst->final = elem;
    lst->nroElementos++;
  }
}

void* removerInicioLSE(TLista *lst){
  void *carga=NULL;
  if (lst->inicio != NULL){
    TElemento *prim = lst->inicio;
    TElemento *e_novoInicio = prim->prox;
    carga = prim->carga;

    free(prim);
    lst->inicio = e_novoInicio;
    lst->nroElementos--;
    if (lst->inicio == NULL)
      lst->final = NULL;
  }else{
    //printf("Lista Vazia\n");
  }
  return carga;
}

void* removerFinalLSE(TLista *lst){
  void *carga=NULL;
  if(lst->inicio != NULL){
    TElemento *anterior=NULL;
    TElemento *caminhador = lst->inicio;
    while(caminhador->prox!=NULL){
      anterior = caminhador;
      caminhador = caminhador->prox;
    }
    carga = lst->final->carga;

    free(lst->final);
    lst->final = anterior;
    if (lst->final == NULL){
      lst->inicio=NULL;
    }else{
      lst->final->prox = NULL;
    }
    lst->nroElementos--;
  }else{
    //printf("Lista Vazia\n");
  }
  return carga;
}

void imprimirLSE(TLista *lst, TImpressora impressora){
  if (lst->inicio == NULL){
      printf("Lista Vazia\n");
  }else{
    TElemento *caminhador=lst->inicio;
    while(caminhador != NULL){
      impressora(caminhador->carga);
      caminhador = caminhador->prox;
    }
 }
}





struct fila{
  // int tamanhoMax;
  int tamanho;
  TLista *lista;
};

TFila *criarFila(){
  TFila *f = malloc(sizeof(TFila));
  f->tamanho = 0;
  f->lista = criarLista();

  return f;
}

void enfileirar(TFila *f, void *novoElem){
  inserirFinalLSE(f->lista, novoElem);
  f->tamanho++;
}

void *desenfileirar(TFila *f){
  void *elemento = removerInicioLSE(f->lista);
  if(elemento != NULL)
    f->tamanho--;

  return elemento;
}

typedef struct value{
  double valor;
} TValor;




int main(){
  TFila *filinha = criarFila();
  TValor *v;
  v = malloc(sizeof(TValor));
  TValor *a;
  a = malloc(sizeof(TValor));
  TValor *b;
  b = malloc(sizeof(TValor));

  char funcao;
  char tipo[7];
  int aux;
  double auxd;

  scanf(" %s",&tipo);

  if(strcmp(tipo,"inteiro") == 0 ){

    scanf(" %c",&funcao);

    while(funcao != 'X'){
      if(funcao == 'E'){
         v = malloc(sizeof(TValor));
         scanf("%lf",&auxd);
         v->valor = auxd;
         enfileirar(filinha,v);
       }
       else if(funcao == 'D'){
         if(filinha->tamanho >0){  
            a = malloc(sizeof(TValor));
            a = desenfileirar(filinha);
            printf("%d\n",(int) a->valor);
         }
       }
       else if(funcao == 'P'){
         a = malloc(sizeof(TValor));
         a = (filinha->lista->inicio->carga);
         printf("%d\n",(int)a->valor);
       }
       else if(funcao == 'U'){
         a = malloc(sizeof(TValor));
         a = filinha->lista->final->carga;
         printf("%d\n", (int) (a->valor));
       }
       else if(funcao == 'C'){
         printf("%d\n", filinha->tamanho);
       }
       else if(funcao == 'V'){
         if(filinha->tamanho == 0){
            printf("verdadeiro\n");
         }
         else{
            printf("falso\n");
         }
       }

       scanf(" %c",&funcao);
    }
    

  }

  else if(strcmp(tipo,"double") == 0){
   
      scanf(" %c",&funcao);

    while(funcao != 'X'){
      if(funcao == 'E'){
         v = malloc(sizeof(TValor));
         scanf("%lf",&auxd);
         v->valor = auxd;
         enfileirar(filinha,v);
       }
       else if(funcao == 'D'){
         if(filinha->tamanho >0){
            a = malloc(sizeof(TValor));
            a = desenfileirar(filinha);
            printf("%.3lf\n", a->valor);
         }
       }
       else if(funcao == 'P'){
         a = malloc(sizeof(TValor));
         a = (filinha->lista->inicio->carga);
         printf("%.3lf\n",a->valor);
       }
       else if(funcao == 'U'){
         a = malloc(sizeof(TValor));
         a = filinha->lista->final->carga;
         printf("%.3lf\n", (a->valor));
       }
       else if(funcao == 'C'){
         printf("%d\n", filinha->tamanho);
       }
       else if(funcao == 'V'){
         if(filinha->tamanho == 0){
            printf("verdadeiro\n");
         }
         else{
            printf("falso\n");
         }
       }

       scanf(" %c",&funcao);
    }

  }

}
