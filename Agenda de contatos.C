#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// ESTRUTURA DA AGENDA
typedef struct {
    char rua[50];
    char numero[10];
    char complemento[50];
    char bairro[30];
    char cidade[30];
    char estado[30];
} Endereco;

typedef struct {

    char telefone[15];
    char tipo_telefone[10];

} Telefone;

typedef struct {
    char primeiro_nome[30];
    char ultimo_nome[30];
    char aniversario[10];
    char email[50];
    int quantidade_telefones;
    Endereco endereco;
    Telefone telefones[5];

} Contatos;


typedef struct {

    Contatos *contato;
    int cont;
    int limite;

} AgendaArray;


//VARIAVEL GLOBAL DA AGENDA
AgendaArray *list;


//CRIAÇÃO DA AGENDA
AgendaArray* criar_Agenda(int cont) {

    //ALOCAÇÃO
    AgendaArray *Agenda = (AgendaArray*) malloc(sizeof(AgendaArray));

    Agenda->cont = cont;
    Agenda->limite = cont+100;

    Agenda->contato = (Contatos*) malloc(Agenda->limite * sizeof(Contatos));

    //CONFERIR
    if (Agenda == NULL || Agenda->contato == NULL) {
        printf("ERRO: SEM MEMORIA");
        exit(0);
    }
    

    return Agenda;

}


//LISTA VAZIA E AVISO
int lista_vazia() {
    if (list->cont == 0) {
        printf("======================================\n");
        printf("AVISO: NAO É POSSIVEL EFETUAR A AÇAO COM A LISTA VAZIA\n");
        return 1;
    }
    return 0;
}


//ordenação 0 = nascimento, 1 = nome 
void ordernar(int op) {
    int tam = list->cont;
    Contatos *aux = (Contatos*)malloc(sizeof(Contatos));

    //nome
    if (op) {
        for (int x = 0; x < tam; ++x) {
            for (int y = x; y < tam; ++y) {
                if (strcmp(list->contato[x].primeiro_nome, list->contato[y].primeiro_nome) > 0) {
                    memcpy(aux, &list->contato[x], sizeof(Contatos));
                    memcpy(&list->contato[x], &list->contato[y], sizeof(Contatos));
                    memcpy(&list->contato[y], aux, sizeof(Contatos));
                }
            }
        }
    }

    //niver
    else {
        for (int x = 0; x < tam; ++x) {
            for (int y = x; y < tam; ++y) {
                if (strcmp(list->contato[x].aniversario, list->contato[y].aniversario) > 0) {
                    memcpy(aux, &list->contato[x], sizeof(Contatos));
                    memcpy(&list->contato[x], &list->contato[y], sizeof(Contatos));
                    memcpy(&list->contato[y], aux, sizeof(Contatos));
                }
            }
        }
    }

    //limpa aux
    free(aux);
}


//escreve contato na pos
void escrever_contato(int i) {
    printf("======================================\n");
    printf("Posicao Contato: %d\n", i);
    printf("Primeiro Nome -> %s\n", list->contato[i].primeiro_nome);
    printf("Ultimo nome -> %s\n", list->contato[i].ultimo_nome);

    for(int j = 0; j < list->contato[i].quantidade_telefones; j++) {
        printf("Telefone[%d] -> %s -> %s\n", j, list->contato[i].telefones[j].telefone, list->contato[i].telefones[j].tipo_telefone);
    }
    
    printf("Email -> %s\n", list->contato[i].email);
    printf("Aniversario -> %s\n", list->contato[i].aniversario);
    printf("Informações de endereco:\n");
    printf("Numero -> %s", list->contato[i].endereco.numero);
    printf("Rua -> %s", list->contato[i].endereco.rua);
    printf("Bairro -> %s", list->contato[i].endereco.bairro);
    printf("Cidade -> %s", list->contato[i].endereco.cidade);
    printf("Estado -> %s", list->contato[i].endereco.estado);
    printf("Complemento -> %s", list->contato[i].endereco.complemento);
    printf("======================================\n");
}



//VERIFICAÇÃO DOS DADOS PARA PADRONIZAR A ENTRADA
void verificar(int op, int pos) {

    //limpar stdin
    fflush(stdin);

    //verificar primeiro nome
    if (op == 1) {
        if (strlen(list->contato[pos].primeiro_nome) < 3) {
            printf("É NECESSARIO UM PRIMEIRO NOME MAIOR QUE 3 CARACTERES, DIGITE NOVAMENTE -> ");
            scanf("%s", list->contato[pos].primeiro_nome);
            verificar(1, pos);

        }
    }

    //verificar ultimo nome
    else if (op == 2) {
        if (strlen(list->contato[pos].ultimo_nome) < 3) {
            printf("É NECESSARIO UM ULTIMO NOME MAIOR QUE 3 CARACTERES, DIGITE NOVAMENTE -> ");
            scanf("%s", list->contato[pos].ultimo_nome);
            verificar(2, pos);
        }
    }
    
    //verificar email
    else if (op == 4) {
        for (int i = 0; i < list->cont; i++) {
            if (strcmp(list->contato[pos].email, list->contato[i].email) == 0) {
                printf("JA EXISTE UM CONTATO COM O MESMO EMAIL, DIGITE OUTRO -> ");
                scanf("%s", list->contato[pos].email);
                verificar(4, pos);
            }
        }
        
    }

    //verificar aniverasario
    else if (op == 5) {
        if (strlen(list->contato[pos].aniversario) != 8) {
            printf("É NECESSARIO UM ANIVERSARIO VALIDO EX(20040814) -> ");
            scanf("%s", list->contato[pos].aniversario);
            verificar(5, pos);
        }
        
    }
}


//ADICIONAR ENDEREÇO
void adicionar_endereco(int pos) {
    //retirar bug devido ao scanf para os fgets funcionar
    getchar();

    //INTERFACE E LEITURA
    printf("======================================\n");
    printf("ENDERECO\n");
    printf("======================================\n");
    printf("NUMERO -> ");
    fgets(list->contato[pos].endereco.numero,9,stdin);
    printf("RUA -> ");
    fgets(list->contato[pos].endereco.rua,49,stdin);
    printf("BAIRRO -> ");
    fgets(list->contato[pos].endereco.bairro,29,stdin);
    printf("CIDADE -> ");
    fgets(list->contato[pos].endereco.cidade,29,stdin);
    printf("ESTADO -> ");
    fgets(list->contato[pos].endereco.estado,29,stdin);
    printf("COMPLEMENTO -> ");
    fgets(list->contato[pos].endereco.complemento,49,stdin);
}

//VERIFICA SE TELEFONE É VALIDO
void verificar_celular(int pos, int qual) {
    int digitos = strlen(list->contato[pos].telefones[qual].telefone);
    if (digitos < 8 || digitos > 14) {
        printf("É NECESSARIO UM NUMERO VALIDO, DIGITE NOVAMENTE -> ");
        scanf("%s", list->contato[pos].telefones[qual].telefone);
        verificar_celular(pos, qual);
    }
}

//INSERÇÃO DE DADOS
void inserir() {
    int op;

    if (list->cont <= list->limite-1) {
        printf("======================================\n");
        printf("ADICIONAR CONTATO\n");
        printf("======================================\n");
        printf("PRIMEIRO NOME -> ");
        scanf("%s", list->contato[list->cont].primeiro_nome);
        verificar(1, list->cont);

        printf("ULTIMO NOME -> ");
        scanf("%s", list->contato[list->cont].ultimo_nome);
        verificar(2, list->cont);

        printf("TELEFONE PRIMARIO -> ");
        scanf("%s", list->contato[list->cont].telefones[0].telefone);
        verificar_celular(list->cont, 0);
        printf("TIPO DO TELEFONE -> ");
        scanf("%s", list->contato[list->cont].telefones[0].tipo_telefone);

        printf("DESEJA ADICIONAR MAIS NUMEROS?\n");
        printf("0 ->  NAO\n");
        printf("1 ->  SIM\n");
        scanf("%d", &op);

        if (op) {
            printf("QUANTOS NUMEROS DESEJA? (MAXIMO 4)\n");
            scanf("%d", &op);
            if (op > 4 || op <= 0)
                printf("OPCAO INVALIDA");
            else {
                list->contato[list->cont].quantidade_telefones = op+1;
                for (int i = 1; i < op+1; i++) {
                    printf("TELEFONE -> ");
                    scanf("%s", list->contato[list->cont].telefones[i].telefone);
                    verificar_celular(list->cont, i);
                    printf("TIPO DO TELEFONE -> ");
                    scanf("%s", list->contato[list->cont].telefones[i].tipo_telefone);
                }
            }

        }
        

        printf("EMAIL -> ");
        scanf("%s", list->contato[list->cont].email);
        verificar(4, list->cont);

        printf("ANIVERSARIO (ex:20040814) -> ");
        scanf("%s", list->contato[list->cont].aniversario);
        verificar(5, list->cont);

        printf("DESEJA ADICIONAR ENDERECO?\n");
        printf("0 ->  NAO\n");
        printf("1 ->  SIM\n");
        scanf("%d", &op);

        //FUNÇÃO COM FGETS PARA ADICIONAR ENDEREÇO
        if (op)
            adicionar_endereco(list->cont);

        //PADRÃO DO FGETS COM \n NO FINAL, PARA FUNCIONAR SEM PROBLEMAS NO LISTAR!
        else {
            int pos = list->cont;
            list->contato[pos].endereco.numero[0] = '\n';
            list->contato[pos].endereco.rua[0] = '\n';
            list->contato[pos].endereco.bairro[0] = '\n';
            list->contato[pos].endereco.cidade[0] = '\n';
            list->contato[pos].endereco.estado[0] = '\n';
            list->contato[pos].endereco.complemento[0] = '\n';

        }

        //AUMENTAR CONTADOR
        list->cont++;

        system("clear||cls");
        printf("======================================\n");
        printf("AVISO: CONTATO ADICIONADO COM SUCESSO!\n");

    }
    else {
        printf("======================================\n");
        printf("ERRO: AGENDA CHEIA - SALVE E REINICIE PARA MAIS ESPACO");
    }
}



void pesquisar() {
    if (lista_vazia() == 0) {

        int op3, qtd = 0;
        char pesquisa[50];

        //INTERFACE
        printf("======================================\n");
        printf("PESQUISAR\n");
        printf("======================================\n");
        printf("COMO DESEJA PESQUISAR?\n");
        printf("0 ->  POR PRIMEIRO NOME\n");
        printf("1 ->  POR NASCIMENTO\n");
        scanf("%d", &op3);

        //PESQUISA POR ANIVERSARIO
        if (op3) {

            printf("Aniversario -> ");
            scanf("%s", pesquisa);
            system("clear||cls");
            printf("======================================\n");
            printf("PESQUISAS ENCONTRADAS:\n");
            ordernar(0);
            for (int i = 0; i < list->cont; i++) {
                if (strcmp(list->contato[i].aniversario, pesquisa) == 0) {
                    escrever_contato(i);
                    qtd++;
                }
            }
        }

        //PESQUISA POR NOME
        else {
            printf("Primeiro Nome -> ");
            scanf("%s", pesquisa);
            system("clear||cls");
            printf("======================================\n");
            printf("PESQUISAS ENCONTRADAS:\n");
            ordernar(1);
            for (int i = 0; i < list->cont; i++) {
                if (strcmp(list->contato[i].primeiro_nome, pesquisa) == 0) {
                    escrever_contato(i);
                    qtd++;
                }
            }

        }

        if (qtd == 0) {
            printf("SEM RESULTADOS!\n");
        }
        
    }
}



void listar() {
    if (lista_vazia() == 0) {

        printf("======================================\n");
        printf("LISTANDO %d CONTATOS\n", list->cont);

        //ORDERNA ANTES DE LISTAR POR ORDEM ALFABETICA
        ordernar(1);

        for (int i = 0; i < list->cont; i++) {
            escrever_contato(i);
        }
    }
}



int verificar_pos(int pos) {

    if (pos < 0 || pos > list->cont-1) {

        printf("Posicao invalida, digite outra");
        printf("Posicao -> ");

        scanf("%d", &pos);

        verificar_pos(pos);
    }
    return pos;
}



void mudar() {
    if (lista_vazia() == 0) {

        //MENU DE ESCLHAS
        int lis, pos, op2;

        printf("Deseja listar os contados antes de prosseguir?\n");
        printf("0 ->  NAO\n");
        printf("1 ->  SIM\n");
        scanf("%d", &lis);

        if (lis)
            listar();

        printf("======================================\n");
        printf("MUDAR\n");
        printf("======================================\n");
        printf("Em qual posicao esta o contato que você quer mudar?\n");
        printf("Posicao -> ");

        scanf("%d", &pos);
        pos = verificar_pos(pos);

        printf("Oque voce quer mudar?\n");
        printf("1 ->  PRIMEIRO NOME\n");
        printf("2 ->  ULTIMO NOME\n");
        printf("3 ->  CELULARES\n");
        printf("4 ->  EMAIL\n");
        printf("5 ->  ANIVERSARIO\n");
        printf("6 ->  ENDERECO\n");
        printf("Escolha -> ");

        scanf("%d", &op2);

        //MUDANÇA E VERIFICAÇÃO PARA UM PADRÃO DE DADOS

        if (op2 == 1) {
            printf("PRIMEIRO NOME -> ");
            scanf("%s", list->contato[pos].primeiro_nome);
            verificar(1, pos);
        }

        if (op2 == 2) {
            printf("ULTIMO NOME -> ");
            scanf("%s", list->contato[pos].ultimo_nome);
            verificar(2, pos);
        }

        if (op2 == 3) {
            printf("CELULARES\n");
            printf("QUAL DELES DESEJA MUDAR?\n");
            printf("0 -> %s\n", list->contato[pos].telefones[0].telefone);
            printf("1 -> %s\n", list->contato[pos].telefones[1].telefone);
            printf("2 -> %s\n", list->contato[pos].telefones[2].telefone);
            printf("3 -> %s\n", list->contato[pos].telefones[3].telefone);
            printf("4 -> %s\n", list->contato[pos].telefones[4].telefone);
            printf("Escolha -> ");
            scanf("%d", &op2);
            printf("Telefone -> ");
            scanf("%s", list->contato[pos].telefones[op2].telefone);
            verificar_celular(pos,op2);
            printf("Tipo -> ");
            scanf("%s", list->contato[pos].telefones[op2].tipo_telefone);
        }

        if (op2 == 4) {
            printf("EMAIL -> ");
            scanf("%s", list->contato[pos].email);
            verificar(4, pos);
        }

        if (op2 == 5) {
            printf("ANIVERSARIO -> ");
            scanf("%s", list->contato[pos].aniversario);
            verificar(5, pos);
        }

        if (op2 == 6) {
            adicionar_endereco(pos);
        }

        system("clear||cls");
        printf("======================================\n");
        printf("AVISO: INFORMACAO ALTERADA COM SUCESSO!\n");
    }
}


\
void remover() {
    if (lista_vazia() == 0) {

        int lis, pos;

        printf("Deseja listar os contados antes de prosseguir?\n");
        printf("0 ->  NAO\n");
        printf("1 ->  SIM\n");
        scanf("%d", &lis);

        if (lis)
            listar();

        printf("======================================\n");
        printf("REMOVER\n");
        printf("======================================\n");
        printf("Em qual posicao esta o contato que você quer remover?\n");
        printf("Posicao -> ");

        scanf("%d", &pos);
        pos = verificar_pos(pos);

        for (int i = pos; i < list->cont-1; i++) {
            
            memcpy(&list->contato[i], &list->contato[i+1], sizeof(Contatos));

        }

        list->cont--;

        system("clear||cls");
        printf("======================================\n");
        printf("AVISO: CONTATO REMOVIDO COM SUCESSO!\n");
    }
}



void salvar() {
    
    if (list->cont == 0) {
        int op;

        printf("A lista esta vazia, deseja salvar assim mesmo?\n");
        printf("0 ->  NAO\n");
        printf("1 ->  SIM\n");
        scanf("%d", &op);
        system("clear||cls");
        if (op == 0) {
            return;
        }
    }

    //APAGAR ARQUIVO ANTERIOR E DEFINIR PARA GRAVAR NO FIM DO NOVO COM AB
    remove("contatos.bin");
    remove("agenda.bin");

    FILE *contatos = fopen("contatos.bin","ab");
    FILE *agenda = fopen("agenda.bin","ab");
    system("clear||cls");
    printf("======================================\n");

    //SE OS DOIS ESTIVEREM DEFINIDOS E CRIADOS
    if (contatos != NULL || agenda != NULL) {

        //GRAVA CONTADOR
        fwrite(&list->cont, sizeof(list->cont), 1, agenda);

        //GRAVA PESSOAS
        for (int i = 0; i < list->cont; i++) {
            fwrite(&list->contato[i], sizeof(Contatos), 1, contatos);
        }

        //fecha arquivo
        fclose(contatos);
        fclose(agenda);

        printf("AVISO: GRAVADO COM SUCESSO\n");
    }

    else {
        printf("AVISO: ERRO AO GRAVAR\n");
    }
}




void ler_criar()
{
	//ABRE O ARQUIVO PARA LEITURA
	FILE *contatos = fopen("contatos.bin", "rb");
    FILE *agenda = fopen("agenda.bin", "rb");

    //SE OS ARQUIVOS EXISTEIREM
	if (agenda != NULL || contatos != NULL) {

        //LER CONTADOR E CRIAR AGENDA COM CONT+10 DE LIMITE
        int cont;
        fread(&cont, sizeof(int), 1, agenda);
        list = criar_Agenda(cont);

         
        //CRIA AUXILIAr, GRAVA NELE E PASSA PARA AGENDA CRIADA NO LIST
		Contatos aux;
        for (int i = 0; i < list->cont; i++) {

            fread(&aux, sizeof(Contatos), 1, contatos);
            list->contato[i] = aux;
            
		}

        //fecha
        fclose(contatos);
        fclose(agenda);

        if (list->cont == 0);
        else {
            printf("======================================\n");
            printf("AVISO: A SESSAO ANTERIOR FOI CARREGADA!\n");
        }
	}

    //SENÃO CRIA UMA AGENDA NOVA COM CAPACIDADE INICIAL = 10;
	else {
        list = criar_Agenda(0);
	}

    
}



int main() {

    ler_criar();

    int escolha = 0;
    
    do {
        printf("======================================\n");
        printf("AGENDA DE CONTATOS\n");
        printf("======================================\n");
        printf("1 -> Adcionar Contato\n");
        printf("2 -> Pesquisar\n");
        printf("3 -> Listar\n");
        printf("4 -> Mudar\n");
        printf("5 -> Remover\n");
        printf("6 -> Salvar\n");
        printf("7 -> Sair\n");
        printf("Escolha -> ");
        scanf("%d", &escolha);
        printf("\n\n");
        fflush(stdin);
        system("clear||cls");

        switch (escolha) {

        case 1:
            inserir();break;
        case 2:
            pesquisar();break;
        case 3:
            listar();break;
        case 4:
            mudar();break;
        case 5:
            remover();break;
        case 6:
            salvar();break;
        case 7:
            printf("Obrigado por usar!");break;
        default:
            printf("Invalido");break;

    }

    } while (escolha != 7);
    return 0;
}