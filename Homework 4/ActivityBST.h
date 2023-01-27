#ifndef _ACTIVITY_BST
#define _ACTIVITY_BST

#include <string>
#include <iostream>


using namespace std;

struct tree_node {
	int time;
	string activity;
	tree_node* right;
	tree_node* left;
	tree_node* parent;
	tree_node(int t, const string& a) : time(t), activity(a),
		right(nullptr), left(nullptr),
		parent(nullptr) {}
};


class ActivityBST {

private:
	tree_node* root;

public:
	ActivityBST();
	ActivityBST(const ActivityBST&);
	void constrHelper(tree_node*&, tree_node*&);
	~ActivityBST();
	void destructHelper(tree_node*&);
	void add(int, const string&);
	ActivityBST& operator=(const ActivityBST&);
	ActivityBST operator+(const ActivityBST&) const;
	ActivityBST& operator+=(const ActivityBST&);
	friend ostream& operator<<(ostream&, const ActivityBST&);
};

ostream& operator<<(ostream&, const ActivityBST&);

#endif 

