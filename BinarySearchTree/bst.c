#include <stdio.h>
#include <stdlib.h>

// Node တစ်ခုချင်းစီ၏ ပုံစံကို သတ်မှတ်ခြင်း
struct Node
{
        int data;           // သိမ်းဆည်းမည့် တန်ဖိုး
        struct Node *left;  // ဘယ်ဘက် အခက်သို့ ညွှန်ပြသည့် pointer
        struct Node *right; // ညာဘက် အခက်သို့ ညွှန်ပြသည့် pointer
};

// Node အသစ်တစ်ခု တည်ဆောက်ပေးသည့် function
struct Node *createNode(int value)
{
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node)); // Memory နေရာချခြင်း
        newNode->data = value;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
}

// BST ထဲသို့ node အသစ် ထည့်သွင်းခြင်း (Recursive နည်းလမ်း)
struct Node *create_bst(struct Node *root, int value)
{
        if (root == NULL)
        { // သစ်ပင် အလွတ်ဖြစ်နေလျှင် node အသစ်ကို root လုပ်မည်
                return createNode(value);
        }

        if (value < root->data)
        { // တန်ဖိုးငယ်လျှင် ဘယ်ဘက်သို့သွား
                root->left = create_bst(root->left, value);
        }
        else if (value > root->data)
        { // တန်ဖိုးကြီးလျှင် ညာဘက်သို့သွား
                root->right = create_bst(root->right, value);
        }
        else
        { // တန်ဖိုးတူနေလျှင် ထပ်မထည့်တော့ပါ
                printf("Duplicate value not allowed!\n");
        }

        return root;
}

//

// အစီအစဉ်လိုက် ထုတ်ပြခြင်း (Inorder: ဘယ် -> အလယ် -> ညာ)
void inorderTraversal(struct Node *root)
{
        if (root != NULL)
        {
                inorderTraversal(root->left);
                printf("%d ", root->data);
                inorderTraversal(root->right);
        }
}

// (Preorder: အလယ် -> ဘယ် -> ညာ)
void preorderTraversal(struct Node *root)
{
        if (root != NULL)
        {
                printf("%d ", root->data);
                preorderTraversal(root->left);
                preorderTraversal(root->right);
        }
}

// (Postorder: ဘယ် -> ညာ -> အလယ်)
void postorderTraversal(struct Node *root)
{
        if (root != NULL)
        {
                postorderTraversal(root->left);
                postorderTraversal(root->right);
                printf("%d ", root->data);
        }
}

/* ================= လုပ်ဆောင်ချက် အသစ်များ ================= */

// တန်ဖိုးတစ်ခုကို ရှာဖွေခြင်း
int searchNode(struct Node *root, int value)
{
        if (root == NULL)
                return 0; // မတွေ့ပါက 0 ပြန်ပေး

        if (value == root->data)
                return 1; // တွေ့ပါက 1 ပြန်ပေး
        else if (value < root->data)
                return searchNode(root->left, value);
        else
                return searchNode(root->right, value);
}

// သစ်ပင်၏ အမြင့် (Height) ကို ရှာခြင်း
int findHeight(struct Node *root)
{
        if (root == NULL)
                return -1; // အောက်ဆုံးအဆင့်ရောက်လျှင် -1 ပြန်

        int leftHeight = findHeight(root->left);
        int rightHeight = findHeight(root->right);

        // ဘယ်/ညာ အမြင့်ဆုံးဘက်ကိုယူပြီး 1 ပေါင်းပေးခြင်း
        return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Node အရေအတွက် စုစုပေါင်းကို ရေတွက်ခြင်း
int countNodes(struct Node *root)
{
        if (root == NULL)
                return 0;
        return 1 + countNodes(root->left) + countNodes(root->right);
}

// အငယ်ဆုံးတန်ဖိုးရှိသည့် Node ကိုရှာခြင်း (ဘယ်ဘက်အစွန်ဆုံး)
struct Node *findSmallest(struct Node *root)
{
        if (root == NULL)
                return NULL;
        while (root->left != NULL)
                root = root->left;
        return root;
}

// အကြီးဆုံးတန်ဖိုးရှိသည့် Node ကိုရှာခြင်း (ညာဘက်အစွန်ဆုံး)
struct Node *findLargest(struct Node *root)
{
        if (root == NULL)
                return NULL;
        while (root->right != NULL)
                root = root->right;
        return root;
}

// Node တစ်ခုကို ဖျက်ခြင်း (Deletion)
struct Node *deleteNode(struct Node *root, int value)
{
        if (root == NULL)
                return NULL;

        // ဖျက်မည့် node ကို အရင်ရှာပါ
        if (value < root->data)
        {
                root->left = deleteNode(root->left, value);
        }
        else if (value > root->data)
        {
                root->right = deleteNode(root->right, value);
        }
        else
        {
                // Case 1: Leaf node (အခက်မရှိသော node)
                if (root->left == NULL && root->right == NULL)
                {
                        free(root);
                        return NULL;
                }
                // Case 2: အခက် တစ်ဖက်ပဲ ရှိသော node
                else if (root->left == NULL)
                {
                        struct Node *temp = root->right;
                        free(root);
                        return temp;
                }
                else if (root->right == NULL)
                {
                        struct Node *temp = root->left;
                        free(root);
                        return temp;
                }
                // Case 3: အခက် နှစ်ဖက်လုံး ရှိနေသော node
                else
                {
                        // ညာဘက်ခြမ်းမှ အငယ်ဆုံး node ကို ရှာပြီး အစားထိုးသည်
                        struct Node *temp = findSmallest(root->right);
                        root->data = temp->data;
                        root->right = deleteNode(root->right, temp->data);
                }
        }
        return root;
}

// သစ်ပင်တစ်ခုလုံးကို ဖျက်ပြီး memory ရှင်းထုတ်ခြင်း
struct Node *deleteTree(struct Node *root)
{
        if (root == NULL)
                return NULL;

        deleteTree(root->left);
        deleteTree(root->right);
        free(root);

        return NULL;
}

/* ================= မီနူး စနစ် ================= */

int main()
{
        struct Node *root = NULL;
        int choice, value;

        while (1)
        {
                printf("\n===== Binary Search Tree Menu =====\n");
                printf("1. Insert Node\n2. Inorder Traversal\n3. Preorder Traversal\n4. Postorder Traversal\n");
                printf("5. Search Node\n6. Find Height\n7. Count Nodes\n8. Find Smallest\n9. Find Largest\n");
                printf("10. Delete Node\n11. Delete Entire Tree\n12. Exit\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch (choice)
                {
                case 1:
                        printf("Enter value: ");
                        scanf("%d", &value);
                        root = create_bst(root, value);
                        break;
                case 2:
                        printf("Inorder: ");
                        inorderTraversal(root);
                        printf("\n");
                        break;
                case 3:
                        printf("Preorder: ");
                        preorderTraversal(root);
                        printf("\n");
                        break;
                case 4:
                        printf("Postorder: ");
                        postorderTraversal(root);
                        printf("\n");
                        break;
                case 5:
                        printf("Search: ");
                        scanf("%d", &value);
                        if (searchNode(root, value))
                                printf("Found!\n");
                        else
                                printf("Not found!\n");
                        break;
                case 6:
                        printf("Height: %d\n", findHeight(root));
                        break;
                case 7:
                        printf("Total: %d\n", countNodes(root));
                        break;
                case 8:
                {
                        struct Node *min = findSmallest(root);
                        if (min)
                                printf("Smallest: %d\n", min->data);
                        else
                                printf("Empty.\n");
                        break;
                }
                case 9:
                {
                        struct Node *max = findLargest(root);
                        if (max)
                                printf("Largest: %d\n", max->data);
                        else
                                printf("Empty.\n");
                        break;
                }
                case 10:
                        printf("Delete value: ");
                        scanf("%d", &value);
                        root = deleteNode(root, value);
                        break;
                case 11:
                        root = deleteTree(root);
                        printf("Deleted.\n");
                        break;
                case 12:
                        exit(0);
                default:
                        printf("Invalid choice!\n");
                }
        }
        return 0;
}