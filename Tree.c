#include <stdio.h>
#include <stdlib.h>

typedef struct dis{
    char nome_disciplina[100];
    int cod_disciplina;
    float nota_final;
}DIS;

typedef struct no{
    int matricula;
    char* nome;
    char* numero_tel;
    DIS** dis_al;
    int tamanho_vetor;
    struct no *esq;
    struct no *dir;
}NO;

NO* raiz = NULL;
void add_disciplina(NO* novo, int pos);

NO* busca(int x, NO* aux){
    if(aux == NULL){
        printf("\nMatricula Inexistente\n");
        menu_principal();
        return NULL; 
    }else if(x == aux->matricula){
        return aux; 
    }else if(x<aux->matricula){ 
        if(aux->esq != NULL){
            return busca(x, aux->esq);
        }else{
            return aux; 
        }
    }else{
        if(aux->dir != NULL){
            return busca(x, aux->dir);
        }else{
            return aux; 
        }
    }
}

void add_disciplina(NO* novo, int pos){
        int k;
        float j;
        printf("digite o nome da disciplina:\n");
        scanf(" %[^\n]", novo->dis_al[pos]->nome_disciplina);
        printf("digite o codigo da disciplina:\n");
        scanf("%d",&k);
        printf("digite a nota final:\n");
        scanf("%f",&j);
        novo->dis_al[pos]->cod_disciplina = k;
        novo->dis_al[pos]->nota_final = j;
    }

int add(int x, char y[100], char z[50]){
    NO* resp = busca(x, raiz);
    if(resp == NULL || resp->matricula != x){
        NO* novo = malloc (sizeof(NO));
        novo->nome = y;
        novo->numero_tel = z;
        novo->matricula = x;
        novo->tamanho_vetor = 0;
        printf("quantas disciplinas deseja adicionar?\n");
        scanf("%d", &novo->tamanho_vetor);
        novo->dis_al = malloc(novo->tamanho_vetor * sizeof(DIS*));
        
        for(int i = 0; i < novo->tamanho_vetor; i++){
            novo->dis_al[i] = malloc(sizeof(DIS));
        }
        for(int i = 0; i < novo->tamanho_vetor; i++){
            add_disciplina(novo, i);
        }
        
        novo->esq = NULL;
        novo->dir = NULL;

        if(resp == NULL){
            raiz = novo;
        }else{
            if(x < resp->matricula){
                resp->esq = novo;
            }else{
                resp->dir = novo;
            }
        }
        return 1;
    }
    else{
        printf("Add invalida, Matricula duplicada");
        return 0;
    }
}

NO* remover(NO* aux, int x){
    if(aux == NULL){ 
        printf("valor nao encontrado!\n");
        return NULL;
    }
    else{
        if(aux->matricula == x){
            if(aux->esq == NULL && aux->dir == NULL){ 
                free(aux);
                return NULL;
            }
            else{
                if(aux->esq == NULL || aux->dir == NULL){
                    NO* i;
                    if(aux->esq != NULL)
                        i = aux->esq;
                    else
                        i = aux->dir;
                    free(aux);
                    return i;
                }
                else{
                    NO* i = aux->esq;
                    while(i->dir != NULL)
                        i = i->dir;
                    aux->matricula = i->matricula;
                    i->matricula = x;
                    aux->esq = remover(aux->esq, x);
                    return aux;
                }
            }
        }
        else{
            if(x<aux->matricula)
                aux->esq = remover(aux->esq, x);
            else
                aux->dir = remover(aux->dir, x);
            return aux;
        }
    }
}

void alterar(int matricula){
    char novo[100];
    char y[50];
    NO *aux = busca(matricula, raiz);
        if(matricula==aux->matricula && aux->matricula != NULL){
            printf("qual dado deseja modificar?\n1-Nome\n2-Telefone\n3-Ambos\n");
            int op;
            scanf("%d",&op);
            switch(op){
                case 1:
                    printf("NOVO NOME:\n");
                    scanf(" %[^\n]", aux->nome);
                    //aux->nome = novo;
                    break;
                case 2:
                    printf("NOVO NUMERO:\n");
                    scanf(" %[^\n]", y);
                    aux->numero_tel = y;
                    break;
                case 3:
                    printf("NOVO NOME:\n");
                    scanf(" %[^\n]", novo);
                    aux->nome = novo;

                    printf("NOVO NUMERO:\n");
                    scanf(" %[^\n]", y);
                    aux->numero_tel = y;
                    break;
            }
        }
        else{
            printf("matricula inexistente");
        }
}

void imprimirAluno(int matricula){
    DIS* vet = malloc(sizeof(DIS));
    NO* aux;
    aux = busca(matricula, raiz);
    if(matricula == aux->matricula){
        printf("Nome do aluno: %s\n", aux->nome);
        printf("Matricula: %d\n", aux->matricula);
        printf("Telefone: %s\n", aux->numero_tel);
        for(int cont_disc = 0; cont_disc < aux->tamanho_vetor; cont_disc ++)
            {
                printf("Disciplina: %s\n", aux->dis_al[cont_disc]->nome_disciplina);
                printf("Codigo: %d\n", aux->dis_al[cont_disc]->cod_disciplina);
                printf("Nota final: %f\n", aux->dis_al[cont_disc]->nota_final);
            }
    }
}

void menu_principal();

void menu_cadastrar(){
    char nome[100];
    int matricula;
    char telefone[50];

    printf("\n              ADICIONAR ALUNO:   \n");
    printf("\nDigite a Matricula:\n");
    scanf("%d", &matricula);
    printf("Digite o nome do Aluno:\n");
    scanf(" %[^\n]", nome);
    printf("Digite o telefone do Aluno:\n");
    scanf(" %[^\n]", &telefone);

    int status = add(matricula, nome, telefone);
    if(status == 0){
        menu_principal();
    }else{
        printf("\nAluno cadastrado com sucesso!\n");
        menu_principal();
    }
}

void menu_alterar(){
    int matricula;
    printf("Digite a matricula do Aluno a ser alterado:\n");
    scanf("%d", &matricula);
    alterar(matricula);
    printf("\nAluno adicionado com sucesso!\n");
    menu_principal();
}

void menu_remover(){
    int matricula;
    int op;
    printf("\nDigite a Matricula do Aluno a ser removido:\n");
    scanf("%d", &matricula);
    NO* alun = busca(matricula, raiz);
    if(alun == NULL){
        printf("Aluno nao encontrado!\n");
        menu_principal();
    }else if(alun->matricula == matricula){
        printf("\nTem certeza que deseja remover o(a) %s?\n", alun->nome );
        printf("1- Sim\n2- Nao\n");
        printf("Digite uma opcao:\n");
        scanf("%d", &op);
        switch (op){
        case 1:
            raiz = remover(raiz, matricula);
            printf("\nAluno removido com sucesso!\n");
            menu_principal();
            break;
        case 2:
            menu_principal();
            break;
        default:
            printf("\nOpcao invalida!\n");
            menu_remover();
            break;
        }
    }else{
        printf("Aluno nao encontrado!\n");
        menu_principal();
    }
    
}

void menu_buscar(){
    int matricula;
    int p;
    printf("Digite a matricula do Aluno a ser buscado:\n");
    scanf("%d", &matricula);
    imprimirAluno(matricula);

    printf("\n\nDeseja pesquisar por outro Aluno?\n1- Sim\n2- Nao\n");
    printf("Digite uma opcao:\n");
    scanf("%d", &p);
    switch (p){
    case 1:
        menu_buscar();
        break;
    case 2:
        menu_principal();
    default:
        printf("\nOpcao Invalida!\n");
        menu_principal();
        break;
    }
}

void menu_principal(){
int op;
    printf("\n");
    printf("\n1- Adicionar um Aluno\n2- Remover um Aluno\n3- Alterar dados de aluno\n4- Buscar dados de Aluno\n0- Fechar Programa\n");
    printf("selecione uma opcao:\n");
    scanf("%d", &op);
    switch (op){
    case 0:
        exit(1);
        break;
    case 1:
        menu_cadastrar();
        break;
    case 2:
        menu_remover();
        break;
    case 3:
        menu_alterar();
        break;
    case 4:
        menu_buscar();
        break;
    default:
        printf("Opcao invalida!");
        menu_principal();
        break;
    }
}

int main(){
    printf("Bem vindo!");
    menu_principal();
    printf("\nValeu!-\n");
    return 0;
}