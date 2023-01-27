// Written by Bilgehan Bilgin | ID: 30902

#include "sparse_matrix_2d_linked_list.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;


row_node* read_matrix(const string& filename, int& num_rows, int& num_columns){
	
	ifstream matrix_file;
	string line;
	int value;
	int col_count = 0, cell_count = 0;
	matrix_file.open(filename.c_str());

	// Get the first line, which contains size info
	getline(matrix_file, line);
	stringstream line_str(line);

	// save the values in the first row (size specifications) of file
	line_str >> num_rows;
	line_str >> num_columns;


	// initialize the head of the list
	row_node* head = new row_node;
	cell_node* col_curr = nullptr;
	row_node* row_curr = head;

	while (getline(matrix_file, line)) {
		stringstream line_str(line);
		row_curr->down = new row_node;
		row_curr = row_curr->down;
		row_curr->cell = nullptr;
		while (line_str >> value){
			if (value != 0) {
			// create a new cell node
				// if it's the first cell
				if (cell_count == 0) {
					col_curr = new cell_node;
					row_curr->cell = col_curr;
					col_curr->left = nullptr;
				}
				// otherwise 
				else {			
					cell_node* col_temp = new cell_node;
					col_curr->right = col_temp;
					col_temp->left = col_curr;
					col_curr = col_temp;

				}
				col_curr->right = nullptr;
				col_curr->column = col_count;
				col_curr->value = value;
				cell_count++;
			}
			col_count++;
		}
		col_count = 0;
		cell_count = 0;
	}
	row_curr->down = nullptr;

	// delete the pseudo-head, point the head to the actual head of the list
	row_node* temp = head;
	head = head->down;
	delete temp;

	return head;
}

void print_matrix(row_node* head, int num_rows, int num_columns) {

	row_node* temp_rows = head;
	for (int i = 0; i < num_rows; i ++){
		cell_node* temp_cells = temp_rows->cell;

		// If the row is empty, print a row of zeros and continue with the next row
		if (!temp_cells) {
			for (int j = 0; j < num_columns; j++){
				cout << "0 ";
			}
		}
		// If not, print the row
		else{
			while (temp_cells) {
				// FIRST CELL
				if (!temp_cells->left) {
					// if the first cell is not actually the first element of the matrix, print zeros before it
					if (temp_cells->column != 0) {
						for (int k = 0; k < temp_cells->column; k++) {
							cout << "0 ";
						}
					}
					// if there is a gap in columns first print the value, then print zeros to fill the gap
					cout << temp_cells->value << " ";
					if (temp_cells->right){
						for (int k = temp_cells->column + 1; k < temp_cells->right->column; k++) {
							cout << "0 ";
						}
					}
					// if the first cell is also the last, fill the end with zeros
					else {
						for (int k = temp_cells->column + 1; k < num_columns; k++) {
							cout << "0 ";
						}
					}
				}
				// LAST CELL
				else if (!temp_cells->right) {
					cout << temp_cells->value << " ";
					// fill the end with zeros
					for (int k = temp_cells->column + 1; k < num_columns ; k++) {
						cout << "0 ";
					}
				}
				// IN BETWEEN
				else {
					// if there is a gap in columns print the value, then print zeros to fill the gap
					if (temp_cells->right->column - temp_cells->column > 1) {
						cout << temp_cells->value << " ";
						for (int k = temp_cells->column + 1; k < temp_cells->right->column; k++) {
							cout << "0 ";
						}
					}
					// if there is no gap, just print the value
					else {
						cout << temp_cells->value << " ";
					}
				}
				temp_cells = temp_cells->right;
			}
		}
		temp_rows = temp_rows->down;
		cout << endl;
	}

}

void delete_matrix(row_node* head){
	while (head) {
		// if at least one cell exists in a row, delete all cells
		if (head->cell) {
			cell_node* col_temp = head->cell;
			while (col_temp) {
				cell_node* to_be_deleted = col_temp;
				col_temp = col_temp->right;
				delete to_be_deleted;
			}
		}
		// delete the current row
		row_node* row_temp = head;
		head = head->down;
		delete row_temp;
	}
}

row_node* add_matrices(row_node* left, row_node* right, int num_rows, int num_columns){
	
	int cell_count = 0;
	row_node* head = new row_node;
	cell_node* col_curr = nullptr;
	row_node* row_curr = head;

	// CREATE AN EMPTY LIST
	for (int i = 0; i < num_rows; i++){
		row_curr->down = new row_node;
		row_curr = row_curr->down;
		row_curr->cell = nullptr;
		for (int j = 0; j < num_columns; j++) {
		// create a new cell node
			// if it's the first cell
			if (cell_count == 0) {
				col_curr = new cell_node;
				row_curr->cell = col_curr;
				col_curr->left = nullptr;
			}
			// otherwise 
			else {
				cell_node* col_temp = new cell_node;
				col_curr->right = col_temp;
				col_temp->left = col_curr;
				col_curr = col_temp;

			}
			col_curr->right = nullptr;
			col_curr->column = cell_count;
			col_curr->value = 0;
			cell_count++;
		}
		cell_count = 0;
	}
	row_curr->down = nullptr;

	// delete the pseudo-head, point head to the actual head of the list
	row_node* temp = head;
	head = head->down;
	delete temp;



	// Initialize pointers for each matrix to be added
	row_node* lhs_row = left;
	row_node* rhs_row = right;
	cell_node* lhs_cell = nullptr;
	cell_node* rhs_cell = nullptr;

	row_curr = head;
	for (int i = 0; i < num_rows; i++){
		// Point each cell pointer to first cell of the row
		col_curr = row_curr->cell;
		lhs_cell = lhs_row->cell;
		rhs_cell = rhs_row->cell;
		for (int k = 0; k < num_columns; k++){
			if (lhs_cell && k == lhs_cell->column) {
				col_curr->value += lhs_cell->value;
				lhs_cell = lhs_cell->right;
			}
			if (rhs_cell && k == rhs_cell->column) {
				col_curr->value += rhs_cell->value;
				rhs_cell = rhs_cell->right;
			}
			// a short-circuit that may or may not help when adding up large matrices
			if (!(lhs_cell || rhs_cell)) { break; }
			col_curr = col_curr->right;
		}
		row_curr = row_curr->down;
		lhs_row = lhs_row->down;
		rhs_row = rhs_row->down;
	}

	// Delete the cells that has the value 0
	row_node* row = head;
	while (row) {
		cell_node* col_temp = row->cell;
		while (col_temp)
		{
			if (col_temp && col_temp->value == 0)
			{
				cell_node* to_be_deleted = col_temp;
				// if current cell is the first cell of the row
				if (!col_temp->left)
				{
					// if current cell is the only cell (both first and last)
					if (!col_temp->right) {
						row->cell = nullptr;
						delete to_be_deleted;
						col_temp = nullptr;
					}
					else {
						row->cell = col_temp->right;
						col_temp = col_temp->right;
						delete to_be_deleted;
						to_be_deleted = col_temp;
						col_temp->left = nullptr;
					}
				}
				// if current cell is the last cell of the row
				else if (!col_temp->right)
				{
					to_be_deleted = col_temp;
					col_temp->left->right = col_temp->right;
					col_temp = nullptr;
					delete to_be_deleted;
				}
				// if current cell is in the middle
				else
				{
					to_be_deleted = col_temp;
					col_temp->left->right = col_temp->right;
					col_temp->right->left = col_temp->left;
					col_temp = col_temp->right;
					delete to_be_deleted;
					to_be_deleted = col_temp;

				}
			}
			else
			{
				col_temp = col_temp->right;
			}
		}
		row = row->down;
	}
	return head;
}

bool check_symmetry(row_node* up) {

	row_node* upper_row = up;
	cell_node* upper_cell = up->cell;

	int row_index = 0;
	while (true)
	{
		// If end of the row has been reached
		if (!upper_cell)
		{
			// If we're not at the last cell of the last row, proceed to the next row
			if (upper_row->down)
			{
				upper_row = upper_row->down;
				upper_cell = upper_row->cell;
				row_index++;
			}
			// If we're at the last cell of the last row, then end the loop
			else
			{
				break;
			}
		}
		// If the current cell is included in the upper half of the matrix
		else if (upper_cell->column > row_index)
		{
			row_node* lower_row = up;
			cell_node* lower_cell = nullptr;

			// Go to the corresponding cell in the lower half of the matrix
			for (int i = 0; i < upper_cell->column; i++)
			{
				lower_row = lower_row->down;
			}
			if (lower_row->cell)
			{
				lower_cell = lower_row->cell;
			}
			else
			{
				return false;
			}


			bool flag = true;
			// Iterate through the cells of the lower row
			while (lower_cell)
			{
				if (lower_cell->column == row_index)
				{
					if (lower_cell->value != upper_cell->value)
					{
						return false;
					}
					flag = false;
					break;
				}
				lower_cell = lower_cell->right;
			}
			// If the corresponding position has never been reached, there can't be symmetry
			if (flag)
			{
				return false;
			}
			
			upper_cell = upper_cell->right;
			
		}
		// If the current cell is not included in the upper half of the matrix, go to the next cell
		else
		{
			upper_cell = upper_cell->right;

		}


	}
	return true;
}

bool is_symmetric(row_node* head, int num_rows, int num_columns){

	// If num_columns and num_rows are not equal, then the matrix can't be symmetric
	if (num_rows != num_columns) {
		return false;
	}

	// If the number of elements on each side of the matrix (when the matrix is cut diagonally)
	// are not equal, then the matrix can't be symmetric
	row_node* temp = head;
	int cell_counter = 0, row_index = 0, diagonal_count = 0;
	while (temp)
	{
		cell_node* cell_ptr = temp->cell;
		while (cell_ptr) {
			if (cell_ptr->column == row_index) {
				diagonal_count++;
			}
			cell_counter++;;
			cell_ptr = cell_ptr->right;
		}
		temp = temp->down;
		row_index++;
	}
	if ((cell_counter - diagonal_count)%2 != 0){
		return false;
	}

	// If a matrix has only one element (1x1), then it must be symmetric
	if (num_rows == 1 && num_columns == 1)
	{
		return true;
	}

	// Check symmetry for each element of the upper half
	if (check_symmetry(head))
	{
		return true;
	}
	return false;
}

row_node* transpose(row_node* head, int num_rows, int num_columns){

	// initialize the row nodes of the linked list for transposed matrix
	row_node* transposed = new row_node;
	row_node* temp1 = nullptr;
	row_node* temp2 = transposed;
	for (int i = 0; i < num_columns - 1; i++)
	{
		temp1 = new row_node;
		temp1->cell = nullptr;
		temp2->down = temp1;
		temp2 = temp2->down;
	}
	temp1 = temp2 = transposed;
	
	row_node* row_ptr = head;
	cell_node* cell_ptr = head->cell;
	int row_index = 0;
	while (row_ptr)
	{
		// If there is at least one cell left in the row
		if (cell_ptr) {
			for (int i = 0; i < cell_ptr->column; i++)
			{
				temp1 = temp1->down;
			}
			cell_node* add_temp = temp1->cell;
			// If this is the first cell in the transposed row
			if (!add_temp)
			{
				add_temp = temp1->cell = new cell_node;
				add_temp->left = add_temp->right = nullptr;
				add_temp->value = cell_ptr->value;
				add_temp->column = row_index;
			}
			// If this is not the first
			else
			{
				// Iterate until the last cell, then create and link the new cell at the end
				while (add_temp){
					if (add_temp->right)
					{
						add_temp = add_temp->right;
					}
					else
					{
						add_temp->right = new cell_node;
						add_temp->right->value = cell_ptr->value;
						add_temp->right->column = row_index;
						add_temp->right->left = add_temp;
						add_temp->right->right = nullptr;
						break;

					}
				}
			}

			if (cell_ptr->right)
			{
				cell_ptr = cell_ptr->right;
			}
			// If this was the last cell
			else
			{
				row_ptr = row_ptr->down;
				if (!row_ptr)
				{
					break;
				}
				cell_ptr = row_ptr->cell;

				row_index++;
			}
			
		}
		// If there are no cells in the row, continue with the next row
		else
		{
			row_ptr = row_ptr->down;
			if (!row_ptr)
			{
				break;
			}
			cell_ptr = row_ptr->cell;
			row_index++;
		}
		temp1 = transposed;
	}

	return transposed;
}
