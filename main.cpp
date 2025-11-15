#include <iostream>
#include "listaTelefonica.h"

int main()
{
    int escolha;
    string nome, num, aux;
    no *arvore = NULL;
    while (true)
    {
        system("clear || cls");
        cout << "Seja Bem vindo ao sistema de agenda telefonica! \n"
             << "Digite 1 para registrar um telefone na agenda \n"
             << "Digite 2 para remover um telefone da agenda \n"
             << "Digite 3 para editar um telefone da agenda \n"
             << "Digite 4 para buscar um telefone na agenda \n"
             << "Digite 5 para mostrar todos os telefones\n"
             << "Digite 6 para sair \n"
             << endl;
        cin >> escolha;
        switch (escolha)
        {
        case 1:
            system("clear || cls");
            cout << "Digite o nome: " << endl;
            cin.ignore();
            getline(cin, nome);
            cout << "Digite o numero: " << endl;
            getline(cin, num);
            arvore = insereAVL(arvore, nome, num);
            break;
        case 2:
            system("clear || cls");
            cout << "Digite o nome da pessoa que voce quer excluir o telefone: " << endl;
            cin.ignore();
            getline(cin, nome);
            arvore = removeAVLNome(arvore, nome);
            break;
        case 3:
            system("clear || cls");
            cout << "Digite o nome da pessoa com o telefone que voce quer editar: " << endl;
            cin.ignore();
            getline(cin, nome);
            cout << "Digite o novo numero de telefone: " << endl;
            getline(cin, num);
            arvore = editaAVLNome(arvore, nome, num);
            break;
        case 4:
            system("clear || cls");
            cout << "Digite o nome da pessoa que voce quer buscar o telefone: " << endl;
            cin.ignore();
            getline(cin, nome);
            buscaNumero(arvore, nome);
            cin >> aux;
            break;
        case 5:
            system("clear || cls");
            emOrdem(arvore);
            cin >> aux;
            break;
        case 6:
            return 0;
            break;

        default:
            break;
        }
    }
}