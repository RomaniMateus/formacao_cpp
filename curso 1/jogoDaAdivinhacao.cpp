#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    cout << "**************************************" << endl;
    cout << "* Bem-vindos ao jogo da adivinhação! *" << endl;
    cout << "**************************************" << endl;

    cout << "Escolha o seu nível de dificuldade:" << endl;
    cout << "Fácil (F), Médio (M) ou Difícil (D)" << endl;

    char dificuldade; 
    cin >> dificuldade; //capturando a resposta do usuário.

    int numero_de_tentativas;

    //definindo uma quantidade total de tentativas para cada nível de dificuldade.
    if(dificuldade == 'F'){
        numero_de_tentativas = 15;
    }
    else if(dificuldade == 'M'){
        numero_de_tentativas = 10;
    }
    else {
        numero_de_tentativas = 5;
    }

    srand(time(NULL)); //configurando um número aleatório para a constante NUMERO_SECRETO;
    const int NUMERO_SECRETO = rand() % 100;

    bool nao_acertou = true;
    int tentativas = 0;

    double pontos = 1000.0; //pontuação inicial do usuário;

    for(tentativas = 1;tentativas <= numero_de_tentativas;tentativas++){ //laço responsável por rodar apenas a quantidade permitida de tentativas que o usuário selecionou.

        int chute;
        cout << "Tentativa " << tentativas << endl;
        cout << "Qual seu chute? ";
        cin >> chute;

        double pontos_perdidos = abs(chute - NUMERO_SECRETO)/2.0; //utilizando o método abs() para calcular o módulo (distância) do chute dado até o valor do número secreto;

        pontos -= pontos_perdidos;

        cout << "O valor do seu chute é: " << chute << endl;
        bool acertou = chute == NUMERO_SECRETO;
        bool maior = chute > NUMERO_SECRETO;

        if (acertou)
        {
            cout << "Parabéns! Você acertou o número secreto!" << endl;
            nao_acertou = false;
            break;
        }
        else if (maior)
        {
            cout << "Seu chute foi maior que o número secreto!" << endl;
        }
        else
        {
            cout << "Seu chute foi menor que o número secreto!" << endl;
        }
    }

    cout << "Fim de jogo!" << endl;
    
    if(nao_acertou){
        cout << "Você perdeu! Tente novamente!" << endl;
    }
    else{
        cout << "Você acertou o número secreto em " << tentativas << " tentativas" << endl;
        cout.precision(2);
        cout << fixed;
        cout << "Sua pontuação foi de " << pontos << " pontos." << endl;
    }
}