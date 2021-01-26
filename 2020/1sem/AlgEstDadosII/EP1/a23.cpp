#include "a23.h"
/*No(): Construtor de "Nó 2" (nó binário) para incluir, basicamente, a raíz*/
No:: No(infoTSO *info, long n, No* Pai){
  infoEsq = info;
  infoDir = NULL;
  N = n;
  nchaves = 1;
  esq = dir = NULL;
  pai = Pai;
  infoDir = NULL;
  centro = NULL;
}

No:: No(infoTSO *info, long n, No *Esq, No *Dir, No *Pai){
  infoEsq = info;
  infoDir = NULL;
  N = n;
  nchaves = 1;
  pai = Pai;
  dir = Dir;
  esq = Esq;
  centro = NULL;
}

// Construtor de Cópia
No:: No(No *no){
  infoEsq = infoCopia(no->infoEsq);
  infoDir = infoCopia(no->infoDir);
  N = no->N;
  nchaves = no->nchaves;
  pai = no->pai;
  esq = no->esq;
  centro = no->centro;
  dir = no->dir;
}

No:: ~No(){
  DelInfo(infoEsq);
  DelInfo(infoDir);
  infoEsq = infoDir = NULL;
  esq = centro = dir = NULL;
}

A23:: A23(){
  raiz = NULL;
  N = 0;
}

A23:: ~A23(){
  destroi(raiz);
  N = 0;
  raiz = NULL;
}

void A23:: destroi(No *no){
  if (!no)
    return;
  destroi(no->esq);
  destroi(no->centro);
  destroi(no->dir);
  delete no;
  no = NULL;
}


long A23:: tamSub(No *no){
  if (!no)
    return 0;
  else
    return no->N;
}

long A23:: tam(){
  return N;
}

No * A23:: busca(No *no, Chave chave){
  if (!no)
    return NULL;
  
  if (igual(no->infoEsq->chave, chave) || igual(no->infoDir->chave, chave))
    return no;
  
  if (menor(chave, no->infoEsq->chave))
    no = busca(no->esq, chave);
  else if (no->nchaves == 1 && maior(chave, no->infoEsq->chave))
    no = busca(no->dir, chave);
  else if (no->nchaves == 2 && menor(chave, no->infoDir->chave))
    no = busca(no->centro, chave);
  else
    no = busca(no->dir, chave);
  return no;
}

/* buscaPai(): Encontra o Pai de um Nó nulo. Se o nó com a chave existir retorna o nó, também
   Útil na função de inserir().
   ATENÇÃO: Resultado deve ser testado, para ver se encontrou o pai do nó nulo, ou um nó com a chave
 */
No * A23:: buscaPaiDoNulo(No *no, Chave chave, No *pai){
  if (!no)
    return pai;
  
  if (igual(no->infoEsq->chave, chave)){
    return no;
  }
  if (no->nchaves == 2 && no->infoDir)
    if (igual(no->infoDir->chave, chave))
      return no;
  
  if (menor(chave, no->infoEsq->chave))
    return  buscaPaiDoNulo(no->esq, chave, no);
  else if (no->nchaves == 1 && maior(chave, no->infoEsq->chave))
    return buscaPaiDoNulo(no->dir, chave, no);
  else if (no->nchaves == 2 && menor(chave, no->infoDir->chave))
    return buscaPaiDoNulo(no->centro, chave, no);
  else
    return buscaPaiDoNulo(no->dir, chave, no);
  //return no;
}

void A23:: insere(Chave *chave, long n){
  long i;
  for (i = 0; i < n; i++)
    insere(chave[i], i);
}

/* insere(): Insere na árvore 2-3
   O algoritmo, primeiro procura pela chave a ser inserida até não encontrá-la.
   - Quando a chave é encontrada, simplesmente acrescenta a nova posição em que a chave foi encontrada no texto de origem
   - Quando a chave não é encontrada, e não há um pai, a raíz é nula, e um nó é inserido na raiz
   - Se um pai onde começar a inserção da chave é encontrado, chama outra função recursiva para fazer o serviço
   - Só em uma hipótese é criado um novo nó alterando o tamanho da árvore: Quando o nó raíz é nulo
   Variáveis:
     Chave chave: Chave a ser inserida
     long pos   : posição da chave no texto de origem */
void A23:: insere(Chave chave, long pos){
  infoTSO *info;
  // Se a chave não existir, retorna o nó pai para inserir a chave
  No *pai = buscaPaiDoNulo(raiz, chave, NULL);
  if (pai){
    // Os dois ifs abaixo testam se pai não é pai, ou seja, se pai é, na verdade, o próprio nó com a chave procurada
    if (igual(pai->infoEsq->chave, chave)){
      insereInfo(chave, pos, pai->infoEsq);
      return;
    }
    else if (pai->nchaves == 2 && igual(pai->infoDir->chave, chave)){
      insereInfo(chave, pos, pai->infoDir);
      return;
    }
  }
  else { // única vez em que um nó será criado sem chamar a próxima função: Na raiz
    info = novaInfo();
    insereInfo(chave, pos, info);
    raiz = new No(info, 1, NULL);
    N++;
    return;
  }
  // Se pai existe, e é de fato pai, ou seja, é o nó onde o processo de inserir a chave na árvore 23 se inicia...
  info = novaInfo();
  insereInfo(chave, pos, info);
  No *novo = new No(info, 1, NULL);
  insere(pai, novo);
}

/* insere(): Insere na árvore 2-3
   Depois da fase em que há um pai para iniciar a inserção da chave na árvore
   - Se pai é um "nó 2" (nó binário), a chave é inserida ao lado da chave anterior no mesmo nó, e este se torna um "nó três" (nó ternário)
   - Se pai é um "nó 3", divide-se o nó pai em 2, e adotam-se procedimentos recursivos para adicionar a chave
   Variáveis:
     No *no      : Nó a partir do qual se tentará fazer a inserção
     *novo: Novo nó a ser inserido contendo a chave e a posição em que foi encontrada no texto externo*/
void A23:: insere(No *no, No *novo){
  
  // Se o novo subiu até que seu pai seja nulo, é porque o novo é a raiz
  if (!no){ // Caso base
    raiz = novo;
    N++;
    raiz->N = tamSub(raiz->esq) + tamSub(raiz->centro) + tamSub(raiz->dir) + 1;
    return;
  }
  
  // Caso "nó 2": Simplesmente coloca a chave do novo nó ao lado da chave do nó pai, e este torna-se um "nó 3" (merge)
  if (no->nchaves == 1){ // Caso base 2
    if (menor(novo->infoEsq->chave, no->infoEsq->chave)){
      no->infoDir = no->infoEsq;
      no->infoEsq = infoCopia(novo->infoEsq);
      no->esq = novo->esq;
      no->centro = novo->dir;
    }
    else {
      no->infoDir = infoCopia(novo->infoEsq);
      no->centro = novo->esq;
      no->dir = novo->dir;
    }
    no->nchaves = 2;
    no->N = tamSub(no->esq) + tamSub(no->centro) + tamSub(no->dir) + 1;
    N++; // Só fazer N++ quando no->nchaves == 2 se o nó subir para a raíz
    return;
  }

  // Caso "nó 3"
  if (no->nchaves == 2){
    // Quebra o "nó 3", junta com o novo, e produz uma subárvore com os 3 novos "nó 2" cuja raiz é o nó do meio
    novo = quebraNo(no, novo);
    no = novo->pai;
    insere(no, novo);
  }
}

/* quebraNo(): Quebra o nó pai em "nós 2", junta com o novo nó, promovendo o que possui a chave de valor médio entre eles
   Baseado no algoritmo e nas figuras do documento https://www.cs.princeton.edu/~dpw/courses/cos326-12/ass/2-3-trees.pdf, na página 5
   Variáveis:
   No *no  : nó a ser quebrado
      *novo: nó ser inserido
      Retorno: Nó com subárvore "Nó - 2" enraizada na chave média */
No * A23:: quebraNo(No* no, No* novo){
  No *p;
  // Insere novo à esquerda de nó, coloca infoDir à direita de nó, que herda os antigos links centro e direita de nó
  if (menor(novo->infoEsq->chave, no->infoEsq->chave)){
    no->esq = novo;
    novo->pai = no;
    p = new No(no->infoDir, tamSub(no->centro) + tamSub(no->dir) + 1, no->centro, no->dir, no);
    no->infoDir = NULL;
    no->centro = NULL;
    no->dir = p;
    no->N = tamSub(no->esq) + tamSub(no->centro) + tamSub(no->dir) + 1;
  }
  // Insere novo no nó, em infoEsq, antigo infoEsq é criado em p e inserido à esquerda, herdando seu link à esquerda. InfoDir é criado, herdando seu nó à direita, recebendo nó direito de novo à esquerda. Da mesma forma, antigo nó recebe novo->esq à direita
  else if (maior(novo->infoEsq->chave, no->infoEsq->chave) && menor(novo->infoEsq->chave, no->infoDir->chave)){
    // operações de swap
    novo->infoDir = no->infoEsq;
    no->infoEsq = novo->infoEsq;
    novo->infoEsq = novo->infoDir;
    novo->infoDir = NULL;
    p = new No(no->infoDir, tamSub(novo->dir) + tamSub(no->dir) + 1, novo->dir, no->dir, no); // criando nó à direita de nó e fazendo swap
    no->infoDir = NULL;
    novo->dir = novo->esq;
    novo->esq = no->esq;
    no->esq = novo;
    novo->pai = no;
    //swap e criação completa, apenas atualizando o tamanho dos nós
    novo->N = 1 + tamSub(novo->esq) + tamSub(novo->dir);
    no->N = 1 + tamSub(no->esq) + tamSub(no->dir);
  }
  // Insere novo à direita de nó, coloca infoEsq à esquerda de nó, que herda os antigos links esquerda e centro de nó
  else {
    no->dir = novo;
    novo->pai = no;
    p = new No(no->infoEsq, tamSub(no->esq) + tamSub(no->centro) + 1, no->esq, no->centro, no);
    no->infoEsq = no->infoDir;
    no->infoDir = NULL;
    no->centro = NULL;
    no->esq = p;
    no->N = tamSub(no->esq) + tamSub(no->centro) + tamSub(no->dir) + 1;
  }
  no->nchaves = 1;
  return no;
}
