#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct Node {
    int data;
    struct Node *left, *right;
};

struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    if (node == NULL) {
        printf("Error: Gagal alokasi memori untuk node baru.\n");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

struct Node* insert(struct Node* root, int data) {
    if (root == NULL)
        return newNode(data);
    
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
        
    return root;
}

int maxDepth(struct Node* node) {
    if (node == NULL)
        return -1;
    else {
        int lDepth = maxDepth(node->left);
        int rDepth = maxDepth(node->right);

        if (lDepth > rDepth)
            return (lDepth + 1);
        else
            return (rDepth + 1);
    }
}

void printTree(struct Node* root) {
    if (root == NULL) return;

    char char_ul = 218;
    char char_ur = 191;
    char char_horizontal = 196; 
    
    int depth = maxDepth(root);
    
    if (depth == 0) { 
        printf("%d\n", root->data);
    } 
    else if (depth == 1) { 
        if (root->left == NULL && root->right != NULL) { 
            printf("%d%c\n", root->data, char_ur);
            printf("  %d\n", root->right->data);
        } 
        else if (root->left != NULL && root->right == NULL) { 
            printf("%c%d\n", char_ul, root->data);
            printf("%d\n", root->left->data);
        } 
        else {
            printf("%c%d%c\n", char_ul, root->data, char_ur);
            printf("%d %d\n", root->left->data, root->right->data);
        }
    }
    else if (depth == 2) {
        int leftHasTwoChildren = (root->left != NULL && 
                                  root->left->left != NULL && 
                                  root->left->right != NULL);
        
        if (leftHasTwoChildren) {
            printf("   %c%c%c%c%d%c\n", 
                   char_ul, char_horizontal, char_horizontal, char_horizontal, 
                   root->data, char_ur);
            printf("%c%d%c     %d\n", 
                   char_ul, root->left->data, char_ur, root->right->data);
            printf("%d %d\n", 
                   root->left->left->data, root->left->right->data);
        }
        else if (root->left != NULL && root->left->left != NULL && root->right != NULL) {
            printf("   %c%d%c\n", char_ul, root->data, char_ur);
            printf("%c%d   %d\n", char_ul, root->left->data, root->right->data);
            printf("%d\n", root->left->left->data);
        }
        else if (root->left == NULL && root->right != NULL && root->right->right != NULL) {
            printf("%d%c\n", root->data, char_ur);
            printf("  %d%c\n", root->right->data, char_ur);
            printf("    %d\n", root->right->right->data);
        }
        else if (root->left != NULL && root->right != NULL) {
            printf("%c%d%c\n", char_ul, root->data, char_ur);
            printf("%d  %d\n", root->left->data, root->right->data);
        }
    }
}

int main() {
    struct Node* root = NULL;
    int angka;
    char lagi;
    int depth = 0;

    do {
        printf("\nMasukan angka bulat: ");
        scanf("%d%*c", &angka);

        root = insert(root, angka);
        depth = maxDepth(root);

        printf("\nSusunan Binary Tree (Depth: %d)\n", depth);
        printTree(root);

        printf("\nMasih ada masukan? Y/T ");
        scanf("%c%*c", &lagi); 
        
    } while (lagi == 'Y' || lagi == 'y');

    return 0;
}