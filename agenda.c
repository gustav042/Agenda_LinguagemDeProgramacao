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

int compara_evento_descricao( struct evento x, struct evento y );

void mostra_vetor( struct evento *v, int n );
int busca_evento( struct evento *v, int n, char *descricao );
void ordena_vetor( struct evento *v, int n );
void mostra_vetor_por_letra( struct evento *v, int n , char letra );
void mostra_vetor_por_data( struct evento *v, int n , int dia, int mes, int ano );

int main(int argc, char *argv[]) {
	int i, n = 0;  // Quantidade de eventos
	struct evento *v = NULL; // Ponteiro para o vetor de eventos
	char descricao[30];
	int idx, dia, mes, ano;
	char letra;
	
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
		printf("5-Buscar por letra inicial\n6-Ordena\n7-Sair\n");
		scanf("%d", &opcao);
		
		switch( opcao ){
			case 1:
				n++;
				v = realloc( v, sizeof( struct evento ) * n );
				le_evento( &v[n-1] );
				//ordena_vetor( v, n ); // para o trabalho...
				system("PAUSE");
				break;
			
			case 2:
				mostra_vetor( v, n );
				system("PAUSE");
				break;
				
			case 3:
				printf("Digite um dia: ");
				scanf(" %d", &dia);
				printf("Digite um mes: ");
				scanf(" %d", &mes);
				printf("Digite um ano: ");
				scanf(" %d", &ano);
				mostra_vetor_por_data( v, n, dia, mes, ano );
				system("PAUSE");
				break;

				
			case 4:
				printf("Digite o descricao da evento a ser buscada: ");
				scanf(" %[^\n]", descricao );
				
				idx = busca_evento( v, n, descricao );
				if( idx == -1 )
					printf("evento nao encotrada!\n");
				else{
					printf("%d : ", idx+1 );
					mostra_evento( v[idx] );
				}
				system("PAUSE");
				break;
				
			case 5:
				printf("Digite uma letra: ");
				scanf(" %c", &letra);
				mostra_vetor_por_letra( v, n, letra );
				system("PAUSE");
				break;
				
			case 6:
				ordena_vetor( v, n );
				printf("Vetor ordenado com sucesso!\n");
				system("PAUSE");
				break;
			
			
		}
		
	}while( opcao != 7 );
	
	// Grava vetor no arquivo!
	f = fopen( "cadastro.txt", "wt" );
	fprintf( f, "%d\n", n); // 1a informação do arquivo é a quantidade de eventos
	for( i = 0 ; i < n ; i++ ){
		fprintf( f, "%d\n%d\n%d\n", v[i].data.dia, v[i].data.mes, v[i].data.ano);	
		fprintf( f, "%s\n%s\n", v[i].descricao, v[i].local);

	}
	fclose( f );
	
	free( v );
	
	/*
	
	struct evento fulano;
	le_evento( &fulano );
	mostra_evento( fulano );
	
	struct data y;
	le_data( &y );	
	fulano.data = y;	
	mostra_evento( fulano );
	
	*/
	
	return 0;
}

void le_evento( struct evento *p ){
	printf("Digite a data:\n");
	le_data( &p->data );
	printf("Digite a descricao: ");
	scanf(" %[^\n]", p->descricao);
	printf("Digite o local: ");
	scanf(" %[^\n]", p->local);

}

void mostra_evento( struct evento x ){
	printf("(%s, %s, [", x.descricao, x.local);
	mostra_data( x.data );
	printf("])\n");
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
	printf("%d/%d/%d", x.dia, x.mes, x.ano);
}

void mostra_vetor( struct evento *v, int n ){
	if( n == 0 )
		printf("Nao ha eventos cadastradas!\n");
	else{
		int i;
		printf("Lista de eventos cadatradas:\n");
		for( i = 0 ; i < n ; i++ ){
			printf("%d : ", i+1 );
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
			if( compara_evento_descricao( v[j], v[i_menor ] ) < 0 )
				i_menor = j;
		}
		struct evento temp = v[i];
		v[i] = v[i_menor];
		v[i_menor] = temp;
	}
}


int compara_evento_descricao( struct evento x, struct evento y ){
	return strcmp( x.descricao, y.descricao );	
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
	printf("Lista de eventos na data [%d/%d/%d]:\n", dia, mes, ano);
	for( i = 0 ; i < n ; i++ )
		if( (v[i].data.dia == dia) && (v[i].data.mes == mes) && (v[i].data.ano == ano))
			mostra_evento( v[i] );
}
