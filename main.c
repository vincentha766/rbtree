#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define DATALEN 1

enum color {
	RED = 1,
	BLACK
};

struct node {
	struct node *parent, *left, *right;
	enum color color;
	char data[DATALEN];
};

const struct node NIL_NODE = {NULL, NULL, NULL, BLACK};
#define NIL (struct node*)&NIL_NODE

int is_leaf(struct node *n)
{
	return n == NIL;
}

struct node *create_node()
{
	struct node *p = (struct node *)malloc(sizeof(struct node));
	if (p != NULL) {
		p->parent = NULL;
		p->left = p->right = NIL;
		p->color = BLACK;
		memset(p->data, 0, DATALEN);
	}
	return p;
}

void assign_value(struct node *node, const char data[])
{
	memcpy(node->data, data, DATALEN);
}

void destroy_node(struct node *n)
{
	if (!is_leaf(n))
		free(n);
}

void set_data(struct node *n, const char data[])
{
	memcpy(n->data, data, DATALEN);
}

int cmp(const char data1[], const char data2[])
{
	for (int i = 0; i < DATALEN; i++) {
		if (data1[i] != data2[i])
			return data1[i] - data2[i];
	}
	return 0;
}

void replace_node(struct node *n, struct node *child)
{
	if (is_leaf(child)) {
		if (n == n->parent->left)
			n->parent->left = child;
		else
			n->parent->right = child;
	}
	struct node *node = create_node();
	node->parent = n->parent;
	node->left = n->left;
	node->right = n->right;
	memcpy(node->data, child->data, DATALEN);
	node->color = child->color;
}

void delete_one_child(struct node *root, struct node *n)
{
	struct node *child = is_leaf(n->right) ? n->left : n->right;
}

struct node *create_tree(const char data[])
{
	//stub
	struct node *root = create_node();
	root->parent = NULL;
	root->left = NIL;
	root->right = NIL;
	root->color = BLACK;
	set_data(root, data);
	return root;
}

// simpler search, quicker
struct node *rbtree_search(struct node *root, const char data[])
{
	struct node *p = root;
	while (p != NIL) {
		int result = cmp(p->data, data);
		if (result == 0)
			return p;
		if (result > 0)
			p = p->left;
		else
			p = p->right;
	}
	return NIL;
}

struct node *rbtree_insert(struct node *root, const char data[])
{
	struct node *p = root;
	if (is_leaf(p))
		return create_tree(data);
	int result;
	while (1) {
		result = cmp(p->data, data);
		if (result == 0)
			return p;
		else if (result > 0 && !is_leaf(p->left))
			p = p->left;
		else if (result < 0 && !is_leaf(p->right))
			p = p->right;
		else 
			break;
	}

	struct node *new_node = create_node();
	assign_value(new_node, data);
	new_node->parent = p;

	if (result > 0)
		p->left = new_node;	
	else
		p->right = new_node;	

	// FIX ME
	// do jobs to make rb tree rules satisfied

	return new_node;
}

struct node *tree = NULL;
const char datas[10][DATALEN] = {"b", "d", "a", "k", "z", "l", "p", "t", "g", "e"};

int main(void) 
{
	struct node *tree = create_tree((char*)datas[0]);
	for (int i = 1; i < 10; i++)
		rbtree_insert(tree, datas[i]);
	
	printf("%s\n", rbtree_search(tree, datas[9])->data);
	return 0;
}
