
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct {
    int id;
    char name[9];
    int father_id;
    struct Dirs *prox;
    
} Dirs;
//typedef struct Dirs TDirs;
//---------------------------------------------------------------------------



/* -----------------------------------------------------------------------------
 Prototipos das funcoes
 ------------------------------------------------------------------------------*/
void Inicializar_Dirs (Dirs *inicio);
void Inserir (Dirs *inicio);
void Listar (Dirs *inicio);
void Remove (Dirs *inicio);
void PWD (Dirs *inicio);
void CD (Dirs *inicio);
/* Variaveis global */
int id=0, currentDir = 0;
char parans[9];


/* -----------------------------------------------------------------------------
 PRINCIPAL
 ------------------------------------------------------------------------------*/
int main(void)
{
    
    Dirs *ini = (Dirs *) malloc(sizeof(Dirs));
    //ini = malloc (sizeof (Dirs));
    //Dirs ini;
    char linha_comando[80], *comando, *parametro;
    Inicializar_Dirs(&ini);
    
    while (1>0) {
    printf("$ ");
    gets(linha_comando);
    comando = strtok(linha_comando, " ");
    parametro = strtok(NULL, "\0");
    if(parametro == NULL) {
        strcpy(parans, " ");
    } else {
        strcpy(parans, parametro);
    }
    
    if(strcmp (comando, "mkdir") == 0) {
        Inserir(&ini);
    }
    //Inserir(&ini);
    //Inserir(&ini);
    //Inserir(&ini, "TES");
    //Remove(&ini, "test");
    //printf("%s", ini.name);
    if(strcmp (comando, "ls") == 0) {
        Listar(&ini);
    }
    if(strcmp (comando, "pwd") == 0) {
        PWD(&ini);
        //printf("ENTROU PWD");
    }
    if(strcmp (comando, "rmdir") == 0) {
        Remove(&ini);
    }
    if(strcmp (comando, "cd") == 0) {
        CD(&ini);
    }
        
    }
    
    
    
    return 0;
    
}


void Inicializar_Dirs (Dirs *inicio)
{
    inicio->id = id;
    strcpy(inicio->name, "/");
    inicio->father_id = 0;
    inicio->prox = NULL;
}

void Inserir (Dirs *inicio)
{
    id++;
    Dirs *percorre;
    
    /* Criacao do novo no - AlocaÁ„o de memoria */
    Dirs *no_novo = (Dirs *) malloc(sizeof(Dirs));
    no_novo -> id = id;
    no_novo -> father_id = currentDir;
    strcpy(no_novo->name, parans);
    no_novo -> prox = NULL;
    
        percorre = inicio;
        while (percorre->prox != NULL)
        {
            percorre = percorre -> prox;
        }
        percorre->prox = no_novo;
    
}


void Listar (Dirs *inicio)
{
    Dirs *percorre;
    percorre = inicio;
    while (1 > 0)
    {
        if(percorre->father_id == currentDir && strcmp (percorre->name, "/") != 0) {
            printf("       %s \n", percorre->name);
        }
        //printf("\n %s", percorre->name);
        
        if(percorre->prox == NULL) {break;}
        percorre = percorre -> prox;
    }
    //printf("\n %d", percorre->id);
    
}

void Remove (Dirs *inicio)
{
    int i =0;
    Dirs *percorre, *percorreAnt;
    percorre = inicio;
    while (1 > 0)
    {
        if(percorre->father_id == currentDir && strcmp (percorre->name, parans) == 0 &&percorre->id !=0) {
        //if(percorre->id == 1) {
            if(percorre->prox == NULL) {
                percorreAnt -> prox = NULL;
                free(percorre);
            } else {
                //meio
                percorreAnt->prox = percorre->prox;
            }
        }
        if(percorre->prox == NULL) {break;}
        percorreAnt = percorre;
        percorre = percorre -> prox;
        i++;
    }
  
}


void CD (Dirs *inicio)
{
    Dirs *percorre;
    percorre = inicio;
    if(strcmp (parans, "..") == 0) {
        //ir ao pai
        while (1 > 0)
        {
            if(percorre->id == currentDir) {
                currentDir = percorre->father_id;
            }
            if(percorre->prox == NULL) {break;}
            percorre = percorre -> prox;
        }
    } else {
        //entrar
        while (1 > 0)
        {
            if(percorre->father_id == currentDir && strcmp (percorre->name, parans) == 0 &&percorre->id !=0) {
                currentDir = percorre->id;
            }
            if(percorre->prox == NULL) {break;}
            percorre = percorre -> prox;
        }
    }
    
    
}

void PWD (Dirs *inicio) {
    Dirs *percorre;
    percorre = inicio;
    while (1 > 0)
    {
        if(percorre->id == currentDir) {break;}
        percorre = percorre -> prox;
    }
    printf("%s \n", percorre->name);
}
