#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEVEL 33
typedef struct skiplist
{
	int value;
	int level;
	struct skiplist *next[MAX_LEVEL];
}skiplist;
skiplist *head;
int level=0;
void insert(int value)
{
	skiplist *x = head;
	int i;
	skiplist *update[MAX_LEVEL];
	for(i=level;i>=0;i--) 
	{
		while(x->next[i]!=NULL&&x->next[i]->value<value) 
		{
			x=x->next[i];
		}
		update[i]=x;
	}
	x=x->next[0];
	if(x==NULL||x->value!=value)
	{
		//printf("insert \n");
		/*int rnd=rand(),l=0;
		  for(i=rnd;(i&1);i>>=1)
		  l++;*/
		int l=0,sd=rand()%2;
		while(sd==1)
		{
			l++;
			sd=rand()%2;
			if(l>level)
				break;
		}
		if(l>=MAX_LEVEL)
			l=MAX_LEVEL-1;
		if(l>level)
		{	
			l=level+1;
			for (i = level + 1; i <= l; i++) 
			{
				update[i]=head;
			}
			level=l;
		}
		x=(skiplist*)malloc(sizeof(skiplist));
		x->value=value;
		x->level=l;
		for (i = 0; i <= l; i++) 
		{
			x->next[i] = update[i]->next[i];
			update[i]->next[i] = x;
		}
	}
}
void delete(int value)
{
	skiplist *x = head;
	int i;
	skiplist *update[MAX_LEVEL];
	for (i = level; i >= 0; i--) 
	{
		while (x->next[i] != NULL && x->next[i]->value < value) 
		{
			x = x->next[i];
		}
		update[i] = x;
	}
	x=x->next[0];
	if (x !=NULL && x->value == value) 
	{
		for (i = 0; i <= level; i++) {
			if (update[i]->next[i] != x)
				break;
			update[i]->next[i] = x->next[i];
		}
		free(x);
		printf("DELETED\n");
		while (level > 0 && head->next[level] == NULL) 
		{
			level--;
		}
	}
	else
		printf("NOT FOUND\n");
}
int  find(int value)
{
	skiplist *x = head;
	int i;
	skiplist *update[MAX_LEVEL];
	for (i = level; i >= 0; i--) 
	{
		while (x->next[i] != NULL && x->next[i]->value < value) 
		{
			x = x->next[i];
		}
		update[i] = x;
	}
	x=x->next[0];

	if (x !=NULL && x->value == value) 
	{
		return 1;
		}
	return 0;
}
void print()
{
	skiplist *x=head->next[0];
	while(x!=NULL)
	{
		printf("%d ",x->value);
	//	int i;
	/*	for(i=x->level;i>=0;i--)
		{
			skiplist *t=x;
			while(t!=NULL)
			{
				printf("%d ",t->value);
				t=t->next[i];
			}
			printf("\n");

		}
		printf("\n");*/
		x=x->next[0];
	}
	printf("\n");
}
int main()
{
	head=(skiplist*)malloc(sizeof(skiplist));
	head->value=-4323132;
/*	int a=1;
	while(a!=0)
	{
		scanf("%d",&a);
		insert(a);
		print();
	}
	a=1;
	while(a!=0)
	{
		scanf("%d",&a);
		delete(a);
		print();
	}*/
	char a;
	int d;
	a=getchar_unlocked();
	while(a==' ' || a=='\n')
	{	
		a=getchar_unlocked();
	}
	while(a!='q')
	{
		
	if(a=='i'||a=='I')
	{		
		scanf("%d",&d);
		/*a=getchar_unlocked();
		while(a==' ' || a=='\n')
		{	
				a=getchar_unlocked();
		}
		d=0;
		int y=0;
		if(a=='-')
		{
			y=1;
			a=getchar_unlocked();
		}
		while(a!='\n')
		{
			d=d*10+a-'0';
			a=getchar_unlocked();
		}
		if(y==1)
			d=d*-1;	*/
		insert(d);
	}	
	else if(a=='d'||a=='D')
	{		
		scanf("%d",&d);
		delete(d);
	}
	else if(a=='p'||a=='P')
		print();
	else if(a=='S'||a=='s')
	{
		scanf("%d",&d);
		int f=find(d);
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
