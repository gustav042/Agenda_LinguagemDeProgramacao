//teste tstes teste
//teste 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Z 50

struct evento{
	struct data data;
	struct horario inicio;
	struct horario fim;
	char descricao[Z] ;
	char local[Z];
};

struct data{
	int dia, mes, ano;
};

struct horario{
	int hora, minuto;
};

void conflito(struct data *p);
void le_evento( struct evento *p );
void mostra_evento( struct evento x );

void le_data( struct data *p );
void mostra_data (struct data x );

int compara_evento_nome( struct evento x, struct evento y );

void mostra_vetor( struct evento *v, int n );
int busca_evento( struct evento *v, int n, char *nome );
void ordena_vetor( struct evento *v, int n );
void mostra_vetor_por_letra( struct evento *v, int n , char letra );
void mostra_vetor_por_ano( struct evento *v, int n , int ano );

int main(int argc, char *argv[]) {
	int n = 0;  // Quantidade de eventos
	struct evento *v = NULL; // Ponteiro para o vetor de eventos
	char nome[30];
	int idx, data_busca;
	char letra;
	
	int opcao;
	do{
		system("CLS");
		printf("1-Cadastrar\n2-Mostrar todos os eventos da agenda\n");
		printf("3-Mostrar eventos em uma data\n4-Mostrar eventos com mesma descricao\n");
		printf("5-Remover evento\n6-Sair do programa\n");
		scanf("%d", &opcao);
		
		switch( opcao ){
			case 1:
				n++;
				v = realloc( v, sizeof( struct evento ) * n );
				le_evento( &v[n-1] );
				system("PAUSE");
				break;
			
			case 2:
				mostra_vetor( v, n );
				system("PAUSE");
				break;
				
			case 3:
				printf("Digite o nome da evento a ser buscada: ");
				scanf(" %[^\n]", nome );
				
				idx = busca_evento( v, n, nome );
				if( idx == -1 )
					printf("evento nao encotrada!\n");
				else{
					printf("%d : ", idx+1 );
					mostra_evento( v[idx] );
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
				scanf(" %d", &data_busca);
				mostra_vetor_por_ano( v, n, data_busca );
				system("PAUSE");
				break;
		}
	
	}while( opcao != 7 );
	free( v );	
	return 0;
}

void le_evento( struct evento *p ){
	printf("Digite a data: ");
	le_data( &p->data );
	printf("Digite o horario de inicio: ");
	le_horario(&p->inicio);
	printf("Digite o horario de fim: ");
	le_horario(&p->fim);
	printf("Digite uma descrição: ");
	scanf("%[^\n]", p->descricao);
	printf("Digite o local: ");
	scanf("%[^\n]", p->local);
}

void mostra_evento( struct evento x ){
	mostra_data( x.data );
	mostra_horario(x.inicio);
	printf("-");
	mostra_horario(x.fim);
	printf("%s, %s\n", x.local, x.descricao);
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
	printf("(%d/%d/%d)", x.dia, x.mes, x.ano);
}

void mostra_horario(struct horario x ){
	printf("(%ih%im)", x.hora, x.minuto);
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

void ordena_vetor( struct evento *v, int n ){
	int i;
	for( i = 0 ; i < n-1 ; i++ ){
		int j, i_menor = i;
		for( j = i+1 ; j < n ; j++ ){
			if( compara_evento_nome( v[j], v[i_menor ] ) < 0 )
				i_menor = j;
		}
		struct evento temp = v[i];
		v[i] = v[i_menor];
		v[i_menor] = temp;
	}
}


void mostra_descricao( struct evento *v, int n ){
	int i;
	char descricao[Z];
	printf("Digite uma descricao: ");
	scanf("%[^\n]", &descricao);
	for( i = 0 ; i < n-1 ; i++ ){
		if( compara_evento_descricao(v[i], descricao))
			mostra_evento(v[i]);}}

int compara_evento_descricao( struct evento x, char descricao ){
	return strcmp( x.descricao, descricao );	
}