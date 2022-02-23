#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Z 40

struct data{
	int dia, mes, ano;
};

struct horario{
	int hora, minuto;
};

struct evento{
	struct data data;
	struct horario inicio;
	struct horario fim;
	char descricao[Z] ;
	char local[Z];
};

void le_evento( struct evento *p );
void mostra_evento( struct evento x );

void le_data( struct data *p );
void mostra_data (struct data x );

void le_horario( struct horario *p );
void mostra_horario (struct horario x );

int compara_data( struct evento x, struct evento y );
void mostra_vetor( struct evento *v, int n );
int busca_evento( struct evento *v, int n, char *descricao );
void ordena_vetor( struct evento *v, int n );
void mostra_vetor_por_letra( struct evento *v, int n , char letra );
void mostra_vetor_por_data( struct evento *v, int n , int dia, int mes, int ano );

int remove_evento(struct evento *v, int n, int dia, int mes, int ano, int hora, int minuto);
int sobrepor( struct evento *v, int n);
int validacao( struct evento *v, int n);
void entrada_invalida(struct evento *v, int n);


int main(int argc, char *argv[]) {
	int i, n = 0;  // Quantidade de eventos
	struct evento *v = NULL; // Ponteiro para o vetor de eventos
	char descricao[30];
	int idx, dia, mes, ano, hora, minuto, valida;
	
	FILE *f;
	f = fopen( "cadastro.txt" , "rt" );
	if( f != NULL){
		// Carrega dados do arquivo, alocando o vetor v;
		fscanf( f , "%d", &n); // Carrega a quantidade de eventos (1a info no arquivo)
		v = malloc( sizeof( struct evento ) * n );
		for( i = 0 ; i < n ; i++ ){
			fscanf( f, "%d", &v[i].data.dia);
			fscanf( f, "%d", &v[i].data.mes);
			fscanf( f, "%d", &v[i].data.ano);
			fscanf( f, "%d", &v[i].inicio.hora);
			fscanf( f, "%d", &v[i].inicio.minuto);
			fscanf( f, "%d", &v[i].fim.hora);
			fscanf( f, "%d", &v[i].fim.minuto);
			fscanf( f, " %[^\n]", v[i].descricao);
			fscanf( f, " %[^\n]", v[i].local);

		}
		fclose( f );
		printf("%d registros carregados com sucesso!\n", n);
		system("PAUSE");
	}
	
	int opcao;
	do{
		system("CLS");
		printf("1-Cadastrar\n2-Mostrar lista\n3-Mostra por data\n4-Mostra por descricao\n");
		printf("5-Remover evento\n6-Sair\n");
		scanf("%d", &opcao);
		dia = 0;
		mes = 0;
		ano = 0;
		
		switch( opcao ){
			case 1:
				n++;
				v = realloc( v, sizeof( struct evento ) * n );
				le_evento( &v[n-1] );

				valida = validacao(v, n);
				idx = sobrepor(v, n);
				if(valida == -1){
					printf("Data ou hora com valores invalidos!\n");
					entrada_invalida(v, n);
					n--;
				} else if(idx == -1){
					printf("Um horario nao pode sobrepor o horario de outro evento!\n");
					entrada_invalida(v, n);
					n--;
				} else {
					ordena_vetor(v, n);
				}

				system("PAUSE");
				break;
				

			case 2:
				if(n == 0){
					printf("Nao ha nenhum evento registrado!\n");
				} else {
					mostra_vetor( v, n );
				}

				system("PAUSE");
				break;
				
			case 3:
				if(n == 0){
					printf("Nao ha nenhum evento registrado!\n");
				} else {
					printf("Digite um dia: ");
					scanf(" %d", &dia);
					printf("Digite um mes: ");
					scanf(" %d", &mes);
					printf("Digite um ano: ");
					scanf(" %d", &ano);
					mostra_vetor_por_data( v, n, dia, mes, ano );
				}

				system("PAUSE");
				break;

				
			case 4:
				if(n == 0){
					printf("Nao ha nenhum evento registrado!\n");
				} else {				
					printf("Digite o descricao da evento a ser buscada: ");
					scanf(" %[^\n]", descricao );
					
					idx = busca_evento( v, n, descricao );
					if( idx == -1 )
						printf("evento nao encotrada!\n");
					else{
						printf("---- Evento %d ----\n", idx+1 );
						mostra_evento( v[idx] );
					}
				}

				system("PAUSE");
				break;
				
			case 5:
				if(n == 0){
					printf("Nao ha nenhum evento registrado!\n");
				} else {
					printf("Digite a data do evento a ser removido.");
					printf("\nDia: ");
					scanf("%d", &dia);
					printf("Mes: ");
					scanf("%d", &mes);
					printf("Ano: ");
					scanf("%d", &ano);
					printf("Digite o horario de inicio do evento a ser removido.");
					printf("\nHora: ");
					scanf("%d", &hora);
					printf("Minuto: ");
					scanf("%d", &minuto);
					int x = remove_evento(v, n, dia, mes, ano, hora, minuto);
					if (x>0){
						n--;
						v = realloc( v, sizeof( struct evento ) * n );
				}}
				system("PAUSE");
				break;
		}
		
	}while( opcao != 6 );
	
	f = fopen( "cadastro.txt", "wt" );
	fprintf( f, "%d\n", n);
	for( i = 0 ; i < n ; i++ ){
		fprintf( f, "%d\n%d\n%d\n", v[i].data.dia, v[i].data.mes, v[i].data.ano);	
		fprintf( f, "%d\n%d\n%d\n", v[i].inicio.hora, v[i].inicio.minuto, v[i].fim.hora, v[i].fim.minuto);	
		fprintf( f, "%s\n%s\n", v[i].descricao, v[i].local);

	}
	fclose( f );
	
	free( v );

	return 0;
}

void le_evento( struct evento *p ){
	printf("Digite a data:\n");
	le_data( &p->data );
	printf("Digite o horario de inicio:\n");
	le_horario( &p->inicio );
	printf("Digite o horario de fim:\n");
	le_horario( &p->fim );
	printf("Digite a descricao: ");
	scanf(" %[^\n]", p->descricao);
	printf("Digite o local: ");
	scanf(" %[^\n]", p->local);

}

void mostra_evento( struct evento x ){
	printf("Data:_______________");
	mostra_data( x.data );
	printf("Horario: ___________");
	mostra_horario( x.inicio );
	printf("-");
	mostra_horario( x.fim );
	printf("\n");
	printf("Descricao e local:___");
	printf("%s, %s \n\n", x.descricao, x.local);
}

void le_data( struct data *p ){
	printf("Digite o dia: ");
	scanf("%d", &p->dia);
	printf("Digite o mes: ");
	scanf("%d", &p->mes);
	printf("Digite o ano: ");
	scanf("%d", &p->ano);
}

void mostra_data (struct data x ){
	printf("%d/%d/%d\n", x.dia, x.mes, x.ano);
}

void le_horario( struct horario *p ){
	printf("Digite as horas: ");
	scanf("%d", &p->hora);
	printf("Digite os minutos: ");
	scanf("%d", &p->minuto);
}

void mostra_horario (struct horario x ){
	printf("[%dh%dmin]", x.hora, x.minuto);
}

void mostra_vetor( struct evento *v, int n ){
	if( n == 0 )
		printf("Nao ha eventos cadastrados!\n");
	else{
		int i;
		printf("Lista de eventos cadastrados:\n\n");
		for( i = 0 ; i < n ; i++ ){
			printf("---- Evento %d ----\n", i+1 );
			mostra_evento( v[i] );
		}
	}
}

int busca_evento( struct evento *v, int n, char *descricao ){
	int i;
	for( i = 0 ; i < n ; i++ )
		if( strcmp( v[i].descricao, descricao ) == 0 )
			return i;
	
	return -1;
}

void ordena_vetor( struct evento *v, int n ){
	int i;
	for( i = 0 ; i < n-1 ; i++ ){
		int j, i_menor = i;
		for( j = i+1 ; j < n ; j++ ){
			if( compara_data( v[j], v[i_menor ] ) < 0 )
					i_menor = j;}
		struct evento temp = v[i];
		v[i] = v[i_menor];
		v[i_menor] = temp;
	}}


int compara_data( struct evento x, struct evento y ){
	if(x.data.ano < y.data.ano)
		return -1;
	else if(x.data.ano > y.data.ano)
		return 0;
	else if(x.data.mes < y.data.mes)
		return -1;
	else if(x.data.mes > y.data.mes)
		return 0;
	else if(x.data.dia < y.data.dia)
		return -1;	
	else if(x.data.dia > y.data.dia)
		return 0;	
	else if(x.inicio.hora < y.inicio.hora)
		return -1;
	else if(x.inicio.hora > y.inicio.hora)
		return 0;
	else if(x.inicio.minuto < y.inicio.minuto)
		return -1;
	else if(x.inicio.minuto > y.inicio.minuto)
		return 0;
	else 
		return 0;
}

void mostra_vetor_por_letra( struct evento *v, int n , char letra ){
	int i;
	printf("Lista de eventos cujo descricao comeca com a letra %c\n", letra);
	for( i = 0 ; i < n ; i++ )
		if( v[i].descricao[0] == letra )
			mostra_evento( v[i] );
}

void mostra_vetor_por_data( struct evento *v, int n , int dia, int mes, int ano ){
	int i;
	printf("Lista de eventos na data [%d/%d/%d]:\n\n", dia, mes, ano);
	for( i = 0 ; i < n ; i++ )
		if( (v[i].data.dia == dia) && (v[i].data.mes == mes) && (v[i].data.ano == ano))
			mostra_evento( v[i] );
}

int remove_evento(struct evento *v, int n, int dia, int mes, int ano, int hora, int minuto){
	int i, x=-1;

	for(i = 0; i < n; i++)
		if(v[i].data.dia == dia && v[i].data.mes == mes && v[i].data.ano ==	ano && v[i].inicio.hora == hora && v[i].inicio.minuto == minuto)
			x = i;
	if(x == -1){
		printf("Evento nao encontrado!\n");
		return -1;}
	else if(x < n){
		for(i = x; i < n; i++){
			strcpy(v[i].descricao, v[i+1].descricao);		
			strcpy(v[i].local, v[i+1].local);
			v[i].data.dia = v[i+1].data.dia;
			v[i].data.mes = v[i+1].data.mes;
			v[i].data.ano = v[i+1].data.ano;
			v[i].inicio.hora = v[i+1].inicio.hora;
			v[i].inicio.minuto = v[i+1].inicio.minuto;
			v[i].fim.hora = v[i+1].fim.hora;
			v[i].fim.minuto = v[i+1].fim.minuto;
		}		
	}	
}

int sobrepor( struct evento *v, int n){
	int i, dia, mes, ano, horario_ini, horario_fim, horario_ini2, horario_fim2;
	dia = v[n-1].data.dia;
	mes = v[n-1].data.mes;
	ano = v[n-1].data.ano;
	horario_ini = 100*v[n-1].inicio.hora + v[n-1].inicio.minuto; //transformei o horario em um valor inteiro para comparar
	horario_fim = 100*v[n-1].fim.hora + v[n-1].fim.minuto;
	for(i = 0; i < n; i++){
	horario_ini2 = 100*v[i].inicio.hora + v[i].inicio.minuto;
	horario_fim2 = 100*v[i].fim.hora + v[i].fim.minuto;
	if(	dia == v[i].data.dia && mes == v[i].data.mes && ano == v[i].data.ano){
		if((horario_ini > horario_ini2) && (horario_ini < horario_fim2))
			return -1;
		if((horario_fim > horario_ini2) && (horario_fim < horario_fim2))
			return -1;
		if((horario_ini < horario_ini2) && (horario_fim > horario_fim2))
			return -1;}}
	return 0;
}

int validacao( struct evento *v, int n){
	int dia, mes, ano, hora_ini, min_ini, hora_fim, min_fim;

	dia = v[n-1].data.dia;
	mes = v[n-1].data.mes;
	ano = v[n-1].data.ano;
	hora_ini = v[n-1].inicio.hora;
	min_ini = v[n-1].inicio.minuto;
	hora_fim = v[n-1].fim.hora;
	min_fim = v[n-1].fim.minuto;

	if(dia < 1 || dia > 31)
		return -1;
	
	if(mes == 2 && dia > 29) 
		return -1;

    if(mes == 2 && dia == 29 && ano % 4 != 0) //ano bissexto
        return -1;


	if(mes < 1 || mes > 12)
		return -1;

	if(ano < 2022)
		return -1;
	
	if(hora_ini < 0 || hora_ini > 23)
		return -1;

	if(min_ini < 0 || min_ini > 59)
		return -1;

	if(hora_fim < 0 || hora_fim > 23)
		return -1;

	if(min_fim < 0 || min_fim > 59)
		return -1;
	
	return 0;
}

void entrada_invalida(struct evento *v, int n){
	int dia, mes, ano, hora, minuto;

	dia = v[n-1].data.dia;
	mes = v[n-1].data.mes;
	ano = v[n-1].data.ano;
	hora = v[n-1].inicio.hora;
 	minuto = v[n-1].inicio.minuto;
	remove_evento(v, n, dia, mes, ano, hora, minuto);
}
