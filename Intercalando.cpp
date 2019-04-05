#include <stdio.h>
#include <stdlib.h>
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

void intercala(char n1[40], char n2[40], char n3[40]){
    Endereco a; 
    Endereco b;
    FILE *f1 = fopen(n1, "r");
    FILE *f2 = fopen(n2, "r"); 
    FILE *f3 = fopen(n3, "w"); 
    fread(&a, 300, 1, f1);
    fread(&b, 300, 1, f2);

    while(!feof(f1)&&!feof(f2)){
        if(strncmp(a.cep, b.cep, 8) < 0){
            fprintf(f3,"%.72s%.72s%.72s%.72s%.2s%.8s \n",a.logradouro,a.bairro,a.cidade,a.uf,a.sigla,a.cep);
            fread(&a, 300, 1, f1);
        }
        else{
            fprintf(f3, "%.72s%.72s%.72s%.72s%.2s%.8s \n",b.logradouro,b.bairro,b.cidade,b.uf,b.sigla,b.cep);
            fread(&b, 300, 1, f2);
        }

    }
    while(!feof(f1))    {
        fprintf(f3, "%.72s%.72s%.72s%.72s%.2s%.8s \n",a.logradouro,a.bairro,a.cidade,a.uf,a.sigla,a.cep);
        fread(&a, 300, 1, f1);
    }
    while(!feof(f2))    {
        fprintf(f3, "%.72s%.72s%.72s%.72s%.2s%.8s \n",b.logradouro,b.bairro,b.cidade,b.uf,b.sigla,b.cep);
        fread(&b, 300, 1, f2);
    }

    fclose(f1);
    fclose(f2);
    fclose(f3);
}

void copia(char n1[40], char n2[40]){
    FILE *f1 = fopen(n1, "r");
    FILE *f2 = fopen(n2, "w");
    char linha[300];
    fread(linha, 300, 1, f1);
    while(!feof(f1)){
        fprintf(f2, "%.300s", linha);
        fread(linha, 300, 1, f1);
    }
    fclose(f1);
    fclose(f2);
}

int main(int argc, char**argv){
    printf("\nInsira a quantidade de blocos ordenados:");
    int arquivos;
    scanf("%d", &arquivos);

    if(arquivos > 1){
        int intercalar = arq;
        int gerad= 0;

        if(arquivos%2 != 0){
            intercalar--;
        }
        for(int x = 0, y = 0; x < intercalar; x+=2){
            char n1[27];
            char n2[27];
            char n3[31];

            sprintf(n1, "ord_blocos/ord_bloco%d.dat", x+1);
            sprintf(n2, "ord_blocos/ord_bloco%d.dat", x+2);
            sprintf(n3, "inter_blocos/intercalado%d.dat", ++y);

            intercala(n1, n2, n3);
            gerad++;

            if(x+2 >= intercalar)
            {
                if(intercalar!=arquivos)
                {
                    char n1[27];
                    char n2[31];

                    sprintf(n1, "ord_blocos/ord_bloco%d.dat", arquivos);
                    sprintf(n2, "inter_blocos/intercalado%d.dat", ++y);
                    copia(n1, n2);
                    gerad++;
                }
                break;
            }
        }
        int num = gerad;

        while(gerad>1){
            intercalar = gerad;
            int aux = intercalar;
            int ultimo = num;

            if(gerad%2 != 0){
                intercalar--;
            }
            gerou = 0;

            for(int x = (num-aux), y = 0; y<intercalar; x+=2, y+=2){
                char n1[31];
                char n2[31];
                char n3[31];

                sprintf(n1, "inter_blocos/intercalado%d.dat", x+1);
                sprintf(n2, "inter_blocos/intercalado%d.dat", x+2);
                sprintf(n3, "inter_blocos/intercalado%d.dat", ++num);

                intercala(n1, n2, n3);
                gerad++;
                if(y+2>=intercalar){
                    if(intercalar!=aux){
                        char n1[31];
                        char n2[31];

                        sprintf(n1, "inter_blocos/intercalado%d.dat", ultimo);
                        sprintf(n2, "inter_blocos/intercalado%d.dat", ++num);
                        copia(n1, n2);
                        gerad++;
                    }
                    break;
                }
            }
        }
    }
    return 0;
}
