#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do nó da árvore
typedef struct BookNode {
    int id;
    char title[100];
    struct BookNode* left;
    struct BookNode* right;
} BookNode;

// Função para criar um novo nó de livro
BookNode* createBookNode(int id, const char* title) {
    BookNode* newBook = (BookNode*)malloc(sizeof(BookNode));
    newBook->id = id;
    strcpy(newBook->title, title);
    newBook->left = NULL;
    newBook->right = NULL;
    return newBook;
}

// Função para inserir um livro na árvore
BookNode* insertBookNode(BookNode* node, int id, const char* title) {
    if (node == NULL) {
        return createBookNode(id, title);
    }

    if (id < node->id) {
        node->left = insertBookNode(node->left, id, title);
    } else {
        node->right = insertBookNode(node->right, id, title);
    }

    return node;
}

// Função para encontrar o sucessor in-order (o menor nó na subárvore à direita)
BookNode* findMin(BookNode* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

// Função para remover um livro da árvore
BookNode* removeBookNode(BookNode* root, int id) {
    if (root == NULL) {
        return NULL;
    }

    // Procurando o nó a ser removido
    if (id < root->id) {
        root->left = removeBookNode(root->left, id);
    } else if (id > root->id) {
        root->right = removeBookNode(root->right, id);
    } else {
        // Caso 1: O nó é uma folha (sem filhos)
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        // Caso 2: O nó tem apenas um filho
        else if (root->left == NULL) {
            BookNode* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            BookNode* temp = root->left;
            free(root);
            return temp;
        }
        // Caso 3: O nó tem dois filhos
        else {
            BookNode* temp = findMin(root->right);  // Encontra o sucessor in-order
            root->id = temp->id;                    // Substitui o ID pelo do sucessor
            strcpy(root->title, temp->title);       // Substitui o título
            root->right = removeBookNode(root->right, temp->id);  // Remove o sucessor
        }
    }

    return root;
}

// Função para buscar um livro pelo ID
BookNode* searchBookNode(BookNode* node, int id) {
    if (node == NULL || node->id == id) {
        return node; // Retorna o nó se for encontrado ou NULL se não for
    }

    if (id < node->id) {
        return searchBookNode(node->left, id);
    } else {
        return searchBookNode(node->right, id);
    }
}

// Função para listar livros em ordem (in-order traversal)
void listBooks(BookNode* node) {
    if (node != NULL) {
        listBooks(node->left);
        printf("ID: %d, Título: %s\n", node->id, node->title);
        listBooks(node->right);
    }
}

// Função principal
int main() {
    BookNode* root = NULL;

    // Adicionando livros à árvore
    root = insertBookNode(root, 50, "JavaScript Essentials");
    root = insertBookNode(root, 30, "Learn Python");
    root = insertBookNode(root, 70, "Data Structures in C++");
    root = insertBookNode(root, 20, "HTML & CSS Design");
    root = insertBookNode(root, 40, "Node.js Guide");
    root = insertBookNode(root, 60, "Algorithms with Java");
    root = insertBookNode(root, 80, "Database Systems");

    // Listando os livros em ordem de ID
    printf("Lista de Livros em Ordem de ID:\n");
    listBooks(root);

    // Removendo um livro
    printf("\nRemovendo o livro com ID 40...\n");
    root = removeBookNode(root, 40);

    // Listando os livros após a remoção
    printf("\nLista de Livros após remoção:\n");
    listBooks(root);

    // Buscando um livro específico
    int searchId = 40;
    BookNode* foundBook = searchBookNode(root, searchId);
    if (foundBook) {
        printf("\nLivro encontrado: ID: %d, Título: %s\n", foundBook->id, foundBook->title);
    } else {
        printf("\nLivro não encontrado.\n");
    }

    return 0;
}
