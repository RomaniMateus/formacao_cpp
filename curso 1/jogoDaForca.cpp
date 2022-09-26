#include <locale>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

string palavra_secreta; 
map<char, bool> chutou;
vector<char> chutes_errados;

bool letraExiste( char);
bool naoAcertou();
bool naoEnforcou();
void imprimeCabecalho();
void imprimeErros();
void imprimePalavra();
void chuta();
vector<string> leArquivo();
void sorteiaPalavra();
void salvaArquivo(vector<string>);
void adicionaPalavra();

int main () 
{
    setlocale(LC_ALL, "");

    imprimeCabecalho();

    leArquivo();
    sorteiaPalavra();

    while(naoAcertou() && naoEnforcou())
    {    
        imprimeErros();

        imprimePalavra();

        chuta();
    }

    cout << "Fim de jogo!" << endl;
    cout << "A palavra secreta era: " << palavra_secreta << endl;

    if(naoAcertou())
    {    
        cout << "Você perdeu! Tente novamente!" << endl;
    }
    else
    {    
        cout << "Parabéns! Você acertou a palavra secreta!" << endl;

        cout << "Você deseja adicionar uma nova palavra ao banco? (S/N) ";
        char resposta;
        cin >> resposta;

        if(resposta == 'S')
        {    
            adicionaPalavra();
        }
    }
}

bool letraExiste(char chute)
{
    for(char letra : palavra_secreta)
    {
        if(chute == letra)
        {
            return true;
        }
    }

    return false;
}

bool naoAcertou()
{    
    for(char letra : palavra_secreta)
    {    
        if(!chutou[letra])
        {    
            return true;
        }
    }

    return false;
}

bool naoEnforcou()
{    
    return chutes_errados.size() < 5;
}

void imprimeCabecalho()
{    
    cout << "*********************" << endl;
    cout << "*** Jogo da Forca ***" << endl;
    cout << "*********************" << endl;
    cout << endl;
}

void imprimeErros()
{    
    cout << "Chutes errados: ";

    for(char letra: chutes_errados)
    {    
        cout << letra << " ";
    }

    cout << endl;
}

void imprimePalavra()
{    
    for(char letra : palavra_secreta)
    {    
        if(chutou[letra])
        {    
            cout << letra << " ";
        }
        else
        {    
            cout << "_ ";
        }
    }

    cout << endl;
}

void chuta()
{    
    cout << "Seu chute: ";
    char chute;
    cin >> chute;

    chutou[chute] = true;

    if(letraExiste(chute))
    {    
        cout << "Você acertou! Seu chute está na palavra." << endl;
    }
    else
    {    
        cout << "Você errou! Seu chute não está na palavra." << endl;
        chutes_errados.push_back(chute);
    }

    cout << endl;
}

vector<string> leArquivo()
{    
    ifstream arquivo;
    arquivo.open("palavras.txt");

    if(arquivo.is_open())
    {
        int quantidade_palavras;
        arquivo >> quantidade_palavras;


        vector<string> palavras_do_arquivo;

        for(int i=0;i<quantidade_palavras;i++)
        {
            string palavra_lida;
            arquivo >> palavra_lida;
            palavras_do_arquivo.push_back(palavra_lida);
        }

        arquivo.close();
        return palavras_do_arquivo;
    }
    else
    {
        cout << "Não foi possível acessar o banco de palavras." << endl;
        exit(0);
    }
}

void sorteiaPalavra()
{    
    vector<string> palavras = leArquivo();

    srand(time(NULL));
    int indice_sorteado = rand() % palavras.size();

    palavra_secreta = palavras[indice_sorteado];
}

void salvaArquivo(vector<string> nova_lista)
{    
    ofstream arquivo;
    arquivo.open("palavras.txt");
    if(arquivo.is_open())
    {    
        arquivo << nova_lista.size() << endl;

        for(string palavra : nova_lista)
        {    
            arquivo << palavra << endl;
        }

        arquivo.close();
    }
    else
    {    
        cout << "Não foi possível acessar o banco de palavras." << endl;
        exit(0);
    }
}

void adicionaPalavra()
{    
    cout << "Digite a nova palavra, usando letras maiúsculas." << endl;
    string nova_palavra;
    cin >> nova_palavra;

    vector<string> lista_palavras = leArquivo();
    lista_palavras.push_back(nova_palavra);

    salvaArquivo(lista_palavras);
}