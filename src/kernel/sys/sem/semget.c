// Chamada de Sistema sys_semget()

/*
int semget(unsigned key)
A função semget permite que um processo use um semáforo associado a uma chave
(key). Caso nenhum semáforo esteja associado à chave especificada (key), um novo se-
máforo com essa chave deve ser criado.
Em caso de conclusão com êxito, a função deve retornar o identificador do semáforo asso-
ciado a key. Em caso de erro, -1 deve ser retornado.
*/