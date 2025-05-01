#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char nomeAluno[100][100];      
    int idadeAluno[100];           
    char matriculaAluno[100][20];  
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
        strcpy(nomeAluno[i], dado);

        dado = strtok(NULL, ",");
        idadeAluno[i] = atoi(dado);

        dado = strtok(NULL, ",");
        if (dado != NULL) {
            int comprimento = strlen(dado);
            if (dado[comprimento - 1] == '\n') {
                dado[comprimento - 1] = '\0';
            }
            strcpy(matriculaAluno[i], dado);
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

            if (selecaoUsuario == 1 && strcmp(nomeAluno[i], nomeAluno[j]) > 0) {
                mudarAluno = 1;
            } else if (selecaoUsuario == 2 && idadeAluno[i] > idadeAluno[j]) {
                mudarAluno = 1;
            } else if (selecaoUsuario == 3 && strcmp(matriculaAluno[i], matriculaAluno[j]) > 0) {
                mudarAluno = 1;
            }

            if (mudarAluno) {
                
                char tempNome[100];
                int tempIdade;
                char tempMatricula[20];

                strcpy(tempNome, nomeAluno[i]);
                tempIdade = idadeAluno[i];
                strcpy(tempMatricula, matriculaAluno[i]);

                strcpy(nomeAluno[i], nomeAluno[j]);
                idadeAluno[i] = idadeAluno[j];
                strcpy(matriculaAluno[i], matriculaAluno[j]);

                strcpy(nomeAluno[j], tempNome);
                idadeAluno[j] = tempIdade;
                strcpy(matriculaAluno[j], tempMatricula);
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
        fprintf(arquivoResultados, "%s,%d,%s\n", nomeAluno[i], idadeAluno[i], matriculaAluno[i]);
    }

    fclose(arquivoResultados);

    printf("Arquivo de alunos salvo com sucesso\n");

    return 0;
}
