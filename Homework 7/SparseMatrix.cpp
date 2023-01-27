#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <vector>

using namespace std;

#include "SparseMatrix.h"

SparseMatrix::SparseMatrix(const string& file_name) {
    ifstream fin(file_name);
    if (fin.fail()) {
        throw "File couldn't be opened";
    }
    // actual head_
    head_ = nullptr;
    // head_ of current row
    row_node* curr_head = nullptr;
    // row counter for error checking
    int row = 0;
    fin >> num_rows_ >> num_columns_;
    if (fin.fail()) {
        throw "Invalid number of rows or number of columns";
    }
    string line;
    getline(fin, line);
    while (getline(fin, line)) {
        int col = 0, val;
        stringstream ss(line);
        // if this is the first row
        if (head_ == nullptr) {
            head_ = curr_head = new row_node;
        }
        else {
            curr_head->down = new row_node;
            curr_head = curr_head->down;
        }
        // pointer at last cell added in this row
        cell_node* curr_cell = nullptr;
        while (ss >> val) {
            if (val != 0) {
                cell_node* new_cell = new cell_node;
                new_cell->value = val;
                new_cell->column = col;
                // if first cell in this row
                if (curr_cell == nullptr)
                    curr_head->cell = curr_cell = new_cell;
                else {
                    curr_cell->right = new_cell;
                    curr_cell->right->left = curr_cell;
                    curr_cell = curr_cell->right;
                }
            }
            col++;
            if (col > num_columns_) {
                throw "Too many columns in row " + to_string(row);
            }
        }
        row++;
        if (row > num_rows_) {
            throw "Too many rows";
        }
        if (col < num_columns_) {
            throw "Not enough columns in row " + to_string(row);
        }
    }
    if (row < num_rows_) {
        throw "Not enough rows";
    }
}

SparseMatrix::~SparseMatrix() {
    while (head_ != nullptr) {
        cell_node* cell = head_->cell;
        while (cell != nullptr) {
            cell_node* t = cell->right;
            delete cell;
            cell = t;
        }
        row_node* t = head_->down;
        delete head_;
        head_ = t;
    }
}

ostream& operator<<(ostream& out, const SparseMatrix& rhs) {
    int rows = 0;
    row_node* head = rhs.head_;
    while (head != nullptr) {
        // To know how many zeros to print between cells
        int col = -1;
        cell_node* cell = head->cell;
        while (cell != nullptr) {
            col++;
            // until we get to this cell's column, print zeros
            while (col < cell->column) {
                out << "0 ";
                col++;
            }
            out << cell->value << " ";
            col = cell->column;
            cell = cell->right;
        }
        // If there are more zeros after the last cell in the row,
        // print them
        while (col < rhs.num_columns_ - 1) {
            out << "0 ";
            col++;
        }
        out << endl;
        head = head->down;
        rows++;
    }
    // If there are rows with no cells at all, print zeros for them
    while (rows < rhs.num_rows_) {
        for (int i = 0; i < rhs.num_columns_; i++) {
            out << "0 ";
        }
        out << endl;
        rows++;
    }
    return out;
}

SparseMatrix::SparseMatrix(SparseMatrix&& rhs) noexcept {
    head_ = rhs.head_;
    rhs.head_ = nullptr;
    num_rows_ = rhs.num_rows_;
    num_columns_ = rhs.num_columns_;
}

SparseMatrix::SparseMatrix(row_node* head, int num_rows, int num_columns) : head_(head), num_rows_(num_rows), num_columns_(num_columns) {}

SparseMatrix::SparseMatrix(const SparseMatrix& rhs) : head_(nullptr), num_columns_(rhs.num_columns_), num_rows_(rhs.num_rows_) {
    copy(rhs, head_, num_rows_, num_columns_);
}

SparseMatrix& SparseMatrix::operator=(const SparseMatrix& rhs) {
    if (&rhs != this)
        copy(rhs, head_, num_rows_, num_columns_);
    return *this;
}

void SparseMatrix::copy(const SparseMatrix& rhs, row_node*& head, int& num_rows, int& num_columns) {
    num_rows = rhs.num_rows_;
    num_columns = rhs.num_columns_;
    if (rhs.num_rows_ == 0 || rhs.num_columns_ == 0) return;
    row_node* curr = head = new row_node;
    row_node* other_head = rhs.head_;
    while (other_head != nullptr) {
        cell_node* rhs_cell = other_head->cell;
        cell_node* my_cell = nullptr;
        while (rhs_cell != nullptr) {
            cell_node* new_cell = new cell_node(rhs_cell->column, rhs_cell->value);
            if (my_cell == nullptr) my_cell = curr->cell = new_cell;
            else {
                my_cell->right = new_cell;
                my_cell->right->left = my_cell;
                my_cell = my_cell->right;
            }
            rhs_cell = rhs_cell->right;
        }
        if (other_head->down != nullptr) {
            curr->down = new row_node;
            curr = curr->down;
        }
        other_head = other_head->down;
    }
}

// Helper function that takes a linked list matrix and returns its transpose
row_node* transpose(row_node* head, int num_rows, int num_columns) {

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
                while (add_temp) {
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

void SparseMatrix::row_mul(row_node* &lhs_row, SparseMatrix& rhs_t, row_node* &res_row) {
    //  lhs_row: a row_node pointer pointing to the row of lhs to be multiplied
    //  rhs_t: a SparseMatrix object containing the transposed version of the right-hand-side matrix to be multiplied
    //  res_row: a row_node pointer pointing to the corresponding row of the result matrix where the resulting (1xn) matrix will be added

    //std::lock_guard<mutex> lock(mutexx);
    cell_node* lhs_curr_cell = lhs_row->cell;
    row_node* rhs_curr_row = rhs_t.head_;
    cell_node* rhs_curr_cell = rhs_t.head_->cell;
    cell_node* res_curr_cell = nullptr;
    bool is_row_empty = true;

    // iterate over the columns of rhs
    for (int result_col = 0; result_col < rhs_t.num_rows_; result_col++)
    {
        is_row_empty = true;

        // Perform multiplication of the column of rhs by row of lhs
        while (lhs_curr_cell && rhs_curr_cell)
        {

            // for each product of multiplication, initialize a variable to store its value
            int product = 0;
            if (lhs_curr_cell->column == rhs_curr_cell->column)
            {
                product = lhs_curr_cell->value * rhs_curr_cell->value;
                if (!res_row->cell)
                {
                    res_row->cell = new cell_node;
                    res_curr_cell = res_row->cell;
                    res_curr_cell->value = 0;
                    res_curr_cell->column = result_col;
                    res_curr_cell->left = res_curr_cell->right = nullptr;
                }
                res_curr_cell->value += product;
                rhs_curr_cell = rhs_curr_cell->right;
                lhs_curr_cell = lhs_curr_cell->right;
                is_row_empty = false;
            }
            else if (lhs_curr_cell->column > rhs_curr_cell->column)
            {
                rhs_curr_cell = rhs_curr_cell->right;
            }
            else
            {
                lhs_curr_cell = lhs_curr_cell->right;
            }
        }

        // If the row of products has at least one member, add another cell at the end of the row of results
        if (!is_row_empty)
        {
            cell_node* tmp = res_curr_cell;
            res_curr_cell->right = new cell_node;
            res_curr_cell = res_curr_cell->right;
            res_curr_cell->value = 0;
            res_curr_cell->column = result_col + 1;
            res_curr_cell->left = tmp;
            res_curr_cell->right = nullptr;
        }
        lhs_curr_cell = lhs_row->cell;
        rhs_curr_row = rhs_curr_row->down;
        if (rhs_curr_row)  rhs_curr_cell = rhs_curr_row->cell;
    }

}

// Matrix multiplication member function that multiplies two matrices in a multithreaded fashion
SparseMatrix SparseMatrix::mat_mul(const SparseMatrix& rhs) const {


    // create an empty matrix that has the desired size
    row_node* res_head = new row_node;
    SparseMatrix res(res_head, this->num_rows_, rhs.num_columns_);
    {
        row_node* res_temp = res_head;
        for (int i = 0; i < num_rows_ - 1; i++)
        {
            res_temp->down = new row_node;
            res_temp = res_temp->down;
            res_temp->down = nullptr;
        }
    }

    // Take the transpose of rhs for the sake of iterating more easily (rhs_t will be referred to as rhs from now on)
    SparseMatrix rhs_t(transpose(rhs.head_, rhs.num_rows_, rhs.num_columns_), rhs.num_columns_, rhs.num_rows_);

    // Create a vector of threads
    vector<thread> threads;

    // Divide lhs, rhs and res by their rows, we will multiply each row of lhs by rhs
    const int num_threads = num_rows_;

    // Store the a row pointer to every row of lhs and res in seperate vectors
    vector<row_node*> rows_lhs, rows_res;
    row_node* temp_ptr = head_;
    while (temp_ptr)
    {
        rows_lhs.push_back(temp_ptr);
        temp_ptr = temp_ptr->down;
    }
    temp_ptr = res.head_;
    while (temp_ptr)
    {
        rows_res.push_back(temp_ptr);
        temp_ptr = temp_ptr->down;
    }

    // Start multiplication
    for (int i = 0; i < num_threads; i++)
    {
        threads.emplace_back(thread(&SparseMatrix::row_mul, ref(rows_lhs[i]), ref(rhs_t), ref(rows_res[i])));
    }

    // Join all threads
    for (auto& thread : threads)
    {
        thread.join();
    }


    // A tiny snippet of code that takes care of the extra empty cell at the end of each row
    {
        row_node* temp_row = res.head_;
        while (temp_row)
        {
            cell_node* temp_cell = temp_row->cell;

            while (temp_cell)
            {
                if (temp_cell->value == 0)
                {
                    temp_cell->left->right = nullptr;
                    delete temp_cell;
                    break;
                }
                temp_cell = temp_cell->right;

            }
            temp_row = temp_row->down;
        }
    }

    return res;
}
