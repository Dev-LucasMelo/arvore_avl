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
            printf("\n P: %d",p->chave);
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
            //rotacao dupla para a direita
            printf("\nrotacao dupla para a direita");
            printf("\n P: %d",p->chave);
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

int main()
{
    // inicializando arvore
    arvore ARV;
    ARV = NULL;
    /// code
    int cresceu;

    ARV = inserir(ARV, 6, &cresceu);
    ARV = inserir(ARV, 5, &cresceu);
    ARV = inserir(ARV, 4, &cresceu);
    ARV = inserir(ARV, 3, &cresceu);
    ARV = inserir(ARV, 2, &cresceu);
    ARV = inserir(ARV, 1, &cresceu);

    printf("\npreOrder: ");
    preorder(ARV);

    return 0;
};