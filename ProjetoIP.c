#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Projetofunc.h"

int main()
{
    FILE* ARQ_CONTAS=NULL;
    ARQ_CONTAS=fopen(arq,"a");
    if(!ARQ_CONTAS){
        printf("erro ao criar arquivo");
        return 0;
    }
    fclose(ARQ_CONTAS);
    
    int res,i,total_clientes=0,verificacao,r;
    conta_banco* cliente=charge_mem(&total_clientes);
    
    res=interface_menu();
    if(res==2){
        new:
        while(1){
        total_clientes++;
        printf("Cadastrando uma nova conta...\n");
        cliente=(conta_banco*)realloc(cliente,total_clientes*sizeof(conta_banco));
        interface_cadastro(&cliente[total_clientes-1],total_clientes);
        printf("________________________________\n(1)ACESSAR CONTA\n(2)CADASTRAR NOVA CONTA\n(3)FINALIZAR\n");
        scanf("%d",&res);
        if(res==1)break;
        if(res==3)return 0;
        if(res==2)continue;
        } 
    }
    if(res==1){
        other:
        printf("ACESSE SUA CONTA !\n");
        while(1){
            verificacao=verificar_conta(cliente,total_clientes);
            if(verificacao!=-10)break;
            printf("DADO INVALIDO!\n");
            if(verificacao==-10){
                printf("(1)FINALIZAR\n(2)CONTINUAR\n");
                scanf("%d",&res);
                if(res==1){
                free(cliente);
                return 0;
                }
            }
        }
        res=menu_conta();
            do{
                switch(res){
                    case 1:
                        ver_saldo(&cliente[verificacao]);
                        printf("________________________________\n");
                        printf("(1)REALIZAR OUTRA OPERACAO\n(2)FINALIZAR\n");
                        scanf("%d",&res);
                        if(res==2){
                            free(cliente);
                            return 0;
                        }
                        break;
                    case 2:
                        deposito_extrato(&cliente[verificacao],res);
                        Arq_Updaate(cliente,total_clientes);
                        printf("________________________________\n");
                        printf("(1)REALIZAR OUTRA OPERACAO\n(2)FINALIZAR\n");
                        scanf("%d",&res);
                        if(res==2){
                            free(cliente);
                            return 0;
                        }
                        break;
                    case 3:
                        deposito_extrato(&cliente[verificacao],res);
                        Arq_Updaate(cliente,total_clientes);
                        printf("________________________________\n");
                        printf("(1)REALIZAR OUTRA OPERACAO\n(2)FINALIZAR\n");
                        scanf("%d",&res);
                        if(res==2){
                            free(cliente);
                            return 0;
                        }
                        break;
                    case 4:
                        altera_senha(&cliente[verificacao]);
                        Arq_Updaate(cliente,total_clientes);
                        printf("________________________________\n");
                        printf("(1)REALIZAR OUTRA OPERACAO\n(2)FINALIZAR\n");
                        scanf("%d",&res);
                        if(res==2){
                            free(cliente);
                            return 0;
                        }
                        break;
                    case 7:
                        free(cliente);
                        return 0;
                    case 6:
                        goto new;
                        break;
                    case 5:
                        goto other;
                }
                res=menu_conta();
            }while(1);
    }
    free(cliente);
    return 0;
}