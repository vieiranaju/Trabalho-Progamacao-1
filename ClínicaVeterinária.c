#include <stdio.h>
#include <stdlib.h> 

struct Cadastro {
    char nome[50];
    char nomeDono[50];
    char especie[50];
    char sintoma[200];
    char diagnostico[200];
    int ID;
    int idade;
};

void preencherCadastro(struct Cadastro *cadastros, int x) {

    system("cls");

    setbuf(stdin, NULL);
    printf("Insira o nome do animal: ");
    fgets(cadastros[x].nome, 50, stdin);
    setbuf(stdin, NULL);
    printf("Insira o nome do dono: ");
    fgets(cadastros[x].nomeDono, 50, stdin);
    printf("Insira os Sintomas: ");
    fgets(cadastros[x].sintoma, 200, stdin);
    printf("Insira o diagnostico: ");
    fgets(cadastros[x].diagnostico, 200, stdin);
    setbuf(stdin, NULL);
    printf("Insira a idade: ");
    scanf("%d", &cadastros[x].idade);
    cadastros[x].ID = x + 1;
    printf("\n=========================================");

    FILE *arq = fopen("cadastros.txt", "a");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    
    fprintf(arq, "%s %s %s %s %d %d\n", cadastros[x].nome, cadastros[x].nomeDono, cadastros[x].sintoma, cadastros[x].diagnostico, cadastros[x].ID, cadastros[x].idade);
    
    fclose(arq);
    
}

void visualizarCadastros() {

    system("cls");

    FILE *arq = fopen("cadastros.txt", "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("Cadastros armazenados:\n");
    for(int i = 0; i < total; i++) {
        printf("\n=========================================\n");
        printf("\n- Nome: %s", cadastros[i].nome);
        printf("\n- Nome do responsavel: %s", cadastros[i].nomeDono);
        printf("\n- Idade: %d", cadastros[i].idade); 
        printf("\n- Sintomas: %s", cadastros[i].sintoma);
        printf("\n- Diagnostico: %s", cadastros[i].diagnostico);
        printf("\n- ID: %d ", cadastros[i].ID);
        printf("\n=========================================\n");
    }
    
    fclose(arq);
}

void modificarCadastros(struct Cadastro *cadastros, int total, int id) {

    system("cls");

    if (id < 1 || id > total) {
        printf("ID do cadastro invalido!\n");
        return;
    }

    printf("\nModificando cadastro de ID %d\n", id);
    setbuf(stdin, NULL);
    printf("\nInsira o nome do animal: ");
    fgets(cadastros[id - 1].nome, 50, stdin);
    setbuf(stdin, NULL);
    printf("Insira o nome do dono: ");
    fgets(cadastros[id - 1].nomeDono, 50, stdin);
    setbuf(stdin, NULL);
    printf("Insira os Sintomas: ");
    fgets(cadastros[id - 1].sintoma, 200, stdin);
    setbuf(stdin, NULL);
    printf("Insira o diagnostico: ");
    fgets(cadastros[id - 1].diagnostico, 200, stdin);
    printf("Insira a idade: ");
    scanf("%d", &cadastros[id - 1].idade);
    printf("\n=========================================");

    FILE *arq = fopen("cadastros.txt", "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    FILE *temp_arq = fopen("temp_cadastros.txt", "w");
    if (temp_arq == NULL) {
        printf("Erro ao abrir o arquivo temporario.\n");
        fclose(arq);
        return;
    }

    struct Cadastro temp;
    int encontrado = 0;

    
    while (fscanf(arq, "%s %s %s %s %d %d\n", temp.nome, temp.nomeDono, temp.sintoma, temp.diagnostico, &temp.idade, &temp.ID) != EOF) {
        if (temp.ID == id) {
            fprintf(temp_arq, "%s %s %s %s %d %d\n", cadastros[id - 1].nome, cadastros[id - 1].nomeDono, cadastros[id - 1].sintoma, cadastros[id - 1].diagnostico, cadastros[id - 1].idade, cadastros[id - 1].ID);
            encontrado = 1;
        } else {
            fprintf(temp_arq, "%s %s %s %s %d %d\n", temp.nome, temp.nomeDono, temp.sintoma, temp.diagnostico, temp.idade, temp.ID);
        }
    }

    fclose(arq);
    fclose(temp_arq);


    remove("cadastros.txt");
    rename("temp_cadastros.txt", "cadastros.txt");

    if (!encontrado) {
        printf("ID do cadastro nao encontrado.\n");
    } else {
        printf("\nCadastro modificado com sucesso.\n");
    }
}


void deletarCadastros(struct Cadastro *cadastros, int total, int id) {

    system("cls");

    if (id < 1 || id > total) {
        printf("ID do cadastro invalido!\n");
        return;
    }

    FILE *arq = fopen("cadastros.txt", "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    struct Cadastro *temp = malloc((total - 1) * sizeof(struct Cadastro));
    if (temp == NULL) {
        printf("Erro de alocacao de memoria.\n");
        fclose(arq);
        return;
    }

    int i = 0; 
    for (int j = 0; j < total; j++) {
        if (cadastros[j].ID != id) {
            temp[i] = cadastros[j];
            i++;
        }
    }

    fclose(arq);

    arq = fopen("cadastros.txt", "w");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        free(temp);
        return;
    }

    for (int j = 0; j < total - 1; j++) {
        fprintf(arq, "%s %s %s %s %s %d %d\n", temp[j].nome, temp[j].nomeDono, temp[j].especie, temp[j].sintoma, temp[j].diagnostico, temp[j].idade, temp[j].ID);
    }

    fclose(arq);
    free(temp);
}

void visualizarAnimalPorId(int id) {
    FILE *arq = fopen("cadastros.txt", "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    struct Cadastro animal;
    int encontrado = 0;

    while (fscanf(arq, "%s %s %s %s %d %d\n", animal.nome, animal.nomeDono, animal.sintoma, animal.diagnostico, &animal.ID, &animal.idade) != EOF) {
        if (animal.ID == id) {
            printf("\n=========================================\n");
            printf("\n- Nome: %s", animal.nome);
            printf("\n- Nome do responsavel: %s", animal.nomeDono);
            printf("\n- Sintomas: %s", animal.sintoma);
            printf("\n- Diagnostico: %s", animal.diagnostico);
            printf("\n- ID: %d ", animal.ID);
            printf("\n- Idade: %d\n\n ", animal.idade);
            printf("\n=========================================\n");
            encontrado = 1;
            break;
        }
    }

    fclose(arq);

    if (!encontrado) {
        printf("Animal com ID %d nao encontrado.\n", id);
    }
}


int main() {
    int op = 0, i = 0, n;
    struct Cadastro *cadastros = NULL;

    while (op != 6) {
        printf("\n=========================================\n");
        printf("Opcao [1] = Cadastrar ! ");
        printf("\nOpcao [2] = Visualizar cadastros ! ");
        printf("\nOpcao [3] = Deletar ! ");
        printf("\nOpcao [4] = Modificar Cadastro ! ");
        printf("\nOpcao [5] = Consultar Cadastro ! ");
        printf("\nOpcao [6] = Fechar ! ");
        printf("\n=========================================\n");

        if(op != 6 ){

        scanf("%d", &op);

        switch (op) {
            case 1:
                i++;
                cadastros = (struct Cadastro *)realloc(cadastros, i * sizeof(struct Cadastro));
                printf("\n===========Cadastro numero %d=============\n", i);
                preencherCadastro(cadastros, i - 1);
                break;

            case 2:
                visualizarCadastros();
                break;

            case 3:
                printf("\nInsira o ID do cadastro que deseja deletar:\n");
                scanf("%d", &n);
                deletarCadastros(cadastros, i, n);
                break;

            case 4:
                printf("\nInsira o ID do cadastro que deseja modificar:\n");
                scanf("%d", &n);
                modificarCadastros(cadastros, i, n);
                break;
            case 5:
                printf("Insira qual registro voce quer consultar: ");
                scanf("%d", &n);
                visualizarAnimalPorId(n);
                break;

            default:
                break;
        }
        }
    }

    printf("Adeus!");

    
    free(cadastros);
    
    return 0;
}
