#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

struct Telefone
{
    string nome;
    string num;
};

struct no
{
    Telefone cadastro;
    no *filho_dir;
    no *filho_esq;
    int altura;
};

void buscaNumero(no* T, string nome);

int altura_AVL(no *p);

no *newNode(string nome, string num);

no *rotacaoDireita(no *p);

no *rotacaoEsquerda(no *p);

int getBalance(no *N);

no *insereAVL(no *T, string nome, string num);

no *removeAVLNome(no *T, string nome);

no *maiorAB(no *T);

no *balanceiaArvore(no *T);

no *editaAVLNome(no *T, string nome);

void buscaNumero(no *T, string nome)
{
    if (T == NULL)
    {
        cout << "Nao existe um numero de telefone com o nome de '" << nome << "'" << endl;
    }
    else if (nome > T->cadastro.nome)
    {
        buscaNumero(T->filho_dir, nome);
    }
    else if (nome < T->cadastro.nome)
    {
        buscaNumero(T->filho_esq, nome);
    }
    else
    {
        cout << "O numero de '" << nome << "' " << "eh "
             << T->cadastro.num << endl;
    }
}

no *newNode(string nome, string num)
{
    no *novoNo = new no;
    novoNo->cadastro.nome = nome;
    novoNo->cadastro.num = num;
    novoNo->filho_dir = NULL;
    novoNo->filho_esq = NULL;
    novoNo->altura = 1;

    return novoNo;
}

int altura_AVL(no *p)
{
    if (p == NULL)
        return 0;
    return 1 + max(altura_AVL(p->filho_esq), altura_AVL(p->filho_dir));
}

int getBalance(no *N)
{
    if (N == NULL)
        return 0;
    return altura_AVL(N->filho_dir) - altura_AVL(N->filho_esq);
}

no *rotacaoDireita(no *p)
{
    no *q = p->filho_esq;
    no *temp = q->filho_dir;

    q->filho_dir = p;
    p->filho_esq = temp;

    p->altura = altura_AVL(p);
    q->altura = altura_AVL(q);

    return q;
}

no *rotacaoEsquerda(no *p)
{
    no *q = p->filho_dir;
    no *temp = q->filho_esq;

    q->filho_esq = p;
    p->filho_dir = temp;

    p->altura = altura_AVL(p);
    q->altura = altura_AVL(q);

    return q;
}

no *insereAVL(no *T, string nome, string num)
{
    int fb;
    if (T == NULL)
    {
        return newNode(nome, num);
    }
    if (nome > T->cadastro.nome)
    {
        T->filho_dir = insereAVL(T->filho_dir, nome, num);
    }
    else if (nome < T->cadastro.nome)
    {
        T->filho_esq = insereAVL(T->filho_esq, nome, num);
    }
    else
    {
        return T;
    }

    fb = getBalance(T);
    T->altura = altura_AVL(T);

    if (fb > 1 && nome > T->filho_dir->cadastro.nome)
    {
        return rotacaoEsquerda(T);
    }
    if (fb < -1 && nome < T->filho_esq->cadastro.nome)
    {
        return rotacaoDireita(T);
    }
    if (fb > 1 && nome < T->filho_dir->cadastro.nome)
    {
        T->filho_dir = rotacaoDireita(T->filho_dir);
        return rotacaoEsquerda(T);
    }
    if (fb < -1 && nome > T->filho_esq->cadastro.nome)
    {
        T->filho_esq = rotacaoEsquerda(T->filho_esq);
        return rotacaoDireita(T);
    }

    return T;
}

no *removeAVLNome(no *T, string nome)
{
    // int fb;
    no *p;
    if (T == NULL)
    {
        return NULL;
    }
    if (nome > T->cadastro.nome)
    {
        T->filho_dir = removeAVLNome(T->filho_dir, nome);
    }
    else if (nome < T->cadastro.nome)
    {
        T->filho_esq = removeAVLNome(T->filho_esq, nome);
    }
    else
    {
        if (T->filho_dir == NULL && T->filho_esq == NULL)
        {
            p = T;
            delete p;
            T = NULL;
            // return T;
        }
        else if (T->filho_esq == NULL)
        {
            p = T;
            T = T->filho_dir;
            delete p;
            // return T;
        }
        else if (T->filho_dir == NULL)
        {
            p = T;
            T = T->filho_esq;
            delete p;
            // return T;
        }
        else
        {
            p = maiorAB(T->filho_esq);
            T->cadastro.nome = p->cadastro.nome;
            T->cadastro.num = p->cadastro.num;
            T->filho_esq = removeAVLNome(T->filho_esq, p->cadastro.nome);
        }
        // return T;
    }

    if (T == NULL)
        return T;
    T = balanceiaArvore(T);

    return T;
}

no *maiorAB(no *T)
{
    if (T != NULL)
    {
        while (T->filho_dir != NULL)
        {
            T = T->filho_dir;
        }
        return T;
    }
    else
        return NULL;
}

no *balanceiaArvore(no *T)
{
    int fb;
    T->altura = altura_AVL(T);
    fb = getBalance(T);

    if (fb > 1 && getBalance(T->filho_dir) >= 0)
    {
        return rotacaoEsquerda(T);
    }

    if (fb > 1 && getBalance(T->filho_dir) < 0)
    {
        T->filho_dir = rotacaoDireita(T->filho_esq);
        return rotacaoEsquerda(T);
    }

    if (fb < -1 && getBalance(T->filho_esq) <= 0)
    {
        return rotacaoDireita(T);
    }

    if (fb < -1 && getBalance(T->filho_esq) > 0)
    {
        T->filho_esq = rotacaoEsquerda(T->filho_dir);
        return rotacaoDireita(T);
    }

    return T;
}

void emOrdem(no *T)
{
    if (T != NULL)
    {
        emOrdem(T->filho_esq);
        cout << "Nome: " << T->cadastro.nome << '\n'
             << "Telefone: " << T->cadastro.num << '\n'
             << endl;
        emOrdem(T->filho_dir);
    }
}

no *editaAVLNome(no *T, string nome, string num)
{
    T = removeAVLNome(T, nome);
    T = insereAVL(T, nome, num);

    return T;
}
