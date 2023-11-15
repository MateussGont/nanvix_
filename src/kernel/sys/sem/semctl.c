// Chamada de Sistema sys_semctl()

/*
int semctl(int semid, int cmd, int val);
A função semctl() permite um série de operações de controle no semáforo identificado
por semid. Essas operações são especificadas por cmd e podem ser: GETVAL, retorna
o valor corrente do semáforo; SETVAL, define o valor do semáforo como sendo val; e
IPC_RMID, desvincula o semáforo do processo corrente e o destrói caso não esteja mais
sendo usado.
O valor de retorno da função depende de cmd. Caso esse seja GETVAL, o valor corrente do
semáforo é retornado. Nos demais casos de conclusão com êxito, 0 deve ser retornado. Em
caso de erro -1 deve ser retornado retornado.
*/