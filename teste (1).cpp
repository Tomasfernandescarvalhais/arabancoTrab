#include <iostream>
#include <fstream>
#include <time.h>
#include <locale.h>
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>

using namespace std;

class movimentacao {
	private:
		char historico [50];
		int valor;
        char hora[9];
		char data[9];
	public:

        movimentacao(){
			char hora[9];
			char data[10];
			char a[9];
			strcpy(a , _strdate(data));
			char t[9];
		    t[0] = a[3];
			t[1] = a[4];
			t[2] = a[5];
			t[3] = a[0];
		 	t[4] = a[1];
			t[5] = a[2];
			t[6] = a[6];
			t[7] = a[7];
			t[8] = a[8];
			strcpy(this -> hora , _strtime(hora));
			strcpy(this -> data , t);
			return;
		}


		void sethistorico (const char* historico ) {
			strcpy (this->historico, historico);
		}

		void setvalor (int valor) {
			this->valor = valor;
		}

		char* gethistorico () {
			return this->historico;
		}

		int getvalor () {
			return this->valor;
		}
		char* gethora(){
			return this->hora;
		}

		char* getdata(){
			return this->data;
		}


};


const int MAX_MOV = 30;

class Conta {
	private:
		int numConta;
		int numAgencia;
		char nomeTitular [50];
		char cpf [12];
		int idMov= 0;
		movimentacao M[MAX_MOV];
		double Saldo;

	public:

		void setnumConta (int numConta) {
			this->numConta = numConta;
		}

		void setnumAgencia (int numAgencia) {
			this->numAgencia = numAgencia;
		}

		void setnomeTitular (const char* nomeTitular ) {
			strcpy (this->nomeTitular, nomeTitular);
		}

		void setcpf (const char* cpf ) {
			strcpy (this->cpf, cpf);
		}

		void setSaldo (double Saldo) {
			this->Saldo = Saldo;
		}
		////////

		int getnumConta (){
			return this->numConta;

		}

		int getnumAgencia () {
			return this->numAgencia;
		}

		char* getnomeTitular () {
			return this->nomeTitular;
		}

		char* getcpf () {
			return this->cpf;
		}

		double getSaldo () {
			return this->Saldo;
		}

		int getaddmovimentacao (movimentacao m) {
			M[idMov] = m;
			idMov ++;
		}

		int getNummovimentacao () {
			return this->idMov;
		}

		movimentacao getmovimentacao (int idMov) {
			return this->M[idMov];
		}

};

const int qtdContas = 10;

class Banco {
	private:
		Conta V [qtdContas];
		int id;
		movimentacao g;

	public:
		Banco () {
			this->id = 0;
		}

		void addConta (Conta a) {
			if (id < qtdContas) {
			movimentacao g;
			g.sethistorico("saldo inicial");
			g.setvalor(a.getSaldo());
			a.getaddmovimentacao(g);
			V[id] = a;
			id++;
			}
			else {

				cout << "Banco cheio\n";
			}
		}

		void clientesBanco () {
			cout << "---- CONTAS CADASTRADAS ----\n\n";
        	cout << "----------------------------\n";
            for(int i = 0; i < id; i++){
                cout << "CONTA: " << V[i].getnumConta() << "\n"
                     << "AGENCIA: " << V[i].getnumAgencia() << "\n"
                     << "TITULAR: " << V[i].getnomeTitular() << "\n"
                     << "CPF: " << V[i].getcpf() << "\n"
                     << "SALDO: R$" << V[i].getSaldo() << "\n"
                     << "----------------------------\n";
            }

		}

		void VerifContas (int Conta, int Ag, bool &t, int &cnt) {
			int c, a;
			
			for (int i = 0; i < id; i++) {
				c = V[i].getnumConta();
				a = V[i].getnumAgencia();
				if (c == Conta && a == Ag) {
					t = true;
					cnt = i;
				}
			}
		}

		void alterarContas(const char* titular, const char* cpf, int &cnt){
            int i = cnt;
			strcpy (V[i].getnomeTitular(), titular);
			strcpy (V[i].getcpf(), cpf);
        }


        void delConta(int &cnt){
            int a = cnt;

            for(int i = a; i < id; i++){
                V[i].setnumConta(V[i+1].getnumConta());
                V[i].setnumAgencia(V[i+1].getnumAgencia());
                strcpy(V[i].getnomeTitular(), V[i+1].getnomeTitular());
                strcpy(V[i].getcpf(), V[i+1].getcpf());
                V[i].setSaldo(V[i+1].getSaldo());

                    for(int j = a+1; i < id; i++){
                            V[i].setnumConta(V[i+1].getnumConta());
                            V[i].setnumAgencia(V[i+1].getnumAgencia());
                            strcpy(V[j].getnomeTitular(), V[i+1].getnomeTitular());
                            strcpy(V[j].getcpf(), V[i+1].getcpf());
                            V[i].setSaldo(V[i+1].getSaldo());
                    }
                id--;
            }
        }

		void mostrarSaldo(int &cnt){
            int i = cnt;
            cout << "\n---- MOSTRAR SALDO ----\n\n";
            cout << "----------------------------\n";
            cout << "CONTA: " << V[i].getnumConta() << "\n"
                 << "AGENCIA: " << V[i].getnumAgencia() << "\n"
                 << "TITULAR: " << V[i].getnomeTitular()<< "\n"
                 << "CPF: " << V[i].getcpf()<< "\n"
                 << "SALDO: R$" << V[i].getSaldo()<< "\n"
                 << "----------------------------\n";
        }

		void Deposito (double deposito, int &cnt) {
			int i = cnt;
			double soma;
			if (deposito < 0) {
				cout << "Valor invalido\n";
			}
			else {
				soma = V[i].getSaldo() + deposito;
				V[i].setSaldo(soma);
				movimentacao g;
                g.sethistorico("Deposito");
                g.setvalor(deposito);
                V[i].getaddmovimentacao(g);
				cout << "Deposito realizado\n";
			}

		}

		void VerifTransf(int Conta, int Ag, bool &t, int &cnt, int ContaDest, int AgDest, bool &t2, int &cnt2){
        int c, a;

            for(int i = 0; i < id; i++){
                c = V[i].getnumConta();
                a = V[i].getnumAgencia();

                if(Conta == c && Ag == a){
                    t = true;
                    cnt = i;
                }
            }

            int c2, a2;

            for(int i = 0; i < id; i++){
                c2 = V[i].getnumConta();
                a2 = V[i].getnumAgencia();

                if(ContaDest == c2 && AgDest == a2){
                    t2 = true;
                    cnt2 = i;
                }
            }
        }

		void Saque(double valSaque, int &cnt){
            int i = cnt;
            int sub;

            if(valSaque < 0){
                cout << "\nValor invalido\n";
            }
            else{
                sub = V[i].getSaldo()- valSaque;

                V[i].setSaldo(sub);
                movimentacao g;
                g.sethistorico("Saque");
                g.setvalor(valSaque);
                V[i].getaddmovimentacao(g);

                cout << "\nSaque realizado\n";
            }
        }

        void Transf(double valTransf, int &cnt, int &cnt2){

         	 int sub = 0, soma = 0;


            if(valTransf < 0){
                cout << "\nValor invalido\n";
            }
            else{
                sub = V[cnt].getSaldo() - valTransf;
                soma = V[cnt2].getSaldo() + valTransf;

                V[cnt].setSaldo(sub);
                movimentacao g;
                g.sethistorico("transferencia");
                g.setvalor(valTransf);
                V[cnt].getaddmovimentacao(g);

                V[cnt2].setSaldo(soma);
                g.sethistorico("transferencia");
                g.setvalor(valTransf);
                V[cnt2].getaddmovimentacao(g);

                cout << "\nTransferencia realizada\n";
            }
        }
        
        void ExtratoNaTela(int &cnt){
        	cout << "DATA" <<"\t\t" << "HORA" << "\t\t" << "MOVIMENTACAO" << "\t\t" << "VALOR" << endl;
            for(int i = 0; i < V[cnt].getNummovimentacao() ; i++){
                cout << V[cnt].getmovimentacao(i).getdata() << "\t";
                cout << V[cnt].getmovimentacao(i).gethora() << "\t";
                cout<< V[cnt].getmovimentacao(i).gethistorico() << "\t";
                cout <<"\t" << V[cnt].getmovimentacao(i).getvalor() << "\t" <<endl;
            }
            cout <<"\n" << "TOTAL :" << V[cnt].getSaldo();
            

        }

        void carregarconta (const char *nomearquivo){
            ifstream fin;
            fin.open(nomearquivo, ios::binary);
            if(!fin){
                cout << "Erro ao abrir o arquivo.\n";
            return;
            }
            fin.read ((char*)this, sizeof(Banco));
            fin.close();
        }
        void salvarconta(const char *nomearquivo){
            ofstream fout;
            fout.open(nomearquivo, ios::binary);
            if(!fout){
                cout << "Erro ao criar o arquivo.\n";
            return;
            }
            fout.write ((char*)this, sizeof(Banco));
            fout.close();
        }


       void extratohtml(int cnt){
        int c = 0;
        c = c + 1;
        ofstream fout;
        fout.open("extrato.html");

                if(!fout){
                    cout << "Erro ao criar o arquivo\n";
                }

                else{
                    fout << "<h2><center> EXTRATO BANCÁRIO </center></h2><br>" << "\n";
                    fout << "<center><b>Nome: </b>" <<  V[cnt].getnomeTitular() << "<b>&emsp;&emsp;&emsp;&emsp;&emsp;Conta / Agência: </b> " << V[cnt].getnumConta() << " / " << V[cnt].getnumAgencia() << "</center>\n";
                    fout << "<center><b> Data: </b>" << V[cnt].getmovimentacao(id).getdata() << "<b>&emsp;&emsp;&emsp;&emsp;&emsp; Horário: </b>" <<V[cnt].getmovimentacao(id).gethora() << "</center>\n";

                    fout << "<br><h3><center> Histórico </center></h3><br>" << "\n";


                    fout << "<!DOCTYPE html> <html> <head> <style> table { font-family: CourierNew, sans-serif; border-collapse: collapse; width: 100%; } td, th { border: 2px solid #dddddd; text-align: left; padding: 8px; } tr:nth-child(even) { background-color: #0099cc; } </style> </head> <body> <table> <tr> <th>Data</th> <th>Horário</th> <th>Movimentaçao</th> <th>Valor(R$) </th> <th>Saldo(R$) </th> </tr>";

					for(int i = 0; i < 1 ; i++){


                    fout << "<tr> <td>" << V[cnt].getmovimentacao(i).gethora() << "</td> <td>" << V[cnt].getmovimentacao(i).gethora() << "</td> <td>" <<V[cnt].getmovimentacao(i).gethistorico() << "</td>  <td>"  "</td>  <td>" << V[cnt].getmovimentacao(i).getvalor() << "</td> </tr>";


                    }

                    for(int i = 1; i < V[cnt].getNummovimentacao() ; i++){


                    fout << "<tr> <td>" << V[cnt].getmovimentacao(i).getdata() << "</td> <td>" << V[cnt].getmovimentacao(i).gethora() << "</td> <td>" << V[cnt].getmovimentacao(i).gethistorico()<< "</td>  <td>"   << V[cnt].getmovimentacao(i).getvalor() <<   "</td> <tr>" << V[cnt].getSaldo();


                    }
                    for(int i = 0; i < 1 ; i++){
                    fout << "<tr> <td>" <<  V[cnt].getmovimentacao(i).getdata() << "</td> <td>" << V[cnt+1].getmovimentacao(i).gethora()  << "</td> <td>" << "Total" << "</td>  <td>"  "</td>  <td>" << "RS " <<V[cnt].getSaldo() << "</td> </tr>";
                	}

				}

        fout.close();
    }

};


int main () {
    system("color 0b");
    setlocale(LC_ALL, "Portuguese");
    int op, conta, agencia, cont = 0, resp_extrato;
    int conta_destino, agencia_destino, cont2;
    bool v2 = false;
    double saldo, deposito, val_saque, val_transf;
    char titular[50], cpf[12];
    bool v = false;
    char lancamento[50];
    Banco b;
    Conta c;
    /*
    c.setnumConta(11);
    c.setnumAgencia(11);
    c.setnomeTitular("teste");
    c.setcpf("12345678901");
    c.setSaldo(100);
    b.addConta(c);
    */

    b.carregarconta("contas.txt");
    do{
        system("cls");
        cout << "--------------------------------------------------\n";
        cout << "| --------------------ARABANCO -------------------  |\n";
         cout <<"| ---------------Sempre com você------------------  |\n";
        cout << "--------------------------------------------------\n\n";
        cout << "Menu de opcoes:\n";
        cout << "1 – Cadastrar Conta Corrente\n";
        cout << "2 – Alterar dados de uma Conta Corrente\n";
        cout << "3 – Excluir uma Conta Corrente\n";
        cout << "4 – Consultar Saldo\n";
        cout << "5 – Fazer Deposito\n";
        cout << "6 – Realizar Saque\n";
        cout << "7 – Transferir Valores\n";
        cout << "8 – Mostrar todas as contas e saldos\n";
        cout << "9 – Emitir extrato de conta\n";
        cout << "10 – Sair\n";
        cout << "\nEscolha uma opcao: ";
        cin >> op;

        switch (op){
            case 1:
                system("cls");

                cout << "CADASTRAR NOVA CONTA CORRENTE\n";

                cout << "\nNumero da conta: ";
                cin >> conta;

                cout << "Agencia: ";
                cin >> agencia;

                cout << "Nome do titular: ";
                cin >> titular;

                cout << "CPF do titular: ";
                cin >> cpf;

                cout << "Saldo: ";
                cin >> saldo;

                if(saldo < 0){
                    while(saldo < 0){
                        cout << "Saldo NEGATIVO INVALIDO PARA O SISTEMA\nDigite o saldo novamento: ";
                        cin >> saldo;
                    }
                }

                c.setnumConta(conta);
                c.setnumAgencia(agencia);
                c.setnomeTitular(titular);
                c.setcpf(cpf);
                c.setSaldo(saldo);

                b.addConta(c);

                cout << "\nCONTA CADASTRADA COM SUCESSO!!!\n";

                system("pause");
            break;

            case 2:
                system("cls");

                cout << "ALTERAR DADOS DE UMA CONTA\n";

                cout << "\nDigite o numero da conta: ";
                cin >> conta;

                cout << "Digite o numero da agencia: ";
                cin >> agencia;

                b.VerifContas(conta, agencia, v, cont);

                if(v == true){
                    cout << "\nInforme o nome do novo titular: ";
                    cin >> titular;

                    cout << "Informe o novo CPF: ";
                    cin >> cpf;

                    c.setnomeTitular(titular);
                    c.setcpf(cpf);

                    b.alterarContas(titular, cpf, cont);
                    v = false;

                    cout << "\nCONTA ALTERADA\n";
                }

                if(v == false){
                    cout << "\nCONTA INVALIDA\nTente Novamente\n";
                }

                system("pause");
            break;

            case 3:
                system("cls");

                cout << "EXCLUIR UMA CONTA\n";

                cout << "\nDigite o numero da conta: ";
                cin >> conta;

                cout << "Digite o numero da agencia: ";
                cin >> agencia;

                b.VerifContas(conta, agencia, v, cont);

                if(v == true){
                    b.delConta(cont);

                    cout << "\nCONTA EXCLUIDA\n";
                }

                if(v == false){
                    cout << "\nCONTA INVALIDA\nTente Novamente\n";
                }

                system("pause");
            break;

            case 4:
                system("cls");
                cout << "CONSULTAR SALDO\n";
                cout << "\nDigite o numero da conta: ";
                cin >> conta;
                cout << "Digite o numero da agencia: ";
                cin >> agencia;
                b.VerifContas(conta, agencia, v, cont);
                if(v == true){
                    b.mostrarSaldo(cont);
                    v = false;
                }
                else{
                    cout << "\nCONTA INVALIDA\nTente Novamente\n";
                }

                system("pause");
            break;

            case 5:
                system("cls");

                cout << "REALIZAR DEPOSITO\n";

                cout << "\nDigite o numero da conta: ";
                cin >> conta;
                cout << "Digite o numero da agencia: ";
                cin >> agencia;

                b.VerifContas(conta, agencia, v, cont);

                if(v == true){
                    b.mostrarSaldo(cont);

                    cout << "Digite o valor a ser depositado: R$";
                    cin >> deposito;

                    b.Deposito(deposito, cont);
                    v = false;
                }

                else{
                    cout << "\nCONTA INVALIDA\nTente Novamente\n";
                }

                system("pause");
            break;

            case 6:
                system("cls");

                cout << "REALIZAR SAQUE\n\n";

                cout << "Digite o numero da conta: ";
                cin >> conta;
                cout << "Digite o numero da agencia: ";
                cin >> agencia;

                b.VerifContas(conta, agencia, v, cont);

                if(v == true){
                    b.mostrarSaldo(cont);

                    cout << "Digite o valor de saque: R$";
                    cin >> val_saque;

                    b.Saque(val_saque, cont);
                    v = false;
                }

                else{
                    cout << "\nCONTA INVALIDA\nTente Novamente\n";
                }

                system("pause");
            break;

            case 7:
                system("cls");

                cout << "REALIZAR TRASFERENCIA\n\n";

                cout << "Digite o numero da conta de ORIGEM: ";
                cin >> conta;
                cout << "Digite o numero da agencia da conta de ORIGEM: ";
                cin >> agencia;

                cout << "\nDigite o numero da conta de DESTINO: ";
                cin >> conta_destino;
                cout << "Digite o numero da agencia da conta de DESTINO: ";
                cin >> agencia_destino;

                b.VerifTransf(conta, agencia, v, cont, conta_destino, agencia_destino, v2, cont2);

                if(v == true && v2 == true){

                    cout << "\n";

                    cout << "CONTA DE ORIGEM: \n";
                    b.mostrarSaldo(cont);

                    cout << "\nCONTA DE DESTINO: \n";
                    b.mostrarSaldo(cont2);

                    cout << "\nInforme o valor a ser TRASFERIDO: R$";
                    cin >> val_transf;

                    b.Transf(val_transf, cont, cont2);
                    v = false;
                    v2 = false;
                }
                else{
                    cout << "\nCONTA INVALIDA\nTente Novamente\n";
                }

                system("pause");
            break;

            case 8:
                system("cls");

                b.clientesBanco();

                system("pause");
            break;

            case 9:
                system("cls");

                cout << "1 – EXTRATO NA TELA\n";
                cout << "2 – EXTRATO EM ARQUIVO HTML\n";
                cout << "\nEscolha uma opcao: ";
                cin >> resp_extrato;

                switch(resp_extrato){
                    case 1:
                        system ("cls");

                        cout << "EXTRATO EM TELA: \n\n";

                        cout << "Digite o numero da conta: ";
                        cin >> conta;
                        cout << "Digite o numero da agencia: ";
                        cin >> agencia;

                        b.VerifContas(conta, agencia, v, cont);

                        if(v == true){
                            b.ExtratoNaTela(cont);
                            v = false;
                        }
                        else{
                            cout << "\nCONTA INVALIDA\nTente Novamente\n";
                        }

                        system("pause");
                    break;

                    case 2:
                    	system("cls");
                    	cout << "EXTRATO HTML: \n\n";
                        cout << "Digite o numero da conta: ";
                        cin >> conta;
                        cout << "Digite o numero da agencia: ";
                        cin >> agencia;
                        
                        b.extratohtml(cont);
                    	system(" C:\\Users\\Tomas\\Desktop\\arabanco-tomas-genilson\\extrato.html");
                		system("pause");
									   
                    break;

                    default:
                        system ("cls");
                        cout << "Opção invalida.\n";
                        system("pause");
                        break;
                }

                system("pause");
            break;

            case 10:

           system("pause");
            break;

            default:
                system ("cls");

                    cout << "Opção invalida.\n";

                system("pause");
            break;
        }

    }while (op != 10);
    b.salvarconta("contas.txt");

	return 0;
}
