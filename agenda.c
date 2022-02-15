#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Evento{
	struct Data;
	struct 
};
struct Data{
	int dia, mes, ano;
};

struct horario{
	int hora, minuto;
};

// Apenas mais um exemplo de estrutura que usa a 'data' (sem relevância neste código...)
struct pedido{
	int codigo;
	struct Data data_pedido;
};

void conflito(struct data *p);
void le_pessoa( struct pessoa *p );
void le_pessoa_v2( struct pessoa *p );
void mostra_pessoa( struct pessoa x );
void mostra_pessoa_v2( struct pessoa x );

void le_data( struct data *p );
void mostra_data (struct data x );

int compara_pessoa_nome( struct pessoa x, struct pessoa y );

void mostra_vetor( struct pessoa *v, int n );
int busca_pessoa( struct pessoa *v, int n, char *nome );
void ordena_vetor( struct pessoa *v, int n );
void mostra_vetor_por_letra( struct pessoa *v, int n , char letra );
void mostra_vetor_por_ano( struct pessoa *v, int n , int ano );

int main(int argc, char *argv[]) {
	int n = 0;  // Quantidade de pessoas
	struct pessoa *v = NULL; // Ponteiro para o vetor de pessoas
	char nome[30];
	int idx, ano;
	char letra;
	
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
				le_pessoa_v2( &v[n-1] );
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
					mostra_pessoa_v2( v[idx] );
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
	
	free( v );
	
	/*
	
	struct pessoa fulano;
	le_pessoa_v2( &fulano );
	mostra_pessoa_v2( fulano );
	
	struct data y;
	le_data( &y );	
	fulano.nascimento = y;	
	mostra_pessoa_v2( fulano );
	
	*/
	
	return 0;
}

void le_pessoa( struct pessoa *p ){
	printf("Digite o nome: ");
	scanf(" %[^\n]", p->nome);
	printf("Digite o telefone: ");
	scanf(" %[^\n]", p->telefone);
	printf("Digite a data de nascimento:\n");
	printf("Digite o dia: ");
	scanf("%d", &p->nascimento.dia);
	printf("Digite o mes: ");
	scanf("%d", &p->nascimento.mes);
	printf("Digite o ano: ");
	scanf("%d", &p->nascimento.ano);
}

void le_pessoa_v2( struct pessoa *p ){
	printf("Digite o nome: ");
	scanf(" %[^\n]", p->nome);
	printf("Digite o telefone: ");
	scanf(" %[^\n]", p->telefone);
	printf("Digite a data de nascimento:\n");
	le_data( &p->nascimento );
}

void mostra_pessoa( struct pessoa x ){
	printf("(%s, %s, [%d/%d/%d])\n",
			x.nome, x.telefone, x.nascimento.dia, x.nascimento.mes, x.nascimento.ano);
}

void mostra_pessoa_v2( struct pessoa x ){
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
			mostra_pessoa_v2( v[i] );
		}
	}
}

int busca_pessoa( struct pessoa *v, int n, char *nome ){
	int i;
	for( i = 0 ; i < n ; i++ )
		if( strcmpi( v[i].nome, nome ) == 0 )
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
	return strcmpi( x.nome, y.nome );	
}

void mostra_vetor_por_letra( struct pessoa *v, int n , char letra ){
	int i;
	printf("Lista de pessoas cujo nome comeca com a letra %c\n", letra);
	for( i = 0 ; i < n ; i++ )
		if( v[i].nome[0] == letra )
			mostra_pessoa_v2( v[i] );
}

void mostra_vetor_por_ano( struct pessoa *v, int n , int ano ){
	int i;
	printf("Lista de pessoas que nesceram a partir do ano %d\n", ano);
	for( i = 0 ; i < n ; i++ )
		if( v[i].nascimento.ano >= ano )
			mostra_pessoa_v2( v[i] );
}