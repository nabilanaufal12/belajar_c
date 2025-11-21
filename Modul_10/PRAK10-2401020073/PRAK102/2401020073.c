#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct Node {
    int data;
    struct Node *left, *right;
    int height;
};

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(struct Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    if (node == NULL) {
        printf("Error: Gagal alokasi memori untuk node baru.\n");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

struct Node *rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

struct Node *leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(struct Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct Node* insert(struct Node* node, int data) {
    if (node == NULL)
        return newNode(data);

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
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

    char char_ul = 218;    // ┌
    char char_ur = 191;    // ┐
    char char_horizontal = 196; // ─
    
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
        // Cek apakah ada 2 child di subtree kiri
        int leftHasTwoChildren = (root->left != NULL && 
                                  root->left->left != NULL && 
                                  root->left->right != NULL);
        
        if (leftHasTwoChildren) {
            // Format:    ┌───19┐
            //          ┌17┐     20
            //          1 18
            printf("   %c%c%c%c%d%c\n", 
                   char_ul, char_horizontal, char_horizontal, char_horizontal, 
                   root->data, char_ur);
            printf("%c%d%c     %d\n", 
                   char_ul, root->left->data, char_ur, root->right->data);
            printf("%d %d\n", 
                   root->left->left->data, root->left->right->data);
        }
        else if (root->left != NULL && root->left->left != NULL && root->right != NULL) {
            // Format:    ┌19┐
            //          ┌17   20
            //          1
            printf("   %c%d%c\n", char_ul, root->data, char_ur);
            printf("%c%d   %d\n", char_ul, root->left->data, root->right->data);
            printf("%d\n", root->left->left->data);
        }
        else if (root->left == NULL && root->right != NULL && root->right->right != NULL) {
            // Format: 17┐
            //           19┐
            //             20
            printf("%d%c\n", root->data, char_ur);
            printf("  %d%c\n", root->right->data, char_ur);
            printf("    %d\n", root->right->right->data);
        }
        else if (root->left != NULL && root->right != NULL) {
            // Format sederhana: kedua child ada tapi tidak punya grandchildren
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
        if (scanf("%d", &angka) != 1) {
            printf("Input tidak valid!\n");
            while(getchar() != '\n');
            continue;
        }

        root = insert(root, angka);
        depth = maxDepth(root);

        printf("\nSusunan AVL Tree (Depth: %d)\n", depth);
        printTree(root);

        printf("\nMasih ada masukan? Y/T ");
        scanf(" %c", &lagi);
        
    } while (lagi == 'Y' || lagi == 'y');

    return 0;
}