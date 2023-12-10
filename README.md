# Trabalho-2_Estrutura-de-Dados
Este é um projeto de simulação de controle de exames médicos implementado em C. O programa utiliza estruturas de dados como listas e filas para gerenciar a chegada de pacientes, realização de exames de raio-x e emissão de laudos médicos.
Estrutura do Projeto

# O projeto é organizado em diferentes arquivos:

tp2.h: Contém as declarações das estruturas de dados e funções utilizadas no projeto.

tp2.c: Implementação das funções definidas em tp2.h.

main.c: Programa principal que utiliza as funções implementadas para simular o controle de exames médicos.
    
# Para usar o Makefile, coloque-o na mesma pasta que seus arquivos-fonte e digite "make" no terminal.

# Principais Decisões de Implementação

A chegada de pacientes é simulada com uma probabilidade de 20% a cada iteração do loop, determinando se um paciente chegou ou não.

O tempo de exame de raio-x é aleatório entre 5 e 10 unidades de tempo.

O tempo de preparação do laudo médico é aleatório entre 10 e 30 unidades de tempo.

A ocupação dos aparelhos de raio-x e dos radiologistas é controlada para garantir que apenas um paciente seja atendido por vez.

O tempo médio na fila para laudo é calculado e exibido ao final da simulação.
    
