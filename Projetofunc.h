

#ifndef __PROJ_IP_
#define __PROJ_IP_ 1  
#define arq "DADOS.txt"

typedef struct{
    char * nome_cliente;
    int numero_conta;
    char * senha;
    double saldo;
}conta_banco;
/**
 * Verifica se o usuário deseja criar uma nova conta ou se ele ja possui uma conta
 * @return opção do usuário
 */
int interface_menu(void);
/**
 * Apresenta ao usuário que possui uma conta as opções possiveis
 * @return opção do usuário
 */
int menu_conta(void);
/**
 * realiza o cadastro das infromações do usuário e as escreve no arquivo 
 */
void interface_cadastro(conta_banco* a,int n_clientes);
/**
 * Verifica se a conta que o usuário deseja acessar existe
 * @return indice da conta
 */
int verificar_conta(conta_banco* a,int n_clientes);
/**
 * Verifica o saldo que o usuário possui em sua conta
 */
void ver_saldo(conta_banco* a);
/**
 * Adiciona ou retira valor do saldo do usuário
 */
void deposito_extrato(conta_banco* a,int res);
/**
 * Altera a senha da conta do usuário
 */
void altera_senha(conta_banco*a);
/**
 * aloca memoria e carrega as informações lidas do arquivo(banco de dados) em um ponteiro,assim que se inicia o programa
 * @return ponterio de estruta
 */
conta_banco* charge_mem(int *total);
/**
 * Atualiza os dados do arquivo sempre que ocorre alguma modificação
 * Reescre todo o arquivo, permitindo que não haja restrições no tamanho do nome e da senha do usuário
 */
void Arq_Updaate(conta_banco*a,int total_clientes);

#endif