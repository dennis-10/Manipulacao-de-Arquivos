#include <stdio.h>
#include <string.h>
 
typedef struct _Endereco Endereco;
 
struct _Endereco{

    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
};
 
int main(int argc, char**argv){

    FILE *f;
    Endereco e; 

    if(argc != 2){
        fprintf(stderr, "USO: %s [CEP]", argv[0]);
        return 1;
    }
 
    long primeiro, meio, ultimo, posicao;
    f = fopen("cep_ordenado.dat","r");
    fseek(f,0,SEEK_END);
    posicao = ftell(f);
    rewind(f);
    
    primeiro = 0;
    ultimo = (posicao/sizeof(Endereco))-1;

    int achei = 0, lidos = 0;
    
    while(primeiro <= ultimo){

    	lidos++;

    	meio = (primeiro+ultimo)/2;
        fseek(f,meio*sizeof(Endereco),SEEK_SET);
    	fread(&e,sizeof(Endereco),1,f);
        if(strncmp(argv[1],e.cep,8) == 0){
            printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
            achei = 1;
            break;
        }
        else if(strncmp(argv[1],e.cep,8) > 0){
            primeiro = meio+1;
        }
        else{
            ultimo = meio-1;
        }
    }   
    fclose(f);

    if(achei == 0){

        printf("\nNão foi encontrado o resultado para %s. Foram lidos: %d", argv[1], lidos);
    }
    return 0;
}
