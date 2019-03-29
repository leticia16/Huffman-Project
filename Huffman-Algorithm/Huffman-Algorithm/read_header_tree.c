
#include <stdio.h>
#include <stdlib.h>


typedef unsigned char Byte;
typedef unsigned short USHORT;

typedef struct h_tree{
    Byte symbol;
    int frequency;
    struct h_tree *left;
    struct h_tree *right;
} Node;

typedef Node* NODE;

NODE create_node(){
    NODE htree = (NODE) malloc(sizeof(Node));
    htree->left = NULL;
    htree->right = NULL;
    htree->frequency = 0;
    return htree;
}

NODE buildTree(NODE root, Byte *tree, int *index, int treeSize)
{
    NODE node = create_node();

    if(tree[*index] == '*')//nó interno
    {
        node -> symbol = '*';
        ++(*index);
        node -> left = buildTree(node,tree,index,treeSize);
        ++(*index);
        node -> right = buildTree(node, tree,index, treeSize);
    }
    else // é folha
    {
        if(tree[*index] == '\\')// se a folha começar com '\' existem duas possibilidades para o próximo char na leitura
        {
            if(tree[++(*index)] == '\\' && (*index)<treeSize) // a folha é do tipo '\\'
            {
                node -> symbol = '\\';
                return node;
            }
            if(tree[++(*index)] == '*' && (*index)<treeSize)// a folha é do tipo '\*'
            {
                node -> symbol = '*';
                return node;
            }
        }
        else if(!(*index)<treeSize){ //Caso não tenha '\' , a folha será qualquer outro caractere
            node -> symbol = tree[*index];
            return node;
        }
    }
}

void preOrder_tree(NODE node)
{
    if(node == NULL)
    {
        return;
    }
    printf("%c",node->symbol);
    preOrder_tree(node->left);
    preOrder_tree(node->right);
}

int is_bit_i_set(USHORT b, int i){
    USHORT mask = 1 << i;
    return mask & b;
}

void print_bits_byte(USHORT b, int go_to_next_line)
{
    int i;
    for(i = 0; i < 16; i++)
    {
        if(is_bit_i_set(b,i))
        {
            printf("%d", 1);
        }
        else
        {
            printf("%d", 0);
        }
    }
    if (go_to_next_line)
    {
        printf("\n");
    }
}
int read_Header(FILE *file, Byte *tree_array, Byte *trash)
{
    USHORT sizeTree = 0;
    Byte first_byte, second_byte,tree_byte;

    first_byte = fgetc(file); // Pega o primeiro Byte do arquivo
    second_byte = fgetc(file); // Pega o segundo Byte do arquivo

    (*trash) = first_byte >> 5; // Shift bit pra esquerda para obter apenas os 3 bits do lixo, ex: 10100000 ~ (>>5) ~ 00000101
    
    first_byte = first_byte << 3; // Shift bit pra esquerda para retirar o lixo, ex: 11000001 ~ 00001000 
    first_byte = first_byte >> 3; // Shift bit pra direita para voltr ao lugar (já sem o lixo): 00001000 ~ 00000001

    sizeTree = first_byte; //atribui o Byte "first_byte" modificado ao USHORT sizeTree
    sizeTree = sizeTree << 8; // Shift bit para a esquerda para deixar as oito primeiro posições livres para o second_byte
    sizeTree |= second_byte; // concatena USHORT com Byte (através do operador "OU")

    // printf("trash = %d sizeTree = %d\n", *trash, sizeTree); // print apenas para teste

    int i;
    for(i = 0; i < sizeTree; i++) // lê a árvore e coloca no array
    {
        tree_byte = fgetc(file);
        tree_array[i] = tree_byte;
    }
    return sizeTree; //retorna o tamanho para ser usado na função BuildTree
}


int main()
{
    int i = 0;

    Byte input[256];  // Array que recebe o nome do arquivo a ser descompactado
    Byte tree_array[256] = {0};  // Array que receberá a arvore lida no cabeçalho
    Byte trash = 0;   // Lixo que será passado como ponteiro para a função de leitura do cabeçalho

    /* scanf("%s", input);  // Ler o nome do arquivo a ser descomprimidio
       FILE *file = fopen(input,"rb");  //Forma Final para ler qualquer arquivo
    */

    FILE *file = fopen("new.txt","rb");  // Para teste com o arquivo test.txt

    int sizeTree = read_Header(file,tree_array,&trash);   // Ler o Cabeçalho e retorna o tamanho da árvore
    NODE root = buildTree(NULL,tree_array,&i,sizeTree); //Montar a árvore e retorna o nó raíz
    // preOrder_tree(root); // Apenas para teste: Printa a árvore em pré ordem 
    puts("");
    fclose(file);
    return 0;
}
