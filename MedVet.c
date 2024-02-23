#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 100

struct Cadastro {

	char nome[50];
    char nomeDono[50];
    char especie[50];
    int idade;
    char inscricaoSintoma[100];
    char diagnostico[100];

};

void Cadastrar(struct Cadastro cadastro[], int *ID){

    printf("\n__________________________________");

    setbuf(stdin, NULL);
    printf("\n-> Insira o Nome do pet: \n");
    fgets(cadastro[*ID].nome, 50, stdin);

    setbuf(stdin, NULL);
    printf("\n-> Insira o nome do dono: \n");
    fgets(cadastro[*ID].nomeDono, 50, stdin);

    setbuf(stdin, NULL);
    printf("\n-> Insira a especie: \n");
    fgets(cadastro[*ID].especie, 50, stdin);

    printf("\n-> Insira a idade:\n");  
    scanf("%d", &cadastro[*ID].idade);

    setbuf(stdin, NULL);
    printf("\n-> Decreva os sintomas: \n");
    fgets(cadastro[*ID].inscricaoSintoma, 100, stdin);

    setbuf(stdin, NULL);
    printf("\n-> Decreva o diagnostico: \n");
    fgets(cadastro[*ID].diagnostico, 100, stdin);

    (*ID)++;


}

void exibirCadastros(struct Cadastro cadastro[], int ID){
    printf("\nJogos cadastrados:\n");

    for (int i = 0; i < ID; i++) {
        printf("\n------------------------------------------");
        printf("\n- Nome do pet: %s", cadastro[i].nome);
        printf("\n- Nome do dono: %s", cadastro[i].nomeDono);
        printf("\n- Especie: %s", cadastro[i].especie);
        printf("\n- Idade: %d\n ", cadastro[i].idade);
        printf("\n- Sintomas: %s", cadastro[i].inscricaoSintoma);
        printf("\n- Diagnostico: %s", cadastro[i].diagnostico);

    }
}

void buscaPorID(struct Cadastro cadastro[], int ID, int busca){
    int j = 0;

     for (int i = 0; i < ID; i++) {

        if(ID + 1 == busca){

            printf("\n------------------------------------------");
            printf("\n- Nome: %s", cadastro[busca].nome);
            printf("\n- Genero: %s", cadastro[busca].genero);
            printf("\n- Modo de Jogo: %s", cadastro[busca].modoJogo);
            printf("\n- Plataforma: %s", cadastro[i].plataforma);
            printf("\n- Ranking: %d\n ", cadastro[i].ranking);
            j++;

        }

     }

     if(j == 0){
        printf("Nenhum jogo coincide com o genero buscado !");
     }

}



int main(){

    struct Cadastro cadastro[MAX];
    int opcao, ID = 0;
    int busca;
    int rankingB;

    do {
        printf("\nSelecione a opcao:\n");
        printf("1. Adicionar jogo\n");
        printf("2. Exibir jogos cadastrados\n");
        printf("3. Busca por ID\n");
        printf("5. Verificar se jogo é favorito\n");
        printf("0. Sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                Cadastrar(cadastro, &ID);
                break;
            case 2:
                exibirJogos(cadastro, ID);
                break;
            case 3:
                printf("\nDigite numero de cadastro que deseja buscar: ");
                scanf("%d", busca);
                buscaPorGenero(cadastro, ID, busca);
                break;
            case 4:
                printf("\nDigite o ranking que deseja buscar: ");
                scanf("%d", &rankingB); 
                JogoPorRanking(jogos, ID, rankingB);
                break;
            case 5:
                printf("\nDigite o nome do jogo que deseja verificar: ");
                scanf("%s", jogoF);
                verificarFavorito(jogos, ID, jogoF);
                break;
            case 0:
                printf("\nEncerrando o programa.");
                break;
            default:
                printf("\nOpcao invalida.");
        }
    } while (opcao != 0);

    return 0;
}