#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Projetofunc.h"

int interface_menu(void){
    int res;
    printf("________________________________\n         SEJA BEM VINDO\n________________________________");
    printf("\n(1)JA POSSUI UMA CONTA \n(2)DESEJA CADASTRAR UMA NOVA CONTA\n");
    scanf("%d",&res);
    return res;
}
int menu_conta(void){
    int res;
    printf("________________________________\n");
    printf("QUAL ACAO VOCE DESEJA REALIZAR ?\n");
    printf("(1)VER SALDO\n");
    printf("(2)REALIZAR DEPOSITO\n");
    printf("(3)REALIZAR EXTRATO\n");
    printf("(4)ALTERAR SENHA\n");
    printf("(5)ACESSAR OUTRA CONTA\n");
    printf("(6)CADASTRAR NOVA CONTA\n");
    printf("(7)FINALIZAR\n");
    scanf("%d",&res);
    return res;

}
void interface_cadastro(conta_banco* a,int n_clientes){
    FILE* ARQ_CONTAS=NULL;
    ARQ_CONTAS = fopen(arq,"a+");
    if(!ARQ_CONTAS){
        printf("erro ao abrir arquivo para escrita");
        exit(0);
    }
    
    char buffer[128];
    int tamNome,tamSenha,i;
    printf("INFORME SEU NOME\n|");
    scanf("%*c%[^\n]",buffer);
    tamNome=strlen(buffer);
    a->nome_cliente=(char*)malloc(tamNome+1*sizeof(char));
    strcpy(a->nome_cliente,buffer);
    //printf("%s",a->nome_cliente);
    printf("\nINFORME SUA SENHA\n|");
    scanf("%*c%s",buffer);
    tamSenha=strlen(buffer);
    a->senha=(char*)malloc(tamSenha+1*sizeof(char));
    strcpy(a->senha,buffer);
    a->numero_conta=n_clientes+1000;
    printf("\nO NUMERO DA SUA CONTA E:\n (%d)\n",a->numero_conta);
    a->saldo=0;
    
    fprintf(ARQ_CONTAS,"%s\n",a->nome_cliente);
    fprintf(ARQ_CONTAS,"%d\n",a->numero_conta);
    fprintf(ARQ_CONTAS,"%s\n",a->senha);
    fprintf(ARQ_CONTAS,"%lf\n",a->saldo);  
    fclose(ARQ_CONTAS);
}

int verificar_conta(conta_banco* a,int n_clientes){
    char buffer[128];
    int i,nconta;
    int res;
    printf("DESEJA ACESSAR SUA CONTA VIA:\n(1)NUMERO DA CONTA\n(2)NOME DO CLIENTE\n");
    scanf("%d",&res);
    if(res==1){
        printf("DIGITE O NUMERO DA SUA CONTA\n|");
        scanf("%d",&nconta);
        for(i=0;i<n_clientes;i++){
            if(a[i].numero_conta==nconta){
            printf("CONTA ENCONTRADA\nINFORME SUA SENHA\n|");
            while(1){
                scanf("%s",buffer); 
                res=strcmp(buffer,a[i].senha);
                if(res==0){
                printf("SENHA CORRETA\n");
                break;
                }
                printf("SENHA INCORRETA\nTENTE NOVAMENTE\n");
            }
            return i;
            }
        }
        return -10;
    }
    if(res==2){
        printf("DIGITE SEU NOME\n|");
        scanf("%*c%[^\n]",buffer);
        for(i=0;i<n_clientes;i++){
            if(!strcmp(a[i].nome_cliente,buffer)){
            printf("CONTA ENCONTRADA\nINFORME SUA SENHA\n|");
            while(1){
                scanf("%*c%s",buffer); 
                res=strcmp(buffer,a[i].senha);
                if(res==0){
                printf("SENHA CORRETA\n");
                break;
                }
                printf("SENHA INCORRETA\nTENTE NOVAMENTE\n|");
            }
            return i;
            }
        }
        return -10;
    }

}
void ver_saldo(conta_banco* a){
    printf("________________________________\n");
    printf("SEU SALDO ATUAL E:\n|| %.4lf\n",a->saldo);
    printf("________________________________\n");
}
void deposito_extrato(conta_banco* a,int res){
    double valor;
    if(res==2){
        printf("________________________________\n");
        printf("QUAL VALOR DESEJA DEPOSITAR ?:\n|");
        scanf("%lf",&valor);
        a->saldo=a->saldo+valor;
        ver_saldo(a);
    }
    if(res==3){
        printf("________________________________\n");
        printf("QUAL VALOR DESEJA RETIRAR ?:\n|");
        while(1){
            scanf("%lf",&valor);
            if(a->saldo-valor>=0)break;
            printf("NAO FOI POSSIVEL REALIZAR O EXTRATO\nSALDO INSUFICIENTE\nDIGITE OUTRO VALOR\n|");
        }
        a->saldo=a->saldo-valor;
        ver_saldo(a);
    }

}
void altera_senha(conta_banco* a){
    char buffer[128];
    int tam_old;
    printf("DIGITE SUA SENHA ATUAL\n|");
    while(1){
        scanf("%*c%s",buffer); 
        if(!strcmp(buffer,a->senha)){
            printf("SENHA CORRETA!\n");
            break;
        }
        printf("SENHA INCORRETA\nTENTE NOVAMENTE\n");
    }
    tam_old=strlen(buffer);
    printf("DIGITE SUA NOVA SENHA\n|");
    scanf("%*c%s",buffer);
    a->senha=(char*)realloc(a->senha,tam_old+1*sizeof(char));
    strcpy(a->senha,buffer);
    printf("SENHA ALTERADA COM SUCESSO\n");
}
conta_banco* charge_mem(int *total){
    FILE* ARQ_CONTAS=NULL;
    ARQ_CONTAS=fopen(arq,"r");
    if(!ARQ_CONTAS){
        printf("erro ao abrir arquivo para escrita");
        exit(0);
    }
    conta_banco*a=NULL;
    int i=0,r,cont=0;
    char buffer[128];
    while(1){
        r=fscanf(ARQ_CONTAS,"%[^\n]\n",buffer);
        if(r==EOF)break;
        cont++;
        a=(conta_banco*)realloc(a,cont*sizeof(conta_banco));
        a[i].nome_cliente=(char*)malloc(strlen(buffer)+1*sizeof(char));
        strcpy(a[i].nome_cliente,buffer);        
        fscanf(ARQ_CONTAS,"%d\n",&a[i].numero_conta);       
        fscanf(ARQ_CONTAS,"%s\n",buffer);  
        a[i].senha=(char*)malloc(strlen(buffer)+1*sizeof(char));
        strcpy(a[i].senha,buffer);      
        fscanf(ARQ_CONTAS,"%lf\n",&a[i].saldo);   
        i++;
        } 
    fclose(ARQ_CONTAS);
    *total=cont;
    return a;
}
void Arq_Updaate(conta_banco* a,int total_clientes){
    FILE* ARQ_CONTAS=NULL;
    ARQ_CONTAS=fopen(arq,"w");
    int i;
    for(i=0;i<total_clientes;i++){
    fprintf(ARQ_CONTAS,"%s\n",a[i].nome_cliente);
    fprintf(ARQ_CONTAS,"%d\n",a[i].numero_conta);
    fprintf(ARQ_CONTAS,"%s\n",a[i].senha);
    fprintf(ARQ_CONTAS,"%lf\n",a[i].saldo);
    }
    fclose(ARQ_CONTAS);
}