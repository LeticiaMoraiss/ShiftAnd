#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<locale.h>
#include<iostream>
#include<windows.h>
#include<conio.c> //Biblioteca para cores
using namespace std;

/*========================================================== Assinaturas das Funções ==========================================================================*/
int AbrirArquivoTxt();    //Abre o arquivo no txt
int PesquisaPadrao();   //Pesquisa pelo padrão dentro do texto
void GravandoArquivo(); //Grava dentro do txt o texto com o padrão encontrado em maiusculo
/*============================================================================================================================================================*/

/*========================================================== Variaveis de Escopo Global ======================================================================*/
	char texto[1000]; //Rebece o texto do arquivo txt           obs: o escopo global facilida o uso dessas variveis em mais lugar no programa sem ter que ficar
	char padrao[100]; //Recebe o teto padrão para busca				 passando parametros nas funções
/*============================================================================================================================================================*/

int AbrirArquivoTxt(){
	
	int retorno = 1;
	FILE *file;  //Ponteiro para receber arquivo
	file = fopen ("ARQUIVOTEXTO.txt", "r"); //Ponteiro recebe o arquivo que ira apontar e abre ele no executavel, o "r" significa read ou seja leitura
	
	if(file == NULL){ 
		cout<<"\n\n\t Erro ao abrir arquivo 'ARQUIVOTEXTO.txt', verifique o nome do arquivo ou a pasta de origem!\n ";
		retorno = 0;
	}
	
	textcolor(14);		
	cout<<"\n ====> TEXTO DO ARQUIVO 'ARQUIVOTEXTO.txt' \n\n";	//Imprime o texto na tela
	textcolor(15);
	while(fgets(texto, sizeof(texto) ,file) != NULL){
		cout<<"  "<<texto;
	}
	
	return retorno;	
}

int PesquisaPadrao(){
	char alfabeto[35]={'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v','w', 'x','y', 'z', '.', ',', '!','"','?', ' '};
	int **matriz, l, c; 
	int *R0;
	int pesquisa = 0;
	
	l = strlen(alfabeto); //tamanho do alfabeto
	c = strlen(padrao); //tamanho do padrão
	 
	textcolor(14);
	cout<<"\n\n\n ====> AGUARDE ENQUANTO PROCURAMOS O PADRÃO E PASSAMOS PARA MAIUSCULO\n\n\n";
	Sleep(2000); //Da um delay na tela para simular um processo de busca
     
	matriz = (int **) calloc (l, sizeof(int *)); //Faz alocação dinamica das linhas de uma matriz para fzer a matriz ocorrencia
	if(!matriz){ //Se a matriz for igual a nulo exibe a mensagem
		cout<<"\n Não foi possivel alocar a matriz!";
		return 0;
	}	
	
	for(int i = 0; i < l; i++){
		matriz[i] = (int *) calloc (c, sizeof(int)); //Faz alocação dinamica das colunas de uma matriz para fazer a matriz ocorrencia 
		if(!matriz){ //Se for nulo exibe a mensagem
			cout<<"\n Não foi possivel alocar a matriz!";
			return 0;
		} 	
	}
	
	for(int i = 0; i < l; i++ ){
		for(int j = 0; j < c; j++ ){
			matriz[i][j] = alfabeto[i] == padrao[j];  //Essa comparação ja retorna verdadeiro "1"  ou falso "0" então a matriz ocorrencia ja sera completada 
		}											 //automaticamente com 1 ou 0
	}
	
	R0 = (int *) calloc (c, sizeof(int*)); //Aloca as posições do R0 dinamicamente
	if(!R0){ //Se for nulo exibe a mensagem 
		cout<<"\n Não foi possivel alocar!\n";
		return 0;
	}
	
	textcolor(14);
	cout<<"\n ====> MATRIZ OCORRENCIA \n\n";
	for(int i = 0; i < c; i++ ){
		if(i == 0){
			cout<<"    "<<padrao[i];
		}
		else if(padrao[i] == ' '){
			cout<<padrao[i];
		}
		else{
			cout<<" "<<padrao[i];
		}
		
	}
	cout<<"\n";
	for(int i = 0; i < l; i++){
		textcolor(14);
		cout<<" "<< alfabeto[i]<<": ";  //Exibe o alfabeto
		textcolor(15);
		for(int j = 0; j < c; j++){
			cout<<matriz[i][j]<<" "; //Exibe a matriz ocorrencia 
		}
		if((i+1) == l){ //So exibe o R0 quando ja tiver exibido toda a matriz ocorrencia
			textcolor(14);
			cout<<"\n\n R0: ";
			textcolor(15);
			for(int j = 0; j < c; j++){
				cout<<R0[j]<<" ";
			}
		}
		cout<<"\n";
	}
	textcolor(14);
	cout<<"\n ====> MATRIZ SHIFT-AND \n\n";
	cout<<"\n   R0ant		     M[T[i]]		    R0atual	\n";
	
	for(int i = 0; i < strlen(texto); i++){
		textcolor(14);
		cout<<texto[i]<<": ";
		for(int j = c; j > 0; j--){  //Deslocamento bit a bit 
			R0[j] =  R0[j-1]; //Move as posições do R0 para a frente
			R0[0] = 1;
		}
		textcolor(15);
		for(int j=0; j<c; j++){ //Imprime o R0
			cout<<R0[j]<<" ";
		}
		cout<<"		   ";
		for(int aux=0; aux<strlen(alfabeto); aux++){ //procura na matriz ocorencia o valor de M[T[I]] correspondente a letra do texto
			if(texto[i] == alfabeto[aux]){
				for(int j = 0; j < c; j++){
					textcolor(15);
					cout<<matriz[aux][j]<<" "; //Exibe o valor de M[T[I]]
					if((R0[j]) == 1 && matriz[aux][j] == 1){  //Compara os valores de do R0ant com o M[T[I]] para gerar o R0atual
						R0[j] = 1;
					} 
					else{
						R0[j] = 0;
					}
				}
			}
		}	
		cout<<"			";
		for(int j=0; j<c; j++){ //Exibe o R0 atual
			cout<<R0[j]<<" ";
		}
		
		if(R0[c-1] == 1){ //Se o padrão for encontrado ou seja o bit menos significativo(mais a direita) for 1 ele volta o tamanho do padrão 
			i -= (c - 1); // para colocar em maiusculo
			pesquisa = 1; //Se a pesquisa for igual a 1 é porque o padrão foi encontrado
			for(int aux = 0; aux < c; aux++){
				if(padrao[aux] != ' ' || '!' || '?' || ',' || '.'|| '"') //Condição para não fazer tratamento desnecessario 
					texto[i] = toupper(texto[i]);
				i++; //incrementa a posição no texto
			}
			i--; //Concerta o contador do texto pq ele fica uma casa na frente 
 		}
 		cout<<"\n";
	}
	
	if(pesquisa == 1){ //Se a pesquisa for igual a 1 é porque o padrão foi encontrado, então é chamada a função para gravação do padrão em maiusculo
		GravandoArquivo(); //no txt
	}
	else{
		textcolor(14);
		cout<<"\n ====> PADRÃO NÃO ENONTRADO!!! \n\n";
	}
	
 	free(matriz); //Elimina a matriz da mamoria 
	free(R0); //Elimina o R0 da memora
}

void GravandoArquivo(){
	
	FILE *file;  //Ponteiro para receber arquivo
	file = fopen ("ARQUIVOTEXTO.txt", "r");
	
	textcolor(14);
	cout<<"\n ====> O TEXTO COM O RESULTADO DA BUSCA FOI SALVO NO ARQUIVO 'ARQUIVOTEXTO.txt'! \n\n\n\n";
	
	file = fopen("ARQUIVOTEXTO.txt", "a"); // "a"  de append, salva no final do arquivo sem alterar o texto anterior 
	fprintf(file,"\n\nAs palavras que estão MAIUSCULAS representa seu padrão de busca encontrado\n\n");
	fputs(texto, file);
	
	fclose(file); //Fecha o arquivo	
}

int main(){
	
	setlocale(LC_ALL,"Portuguese");
	
	int retorno;
	
	retorno = AbrirArquivoTxt();
	if(retorno == 0){ //Se o retorno for 0 é pq não foi possivel abrir o arquivo, então o programa é finalizado 
		return 0;
	}
	textcolor(14);
	cout<<"\n\n\n ====> INFORME O PADRÃO PARA A BUSCA DE TEXTO\n\n "; //Pega o padrão informado pelo usuario
	textcolor(15);
	gets(padrao); 
	
	PesquisaPadrao(); //Chamada da função para fazer o shift-and
	
	
getch();
return 0;	
}
