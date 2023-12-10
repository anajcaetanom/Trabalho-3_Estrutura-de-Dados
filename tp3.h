#ifndef TP3_H
#define TP3_H


typedef struct _paciente Paciente;
typedef struct _node Node;
typedef struct _list Lista;
typedef struct _fila Fila;
typedef struct _fila_node FilaNode;
typedef struct _occupation Occupation;
typedef struct _fila_node_registro NodeRegistro;
typedef struct _fila_registro FilaRegistro;
typedef struct _registro Registro;
typedef struct _tempos Tempos;
typedef struct _logEvent LogEvent;
typedef struct _log Log;

// Criação de novo paciente.
Paciente *novo_paciente(const char nome[], const char cpf[], const int idade, const int id);

// Cria nó com o paciente novo.
Node *create_node(Paciente *novoPaciente);

// Cria lista (vazia).
Lista *create_lista();

// Cria fila (vazia).
Fila *create_fila();

// Verifica se lista está vazia.
int list_is_empty(const Lista *L);

// Verifica se fila está vazia.
int fila_is_empty(const Fila *F);

// Adiciona elemento no começo da lista.
void add_no_inicio(Lista *L, Paciente *novoPaciente);

// Adiciona id no final da fila.
void enfileirar_id(Fila *F, int id);

// Adiciona registro no final da fila.
void enfileirar_registro(Fila *F, Registro *registro);

// Retira id no início da fila e o retorna.
int desenfileirar_id(Fila *F);

// Desenfileira registro.
Registro *desenfileirar_registro(Fila *F);

// Criação de registro.
Registro *create_registro(const int id, const int tempo, const char condition[]);

// Criação de array de structs.
Occupation *create_array(int tamanho);

// Retorna ocupação de struct que contenha ocupação.
int get_occupation(Occupation *estrutura, const int i);

// Altera ocupação.
void change_occupation(Occupation *estrutura, const int i, int new_ocupation);

// Retorna a patologia de acordo com suas probabilidades.
char* condition();

// Função para imprimir fila para exame.
void print_fila(Fila *F);

// Função para imprimir struct Paciente.
void print_paciente(Paciente *p);

// Função para imprimir lista de pacientes.
void print_lista(Lista *l);

// Função para imprimir fila de laudo.
void print_fila_registro(Fila *F);

// Cria uma array de struct Tempos.
Tempos *create_array_tempos(int tamanho);

// Insere tempo de entrada.
void insert_entrada(Tempos *array, int tempo_entrada, int index, int id ,char patologia[]);

// Insere tempo de saida.
void insert_tempo_saida(Tempos *array, int tempo_saida, int index);

// Verifica se array está vazia.
int array_is_empty(Tempos *array, int index);

// Retorna indice do elemento que está vazio.
int empty_array_index(Tempos *array, int tamanho);

// Calcula tempo de laudo.
int tempo_laudo(Tempos *array, int index);

// Retorna id de um registro.
int get_id_registro(Registro *r);

// Retorna o indice de um elemento que contem um id especifico.
int index_from_id(Tempos *array, int id, int tamanho_array);

// Imprime uma array.
void print_array(Tempos *array, int index);

// Retorna o diagnostico contido em um registro.
char *get_diagnostico_registro(Registro *r);

// Libera memoria de uma fila.
void free_fila(Fila *F);

// Função para a criação de uma struct log.
Log *create_log();

// Função para a criação de um evento log.
void log_event(Log *log, const char *message);

// Função para a criação/escritura do arquivo log.
void save_log_to_file(const Log *log, const char *filename);

#endif