#include <stdio.h>
#include <stdlib.h>

// Node တစ်ခုချင်းစီအတွက် Structure တည်ဆောက်ပါတယ်။
struct Node
{
	int data;	    // Node ထဲမှာ သိမ်းမယ့် ကိန်းဂဏန်း
	struct Node *left;  // ဘယ်ဘက်က Child Node ဆီသွားမယ့် Pointer
	struct Node *right; // ညာဘက်က Child Node ဆီသွားမယ့် Pointer
};

// Node အသစ်တစ်ခု စတင်ဖန်တီးပေးတဲ့ Function ဖြစ်ပါတယ်။
struct Node *createNode(int value)
{
	// Memory အသစ်တောင်းပြီး Node တစ်ခုစာ နေရာယူပါတယ်။
	struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
	newNode->data = value;
	newNode->left = NULL; // အသစ်ဖြစ်လို့ ဘယ်ညာမှာ ဘာမှမရှိသေးပါဘူး။
	newNode->right = NULL;
	return newNode;
}

// Binary Search Tree (BST) ထဲကို Node အသစ်တွေ ထည့်ပေးတဲ့ Function ဖြစ်ပါတယ်။
struct Node *create_bst(struct Node *root, int value)
{
	// Tree က ဘာမှမရှိသေးရင် Node အသစ်ကို Root အနေနဲ့ သတ်မှတ်ပါတယ်။
	if (root == NULL)
	{
		return createNode(value);
	}

	// တန်ဖိုးက Root ထက် ငယ်ရင် ဘယ်ဘက်ခြမ်းကို သွားပါတယ်။
	if (value < root->data)
	{
		root->left = create_bst(root->left, value);
	}
	// တန်ဖိုးက Root ထက် ကြီးရင် ညာဘက်ခြမ်းကို သွားပါတယ်။
	else if (value > root->data)
	{
		root->right = create_bst(root->right, value);
	}
	// တန်ဖိုးတူနေရင်တော့ BST မှာ လက်မခံပါဘူး။
	else
	{
		printf("Duplicate value not allowed!\n");
	} 
	return root;
}

// Inorder Traversal (Left -> Root -> Right)
void inorderTraversal(struct Node *root)
{
	if (root != NULL)
	{
		inorderTraversal(root->left);  // ဘယ်ဘက်ကို အရင်သွားပါတယ်။
		printf("%d ", root->data);     // အလယ်က Node ကို Print ထုတ်ပါတယ်။
		inorderTraversal(root->right); // ညာဘက်ကို နောက်ဆုံးမှ သွားပါတယ်။
	}
}

// Preorder Traversal (Root -> Left -> Right)
void preorderTraversal(struct Node *root)
{
	if (root != NULL)
	{
		printf("%d ", root->data);	// Root ကို အရင်ဆုံး Print ထုတ်ပါတယ်။
		preorderTraversal(root->left);	// ပြီးမှ ဘယ်ဘက်ကို သွားပါတယ်။
		preorderTraversal(root->right); // နောက်ဆုံးမှ ညာဘက်ကို သွားပါတယ်။
	}
}

// Postorder Traversal (Left -> Right -> Root)
void postorderTraversal(struct Node *root)
{
	if (root != NULL)
	{
		postorderTraversal(root->left);	 // ဘယ်ဘက်ကို အရင်သွားပါတယ်။
		postorderTraversal(root->right); // ညာဘက်ကို ဒုတိယ သွားပါတယ်။
		printf("%d ", root->data);	 // Root ကို အားလုံးပြီးမှ Print ထုတ်ပါတယ်။
	}
}

// User ကနေ ရွေးချယ်ခိုင်းမယ့် Menu-Driven Main Function ဖြစ်ပါတယ်။
int main()
{
	struct Node *root = NULL; // အစမှာ Tree က ဗလာ (NULL) ဖြစ်နေပါမယ်။
	int choice, value;

	while (1)
	{
		printf("\n===== Binary Search Tree Menu =====\n");
		printf("1. Insert Node\n");
		printf("2. Inorder Traversal\n");
		printf("3. Preorder Traversal\n");
		printf("4. Postorder Traversal\n");
		printf("5. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			printf("Enter value to insert: ");
			scanf("%d", &value);
			root = create_bst(root, value); // Node အသစ် ထည့်ပါတယ်။
			break;

		case 2:
			printf("Inorder Traversal: ");
			inorderTraversal(root); // Inorder နဲ့ Print ထုတ်ပါတယ်။
			printf("\n");
			break;

		case 3:
			printf("Preorder Traversal: ");
			preorderTraversal(root); // Preorder နဲ့ Print ထုတ်ပါတယ်။
			printf("\n");
			break;

		case 4:
			printf("Postorder Traversal: ");
			postorderTraversal(root); // Postorder နဲ့ Print ထုတ်ပါတယ်။
			printf("\n");
			break;

		case 5:
			printf("Exiting program...\n");
			exit(0); // Program ကို ပိတ်လိုက်ပါတယ်။

		default:
			printf("Invalid choice! Try again.\n");
		}
	}

	return 0;
}