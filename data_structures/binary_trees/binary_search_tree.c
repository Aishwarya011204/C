/**
 * @file
 * @brief A basic unbalanced binary search tree implementation in C.
 * @details The implementation has the following functionalities implemented:
 * - Insertion
 * - Deletion
 * - Search by key value
 * - Listing of node keys in order of value (from left to right)
 */
#include <stdio.h>
#include <stdlib.h>

/** Node, the basic data structure in the tree */
typedef struct node
{
    struct node *left;  /**< left child */
    struct node *right; /**< right child */
    int data;           /**< data of the node */
} node;

/** The node constructor, which receives the key value input and returns a node
 * pointer
 * @param data data to store in a new node
 * @returns new node with the provided data
 * @note the node must be deleted before program terminates to avoid memory
 * leaks
 */
node *newNode(int data)
{
    node *tmp = (node *)malloc(sizeof(node));
    tmp->data = data;
    tmp->left = NULL;
    tmp->right = NULL;
    return tmp;
}

/** Insertion procedure, which inserts the input key in a new node in the tree
 * @param root pointer to parent node
 * @param data value to store in the new node
 * @returns pointer to parent node
 */
node *insert(node *root, int data)
{
    if (root == NULL)
    {
        root = newNode(data);
    }
    else if (data > root->data)
    {
        root->right = insert(root->right, data);
    }
    else if (data < root->data)
    {
        root->left = insert(root->left, data);
    }
    return root;
}

/** Utilitary procedure to find the greatest key in the left subtree
 * @param root pointer to parent node
 * @returns pointer to parent node
 */
node *getMax(node *root)
{
    if (root->right != NULL)
    {
        return getMax(root->right);
    }
    return root;
}

/** Deletion procedure, which searches for the input key in the tree and removes
 * it if present
 * @param root pointer to parent node
 * @param data value to search for int the node
 * @returns pointer to parent node
 */
node *delete(node *root, int data)
{
    if (root == NULL)
    {
        return root;
    }
    else if (data > root->data)
    {
        root->right = delete(root->right, data);
    }
    else if (data < root->data)
    {
        root->left = delete(root->left, data);
    }
    else if (data == root->data)
    {
        if ((root->left == NULL) && (root->right == NULL))
        {
            free(root);
            return NULL;
        }
        else if (root->left == NULL)
        {
            node *tmp = root;
            root = root->right;
            free(tmp);
            return root;
        }
        else if (root->right == NULL)
        {
            node *tmp = root;
            root = root->left;
            free(tmp);
            return root;
        }
        else
        {
            node *tmp = getMax(root->left);
            root->data = tmp->data;
            root->left = delete(root->left, tmp->data);
        }
    }
    return root;
}

/** Search procedure, which looks for the input key in the tree and returns 1 if
 * it's present or 0 if it's not in the tree
 * @param root pointer to parent node
 * @param data value to store int the new node
 * @returns 0 if value not found in the nodes
 * @returns 1 if value was found
 */
int find(node *root, int data)
{
    if (root == NULL)
    {
        return 0;
    }
    else if (data > root->data)
    {
        return find(root->right, data);
    }
    else if (data < root->data)
    {
        return find(root->left, data);
    }
    else if (data == root->data)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/** Utilitary procedure to measure the height of the binary tree
 * @param root pointer to parent node
 * @returns height of nodes to get to data from parent node
 */
int height(node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        int right_h = height(root->right);
        int left_h = height(root->left);
        return (right_h > left_h) ? (right_h + 1) : (left_h + 1);
    }
}

/** Utilitary procedure to free all nodes in a tree
 * @param root pointer to parent node
 */
void purge(node *root)
{
    if (root != NULL)
    {
        purge(root->left);
        purge(root->right);
        free(root);
    }
}

/** Traversal procedure to list the current keys in the tree in order of value
 * (from the left to the right)
 * @param root pointer to parent node
 */
void inOrder(node *root)
{
    if (root != NULL)
    {
        inOrder(root->left);
        printf("\t[ %d ]\t", root->data);
        inOrder(root->right);
    }
}

/** Helper function to print the tree in a structured way
 * @param root pointer to the current node
 * @param space number of spaces to use for indentation
 */
void printTreeHelper(node *root, int space)
{
    if (root == NULL)
        return;

    space += 10;

    printTreeHelper(root->right, space);

    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%d\n", root->data);

    printTreeHelper(root->left, space);
}

/** Function to print the binary tree
 * @param root pointer to the root node of the tree
 */
void printTree(node *root)
{
    if (root == NULL)
    {
        printf("Tree is empty!\n");
        return;
    }
    printTreeHelper(root, 0);
}

/** Main function */
int main()
{
    node *root = NULL;
    int opt = -1;
    int data = 0;

    while (opt != 0)
    {
        printf(
            "\n\n[1] Insert Node\n[2] Delete Node\n[3] Find a Node\n[4] Get "
            "current Height\n[5] Print Tree in Crescent Order\n[6] Print Tree\n[0] Quit\n");
        scanf("%d", &opt);

        switch (opt)
        {
        case 1:
            printf("Enter the new node's value:\n");
            scanf("%d", &data);
            root = insert(root, data);
            break;

        case 2:
            printf("Enter the value to be removed:\n");
            if (root != NULL)
            {
                scanf("%d", &data);
                root = delete(root, data);
            }
            else
            {
                printf("Tree is already empty!\n");
            }
            break;

        case 3:
            printf("Enter the searched value:\n");
            scanf("%d", &data);
            find(root, data) ? printf("The value is in the tree.\n")
                             : printf("The value is not in the tree.\n");
            break;

        case 4:
            printf("Current height of the tree is: %d\n", height(root));
            break;

        case 5:
            inOrder(root);
            break;

        case 6:
            printTree(root);
            break;
        }
    }

    purge(root);

    return 0;
}
