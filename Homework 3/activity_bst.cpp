// Written by Bilgehan Bilgin | 30902

#include <iostream>
#include "activity_bst.h"

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

// Add an activity with name 'activity' and time 'time'
void add_activity(tree_node*& root, int time, const string& activity){
	
	// Check if time is legal 
	if (!check_time_legality(time))
	{
		std::cout << "ERROR! Could not add activity " <<  activity << " due to illegal time value" << std::endl;
		return;
	}

	// If root doesn't exist, create the root with the values given
	if (!root)
	{
		root = new tree_node(time, activity);
		cout << "Added activity '" << activity << "' at " << number_to_time(time) << endl;		// modified
		return;
	}
	
	// If root exists, then add a new node to the appropriate place in the tree
	tree_node* current_node = root;
	while (true)
	{
		// If the new activity is supposed to be in between two nodes of a "right" branch
		if (false && current_node->right && time > current_node->time && time < current_node->right->time)		// modified
		{
			tree_node* new_node = new tree_node(time, activity);
			tree_node* next_node = current_node->right;
			current_node->right = new_node;
			new_node->right = next_node;
			new_node->parent = current_node;
			next_node->parent = new_node;
			new_node->activity = activity;
			new_node->time = time;
			cout << "Added activity " << activity << " at " << number_to_time(time) << endl;
			return;
		}
		else if (current_node->right && time > current_node->time)		// modified
		{
			current_node = current_node->right;
		}
		else if (current_node->left && time < current_node->time)
		{
			current_node = current_node->left;
		}
		// If we've reached one of the leaves, add the new node and break
		else
		{
			if (time > current_node->time)
			{
				tree_node* new_node = new tree_node(time, activity);
				current_node->right = new_node;
				new_node->parent = current_node;
				cout << "Added activity '" << activity << "' at " << number_to_time(time) << endl;	// modified
			}
			// If the time of the left-most leave is still greater than "time", add the new activity to its left
			else if (time < current_node->time)
			{
				tree_node* new_node = new tree_node(time, activity);
				current_node->left = new_node;
				new_node->parent = current_node;
				cout << "Added activity '" << activity << "' at " << number_to_time(time) << endl;	// modified
			}
			return;
		}
	}
	return;
}

// Print the name of the activity occurring at time 'time'
void print_activity(tree_node* root, int time){

	// Check if time is legal 
	if (!check_time_legality(time))
	{
		std::cout << "ERROR! Could not print activity at specific time due to illegal time" << std::endl;
		return;
	}
	// Get the time in string format
	string time_formatted = number_to_time(time);

	//If no activities have been entered, print free
	if (!root)
	{
		cout << "Time: " << time_formatted << ", Activity: " << "free" << endl;
		return;
	}
	// If only node is the root node, just print the root node
	if (!root->left && !root->right)
	{
		cout << "Time: " << time_formatted << ", Activity: " << root->activity << endl;
		return;
	}

	int most_recent_time = 0, earliest_time = 0;
	string most_recent_activity = "free", earliest_activity;

	tree_node* current_node = root;
	while (current_node)
	{
		if (current_node->right && time > current_node->time && time < current_node->right->time)
		{
			cout << "Time: " << time_formatted << ", Activity: " << current_node->activity << endl;
			return;
		}
		else if (current_node->right && time > current_node->time)
		{
			most_recent_activity = current_node->activity;
			most_recent_time = current_node->time;
			current_node = current_node->right;
		}
		else if (current_node->left && time < current_node->time)
		{
			current_node = current_node->left;
		}
		// If we can find a node whose time value is equal to the value we're searching for, print that activity
		else if (time == current_node->time)
		{
			cout << "Time: " << time_formatted << ", Activity: " << current_node->activity << endl;
			return;
		}
		else
		{
			if (time > current_node->time)
			{
				cout << "Time: " << time_formatted << ", Activity: " << current_node->activity << endl;
				return;
			}
			else if (time < current_node->time)
			{
				cout << "Time: " << time_formatted << ", Activity: " << most_recent_activity << endl;
				return;
			}
		}
	}
	return;
}

// Print the duration of the activity occurring at time 'time'
void print_activity_and_duration(tree_node* root, int time) {

	// First, check if time is legal
	if (!check_time_legality(time))
	{
		std::cout << "ERROR! Could not print activity and duration due to illegal time" << std::endl;
		return;
	}

	// Get the time in string format
	string time_formatted = number_to_time(time);

	// Check if there has been no activity added
	if (!root)
	{
		cout << "Time period : [" << number_to_time(0) << " - " << number_to_time(0) << "] : " << "free" << endl;
		return;
	}

	// Check if root node is the only node
	if (!root->left && !root->right)
	{
		cout << "Time period : [" << number_to_time(root->time) << " - " << number_to_time(0) << "] : " << root->activity << endl;
		return;
	}

	int next_time = 0;
	tree_node* current_node = root;
	while (true)
	{
		if (current_node->right && time > current_node->time && time < current_node->right->time)
		{
			cout << "Time period : [" << number_to_time(current_node->time) << " - " << number_to_time(current_node->right->time) << "] : " << current_node->activity << endl;
			return;
		}
		else if (current_node->right && time > current_node->time)
		{
			current_node = current_node->right;
		}
		else if (current_node->left && !current_node->left->right && time < current_node->time && time > current_node->left->time)
		{
			cout << "Time period : [" << number_to_time(current_node->left->time) << " - " << number_to_time(current_node->time) << "] : " << current_node->left->activity << endl;
			return;

		}
		else if (current_node->left && time < current_node->time)
		{
			next_time = current_node->time;
			current_node = current_node->left;
		}
		else if (!current_node->left && time < current_node->time)
		{
			cout << "Time period : [" << number_to_time(0) << " - " << number_to_time(current_node->time) << "] : " << "free" << endl;
			return;
		}
		// If we can find a node whose time value is equal to the value we're searching for, print that activity
		else if (time == current_node->time)
		{
			if (current_node->right)
			{
				next_time = current_node->right->time;
			}
			cout << "Time period : [" << number_to_time(current_node->time) << " - " << number_to_time(next_time) << "] : " << current_node->activity << endl;
			return;
		}
		else
		{
			cout << "Time period : [" << number_to_time(current_node->time) << " - " << number_to_time(next_time) << "] : " << current_node->activity << endl;
			return;
		}
	}

}

void recursive_print_inorder(tree_node* root, string activity) {

	if (root) {
		// Traversal in order
		recursive_print_inorder(root->left, activity);
		

		if (root->activity == activity) {
			int next_time = 0;
			tree_node* node_ptr = root;

			// If the node has a right branch, that time is the next time
			if (node_ptr->right)
			{
				next_time = node_ptr->right->time;

			}
			// Left node that doesn't have a right branch
			else if (node_ptr->parent->time > node_ptr->time)
			{
				next_time = node_ptr->parent->time;
			}
			// Leave of a right branch
			else
			{
				while (node_ptr->parent)
				{
					if (node_ptr->time < node_ptr->parent->time)
					{
						next_time = node_ptr->parent->time;
						break;
					}
					node_ptr = node_ptr->parent;
				}
			}

			cout << "Time period : [" << number_to_time(root->time) << " - " << number_to_time(next_time) << "] : " << activity << endl;
		}
		recursive_print_inorder(root->right, activity);
	}
}


// Print the duration of every occurrence of activity 'activity'
void print_single_activity(tree_node* root, const string& activity){
	// If the activity is "free", print the appropriate message
	if (activity == "free")
	{
		if (!root)
		{
			cout << "Time period : [" << number_to_time(0) << " - " << number_to_time(0) << "] : " << "free" << endl;;
			return;
		}
		// find the earliest activity and print free with respect to its time
		tree_node* node_ptr = root;
		while (node_ptr)
		{
			if (node_ptr->left)
			{
				node_ptr = node_ptr->left;
			}
			else
			{
				break;
			}
		}

		if (node_ptr->time != 0)
		{
			cout << "Time period : [" << number_to_time(0) << " - " << number_to_time(node_ptr->time) << "] : " << "free" << endl;
		}
		return;
	}

	// Otherwise, search for all occurances of the given activity in the tree

	recursive_print_inorder(root, activity);
}



void recursive_print_inorder(tree_node* root) {
	if (root) {
		recursive_print_inorder(root->left);
		cout << "[" << number_to_time(root->time) << "]" << " - " << root->activity << endl;
		recursive_print_inorder(root->right);
	}
}
// Print the starting time of every activity
void print_all_activities(tree_node* root){
	recursive_print_inorder(root);
}


void recursive_delete_tree(tree_node* root) {
	// Delete using post-order traversal
	if (!root)
	{
		return;
	}
	recursive_delete_tree(root->left);
	recursive_delete_tree(root->right);
	delete(root);
	root = nullptr;
}
// Delete the tree pointed at by `root`
void delete_tree(tree_node* root){
	recursive_delete_tree(root);
}
