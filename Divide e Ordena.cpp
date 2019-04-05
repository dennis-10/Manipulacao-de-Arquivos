#include <stdio.h>
#include <stdlib.h>
 
typedef struct _Endereco Endereco;
 
struct _Endereco
{
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
    
};

int compara(const void *e1, const void *e2)
{
    return strncmp(((Endereco*)e1)->cep,((Endereco*)e2)->cep,8);
}


int main(int argc, char**argv)
{
    FILE *original = fopen("cep.dat", "r");
    FILE *f, *saida;

    int arq=8; 
    int i, rest, linhaArq;
    long numlinhas, l, posicao, qtd;
    char linha[300];
    Endereco *e;
    

    fseek(original,0,SEEK_END);
    posicao = ftell(original);
    rewind(original);
    numlinhas = (posicao/300);  
    linhaArq = numlinhas / arq;
    rest = numlinhas % arq;

    for(i=1; i<= arq; i++)
    {
        char bloco[] = "bloco";
        char nome[7];
        sprintf(nome, "%s%d.dat", bloco, i);
        FILE *limpa = fopen(nome, "w");
        fclose(limpa);

        for(int y=1;y<=linhaArq; y++){   
            FILE *saida = fopen(nome, "a");
            fread(linha,300,1,original);
            fprintf(saida,"%.300s",linha);
            fclose(saida);
        }
        if((i+1) > arq && rest > 0) {
        
        char bloco[] = "bloco";
        char nome[7];
        sprintf(nome, "%s%d.dat", bloco, (i+1));
        FILE *limpa = fopen(nome, "w");
        fclose(limpa);

            for(int x = 0; x < rest; x++){
                
                FILE *saida = fopen(nome, "a");
                fread(linha,300,1,original);
                fprintf(saida,"%.300s",linha);
                fclose(saida);
            }
        }
    }

    fclose(original);

    for(int i=0;i<=qtd ;i++){
 
    char nomearq[11];
    sprintf(nomearq,"bloco%d.dat",i);
     f = fopen("nomearq","r");
    fseek(f,0,SEEK_END);
    posicao = ftell(f);
    qtd = posicao/sizeof(Endereco);
    e = (Endereco*) malloc(posicao);
    rewind(f);
    
    if(fread(e,sizeof(Endereco),qtd,f) == qtd)
    {
        printf("Lido = OK\n");
    }
    qsort(e,qtd,sizeof(Endereco),compara);
    printf("Ordenado = OK\n");
    char nomeord[15];
    sprintf(nomeord, "ord_bloco%d.dat", i);
	f = fopen(nomeord,"w");
	fwrite(e,sizeof(Endereco),qtd,f);
	fclose(f);
	printf("Escrito = OK\n");
	free(e);
 
    fclose(f);
}
    return 0;
}

