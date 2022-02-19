#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data{
	int dia, mes, ano;
};

struct pessoa{
	char nome[30], telefone[20];
	struct data nascimento;
};

// Apenas mais um exemplo de estrutura que usa a 'data' (sem relevância neste código...)
struct pedido{
	int codigo;
	struct data data_pedido;
};

void le_pessoa( struct pessoa *p );
void mostra_pessoa( struct pessoa x );

void le_data( struct data *p );
void mostra_data (struct data x );

int compara_pessoa_nome( struct pessoa x, struct pessoa y );

void mostra_vetor( struct pessoa *v, int n );
int busca_pessoa( struct pessoa *v, int n, char *nome );
void ordena_vetor( struct pessoa *v, int n );
void mostra_vetor_por_letra( struct pessoa *v, int n , char letra );
void mostra_vetor_por_ano( struct pessoa *v, int n , int ano );

int main(int argc, char *argv[]) {
	int i, n = 0;  // Quantidade de pessoas
	struct pessoa *v = NULL; // Ponteiro para o vetor de pessoas
	char nome[30];
	int idx, ano;
	char letra;
	
	FILE *f;
	
	f = fopen( "cadastro.txt" , "rt" );
	if( f != NULL){
		// Carrega dados do arquivo, alocando o vetor v;
		fscanf( f , "%d", &n); // Carrega a quantidade de pessoas (1a info no arquivo)
		v = malloc( sizeof( struct pessoa ) * n );
		for( i = 0 ; i < n ; i++ ){
			fscanf( f, " %[^\n]", v[i].nome);
			fscanf( f, " %[^\n]", v[i].telefone);
			fscanf( f, "%d", &v[i].nascimento.dia);
			fscanf( f, "%d", &v[i].nascimento.mes);
			fscanf( f, "%d", &v[i].nascimento.ano);
		}
		fclose( f );
		printf("%d registros carregados com sucesso!\n", n);
		system("PAUSE");
	}
	
	int opcao;
	do{
		system("CLS");
		printf("1-Cadastrar\n2-Mostrar lista\n3-Buscar\n4-Ordenar\n");
		printf("5-Buscar por letra inicial\n6-Buscar por ano\n7-Sair\n");
		scanf("%d", &opcao);
		
		switch( opcao ){
			case 1:
				n++;
				v = realloc( v, sizeof( struct pessoa ) * n );
				le_pessoa( &v[n-1] );
				//ordena_vetor( v, n ); // para o trabalho...
				system("PAUSE");
				break;
			
			case 2:
				mostra_vetor( v, n );
				system("PAUSE");
				break;
				
			case 3:
				printf("Digite o nome da pessoa a ser buscada: ");
				scanf(" %[^\n]", nome );
				
				idx = busca_pessoa( v, n, nome );
				if( idx == -1 )
					printf("Pessoa nao encotrada!\n");
				else{
					printf("%d : ", idx+1 );
					mostra_pessoa( v[idx] );
				}
				system("PAUSE");
				break;
				
			case 4:
				ordena_vetor( v, n );
				printf("Vetor ordenado com sucesso!\n");
				system("PAUSE");
				break;
			
			case 5:
				printf("Digite uma letra: ");
				scanf(" %c", &letra);
				mostra_vetor_por_letra( v, n, letra );
				system("PAUSE");
				break;
				
			case 6:
				printf("Digite um ano: ");
				scanf(" %d", &ano);
				mostra_vetor_por_ano( v, n, ano );
				system("PAUSE");
				break;
			
		}
		
	}while( opcao != 7 );
	
	// Grava vetor no arquivo!
	f = fopen( "cadastro.txt", "wt" );
	fprintf( f, "%d\n", n); // 1a informação do arquivo é a quantidade de pessoas
	for( i = 0 ; i < n ; i++ ){
		fprintf( f, "%s\n%s\n", v[i].nome, v[i].telefone);
		fprintf( f, "%d\n%d\n%d\n", v[i].nascimento.dia, v[i].nascimento.mes, v[i].nascimento.ano);	
	}
	fclose( f );
	
	free( v );
	
	/*
	
	struct pessoa fulano;
	le_pessoa( &fulano );
	mostra_pessoa( fulano );
	
	struct data y;
	le_data( &y );	
	fulano.nascimento = y;	
	mostra_pessoa( fulano );
	
	*/
	
	return 0;
}

void le_pessoa( struct pessoa *p ){
	printf("Digite o nome: ");
	scanf(" %[^\n]", p->nome);
	printf("Digite o telefone: ");
	scanf(" %[^\n]", p->telefone);
	printf("Digite a data de nascimento:\n");
	le_data( &p->nascimento );
}

void mostra_pessoa( struct pessoa x ){
	printf("(%s, %s, [", x.nome, x.telefone);
	mostra_data( x.nascimento );
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

void mostra_vetor( struct pessoa *v, int n ){
	if( n == 0 )
		printf("Nao ha pessoas cadastradas!\n");
	else{
		int i;
		printf("Lista de pessoas cadatradas:\n");
		for( i = 0 ; i < n ; i++ ){
			printf("%d : ", i+1 );
			mostra_pessoa( v[i] );
		}
	}
}

int busca_pessoa( struct pessoa *v, int n, char *nome ){
	int i;
	for( i = 0 ; i < n ; i++ )
		if( strcmp( v[i].nome, nome ) == 0 )
			return i;
	
	return -1;
}

void ordena_vetor( struct pessoa *v, int n ){
	int i;
	for( i = 0 ; i < n-1 ; i++ ){
		int j, i_menor = i;
		for( j = i+1 ; j < n ; j++ ){
			if( compara_pessoa_nome( v[j], v[i_menor ] ) < 0 )
				i_menor = j;
		}
		struct pessoa temp = v[i];
		v[i] = v[i_menor];
		v[i_menor] = temp;
	}
}


int compara_pessoa_nome( struct pessoa x, struct pessoa y ){
	return strcmp( x.nome, y.nome );	
}

void mostra_vetor_por_letra( struct pessoa *v, int n , char letra ){
	int i;
	printf("Lista de pessoas cujo nome comeca com a letra %c\n", letra);
	for( i = 0 ; i < n ; i++ )
		if( v[i].nome[0] == letra )
			mostra_pessoa( v[i] );
}

void mostra_vetor_por_ano( struct pessoa *v, int n , int ano ){
	int i;
	printf("Lista de pessoas que nesceram a partir do ano %d\n", ano);
	for( i = 0 ; i < n ; i++ )
		if( v[i].nascimento.ano >= ano )
			mostra_pessoa( v[i] );
}
