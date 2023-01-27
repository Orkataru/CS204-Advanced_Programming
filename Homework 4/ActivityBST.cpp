// Written by Bilgehan Bilgin || 00030902

#include "ActivityBST.h"

using namespace std;

string fill_with_zeros(int num_zeros, const string& input) {
	int zeros_to_add = num_zeros - input.length();
	if (zeros_to_add < 0) zeros_to_add = 0;
	return string(zeros_to_add, '0') + input;
}
string number_to_time(int number) {
	if (number > 2359 || number < 0) return "ERROR";
	return fill_with_zeros(2, to_string(number / 100)) + ":" + fill_with_zeros(2,
		to_string(number % 100));
}
bool check_time_legality(int time) {
	string time_str = number_to_time(time);
	if (time_str == "ERROR")
	{
		return false;
	}
	string first_half_str = time_str.substr(0, 2);
	string second_half_str = time_str.substr(3);

	int first_half = stoi(first_half_str);
	int second_half = stoi(second_half_str);

	if (first_half >= 0 && first_half <= 23 && second_half >= 0 && second_half <= 59)
	{
		return true;
	}
	return false;
}

// Default constructor
ActivityBST::ActivityBST() {
	root = nullptr;
}

// Recursive helper function that copies the given tree
void ActivityBST::constrHelper(tree_node* &rhs, tree_node* &node) {
	// pre-order traversal, copy the node to the appropriate place in the tree and link its parent
	if (!rhs)
	{
		return;
	}
	tree_node* new_node = new tree_node(rhs->time, rhs->activity);
	new_node->parent = node;
	node = new_node;
	constrHelper(rhs->left, node->left);
	constrHelper(rhs->right, node->right);
}

// Copy Constructor
ActivityBST::ActivityBST(const ActivityBST& tree) {
	// set the root first
	tree_node* rhs_head = tree.root; 
	this->root = nullptr;
	// If the tree of the obj to be copied is empty, return.
	if (!rhs_head)
	{
		return;
	}
	// call the recursive helper function
	constrHelper(rhs_head, this->root);
}

// Helper function for member function void ActivityBST::add()
void add_activity_helper(tree_node*& root, int time, const string& activity) {

	// If root exists, then add a new node to the appropriate place in the tree
	tree_node* current_node = root;
	// If root is not a nullptr, start traversing the tree
	if (root)
	{
		while (true)
		{	
			if (current_node->right && time > current_node->time)
			{
				current_node = current_node->right;
			}
			else if (current_node->left && time < current_node->time)
			{
				current_node = current_node->left;
			}
			else
			{
				// If the time of the right-most leave is still smaller than "time", add the new activity to its right
				if (time > current_node->time)
				{
					tree_node* new_node = new tree_node(time, activity);
					current_node->right = new_node;
					new_node->parent = current_node;
				}
				// If the time of the left-most leave is still greater than "time", add the new activity to its left
				else if (time < current_node->time)
				{
					tree_node* new_node = new tree_node(time, activity);
					current_node->left = new_node;
					new_node->parent = current_node;
				}
				return;
			}
		}
	}
	// If tree root is nullptr, then create the root node with the given inputs
	else {
		root = new tree_node(time, activity);
	}
	return;
}

// Add an activity with name 'activity' and time 'time'
void ActivityBST::add(int time, const string& activity) {

	// Check if time is legal 
	if (!check_time_legality(time))
	{
		return;
	}
	add_activity_helper(root, time, activity);
} 

// Recursive helper function for the destructor
void ActivityBST::destructHelper(tree_node*& curr) {
	if (curr)
	{
		destructHelper(curr->left);
		destructHelper(curr->right);
		delete curr;
	}
}

// Deallocate the memory space using post-traversal
ActivityBST::~ActivityBST() {
	// Call the recursive helper function
	destructHelper(root);
}

ActivityBST &ActivityBST::operator=(const ActivityBST& rhs) {
	// Check for self-assignment
	if (this == &rhs)
	{
		return *this;
	}
	else
	{
		// First, delete the lhs object
		this->destructHelper(root);

		// Then, (deep) copy the content of rhs to lhs
		tree_node* to_be_copied = rhs.root;
		this->constrHelper(to_be_copied, root);

		// Return the lhs object for cascaded operations
		return *this;
	}
}

// Merges two trees
void merge_trees(tree_node* &root1, tree_node* root2) {

	if (root2)
	{
		merge_trees(root1, root2->left);

		// Add the current node of root2 to the appropriate position in root1
		tree_node* current_node = root1;
		while (current_node)
		{
			if (current_node->right && root2->time > current_node->time)
			{
				current_node = current_node->right;
			}
			else if (current_node->left && root2->time < current_node->time)
			{
				current_node = current_node->left;
			}
			else
			{
				// If the time of the right-most leave is still smaller than "time", add the new activity to its right
				if (root2->time > current_node->time)
				{
					tree_node* new_node = new tree_node(root2->time, root2->activity);
					current_node->right = new_node;
					new_node->parent = current_node;
				}
				// If the time of the left-most leave is still greater than "time", add the new activity to its left
				else if (root2->time < current_node->time)
				{
					tree_node* new_node = new tree_node(root2->time, root2->activity);
					current_node->left = new_node;
					new_node->parent = current_node;
				}
				break;
			}
		}
		merge_trees(root1, root2->right);
	}	
}

// Merges two BST objects and returns the merged BST
ActivityBST ActivityBST::operator+(const ActivityBST& rhs) const {
	if (!rhs.root && !this->root) return *this;
	else if (!rhs.root) return *this;
	else if (!this->root) return rhs;

	ActivityBST res(*this);
	merge_trees(res.root, rhs.root);
	return res;
}

ActivityBST &ActivityBST::operator+=(const ActivityBST& rhs) {
	*this = *this + rhs;
	return *this;
}

// Helper function for operator<<, traverses the tree in-order
void inorderRecursive(ostream& os, tree_node* &head)
{
	if (!head)
	{
		return;
	}
	inorderRecursive(os, head->left);
	os << "[" << number_to_time(head->time) << "] - " << head->activity << endl;
	inorderRecursive(os, head->right);

}

ostream& operator<<(ostream& os, const ActivityBST& bst) {
	string res;
	// use in-order traversal to pass all activities to the os object in order
	tree_node* head = bst.root;
	inorderRecursive(os, head);
	return os;
}