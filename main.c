#include "tp3.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    srand(time(NULL));
    char nomeArquivo[30], nome[30], cpf[20], p[30];
    int idade, r, tempo_de_exame, tempo, id_retirado, index, TempoMedioLaudo;
    int id, uT, qtd, SumTempoLaudo = 0;
    
    Lista *lista_de_pacientes = create_lista(); // Criação da lista de pacientes.
    Fila *fila_para_exame = create_fila(); // Criação da fila para exame.
    Log *log = create_log();

    // Abrindo o arquivo e armazenando os dados.
    printf("Insira nome do arquivo (com a extensão): ");
    scanf("%s", nomeArquivo); 
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        puts("Erro ao abrir arquivo.");
        exit(EXIT_FAILURE);
    }

    /* CHEGADA DE PACIENTES */
    while ((fscanf(arquivo, "%30[^\n]\n%15[^\n]\n%d\n", nome, cpf, &idade) == 3)) {

        do {
            r = rand() % 10 + 1;
            uT++; // Incremento na unidade de tempo.

        } while (!(r <= 2)); // Probabilidade de 20% de chegar um paciente. 

        log_event(log, "Chegada de novo paciente.\n", uT);

        id++;
        Paciente *paciente = novo_paciente(nome, cpf, idade, id); // Criação de paciente.
        add_no_inicio(lista_de_pacientes, paciente); // Inserção do paciente na lista de pacientes.
        log_event(log, "Novo paciente inserido na 'Lista de Pacientes'.\n", uT);

        enfileirar_id(fila_para_exame, id); // Inserção do id na fila para exame.
        log_event(log, "ID inserido na 'Fila para Exame'.\n", uT);

        qtd++;   
    }

    fclose(arquivo); // Fechar arquivo.

    Occupation *aparelhos = create_array(5); // Criação de uma array com 5 aparelhos disponíveis.
    Fila *fila_para_laudo = create_fila(); // Criação da fila para laudo (vazia).

    Tempos *array_tempos = create_array_tempos(qtd);

    /* REALIZAÇÃO DO EXAME DE RAIO-X */
    for (int i = 0; i < qtd; i++) {
        if ((get_occupation(aparelhos, i)) == 0) {
            if ((fila_is_empty(fila_para_exame)) == 1) {

                tempo_de_exame = (rand() % 6 + 5);

                id_retirado = desenfileirar_id(fila_para_exame); // Retira id da fila para exame.

                change_occupation(aparelhos, i, 1); // Muda ocupação para "1" (ocupado).

                for (int j = 0; j <= tempo_de_exame; j++) uT++;

                log_event(log, "Exame de raio-x realizado.\n", uT);

                tempo = uT + tempo_de_exame;

                strcpy(p, condition());

                Registro *registro = create_registro(id_retirado, tempo, p); 

                enfileirar_registro(fila_para_laudo, registro); // Adiciona registro na fila para laudo.

                log_event(log, "Registro inserido na 'Fila para Laudo'.\n", uT);

                if (empty_array_index(array_tempos, qtd) == -1) {
                    printf("Nenhuma struct vazia. Realização do exame de raio x.\n");
                    exit(EXIT_FAILURE);
                }

                index = empty_array_index(array_tempos, qtd);

                insert_entrada(array_tempos, tempo, index, id_retirado, p); // Insere tempo de entrada na fila para laudo, id do paciente e patologia em uma struct vazia.

                uT = tempo;

                change_occupation(aparelhos, i, 0); // Muda ocupação para "0" (livre).

                uT++; // Incremento na unidade de tempo.  
            }
        }
    }   

    free_fila(fila_para_exame); // Liberação de memória.
    free(aparelhos);


    /* REALIZAÇÃO DE LAUDO */

    Occupation *radiologista = create_array(3); //

    for (int i = 0; i < qtd; i++) {
        if ((get_occupation(radiologista, i)) == 0) {
            
            if ((fila_is_empty(fila_para_laudo)) == 1) {
                Registro *r = desenfileirar_registro(fila_para_laudo); // Tira registro da fila para laudo e o retorna.
                id_retirado = get_id_registro(r);
                strcpy(p, get_diagnostico_registro(r));

                index = index_from_id(array_tempos, id_retirado, qtd); // Pega o indice do elemento na array que contem o id do paciente.

                insert_tempo_saida(array_tempos, uT, index); // Insere tempo que o paciente saiu da fila para laudo.

                SumTempoLaudo += tempo_laudo(array_tempos, index); // Acrescenta tempo do laudo na variavel auxiliar para calculo da media.

                tempo_de_exame = rand() % 20 + 10; 

                change_occupation(radiologista, i, 1); // Muda ocupação para "1" (ocupado).

                for (int j = 0; j <= tempo_de_exame; j++) uT++; // Preparação do laudo.

                log_event(log, "Laudo realizado.\n", uT);

                change_occupation(radiologista, i, 0); // Muda ocupação para "0" (livre).

                uT++;
            }
            else puts("Fila para laudo está vazia.");
        }

        
    }

    free_fila(fila_para_laudo);
    free(radiologista);

    TempoMedioLaudo = SumTempoLaudo/qtd;
    printf("Tempo medio geral na fila de laudo: %d\n", TempoMedioLaudo);
    
    save_log_to_file(log, "log.txt");

    return 0;
}