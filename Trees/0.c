#include <stdio.h>
#include <stdlib.h>

// Define a structure for a node in the tree
typedef struct TreeNode {
    int Data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Define a structure for the binary tree
typedef struct BinaryTree {
    TreeNode* root;
} BinaryTree;

// Create a new tree node with given data
TreeNode* create_tree_node(int data) {
    TreeNode* new_node = (TreeNode*) malloc(sizeof(TreeNode));
    if (new_node == NULL) {
        printf("Memory not available!\n");
        exit(1);
    }
    new_node->Data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Insert a node into the binary search tree
TreeNode* insert_node(TreeNode* root, int data) {
    if (root == NULL) {
        return create_tree_node(data);
    }
    if (data < root->Data) {
        root->left = insert_node(root->left, data); // Insert into left subtree
    } else if (data > root->Data) {
        root->right = insert_node(root->right, data); // Insert into right subtree
    }
    return root;
}

// Get the depth of a node (distance from root)
int get_node_depth(TreeNode* root, int val) {
    if (root == NULL) {
        return -1;
    }
    if (root->Data == val) {
        return 0;
    }
    if (val < root->Data) {
        return 1 + get_node_depth(root->left, val);
    } else {
        return 1 + get_node_depth(root->right, val);
    }
}

// Find a node with a specific value
TreeNode* find_node(TreeNode* root, int val) {
    if (root == NULL) {
        return NULL;
    }
    if (root->Data == val) {
        return root;
    }
    TreeNode* left_search = find_node(root->left, val);
    if (left_search != NULL) {
        return left_search;
    } else {
    return find_node(root->right, val);
    }
}

// Get the height of a node (longest path to a leaf)
int get_node_height(TreeNode* node) {
    if (node == NULL) {
        return -1;
    }
    int left_height = get_node_height(node->left);
    int right_height = get_node_height(node->right);
    return 1 + (left_height > right_height ? left_height : right_height);
}

// Get the level of a node (depth + 1)
int get_node_level(TreeNode* root, int val) {
    return get_node_depth(root, val) + 1;
}

// Find the sibling of a node with a given value
TreeNode* get_node_sibling(TreeNode* root, int val) {
    if (root == NULL || (root->left == NULL && root->right == NULL)) {
        return NULL;
    }

    if (root->left != NULL && root->right != NULL) {
        if (root->left->Data == val) {
            return root->right;
        }
        if (root->right->Data == val) {
            return root->left;
        }
    }

    TreeNode* left_search = get_node_sibling(root->left, val);
    if (left_search != NULL) {
        return left_search;
    }
    return get_node_sibling(root->right, val);
}

// In-order traversal: left -> root -> right
int in_order_traversal(TreeNode* root) {
    if (root != NULL) {
        in_order_traversal(root->left);
        printf("%d ", root->Data); // Print the node value
        in_order_traversal(root->right);
    }
    return 0;
}
int pre_traversal(TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->Data); // Print the node value
        in_order_traversal(root->left);
        in_order_traversal(root->right);
    }
    return 0;
}
int post_traversal(TreeNode* root) {
    if (root != NULL) {
        in_order_traversal(root->left);
        in_order_traversal(root->right);
        printf("%d ", root->Data); // Print the node value
    }
    return 0;
}

// Template for any-order traversal (used for teaching)
int any_order_traversal(TreeNode* root) {
    if (root != NULL) {
        // Pre-order action could be here
        any_order_traversal(root->left);
        // In-order action could be here
        any_order_traversal(root->right);
        // Post-order action could be here
    }
    return 0;
}

// Main function
int main() {
    BinaryTree tree;
    tree.root = NULL;

    // Insert nodes into the binary search tree
    tree.root = insert_node(tree.root, 8);
    tree.root = insert_node(tree.root, 3);
    tree.root = insert_node(tree.root, 10);
    tree.root = insert_node(tree.root, 1);
    tree.root = insert_node(tree.root, 6);
    tree.root = insert_node(tree.root, 14);
    tree.root = insert_node(tree.root, 4);
    tree.root = insert_node(tree.root, 7);
    tree.root = insert_node(tree.root, 13);

    // Display in-order traversal
    printf("In-order traversal of the binary tree:\n");
    in_order_traversal(tree.root);
    printf("\n");

    // Check information for a specific node
    int value = 8;
    TreeNode* node = find_node(tree.root, value);
    if (node) {
        printf("Height of %d is %d\n", value, get_node_height(node));

        TreeNode* sibling = get_node_sibling(tree.root, value);
        if (sibling) {
            printf("Sibling of %d is %d\n", value, sibling->Data);
        } else {
            printf("No sibling found for %d\n", value);
        }

        printf("Depth of %d is %d\n", value, get_node_depth(tree.root, value));
        printf("Level of %d is %d\n", value, get_node_level(tree.root, value));
    } else {
        printf("Node %d not found in the tree.\n", value);
    }

    return 0;
}
