/*
	---------PROJETO DE SISTEMA DE CADASTRO AMS----------
	-----Desenvolvido Por Arthur Felipe Muniz Sales------
*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <locale.h>

void MenuDeAcesso();
void MenuDeCadastroDesSenhas_Usuario();
void CadastroAdm();
void CadastroInformacao();
void ConsultaCasdroInfo();
void ConsultaInfoAdm();
void LimpaCache();
int PosicaoDosCaracteres(char caracter);
char CaracterNoVetorDeCaracteres(int posicao);
int Mistura (int posicaRealDoCarecter);
int Desmistura(int posicaoModificada);
//PROTOTIPA��O

char conjuntoDeCaracteres[131] = {'a','�','�','�','�','A','�','�','�','�','b','B','c','C','d','D','e','�','�','�','E','�','�','�','f','F','g','G','h','H','i','�','�','�','I','�','�','�','j','J','k','K','l','L','m','M','n','�','N','�','o','�','�','�','�','O','�','�','�','�','p','P','q','Q','r','R','s','S','t','T','u','�','�','�','U','�','�','�','v','V','x','X','y','�','Y','�','w','W','z','Z',' ','0','1','2','3','4','5','6','7','8','9','!','@','#','$','%','�','&','*','(',')','_','-','=','+','/','?',',','.',';',':','<','>',']','[','}','{','�','�','\\','|'};                                        
//131 caracter VETOR BASE

struct Tabela_Informacoes{
	char site[70];
	char senhaNoSite[70];
	char email[70];
};

struct Tabela_Adm{
	char administradores[70];
	char senhaDeAdm[70];
};

void main(){
	setlocale(LC_ALL, "Portuguese");
	MenuDeAcesso();	
	//return 0;	
}

void MenuDeAcesso(){
	char usuario[70];
	char senha[70];
	bool verifica;
	
	FILE *TabelaAdm;
	
	printf("\n..................Bem vindo Ao SisAMS..................\n\n");
	TabelaAdm = fopen("Administradores.AMS","r");
	
	if(TabelaAdm == NULL){
		printf("Ainda nao existe usuario administrador cadastrado\n");
		printf("Para Cadastrar algum administrador digite senha e usuario padrao\n");
		printf("Usuario e senha eh = admin\n");		
		verifica = true;		
		while (verifica == true){
			printf("Digite o nome de usuario padrao : ");
			gets(usuario);
			LimpaCache();			
			if(strcmp(usuario,"admin")){
				printf("\nUsuario incorreto!\n");
				printf("Tente novamente\n\n");
				verifica = true;
			}else{
				printf("\nUsuario aceito...\n\n");
				printf("Digite a senha Padrao : ");
				gets(senha);
				printf("\n");				
				if(strcmp(senha,"admin")){
					printf("Senha incorreto!\n");
					printf("Tente novamente\n");
					verifica = true;
				}else{
					printf("Primeiro acesso aceito!\n");
					printf("\nAguarde...\n");
					printf("\nVoce sera enviado para a opcoes de cadastro de adm...\n");
					sleep(3);					
					verifica = false;
					LimpaCache();
					CadastroAdm();
				}
			}
		}
	}else{
		int contador;
		int posicao;		
		char userCodificado[70];
		char passwordCodificada[70];		
		char userDecodificado[70];
		char passwordDecodificado[70];		
		char caracter;
		verifica = true;		
		int quantidadeUserCodificada;
		int quantidadeSenhaCodificada;		
		printf("\nVoce tem 3 tentativas para acessar o sistema\n");
		
		for(contador=1; contador < 4; contador++ ){
			printf("\n%d tentativa...\n",contador);
			printf("Digite seu usuario administrador : ");
			gets(usuario);
			printf("Digite sua senha de administrador : ");
			gets(senha);		
			while(!feof(TabelaAdm) && (verifica ==  true) ){				
				fscanf(TabelaAdm,"%s",&userCodificado);	
				quantidadeUserCodificada = strlen(userCodificado);			
				for(contador = 0; contador < quantidadeUserCodificada; contador++){
					posicao = PosicaoDosCaracteres(userCodificado[contador]);
					posicao = Desmistura(posicao);					
					caracter = CaracterNoVetorDeCaracteres(posicao);
					userDecodificado[contador] = caracter;
				}				
				fscanf(TabelaAdm,"%s",&passwordCodificada);	
				quantidadeSenhaCodificada = strlen(passwordCodificada);
				for(contador = 0; contador < quantidadeSenhaCodificada; contador++){
						posicao = PosicaoDosCaracteres(passwordCodificada[contador]);
						posicao = Desmistura(posicao);					
						caracter = CaracterNoVetorDeCaracteres(posicao);
						passwordDecodificado[contador] = caracter;
					}				
				if((strcmp(usuario,userDecodificado)) && (strcmp(senha,passwordDecodificado))){
					printf("\nUsuario e senha nao cadastrado OU Nao Existe...\n");
					verifica = false;					
				}
				else{				
					printf("Usuario e senha correta...");
					printf("\nVoce sera enviado para a opcoes de cadastro...\n");
					contador = 8;
					fclose(TabelaAdm);
					sleep(3);
					LimpaCache();
					verifica = false;
					contador = 7;					
					MenuDeCadastroDesSenhas_Usuario();
				}
			}
		}
		sleep(2);			
	}	
}

void MenuDeCadastroDesSenhas_Usuario(){
	bool verifica = true;
	int opcao;	
	system ("cls");
	
	printf("\n\n-----------MENU DE CADASTRO GERAL-----------\n\n");		
	do{
		printf("Escolha uma das opcoes validas abaixo.\n");
		printf("1 - Cadastrar Administrador\n");
		printf("2 - Consultar Informacoes de adm\n");
		printf("3 - Cadastrar informacoes\n");
		printf("4 - Consultar Informacoes \n");
		printf("5 - Sair - depois 5 novamente para confirmar(Caso necessario)\n\n");		
		printf("Digite uma opcao valida : ");
		LimpaCache();
		scanf("%d",&opcao);		
		switch (opcao){
			case 1 :
				printf("\nOpcao escolhida cadastrar adm\n\n");
				sleep(2);
				system("cls");
				CadastroAdm();				
				break;
			case 2 :
				printf("\nOpcao escolhida Consultar informacao de adm\n\n");
				sleep(2);
				system("cls");
				ConsultaInfoAdm();
				break;
			case 3 :
				printf("\nOpcao escolhida Cadastrar informacao\n\n");
				sleep(2);
				system("cls");
				CadastroInformacao();
				break;
			case 4 :
				printf("\nOpcao escolhida Consultar informacao\n\n");
				sleep(2);
				system("cls");
				ConsultaCasdroInfo();
				break;
			case 5 :
				system("cls");
				printf("\n\nsaindo...\n\n");
				printf("\n\nPrograma Ecerrado...\n\n");
				sleep(2);								
				verifica = false;				
				break;
			default:
				printf("\nOpcao Invalida...\n\n");
				sleep(2);
				system("cls");
				verifica = true;
				break;
		}	
	}while(verifica == true);	
}

void CadastroAdm(){
	FILE *TabelaAdm;
	struct Tabela_Adm adm;
	bool verifica;
	LimpaCache();
	
	int tamandoDigitadoAdm;
	int tamandoDigitadoSN;
	int controlador;
	int posicao;
	char caracter;
	char palavraModificadaADM[70];
	char palavraModificadaSN[70];
	
	verifica = true;
	system ("cls");
	while(verifica == true){	
		printf("\n\n-----------CADASTRO DE ADM-----------\n\n");
		printf("Digite o o novo administrador : ");
		gets(adm.administradores);
		printf("Digite uma senha para esse administrador : ");
		gets(adm.senhaDeAdm);	
		if(strlen(adm.administradores) < 5){
			printf("Digite um Usuario administrador com mais de 5 digitos\n");
		}
		if(strlen(adm.senhaDeAdm) < 8){
			printf("Digite uma Senha com mais de 8 digitos\n");
		}
		else if(strlen(adm.senhaDeAdm) > 8 && strlen(adm.administradores) > 5 ){
			TabelaAdm = fopen("Administradores.AMS","a");			
			tamandoDigitadoAdm = strlen(adm.administradores);			
			for(controlador = 0; controlador < tamandoDigitadoAdm; controlador++){
				posicao = PosicaoDosCaracteres(adm.administradores[controlador]);
				posicao = Mistura(posicao);	
				caracter = CaracterNoVetorDeCaracteres(posicao);
				palavraModificadaADM[controlador] = caracter;				
			}			
			tamandoDigitadoSN = strlen(adm.senhaDeAdm);						
			for(controlador = 0; controlador < tamandoDigitadoSN; controlador++){
				posicao = PosicaoDosCaracteres(adm.senhaDeAdm[controlador]);
				posicao = Mistura(posicao);	
				caracter = CaracterNoVetorDeCaracteres(posicao);
				palavraModificadaSN[controlador] = caracter;			
			}
			
			fprintf(TabelaAdm, "%s\n",palavraModificadaADM);
			fprintf(TabelaAdm, "%s\n",palavraModificadaSN);			
			fclose(TabelaAdm);
			sleep(2);
			printf("\n\nInformacoes salvas....\n\n");
			sleep(2);
			system("cls");
			MenuDeCadastroDesSenhas_Usuario();
			verifica = false;	
		}
	}
}

void CadastroInformacao(){
	FILE * TabelaInfo;
	struct Tabela_Informacoes Tinfo;
	bool verifica;
	LimpaCache();
	TabelaInfo = fopen("Tabela_De_Informacao.AMS","a");	
	int tamandoDigitadoSITE;
	int tamandoDigitadoEMAIL;
	int tamandoDigitadoSNSITE;
	int controlador;
	int posicao;
	char caracter;
	char palavraModificadaSITE[70];
	char palavraModificadaEMAIL[70];
	char palavraModificadaSNSITE[70];
	
	printf("\n\n-----------CADASTRO DE INFORMACOES-----------\n\n");
	printf("Digite o nome do site que vc se cadastrou : ");
	gets(Tinfo.site);	
	printf("Digite o email cadastrado no site : ");
	gets(Tinfo.email);
		
	verifica = true;	
	while(verifica == true){
		printf("Digite a senha cadastrada no site : ");
		gets(Tinfo.senhaNoSite);
		if(strlen(Tinfo.senhaNoSite) < 6){
			printf("N�o existe site que aceite senha menor que 6 digitos...\n");
			printf("Tente Novamente!\n\n");
			sleep(2);
			system("cls");
		}
		else{
			printf("Salvaremos no bando de dados...\n");
			printf("Aguade...");			
			tamandoDigitadoSITE = strlen(Tinfo.site);			
			for(controlador = 0; controlador < tamandoDigitadoSITE; controlador++){
				posicao = PosicaoDosCaracteres(Tinfo.site[controlador]);
				posicao = Mistura(posicao);	
				caracter = CaracterNoVetorDeCaracteres(posicao);
				//printf("\n 2 - %c",caracter);
				palavraModificadaSITE[controlador] = caracter;
			}			
			tamandoDigitadoEMAIL = strlen(Tinfo.email);			
			for(controlador = 0; controlador < tamandoDigitadoEMAIL; controlador++){
				posicao = PosicaoDosCaracteres(Tinfo.email[controlador]);
				posicao = Mistura(posicao);	
				caracter = CaracterNoVetorDeCaracteres(posicao);
				//printf("\n 2 - %c",caracter);
				palavraModificadaEMAIL[controlador] = caracter;
			}			
			tamandoDigitadoSNSITE =  strlen(Tinfo.senhaNoSite);
			for(controlador = 0; controlador < tamandoDigitadoSNSITE; controlador++){
				posicao = PosicaoDosCaracteres(Tinfo.senhaNoSite[controlador]);
				posicao = Mistura(posicao);	
				caracter = CaracterNoVetorDeCaracteres(posicao);
				//printf("\n 2 - %c",caracter);
				palavraModificadaSNSITE[controlador] = caracter;
			}			
			sleep(3);
			system("cls");			
			fprintf(TabelaInfo, "%s\n",palavraModificadaSITE);
			fprintf(TabelaInfo, "%s\n",palavraModificadaEMAIL);
			fprintf(TabelaInfo, "%s\n",palavraModificadaSNSITE);
			fclose(TabelaInfo);
			printf("\n\nInformacoes salvas....\n\n");			
			verifica = false;
			sleep(2);
			system("cls");
			//MenuDeCadastroDesSenhas_Usuario();		
		}
	}
}

void ConsultaCasdroInfo(){
	FILE *consultaInfo;
	char nomeSiteCodificado[70],senhaSiteCodificado[70],emailSiteCodificado[70];
	consultaInfo = fopen("Tabela_De_Informacao.AMS","r");	
	int controlador;
	int posicao;
	int quantidadeCMNomeS;
	int quantidadeDeSS;
	int quantidadeDeESC;	
	char caracter;	
	char nomeSiteDecodificado[70];
	char senhaDoSiteDecodificado[70];
	char emailSiteDecodificado[70];	
	if(consultaInfo == NULL){
		printf("\n Arquivo Nao encontrado...\n\n");
	}else{
		while(!feof(consultaInfo)){				
			fscanf(consultaInfo,"%s",&nomeSiteCodificado);
			quantidadeCMNomeS = strlen(nomeSiteCodificado);
			for(controlador = 0; controlador < quantidadeCMNomeS; controlador++){
				posicao = PosicaoDosCaracteres(nomeSiteCodificado[controlador]);
				posicao = Desmistura(posicao);				
				caracter = CaracterNoVetorDeCaracteres(posicao);
				nomeSiteDecodificado[controlador] = caracter;
			}			
			fscanf(consultaInfo,"%s",&senhaSiteCodificado);
			quantidadeDeSS = strlen(senhaSiteCodificado);
			for(controlador = 0; controlador < quantidadeDeSS; controlador++){
				posicao = PosicaoDosCaracteres(senhaSiteCodificado[controlador]);
				posicao = Desmistura(posicao);				
				caracter = CaracterNoVetorDeCaracteres(posicao);
				senhaDoSiteDecodificado[controlador] = caracter;
			}			
			fscanf(consultaInfo,"%s",&emailSiteCodificado);
			quantidadeDeESC = strlen(emailSiteCodificado);
			for(controlador = 0; controlador < quantidadeDeESC; controlador++){
				posicao = PosicaoDosCaracteres(emailSiteCodificado[controlador]);
				posicao = Desmistura(posicao);				
				caracter = CaracterNoVetorDeCaracteres(posicao);
				emailSiteDecodificado[controlador] = caracter;
			}					
			printf("\nSite Decodificado : %s\t",&nomeSiteDecodificado);
			printf("\nEmail Decodificado: %s\t",&senhaDoSiteDecodificado);
			printf("\nSenha Decodificada: %s\t",&emailSiteDecodificado);
			printf("\n\n -----------------------------------------\n\n");
		}
		fclose(consultaInfo);
	}
}

void ConsultaInfoAdm(){
	FILE *consultaInfoADM;
	char nomeUserAdmCodificado[70],senhaSysCodificada[70];
	consultaInfoADM = fopen("Administradores.AMS","r");	
	int controlador;
	int posicao;	
	int quantidadeDeDigitosNADMC;
	int quantidadeDeSSC;	
	char caracter;	
	char nomeUserAdmDecodificado[70];
	char senhaSysDecodificado[70];	
	if(consultaInfoADM == NULL){
		printf("\n Arquivo Nao encontrado...\n\n");
	}else{
		while(!feof(consultaInfoADM)){			
			fscanf(consultaInfoADM,"%s",&nomeUserAdmCodificado);
			quantidadeDeDigitosNADMC = strlen(nomeUserAdmCodificado);
			for(controlador = 0; controlador < quantidadeDeDigitosNADMC; controlador++){
				posicao = PosicaoDosCaracteres(nomeUserAdmCodificado[controlador]);
				posicao = Desmistura(posicao);				
				caracter = CaracterNoVetorDeCaracteres(posicao);
				nomeUserAdmDecodificado[controlador] = caracter;
			}			
			fscanf(consultaInfoADM,"%s",&senhaSysCodificada);
			quantidadeDeSSC = strlen(senhaSysCodificada);
			for(controlador = 0; controlador < quantidadeDeSSC; controlador++){
				posicao = PosicaoDosCaracteres(senhaSysCodificada[controlador]);
				posicao = Desmistura(posicao);				
				caracter = CaracterNoVetorDeCaracteres(posicao);
				senhaSysDecodificado[controlador] = caracter;
			}			
			printf("\nADM Decodificado : %s\t",&nomeUserAdmDecodificado);
			printf("\nSenha ADM Decodificado: %s\t",&senhaSysDecodificado);
			printf("\n\n -----------------------------------------\n\n");
		}
		fclose(consultaInfoADM);
	}
}

void LimpaCache(){
	fflush(stdin);
}

int PosicaoDosCaracteres(char caracter){
	setlocale(LC_ALL, "Portuguese");
	//criado para aceitar letras com acentos.	
	int controlador;
	int posicaoNoVetor;	
	for(controlador = 0; controlador < 131; controlador++){
		fflush(stdin);
		if( caracter == conjuntoDeCaracteres[controlador]){
			posicaoNoVetor = controlador;
		}
	}	
	return posicaoNoVetor;
}

char CaracterNoVetorDeCaracteres(int posicao){	
	//criado para aceitar letras com acentos.	
	int controlador;
	char CaracterNoVetor;	
	for(controlador = 0; controlador < 131; controlador++){
		fflush(stdin);
		if(posicao == controlador){
			CaracterNoVetor = conjuntoDeCaracteres[controlador];
		}
	}
	return CaracterNoVetor;
}

int Mistura (int posicaRealDoCarecter){
	int valorModificado = 0;
	int controlador;	
	for(controlador = 0; controlador < 131; controlador++){		
		if((posicaRealDoCarecter >= 0) && (posicaRealDoCarecter <= 32)){
			valorModificado = posicaRealDoCarecter + 33;			
		}
		else if((posicaRealDoCarecter > 32) && (posicaRealDoCarecter <= 65)){
			valorModificado = posicaRealDoCarecter - 33;			
		}
		else if((posicaRealDoCarecter >= 66) && (posicaRealDoCarecter <= 100)){
			valorModificado = posicaRealDoCarecter + 31;			
		}
		else if(posicaRealDoCarecter > 100) {
			valorModificado = posicaRealDoCarecter - 35;			
		}
	}
	return valorModificado;
}

int Desmistura(int posicaoModificada){
	int valorReal = 0;
	int controlador;	
	for(controlador = 0; controlador < 131; controlador++){
		if((posicaoModificada >= 33 ) && (posicaoModificada <= 65)){
			valorReal = posicaoModificada - 33;			
		}
		else if((posicaoModificada >= 0) && (posicaoModificada <= 32)){
			valorReal = posicaoModificada + 33;			
		}
		else if((posicaoModificada >= 97) && (posicaoModificada <= 131)){
			valorReal = posicaoModificada - 31;			
		}
		else if((posicaoModificada >= 66) && ((posicaoModificada <= 96 ))) {
			valorReal = posicaoModificada + 35;			
		}		
	}	
}
