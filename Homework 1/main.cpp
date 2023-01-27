// CS 204 Homework 1
// Written by Bilgehan Bilgin

#ifdef _DEBUG
	/*#define DEBUG1
	#define DEBUG2*/
#include <chrono>
#endif

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdlib.h>
using namespace std;


void input(string &LHS_filename, string &RHS_filename, string &RES_filename, string &output_filename){

	cout << "Enter LHS matrix filename: " << endl;
	cin >> LHS_filename;
	cout << "Enter RHS matrix filename: " << endl;
	cin >> RHS_filename;
	cout << "Enter RES filename: " << endl;
	cin >> RES_filename;
	cout << "Enter output filename: " << endl;
	cin >> output_filename;
}

void throw_error(string output_filename, ofstream &output_file){

	cout << "Error!" << endl;
	output_file.open(output_filename.c_str(), ios::out);
	output_file << "Error";
	output_file.close();

	exit(0);

}

vector<vector<int> > create_LHS(string LHS_filename, ifstream &LHS_file, string output_filename, ofstream &output_file ){
	string value, r, c, line;
	int line_num  = 0;
	vector<int> size(2);
	vector<int> tmp;

	// open files
	LHS_file.open(LHS_filename.c_str(), ios::in);

	if(LHS_file.fail()){
		LHS_file.close();
					cout << "lhs fail"<< endl;

		throw_error(output_filename, output_file);
	}

	// get the first two elements of matrix, indicating its size
	getline(LHS_file, line);
	stringstream line_str(line);
	line_str >> r;
	size[0] = stoi(r); // num of rows
	line_str >> c;
	size[1] = stoi(c); // num of columns

	// create the LHS matrix with given dimensions
	vector<vector<int> > LHS(1);
	while(getline(LHS_file, line)){
		stringstream line_str(line);
			 while(line_str >> value){
				// check if value is in range [1, 9] or -1
				if(!((stoi(value) > 0 && stoi(value) < 10) || stoi(value) == -1)){
										cout << "lhs value range error"<< endl;

					throw_error(output_filename, output_file);
				}
				LHS[line_num].push_back(stoi(value));
			}
	
		if (!LHS_file.eof()){
			LHS.push_back(tmp);
		}
		line_num++;



	}

	// check if size of the given vector matches the specified values
		// check for num of rows
		if(size[0] != LHS.size()){
								cout << "lhs row size error"<< endl;

		LHS_file.close();

		throw_error(output_filename, output_file);
		}
		// check for num of columns
		for (int i = 0; i < LHS.size() - 1; i++){
			int temp2 = LHS[i].size();
			int temp1 = LHS[i + 1].size();
			if (temp1 != temp2 || temp1 != size[1]){
				LHS_file.close();
				cout << "lhs column size error"<< endl;

				throw_error(output_filename, output_file);
			}
		}

	// close the files
	LHS_file.close();
	

	// return matrix
	return LHS;
}

vector<vector<int> > create_RHS(string RHS_filename, ifstream &RHS_file, string output_filename, ofstream &output_file ){
	string value, r, c, line;		// r for number of rows, c for number of columns
	int line_num = 0;
	vector<int> size(2);
	vector<int> tmp;

	// open files
	RHS_file.open(RHS_filename.c_str(), ios::in);

	if(RHS_file.fail()){

		RHS_file.close();

				cout << "rhs fail"<< endl;

		throw_error(output_filename, output_file);
	}

	// get the first two elements of matrix, indicating its size
	getline(RHS_file, line);
	stringstream line_str(line);
	line_str >> r;
	size[0] = stoi(r); // num of rows
	line_str >> c;
	size[1] = stoi(c); // num of columns
	// throw error if num of columns is not equal to 1
	if (size[1] != 1){
			cout << "rhs column size error"<< endl;

		throw_error(output_filename, output_file);}

	// create the RHS matrix with given dimensions
	vector<vector<int> > RHS(1);
	while(getline(RHS_file, line)){
		stringstream line_str(line);
			 while(line_str >> value){
				// check if value is in range [1, 9] or -1
				if(!(stoi(value) > 0 && stoi(value) < 10)){
					cout << "rhs value error"<< endl;
					throw_error(output_filename, output_file);
				}
				
				RHS[line_num].push_back(stoi(value));
			}
	
		if (!RHS_file.eof()){
			RHS.push_back(tmp);
		}
		line_num++;



	}

	// check if size of the given vector matches the specified values
		// check for num of rows
		if(size[0] != RHS.size()){
			RHS_file.close();
				cout << "rhs row size error"<< endl;

		throw_error(output_filename, output_file);
		}
		// check for num of columns
		if(RHS[0].size() != 1){
			cout << "rhs column size error"<< endl;

			throw_error(output_filename, output_file);
}
		

	// close the files
	RHS_file.close();
	

	// return matrix
	return RHS;
}

vector<vector<int> > create_RES(string RES_filename, ifstream &RES_file, string output_filename, ofstream &output_file ){
	string value, r, c, line;
	int j = 0;
	vector<int> size(2);
	vector<int> tmp;

	// open files
	RES_file.open(RES_filename.c_str(), ios::in);

	if(RES_file.fail()){

		RES_file.close();
		throw_error(output_filename, output_file);
	}

	// get the first two elements of matrix, indicating its size
	getline(RES_file, line);
	stringstream line_str(line);
	line_str >> r;
	size[0] = stoi(r); // num of rows
	line_str >> c;
	size[1] = stoi(c); // num of columns
	// throw error if num of columns is not equal to 1
	if (size[1] != 1){
		cout << "res column size error"<< endl;
		throw_error(output_filename, output_file);}

	// create the RES matrix with given dimensions
	vector<vector<int> > RES(1);
	while(getline(RES_file, line)){
		stringstream line_str(line);
			 while(line_str >> value){
					if(!(stoi(value) >= 1)){
							cout << "res value error"<< endl;
						throw_error(output_filename, output_file);
					}
					RES[j].push_back(stoi(value));
			 }
	
			if (!RES_file.eof()){
				RES.push_back(tmp);
			}
			j++;

	}

	
	
	// check if size of the given vector matches the specified values
		// check for num of rows
		if(size[0] != RES.size()){
				cout << "res row size error"<< endl;

			RES_file.close();
			throw_error(output_filename, output_file);
		}
		// check for num of columns
		if(RES[0].size() != 1){
					cout << "res column size error"<< endl;

				throw_error(output_filename, output_file);
			}
		

	// close the files
	RES_file.close();
	

	// return matrix
	return RES;
}

bool solved(vector<int> &x, vector<int> &coef, vector<vector<int> > RHS, vector<vector<int> > LHS, vector<vector<int> > RES, int j, int &flag, string &num_str, int &total){

	// add up the left side of the equation
	total = 0;
	for (int k = 0; k < x.size(); k++){
		total += x[k]*coef[k];
	}

	// check equality and set flags accordingly
	if(total == RES[j][0]){
		flag = 0;
		return 0;	 // answer found, don't enter the while loop
	}
	else if(total > RES[j][0]){
		flag = 2;
		return 1;
	}
	else{
		flag = 1;
		return 1;
	}
}

vector<vector<int> > get_var_positions(vector<vector<int> > LHS){

	int height = LHS.size();
	int length = LHS[0].size();
	int num_of_unknowns = 0;
	int l = 0;
	vector<vector<int> > results;
	vector<int> empty_vector;

	for (int i = 0; i < height; i++){
		for (int j = 0; j < length; j++){
			if (LHS[i][j] == -1) {

					results.push_back(empty_vector);
					num_of_unknowns++;
					results[l].push_back(i);
					results[l].push_back(j);
					results[l].push_back(-1);
					l++;
				}
			}
		}

	return results;
}

void add_one(vector<int> &x, int last_digit, int range){
	for(int i = 0; i < range; i++){
		if(x[last_digit-i] != 9){
			x[last_digit-i]++;
			break;
		}
		else{
			x[last_digit-i] = 1;
		}
	}	
}

int main(){

	string LHS_filename, RHS_filename, RES_filename, output_filename;
	vector<vector <int> > LHS, RES, RHS;
	ifstream LHS_file, RHS_file, RES_file;
	ofstream output_file;

	// take filenames as input
	input(LHS_filename, RHS_filename, RES_filename, output_filename);

#ifdef _DEBUG
	auto start = chrono::system_clock::now();
#endif

	// create LHS, RHS, RES matrices
	LHS = create_LHS(LHS_filename, LHS_file,  output_filename, output_file);
	RHS = create_RHS(RHS_filename, RHS_file,  output_filename, output_file);
	RES = create_RES(RES_filename, RES_file,  output_filename, output_file);


	int flag, no_var = 0, total, last_digit;
	vector<int> coef, x;
	string total_num, num_str;

	// first, subtract known values from the right side of the equation
	for (int k = 0; k < LHS.size(); k++){
		for (int i = 0; i < LHS[k].size(); i++){
			if (LHS[k][i] != -1){
				RES[k][0] -= LHS[k][i] * RHS[i][0];
			}
		}
	}

	// start trial-error by iterating row by row
	for (int j = 0; j < LHS.size(); j++){

	// calculate the number of unknowns in the current line
		for (int l = 0; l < LHS[j].size(); l++){
			if(LHS[j][l] == -1){
				no_var++;
			}
		}

		
		// create the initial search value (111...1)
		num_str = string(no_var, '1');
		last_digit = no_var - 1;

		
		// add elements of the num to vector x
		x.clear();
		for (int i = 0; i < num_str.length(); i++){
			x.push_back(num_str[i] -'0');
		}

		// add coefficients of the equation to vector coef
		coef.clear();
		for (int i = 0; i < RHS.size(); i++){
			if(LHS[j][i] == -1){
			coef.push_back(RHS[i][0]);
			}

		}
		

		if(x.size() > 0){
		while(solved(x, coef, RHS, LHS, RES, j, flag, num_str, total)){

			// just increment by 1
			if(flag == 1){
				if(x[last_digit] == 9){
					// add one without exceeding the limit [1, 9] if last digit is 9
					add_one(x, last_digit, x.size());
				}
				else{
					x[last_digit]++;
				}
			}

			//	for better performance, skip to the next digit if (row . vector) is greater than result
			else if(flag == 2){
				x[last_digit] = 1;	// skip to the next digit
				if(x[last_digit-1] == 9){
					// add one without exceeding the limit [1, 9]
					add_one(x, last_digit-1, x.size()-1);
				}
			else{
				x[last_digit-1]++;}
			}
#ifdef _DEBUG
		for(int i = 0; i < x.size(); i++){
		cout << x[i] << " ";
		}
		cout << endl;
#endif
		}
		}


		for(int i = 0; i < x.size(); i++){
		total_num += x[i] + '0';
		}

		num_str = "";		// reset search value string
		no_var = 0;		// reset variable count
}

	// since we started from the lowest possible value and incremented
	//  by 1, total_num must also be the smallest possible solution.

	// assemble the result vector using coordinates of the unknowns and result int.
	vector<vector<int> > result_vector = get_var_positions(LHS);
	for (int i = 0; i < total_num.length(); i++){
		result_vector[i][2] = total_num[i] - '0';
	}


	// write the results into the output file
	output_file.open(output_filename.c_str(), ios::out);
	for(int m = 0; m < result_vector.size() ; m++){
		string new_line = "";
		for (int k = 0; k < result_vector[m].size() ; k++){
			new_line += to_string(result_vector[m][k]) + " ";
		}
		new_line.pop_back();
		output_file << new_line;
		output_file << endl;
	}

#ifdef _DEBUG
	auto end = chrono::system_clock::now();
	cout << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;
#endif

	return 0;
}


	
