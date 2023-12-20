﻿#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Struktura èvora binarnog stabla
struct _node;
typedef struct _node* Position;
typedef struct _node {
    int value;
    Position left;
    Position right;
} Node;

Position createNode(int value);
Position insert(Position root, int value);
int inorder(Position root);
int preorder(Position root);
int postorder(Position root);
Position search(Position root, int value);
int replace(Position root);
int random();

int main() {
    Position root = NULL;
    Position rootRand = NULL;
    srand(time(0));

    /*int rootValue = 0;
    printf("\033[0;32mEnter root value: \033[0m");
    scanf("%d", &rootValue);
    root = insert(root, rootValue);*/

    root = insert(root, 2);
    insert(root, 5);
    insert(root, 7);
    insert(root, 8);
    insert(root, 11);
    insert(root, 1);
    insert(root, 4);
    insert(root, 2);
    insert(root, 3);
    insert(root, 7);

   


    while (1) {
        printf("\nMenu:\n");
        printf("1 - Insert node\n");
        printf("2 - Search node\n");
        printf("3 - Print postorder\n");
        printf("4 - Print preorder\n");
        printf("5 - Print inorder\n");
        printf("6 - exit\n");

        char choice[10] = { 0 };
        printf("Enter your choice: ");
        scanf("%s", choice);

        if (strcmp(choice, "1") == 0) {
            int value = 0;
            printf("\033[0;32mEnter value: \033[0m");
            scanf("%d", &value);
            insert(root, value);
        }
        else if (strcmp(choice, "2") == 0) {
            int value = 0;
            Position result = NULL;
            printf("\033[0;32mEnter value: \033[0m");
            scanf("%d", &value);
            result = search(root, value);
            if (result != NULL)
                printf("\033[0;32mNode %d is found.\033[0m\n", value);
            else
                printf("\033[0;32mNode %d is not found.\033[0m\n", value);
        }
        else if (strcmp(choice, "3") == 0) {
            printf("\033[0;32mPostorder: \033[0m");
            postorder(root);
            printf("\n");
        }
        else if (strcmp(choice, "4") == 0) {
            printf("\033[0;32mPreorder: \033[0m");
            preorder(root);
            printf("\n");
        }
        else if (strcmp(choice, "5") == 0) {
            printf("\033[0;32mInorder: \033[0m");
            inorder(root);
            printf("\n");
        }
        

        else if (strcmp(choice, "6") == 0) {
            printf("\033[0;32mExiting the program.\033[0m\n");
            break;
        }
        else {
            printf("\033[0;31mInvalid choice. Please enter a valid option.\033[0m\n");
        }
    }

    return EXIT_SUCCESS;
}

Position createNode(int value) {
    Position newNode = NULL;
    newNode = (Position)malloc(sizeof(Node));
    if (!newNode) {
        printf("Can't allocate memory!\n");
        return NULL;
    }
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Position insert(Position root, int value) {
    if (root == NULL)
        return createNode(value);

    if (value < root->value)
        root->left = insert(root->left, value);
    else if (value >= root->value)
        root->right = insert(root->right, value);

    return root;
}

int inorder(Position root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->value);
        inorder(root->right);
    }
    return EXIT_SUCCESS;
}

int preorder(Position root) {
    if (root) {
        printf("%d ", root->value);
        preorder(root->left);
        preorder(root->right);
    }
    return EXIT_SUCCESS;
}

int postorder(Position root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->value);
    }
    return EXIT_SUCCESS;
}

Position search(Position root, int value) {
    if (root == NULL || root->value == value)
        return root;

    if (value < root->value)
        return search(root->left, value);

    return search(root->right, value);
}

int replace(Position root) {
    if (root == NULL) {
        return 0;
    }

    // Recursively update left and right subtrees first
    int leftValue = replace(root->left);
    int rightValue = replace(root->right);

    // Store the original value
    int originalValue = root->value;

    // Update the value of the current node to be the sum of its children
    root->value = leftValue + rightValue;

    // Return the sum of the node's value and the sum of its children
    return originalValue + root->value;
}
