#include<stdio.h>
#include<malloc.h>
typedef struct bst
{
	int info;
	int height;
	int valid;
	struct bst *left;
	struct bst *right;
}NODE;
typedef NODE* ROOT;
int set_height(ROOT r)
{
	int left_h = -1;
	int right_h = -1;
	if(r->left)
		left_h = r->left->height;
	if(r->right)
		right_h = r->right->height;
	if(left_h >= right_h)
		r->height = left_h+1;
	else
		r->height = right_h+1;
	return r->height;
}
int compare(int data1, int data2)
{
	if(data1<data2)
		return -1;
	if(data1>data2)
		return 1;
	else
		return 0;
}
void rotate_LL(ROOT *r)
{
	NODE *r1, *r2 = *r,*t1,*t2,*t3;
	r1 = r2->left;
	t1 = r1->left;
	t2 = r1->right;
	t3 = r2->right;
	r1->right = r2;
	r2->left = t2;
	set_height(r1);
	set_height(r2);
	*r = r1;
}
void rotate_RL(ROOT *r)
{
	NODE *r1,*r2, *r3=*r,*t1,*t2,*t3,*t4;
	r1 = r3->left;
	r2 = r1->right;
	t2 = r2->left;
	t3 = r2->right;
	r1->right = t2;
	r3->left = t3;
	r2->left = r1;
	r2->right = r3;
	set_height(r1);
	set_height(r2);
	set_height(r3);
	*r = r2; 
}
void rotate_LR(ROOT *r)
{
	NODE *r1=*r, *r2,*r3,*t1,*t2,*t3,*t4;

	r3 = r1->right;
	r2 = r3->left;
	t2 = r2->left;
	t3 = r2->right;
	r1->right = t2;
	r3->left = t3;
	r2->left = r1;
	r2->right = r3;
	set_height(r1);
	set_height(r2);
	set_height(r3);

	*r = r2;
}
void rotate_RR(ROOT *r)
{
	NODE *r1=*r,*r2,*t1,*t2,*t3;

	r2 = r1->right;
	t1 = r1->left;
	t2 = r2->left;
	t3 = r2->right;
	r1->right = t2;
	r2->left = r1;
	set_height(r1);
	set_height(r2);
	*r = r2;
}
int find_rotation_type(int parent_data, int child_data, int data)
{
	if(compare(data, parent_data)<0) // inserting left
	{
		if(compare(data, child_data)<0)
			return 1;
		else if(compare(data, child_data)==0)
			return 0;
		else
			return 2;

	}
	else //inserting right
	{
		if(compare(data, child_data)>0)
			return 4;
		else if(compare(data, child_data)==0)
			return 0;
		else
			return 3;
	}
}
void do_rotation(ROOT *r, int rotation_type)
{
	if(rotation_type == 1)
		rotate_LL(r);
	else if(rotation_type == 2)
		rotate_RL(r);
	else if(rotation_type == 3)
		rotate_LR(r);
	else if(rotation_type == 4)
		rotate_RR(r);
}
int insert(ROOT *r, int data)
{
	NODE *new_node, *root = *r;
	int left_h = -1, right_h = -1;
	int diff,rotation_type;
	if(root == NULL)
	{
		new_node = (NODE *)malloc(sizeof(NODE));
		new_node->info = data;
		new_node->height = 0;
		new_node->left = new_node->right = NULL;
		new_node->valid=1;
		*r = new_node;
		return 0;
	}
	if(root->left)
		left_h = root->left->height;
	if(root->right)
		right_h = root->right->height;
	if(compare(data, root->info)<0)
	{
		left_h = insert(&(root->left), data);
		rotation_type = find_rotation_type(root->info, root->left->info, data);
	}
	else if(compare(data, root->info)>0)
	{
		right_h = insert(&(root->right), data);
		rotation_type = find_rotation_type(root->info, root->right->info, data);
	}
	else
	{
		//Duplicate key
		return -1;
	}

	diff = left_h-right_h;
	if(diff>1 || diff<-1)
	{
		do_rotation(r,rotation_type);
		root = *r;
	}
	return set_height(root);
}
void print_inorder(NODE *root)
{
	NODE *temp = root;
	if(temp)
	{
		print_inorder(temp->left);
		if(temp->valid==1)
		printf("%d ",temp->info);
		print_inorder(temp->right);
	}
}
void print_preorder(NODE *root)
{
	NODE *temp = root;
	if(temp)
	{
		if(temp->valid==1)
			printf("%d\n",temp->info);
		print_preorder(temp->left);
		print_preorder(temp->right);
	}
}
void print_postorder(NODE *root)
{
	NODE *temp = root;
	if(temp)
	{
		print_postorder(temp->left);
		print_postorder(temp->right);
		if(temp->valid==1)
		printf("%d ",temp->info);
	}
}
int find(NODE *root,int v)
{
	if(root)
	{
		if(root->info==v)
		{
		if(root->valid==1)
			return 1;
		else 
			return 0;
		}
		else if(root->info > v)
			return find(root->left,v);
		else
			return find(root->right,v);
	}
	else
		return 0;
}

int del(NODE *root,int v)
{
//	printf("%d v=%d\n",root->info,v);
	if(root!=NULL)
	{
		if(root->info==v)
		{
			root->valid=0;
	//		printf("val=%d %d\n",root->valid,root->info);
			return 1;
		}
		else if(root->info > v)
			return del(root->left,v);
		else
			return del(root->right,v);
	}
	else
		return 0;
}
int main()
{
	ROOT r = NULL;
	int i,num,data,choice;
	char a;
	int d;
	a=getchar_unlocked();
	while(a==' ' || a=='\n')
	{
		a=getchar_unlocked();
	}
	while(a!='q')
	{

		if(a=='I' || a=='i')
		{
			scanf("%d",&d);
			insert(&r,d);
		}
		else if(a=='D'|| a=='d')
		{
			scanf("%d",&d);
			int f=del(r,d);
			if(f==0)
				printf("NOT FOUND\n");
			else
				printf("DELETED\n");
		}
		else if(a=='P'||a=='p')
		{	 
			print_inorder(r);
			printf("\n");
		}
		else if(a=='S'||a=='s')
		{
			scanf("%d",&d);
			int f=find(r,d);
			if(f==0)
				printf("NOT FOUND\n");
			else
				printf("FOUND\n");


		}
		a=getchar_unlocked();
		while(a==' ' || a=='\n')
		{
			a=getchar_unlocked();
		}
	}

	return 0;
}
