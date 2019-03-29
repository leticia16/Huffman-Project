#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef long long int LLI;

typedef struct list{
    LLI item;
    struct list *next;
}Head;

typedef Head* LIST;

typedef struct tree{
    LLI value;
    struct tree *left;
    struct tree *right;
}Tree;

typedef Tree* TREE;

typedef unsigned int U_int;

LIST create_empty_list()
{
    LIST new_list = (LIST) malloc(sizeof(LIST));
    new_list -> item = 0;
    new_list -> next = NULL;
    return new_list;
}

TREE create_empty_tree()
{
    return NULL;
}

LIST createList(LLI item)
{
    LIST new_list = (LIST) malloc(sizeof(Head));
    new_list -> item = item;
    new_list -> next = NULL;
    return new_list;
}

LIST add_list(LIST h, LLI item)
{
    if(h == NULL)
    {
        return createList(item);
    }
    h -> next = add_list(h -> next, item);
    return h;
}

TREE createTree(LLI value, TREE right, TREE left)
{
    TREE new_tree = (TREE) malloc(sizeof(Tree));
    new_tree -> value = value;
    new_tree -> right = right;
    new_tree -> left = left;
    return new_tree;
}

TREE add_tree(TREE t, LLI item)
{

    if(t == NULL) return createTree(item,NULL, NULL);
    if(item < t -> value)
    {
        t -> left = add_tree(t -> left, item);
    }
    else
    {
        t -> right = add_tree(t -> right, item);
    }
    return t;
}

int searchTree(TREE t, LLI value[], int i, LLI *number_of_comparisons)
{

    if(t == NULL) return -1;
    (*number_of_comparisons)+=1;
    if(t->value == value[i])
    {

        return *number_of_comparisons;
    }
    else
    {
        if(value[i] < t -> value)
        {
            // (*number_of_comparisons)+=1;
            return searchTree(t -> left, value,i+1,number_of_comparisons);
        }
        else
        {
            // (*number_of_comparisons)+=1;
            return searchTree(t -> right, value,i+1,number_of_comparisons);
        }
      }
}

int searchList(LIST list, LLI item[],LLI i, LLI *number_of_comparisons_list)
{
    while (list != NULL)
    {
        (*number_of_comparisons_list) += 1;
        if(list -> item == item[i])
        {
          return *number_of_comparisons_list;
        }
        list = list -> next;
    }
}

LIST add_numbers_to_the_list(LIST list,LLI size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        list = add_list(list,i);
    }
    return list;
}

TREE add_numbers_to_the_tree(TREE tree, LLI size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        tree = add_tree(tree,i);
    }
    return tree;
}

void generate_random(LLI size, LLI random_numbers[])
{
    srand((unsigned) time(NULL));
    int i;
    for (i = 0; i < size; i++)
    {
        random_numbers[i] = rand() % size;
    }
}

void order_abb_numbers(LLI size, LLI numbers[])
{
    LLI i,j;
    LLI aux;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size - 1; j++)
        {
            if(numbers[j] > numbers[j + 1])
            {
                aux = numbers[j];
                numbers[j] = numbers[j+1];
                numbers[j+1] = aux;
            }
        }
    }
}

void order_list_numbers(LLI size, LLI numbers[])
{
    LLI i,j;
    LLI aux;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size - 1; j++)
        {
            if(numbers[j] > numbers[j + 1])
            {
                aux = numbers[j];
                numbers[j] = numbers[j+1];
                numbers[j+1] = aux;
            }
        }
    }
}

int main()
{
    LLI size,i, number, quantity, quantity_comparations;
    LLI comparations_list = 0;
    LLI comparations_abb = 0;
    printf("Enter the quantity of the elements to be inserted: \n");
    scanf("%lld",&size);

    LIST list = create_empty_list();
    TREE tree = create_empty_tree();

    FILE *listArchive = fopen("listaArchive.csv","w");
    FILE *treeArchive = fopen("treeArchive.csv","w");

    fprintf(listArchive,"size,list_c\n");
    fprintf(treeArchive,"size,abb\n");

    printf("Add numbers to the list e abb\n");
    list = add_numbers_to_the_list(list, size);
    tree = add_numbers_to_the_tree(tree, size);

    LLI random_numbers[size];
    printf("Searching the numbers\n");
    generate_random(size,random_numbers);

    LLI sort_abb[size], sort_list[size];

    for (i = 1; i <= size; i++)
    {
        searchList(list, random_numbers,i, &comparations_list);
        searchTree(tree, random_numbers, i, &comparations_abb);
        sort_list[i] = comparations_list;
        sort_abb[i] = comparations_abb;

        comparations_list = 0;
        comparations_abb = 0;
    }

    order_abb_numbers(size, sort_abb);
    order_list_numbers(size, sort_list);

    for (i = 0; i < size - 1; i++)
    {
        fprintf(listArchive,"%lld,%lld\n",i, sort_list[i]);
        fprintf(treeArchive, "%lli,%lli\n",i, sort_abb[i]);
    }
    fclose(listArchive);
    fclose(treeArchive);

    return 0;
}
