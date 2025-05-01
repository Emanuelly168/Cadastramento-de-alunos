#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Aluno {
    char nomeAluno[100];
    int idadeAluno;
    char matriculaAluno[20];
};

int main() {
    struct Aluno alunos[100];
    char registro[200];
    int i = 0, j, totalAlunos = 0;
    FILE *arquivoAluno;

    arquivoAluno = fopen("alunos.csv", "r");

    if (arquivoAluno == NULL) {
        printf("Erro ao abrir o arquivo de alunos\n");
        return 1;
    }

    while (fgets(registro, 200, arquivoAluno)) {
        char *dado;

        dado = strtok(registro, ",");
        strcpy(alunos[i].nomeAluno, dado);

        dado = strtok(NULL, ",");
        alunos[i].idadeAluno = atoi(dado);

        dado = strtok(NULL, ",");
        if (dado != NULL) {
            int comprimento = strlen(dado); 

            strcpy(alunos[i].matriculaAluno, dado);
        }

        i++;
        totalAlunos++;
    }

    fclose(arquivoAluno);

    int selecaoUsuario;
    printf("Ordenar por:\n");
    printf("1 - Nome\n2 - Idade\n3 - Matricula\nEscolha uma das opcoes: ");
    scanf("%d", &selecaoUsuario);

    for (i = 0; i < totalAlunos - 1; i++) {
        for (j = i + 1; j < totalAlunos; j++) {
            int mudarAluno = 0;

            if (selecaoUsuario == 1 && strcmp(alunos[i].nomeAluno, alunos[j].nomeAluno) > 0) {
                mudarAluno = 1;
            } else if (selecaoUsuario == 2 && alunos[i].idadeAluno > alunos[j].idadeAluno) {
                mudarAluno = 1;
            } else if (selecaoUsuario == 3 && strcmp(alunos[i].matriculaAluno, alunos[j].matriculaAluno) > 0) {
                mudarAluno = 1;
            }

            if (mudarAluno) {
                struct Aluno alunoTemp = alunos[i];
                alunos[i] = alunos[j];
                alunos[j] = alunoTemp;
            }
        }
    }

    char nomeArquivo[100];
    printf("Digite o nome do arquivo de saida: ");
    scanf("%s", nomeArquivo);

    FILE *arquivoResultados = fopen(nomeArquivo, "w");
    if (arquivoResultados == NULL) {
        printf("Erro ao criar o arquivo de saida.\n");
        return 1;
    }

    for (i = 0; i < totalAlunos; i++) {
        fprintf(arquivoResultados, "%s,%d,%s\n", alunos[i].nomeAluno, alunos[i].idadeAluno, alunos[i].matriculaAluno);
    }

    fclose(arquivoResultados);

    printf("Arquivo de alunos salvo com sucesso\n");

    return 0;
}