# Nanvix

[![Join us on Slack!](https://img.shields.io/badge/chat-on%20Slack-e01563.svg)](https://join.slack.com/t/nanvix/shared_invite/zt-1yu30bs28-nsNmw8IwCyh6MBBV~B~X7w)

# Implementação de Semáforos no sistema Nanvix

Alunos: Mateus Gontijo, Milleny Teixeira e Caio Silva

## Objetivo

O principal objetivo deste trabalho é desenvolver uma implementação funcional de semáforos em um sistema operacional, proporcionando um mecanismo robusto e eficiente para sincronização de processos concorrentes. Os semáforos desempenham um papel crucial na gestão de recursos compartilhados, prevenindo condições de corrida e garantindo a consistência e integridade dos dados.

## Metodologia 

A implementação do semáforo no sistema Nanvix envolve um bom conhecimento do sistema e de semáforos no geral. Para essa implementação, começamos pela criação de funções de operações básicas e posteriomente a implementação de funções de operação e controle. No todo, as implementações envolveram:

## Estrutura do Semáforo

A estrutura do semáforo foi desenvolvida utilizando uma lista encadeada com uma struct definida com os seguintes campos:

<code>
typedef struct
{
    int value;
    int id;
    volatile int lock; // Adiciona um bloqueio à estrutura do semáforo
    struct process *list;
} Semaphore;
</code>

### Arquivo \src\kernel\sys\sem.c :

Aqui foram implementadas as operações básicas do semáforo: 

- create(id): Cria um semáforo com o ID especificado e inicializa seu valor.
- destroy(sem): Destrói o semáforo, liberando os recursos associados.
- down(sem): Decrementa o valor do semáforo, permitindo que o processo prossiga se o valor for maior que zero. Caso contrário, o processo é bloqueado.
- up(sem): Incrementa o valor do semáforo. Se o valor era zero e há processos bloqueados, um processo é desbloqueado.

### Arquivo \src\kernel\sys\sem\semget.c :

Obtém ou cria um semáforo associado a uma chave, retornando o identificador em caso de sucesso ou -1 em caso de erro.

Exemplo:

<code> 
int sem_id = semget(42); // Obtém o semáforo associado à chave 42
</code>

### src\kernel\sys\sem\semctl.c: 

Realiza operações de controle em um semáforo identificado por semid, como obter ou definir valores, e remover se não estiver em uso. Retorna valores específicos ou -1 em caso de erro.
As operações podem ser:

- GETVAL: Retorna o valor corrente do semáforo.
- SETVAL: Define o valor do semáforo como sendo val.
- IPC_RMID: Desvincula o semáforo do processo corrente e o destrói caso não esteja mais sendo usado.

O valor de retorno da função depende de cmd. Se cmd for GETVAL, o valor corrente do semáforo é retornado. Nos demais casos de conclusão bem-sucedida, 0 é retornado. Em caso de erro, -1 é retornado.

 ### \src\kernel\sys\sem\semop: 
 
 Realiza operações atômicas de incremento/decremento no semáforo identificado por semid, com valores positivos para up() e negativos para down().

<code>
// Executa a operação apropriada
        if (op == 0)
        {
            down(&semaphoreTable[semid]); // Operação down()
            kprintf("\n DOWN REALIZADO");
            return 0;
        }
        else if (op == 1)
        {
            up(&semaphoreTable[semid]); // Operação up()
            kprintf("\n UP REALIZADO");
            return 0;
        }
        else
        {
            kprintf("Operador inválido em sys_semop().");
            return -1;
        }
</code>


# Teste

O teste <code>semaphore_test4</code> simula múltiplos processos leitores e escritores que compartilham acesso a um recurso (um arquivo, no caso). Os semáforos são utilizados para controlar o acesso concorrente, garantindo exclusão mútua entre escritores e permitindo acesso simultâneo para leitores. O teste verifica se a implementação lida corretamente com situações de concorrência.

# Conclusão 

A implementação de semáforos no sistema Nanvix busca oferecer uma solução eficiente para a sincronização de processos concorrentes, abordando desafios como condições de corrida e assegurando a integridade dos dados. 

A estrutura utiliza uma lista encadeada para gerenciar os processos bloqueados e manipular o valor do semáforo. As operações básicas e de controle foram implementadas de forma modular, facilitando a compreensão e manutenção do código. Além disso, testes foram criados para validar o correto funcionamento das operações, incluindo o teste semaphore_test4 que simula situações de concorrência entre leitores e escritores.


# CONSIDERAÇÕES 
O usuario rafaelamesquita foi de utilização do integrante Mateus Silva Gontijo
