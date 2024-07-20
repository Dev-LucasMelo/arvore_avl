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


// função geral que chama as rotações
arvore rotacionar(arvore raiz)
{
    arvore p = raiz;

    if (p->fb > 0)
    {
        arvore u = p->dir;

        if(u->fb >= 0){
            printf("rotacao simples para a esquerda");
            printf("\n P: %d",p->chave);
        }else{
            printf("rotacao dupla para a esquerda");
            printf("\n P: %d",p->chave);
        }
    }
    else
    {
        arvore u = p->esq;

        if(u->fb <= 0){
            //se fator de balanço de u for menor ou igual a 0 a rotação é simples para a direita
            printf("\nrotacao simples para a direita"); 
            printf("\n P: %d",p->chave);
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
        printf("[V: %d]  ", raiz->chave);
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
                    return rotacionar(raiz);
                    break;
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
                    return rotacionar(raiz);
                    break;
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
    }

    return raiz;
}

int main()
{
    // inicializando arvore
    arvore ARV;
    ARV = NULL;
    /// code
    int cresceu;

    ARV = inserir(ARV, 1, &cresceu);
    ARV = inserir(ARV, 3, &cresceu);
    ARV = inserir(ARV, 2, &cresceu);

    printf("\npreOrder: ");
    preorder(ARV);

    return 0;
};