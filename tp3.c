#include "tp3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



/////////////// PACIENTES ///////////////

struct _paciente {
    char nome[30];
    char cpf[15];
    int idade;
    int id;
};

struct _node {
    Paciente *dados;
    Node *prev; 
    Node *next; 
};

struct _list {
    Node *begin;
    Node *end;
    int size;
};


// Cria lista (vazia).
Lista *create_lista() {
    Lista *nova_lista = (Lista*) calloc(1, sizeof(Lista));

    if (nova_lista == NULL) {
        puts("Falha na alocação de nova lista.");
        exit(EXIT_FAILURE);
    }

    nova_lista->begin = NULL;
    nova_lista->end = NULL;
    nova_lista->size = 0;

    return nova_lista;
}

// Verifica se lista está vazia.
int list_is_empty(const Lista *L) {
    if (L->size == 0) return 0;
    else return 1;
}

// Criação de novo paciente.
Paciente *novo_paciente(const char nome[], const char cpf[], const int idade, const int id) {
    Paciente *novoPaciente = (Paciente*) calloc(1, sizeof(Paciente));

    if (novoPaciente == NULL) {
        puts("Falha na alocação de novo paciente.");
        exit(EXIT_FAILURE);
    }

    strcpy(novoPaciente->nome, nome);
    strcpy(novoPaciente->cpf, cpf);
    novoPaciente->idade = idade;
    novoPaciente->id = id;
    
    return novoPaciente;
}

// Cria nó com o paciente novo.
Node *create_node(Paciente *novoPaciente) {
    Node *new_node = (Node*) calloc(1, sizeof(Node));

    if (new_node == NULL) {
        puts("Falha na alocação de novo nó.");
        exit(EXIT_FAILURE);
    }
    
    new_node->prev = NULL;
    new_node->next = NULL;
    new_node->dados = novoPaciente;

    return new_node;
}

// Adiciona elemento no começo da lista.
void add_no_inicio(Lista *L, Paciente *novoPaciente) {
    Node *n = create_node(novoPaciente);

    if (n == NULL) {
        puts("Falha na alocação de novo nó (add_no_inicio).");
        exit(EXIT_FAILURE);
    }

    n->next = L->begin;

    if ((list_is_empty(L)) == 0) {
        L->end = n;
    }
    else {
        L->begin->prev = n;
    }
    L->begin = n;
    L->size++;
}



/////////////// LAUDO ///////////////

struct _fila_node {
    int id;
    Registro *registro;
    FilaNode *next;
};

struct _fila {
    FilaNode *front;
    FilaNode *rear;
};


// Cria fila (vazia).
Fila *create_fila() {
    Fila *F = (Fila*) calloc(1, sizeof(Fila));

    if (F == NULL) {
        puts("Falha na alocação de nova fila.");
        exit(EXIT_FAILURE);
    }

    F->front = F->rear = NULL;

    return F;
}

// Verifica se fila está vazia.
int fila_is_empty(const Fila *F) {
    if (F->front == NULL) return 0;
    else return 1;
}

// Adiciona id no final da fila.
void enfileirar_id(Fila *F, int id) {
    FilaNode *node = (FilaNode*) calloc(1, sizeof(FilaNode));

    if (node == NULL) {
        puts("Falha na alocação de novo nó (enfileirar_id).");
        exit(EXIT_FAILURE);
    }

    node->id = id;
    node->registro = NULL;
    node->next = NULL;

    if ((fila_is_empty(F)) == 0) F->front = node;
    else F->rear->next = node;

    F->rear = node;
}

// Retira elemento no início da fila e o retorna.
int desenfileirar_id(Fila *F) {

    int id = F->front->id;
    FilaNode *f = F->front; // Store for removal

    if (F->front != F->rear)
        F->front = F->front->next;
    else
        F->front = F->rear = NULL;

    free(f);
    return id;
}

// Libera memoria de uma fila.
void free_fila(Fila *F)
{
   FilaNode *n = F->front;
   while (n != NULL)
   {
      FilaNode *t = n->next; 
      free(n);                
      n = t;                  
   }
   free(F); 
}



/////////////// REGISTRO ///////////////

struct _registro {
    int id;
    int tempo;
    char condition[30];
};


// Criação de registro.
Registro *create_registro(const int id, const int tempo, const char condition[]) {
    Registro *registro = (Registro*) calloc(1, sizeof(Registro));

    if (registro == NULL) {
        puts("Falha na alocação de novo registro.");
        exit(EXIT_FAILURE);
    }

    registro->id = id;
    registro->tempo = tempo;
    strcpy(registro->condition, condition);
    
   

    return registro;
}

// Adiciona registro no final da fila.
void enfileirar_registro(Fila *F, Registro *registro) {
    FilaNode *node = (FilaNode*) calloc(1, sizeof(FilaNode));

    if (node == NULL) {
        puts("Falha na alocação de novo nó (enfileirar_registro).");
        exit(EXIT_FAILURE);
    }

    node->id = 0;
    node->registro = registro;
    node->next = NULL;

    if ((fila_is_empty(F)) == 0)F->front = node;
    else F->rear->next = node;

    F->rear = node;
}

// Desenfileira registro.
Registro *desenfileirar_registro(Fila *F) {

    Registro *r = F->front->registro;
    FilaNode *f = F->front; 

    if (F->front != F->rear)
        F->front = F->front->next;
    else
        F->front = F->rear = NULL;

    free(f);
    return r;
}

// Retorna a patologia de acordo com suas probabilidades.
char* condition() {
    int n = rand() % 100 + 1;
    int prob1 =  30;
    int prob2 =  50;
    int prob3 =  70;
    int prob4 =  85;

    static char c[30];

    if (n <= prob1) strcpy(c, "Saude Normal");
    else if (n > prob1 && n <= prob2) strcpy(c, "Bronquite");
    else if (n > prob2 && n <= prob3) strcpy(c, "Pneumonia");
    else if (n > prob3 && n <= prob4) strcpy(c, "Fratura de Femur");
    else strcpy(c, "Apendicite");

    return c;
}

// Retorna id de um registro.
int get_id_registro(Registro *r) { 
    return r->id;
}

// Retorna o diagnostico contido em um registro.
char *get_diagnostico_registro(Registro *r) {
    char *aux = (char*)calloc((strlen(r->condition) + 1), sizeof(char));
    strcpy(aux, r->condition);
    return aux;
}



/////////////// OCUPAÇÃO ///////////////

struct _occupation {
    int occupation;
};


// Retorna ocupação de struct que contenha ocupação.
int get_occupation(Occupation *estrutura, const int i) {
    return estrutura[i].occupation;
}

// Altera ocupação.
void change_occupation(Occupation *estrutura, const int i, int new_ocupation) {
    estrutura[i].occupation = new_ocupation;
}



/////////////// TEMPO ///////////////

struct _tempos {
    int tempo_entrada;
    int tempo_saida;
    char patologia[30];
    int id;
};


// Insere tempo de entrada.
void insert_entrada(Tempos *array, int tempo_entrada, int index, int id ,char patologia[]) {
    array[index].tempo_entrada = tempo_entrada;
    strcpy(array[index].patologia, patologia);
    array[index].id = id;
}

// Insere tempo de saida.
void insert_tempo_saida(Tempos *array, int tempo_saida, int index) {
    array[index].tempo_saida = tempo_saida;
}

// Cria uma array de struct Tempos.
Tempos *create_array_tempos(int tamanho) {
    Tempos *tempos = (Tempos*)malloc(tamanho * sizeof(Tempos));

    if (tempos == NULL) {
        puts("Falha na alocação de novo array. create_array_tempos.");
        exit(EXIT_FAILURE);
    } 

    for (int i = 0; i < tamanho; i++) {
        tempos[i].tempo_entrada = 0;
        tempos[i].tempo_saida = 0;
        strcpy(tempos[i].patologia, "0");
        tempos[i].id = 0;
    }

    return tempos;
}

// Calcula tempo de laudo.
int tempo_laudo(Tempos *array, int index) {
    int t = (array[index].tempo_saida) - (array[index].tempo_entrada);
    return t;
}



/////////////// LOGGING ///////////////

struct _logEvent {
    char message[256];
    time_t timestamp;
};

struct _log {
    LogEvent events[500]; 
    int count;
};

// Função para a criação de uma struct log.
Log *create_log() {
    Log *log = (Log*) calloc(1, sizeof(Log));
    if (log != NULL) {
        log->count = 0;
    }
    return log;
}

// Função para a criação de um evento log.
void log_event(Log *log, const char *message) {
    if (log != NULL) {
        LogEvent *new_event = (LogEvent*)calloc(1, sizeof(LogEvent));
        strcpy(new_event->message, message);
        new_event->message[sizeof(new_event->message) - 1] = '\0'; // Garante a terminação nula
        new_event->timestamp = time(NULL);

        log->events[log->count++] = *new_event;

        free(new_event);
    }
    else {
        fprintf(stderr, "Erro na alocação de memória para LogEvent.\n");
    }
}

// Função para a criação/escritura do arquivo log.
void save_log_to_file(const Log *log, const char *filename) {
    if (log != NULL) {
        FILE *file = fopen(filename, "w");
        if (file != NULL) {
            fprintf(file, "Timestamp\tMessage\n");
            for (int i = 0; i < log->count; ++i) {
                fprintf(file, "%s\t%s\n", ctime(&log->events[i].timestamp), log->events[i].message);
            }
            fclose(file);
        } else {
            perror("Error opening file");
        }
    }
}



/////////////// PRINTS ///////////////

// Função para imprimir fila para exame.
void print_fila(Fila *F) {
   for (FilaNode *f = F->front; f != NULL; f = f->next)
      printf("%d ", f->id);

   printf("\n");
}

// Função para imprimir fila de laudo.
void print_fila_registro(Fila *F) {
    puts("\n-------------FILA DE REGISTRO-------------");
    for (FilaNode *f = F->front; f != NULL; f = f->next)
        printf("\n!registro!\nID: %d\nTempo: %d\nCondição: %s\n\n", f->registro->id, f->registro->tempo, f->registro->condition);

   printf("\n");
}

// Função para imprimir struct Paciente.
void print_paciente(Paciente *p) {
    char nome[30];
    char cpf[20];
    int idade;
    int id;
    
    strcpy(nome, p->nome);
    strcpy(cpf, p->cpf);
    idade = p->idade;
    id = p->id;
    
    printf("Nome: %s\nCPF: %s\nIdade: %d\nID: %d\n", nome, cpf, idade, id);
}

// Função para imprimir lista de pacientes.
void print_lista(Lista *l) {
   for (Node *p = l->begin; p != NULL; p = p->next)
   {
      print_paciente(p->dados); 
   }
   printf("\n"); 
}



/////////////// ARRAY ///////////////

// Criação de array de structs.
Occupation *create_array(int tamanho) {
    Occupation *aparelhos = (Occupation*) calloc(tamanho, sizeof(Occupation));

    if (aparelhos == NULL) {
        puts("Falha na alocação de novo array. Linha 241.");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < tamanho; i++) {
        aparelhos[i].occupation = 0;
    }

    return aparelhos;
}   

// Verifica se array está vazia.
int array_is_empty(Tempos *array, int index) {
    if ((array[index].tempo_entrada == 0) && (array[index].tempo_saida == 0) && strcmp(array[index].patologia, "0") == 0) return 0;

    return 1;
}

// Retorna indice do elemento que está vazio.
int empty_array_index(Tempos *array, int tamanho) {
    for (int i = 0; i <  tamanho; i++) {
        if (array_is_empty(array, i) == 0) return i;
    }
    
    return -1;
}

// Retorna o indice de um elemento que contem um id especifico.
int index_from_id(Tempos *array, int id, int tamanho_array) {
    for (int i = 0; i < tamanho_array; i++) {
        if (array[i].id == id) return i;
    }

    return -1;
}

// Imprime uma array.
void print_array(Tempos *array, int index) {
    int tE, tS, id;
    char p[30];

    tE = array[index].tempo_entrada;
    tS = array[index].tempo_saida;
    id = array[index].id;
    strcpy(p, array[index].patologia);
    printf("\nTempo de entrada: %d\nTempo de saida: %d\nID: %d\nDiagnostico: %s\n",tE, tS, id, p);

}




