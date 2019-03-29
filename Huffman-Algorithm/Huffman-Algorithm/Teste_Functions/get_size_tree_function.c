void get_size_tree(NODE node, int *size, Byte *TreeString)
{
	if(node == NULL)
	{
		return;
	}
    TreeString[*size] = node->symbol; // Atribui cada caractere à posição size do array
	if((TreeString[(*size)] == '*' || TreeString[(*size)] == '\\') && is_leaf(node))
	{
		Byte aux;
		aux = TreeString[*size];
		TreeString[*size] = '\\';
		TreeString[++(*size)] = aux; 
	}
	++(*size); // somando o tamanho da árvore
	get_size_tree(node->left, size,TreeString);
	get_size_tree(node->right, size, TreeString);
}
