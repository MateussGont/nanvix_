# Nanvix

[![Join us on Slack!](https://img.shields.io/badge/chat-on%20Slack-e01563.svg)](https://join.slack.com/t/nanvix/shared_invite/zt-1yu30bs28-nsNmw8IwCyh6MBBV~B~X7w)

# Implementação de Semáforos no sistema Nanvix

Alunos: Mateus Gontijo e Milleny Teixeira

## Objetivo

O principal objetivo deste trabalho é desenvolver uma implementação funcional de semáforos em um sistema operacional, proporcionando um mecanismo robusto e eficiente para sincronização de processos concorrentes. Os semáforos desempenham um papel crucial na gestão de recursos compartilhados, prevenindo condições de corrida e garantindo a consistência e integridade dos dados.

## Metodologia 

A implementação do semáforo no sistema Nanvix envolve um bom conhecimento do sistema e de semáforos no geral. Para essa implementação, começamos pela criação de funções de operações básicas e posteriomente a implementação de funções de operação e controle. No todo, as implementações envolveram:

**Arquivo \src\kernel\sys\sem.c** :

- create(n): cria um semáforo semáforo e o inicializa com o valor n.
- down(): testa o valor do semáforo. Se esse valor for maior que zero, ele é decrementado eo processo continua sua execução normalmente. Caso contrário, o processo é bloqueado.
- up(): testa se o valor do semáforo é zero. Em caso afirmativo e existir algum processo bloqueado no semáforo, o processo é desbloqueado. Caso contrário o valor do semáforo é incrementado.
- destroy(): destrói o semáforo

**Arquivo \src\kernel\sys\sem\semget.c :** Obtém ou cria um semáforo associado a uma chave, retornando o identificador em caso de sucesso ou -1 em caso de erro.

 **\src\kernel\sys\sem\semctl.c**: Realiza operações de controle em um semáforo identificado por semid, como obter ou definir valores, e remover se não estiver em uso. Retorna valores específicos ou -1 em caso de erro.

 **\src\kernel\sys\sem\semop:** Realiza operações atômicas de incremento/decremento no semáforo identificado por semid, com valores positivos para up() e negativos para down().

 ## Estrutura do Semáforo

A estrutura do semáforo foi desenvolvida utilizando uma lista encadeada com uma struct definida com os seguintes campos:

<code>
typedef struct
{
    int value; 
    int id;
    volatile int lock; 
    struct process *list;
} Semaphore;
</code>

value: valor do semáforo 
id: id do semáforo
lock: variável de bloqueio do semáforo
list: lista de processos pra usar o semáforo

# Teste

O teste <code>semaphore_test4</code> simula múltiplos processos leitores e escritores que compartilham acesso a um recurso (um arquivo, no caso). Os semáforos são utilizados para controlar o acesso concorrente, garantindo exclusão mútua entre escritores e permitindo acesso simultâneo para leitores. O teste verifica se a implementação lida corretamente com situações de concorrência.
