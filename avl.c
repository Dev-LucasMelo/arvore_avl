#include <stdio.h>
#include <stdlib.h>

// Representação da estrutura do nó
typedef struct no
{
    int chave;
    struct no *esq, *dir;
    int fb;
} no;

typedef no *arvore;

arvore rotacao_simples_direita(arvore raiz){
    arvore p,u,t2;

    p = raiz;
    u = p->esq;
    t2 = u->dir;

    u->dir = p;
    p->esq = t2;

    return u;
}

arvore rotacao_simples_esquerda(arvore raiz){
    arvore p,u,t2;

    p = raiz;
    u = p->dir;
    t2 = u->esq;

    //atualizacao de ponteiros 
    u->esq = p;
    p->dir = t2;

    return u;
}
// função geral que chama as rotações e atualiza fator de balanço

arvore rotacao_dupla_direita(arvore raiz){
    //atualizacao de ponteiros
    raiz->esq = rotacao_simples_esquerda(raiz->esq);
    raiz = rotacao_simples_direita(raiz);
   
    return raiz;
}

arvore rotacao_dupla_esquerda(arvore raiz){
    raiz->dir = rotacao_simples_direita(raiz->dir);
    raiz = rotacao_simples_esquerda(raiz);

    return raiz;
}

arvore rotacionar(arvore raiz)
{
    arvore p = raiz;

    if (p->fb > 0)
    {
        //rotacao esquerda 
        arvore u = raiz->dir;

        if(u->fb >= 0){
            //atualização de fator de balanço para cada caso de U (calculos)
            if(u->fb == 1){
                p->fb = 0;
                u->fb = 0;
            }else{
                p->fb = 1;
                u->fb = -1;
            }

            return rotacao_simples_esquerda(raiz);
        }else{
            //atualização de fator de balanço para cada caso de V (calculos) 
            arvore v = u->esq;

            switch (v->fb)
            {
            case -1:
                p->fb = 0;
                u->fb = 1;
                v->fb = 0;
                break;
            case 0:
                p->fb = 0;
                u->fb = 0;
                v->fb = 0;
                break;
            case 1:
                p->fb = -1;
                u->fb = 0;
                v->fb = 0;
                break;
            }

            return rotacao_dupla_esquerda(raiz);
        }
    }
    else
    {
        arvore u = raiz->esq;

        if(u->fb <= 0){
            //se fator de balanço de u for menor ou igual a 0 a rotação é simples para a direita

            if(u->fb == -1){
                p->fb = 0;
                u->fb = 0;
            }else{
                u->fb = 1;
                p->fb = -1; 
            }

            return rotacao_simples_direita(raiz);
        }else{
            arvore v = u->dir;

            //atualizacao de fator de balanço dupla direita
            switch (v->fb)
            {
            case -1:
                p->fb = 1;
                u->fb = 0;
                v->fb = 0;
                break;
            case 0:
                p->fb = 0;
                u->fb = 0;
                v->fb = 0;
                break;
            case 1:
                p->fb = 0;
                u->fb = -1;
                v->fb = 0;
                break;
            }

            return rotacao_dupla_direita(raiz);
        }

    }


    return raiz;
};

void preorder(arvore raiz)
{
    // Caso base implícito na negativa
    if (raiz != NULL)
    {
        printf("[V: %d|FB: %d] -> ", raiz->chave,raiz->fb);
        preorder(raiz->esq);
        preorder(raiz->dir);
    }
}

arvore inserir(arvore raiz, int valor, int *cresceu)
{
    if (raiz == NULL)
    {
        arvore NOVO = (arvore)malloc(sizeof(struct no));

        NOVO->chave = valor;
        NOVO->dir = NULL;
        NOVO->esq = NULL;
        NOVO->fb = 0; // todo novo nó inserido o fator de balanço é 0
        *cresceu = 1;

        return NOVO;
    }
    else
    {
        if (valor > raiz->chave)
        {
            // inserir na direita
            raiz->dir = inserir(raiz->dir, valor, cresceu); // passando endereço de memoria

            // atualização de fator de balanço
            if (*cresceu)
            {
                switch (raiz->fb)
                {
                case -1:
                    raiz->fb = 0;
                    *cresceu = 0;
                    break;
                case 0:
                    raiz->fb = 1;
                    *cresceu = 1;
                    break;
                case 1:
                    *cresceu = 0;
                    return rotacionar(raiz);
                }
            }
        }
        else
        {
            raiz->esq = inserir(raiz->esq, valor, cresceu); // passando endereço de memoria
            // inserir na esquerda

            if (*cresceu)
            {
                switch (raiz->fb)
                {
                case -1:
                    *cresceu = 0;
                    return rotacionar(raiz);
                case 0:
                    raiz->fb = -1;
                    *cresceu = 1;
                    break;
                case 1:
                    raiz->fb = 0;
                    *cresceu = 0;
                    break;
                }
            }
        }
        return raiz;
    }
}

arvore remover(arvore raiz, int valor, int *diminuiu){
    //caso base 

    //tratamento para remover algo de arvore vazia
    if(raiz == NULL){
        *diminuiu = 0;
        return NULL;
    }

    //encontrou o elemento na arvore
    if(raiz->chave == valor){
        *diminuiu = 1; // -> indica que diminuiu

        // possui 0 filhos
        if(raiz->dir == NULL && raiz->esq==NULL){
            free(raiz);
            return NULL;
        }

        //possui exatamente um filho direito
        if(raiz->dir != NULL && raiz->esq==NULL){
            arvore aux = raiz->dir;
            free(raiz);
            return aux;
        }

        //possui exatamente um filho esquerdo
        if(raiz->dir == NULL && raiz->esq != NULL){
            arvore aux = raiz->esq;
            free(raiz);
            return aux;
        }

        //2 filhos (chama caso 0 filhos ou 1 filho recursivamente)
        if(raiz->dir != NULL && raiz->esq != NULL){
            arvore aux = raiz->esq;

            while (aux->dir != NULL){
                aux = aux->dir;
            };
            
            raiz->chave = aux->chave;
            aux->chave = valor;

            raiz->esq = remover(raiz,valor,diminuiu);
            return raiz;
        }

    }else{
        //procura elemento e atualiza fatores de balanço
        if(valor > raiz->chave){
            //implementar caso recursivo a direita + atualização de fator de balanço para cada caso
        }else{
            //implementar caso recursivo a esquerda + atualização de fator de balanço para cada caso
        }
        
    }

    return raiz;
}

int main()
{
    // inicializando arvore
    arvore ARV;
    ARV = NULL;
    int cresceu;
    int diminuiu;

    ARV = inserir(ARV, 20, &cresceu);
    ARV = inserir(ARV, 30, &cresceu);
    ARV = inserir(ARV, 10, &cresceu);
    ARV = inserir(ARV, 25, &cresceu);
    ARV = inserir(ARV, 35, &cresceu);
    ARV = inserir(ARV, 15, &cresceu);
    ARV = inserir(ARV, 5, &cresceu);
    ARV = inserir(ARV, 40, &cresceu);
    ARV = inserir(ARV, 13, &cresceu);

    printf("\npreOrder: ");
    preorder(ARV);



    return 0;
};