/*
 *this code write by b11215033
 *not allow and not responsible for any plagiarism
 * */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

namespace BDD {
	int input_size;
	int output_size;
	vector<string> name_list;
	string func_name;
	vector<string> solution_list;
}

int main(int argc, char* argv[]) {

	if (argc != 3) {
		cout << "only accept two input" << endl;
		return -1;
	}
	
	ifstream src;
	src.open(argv[1], ios::in);
	
	string order;
	while (getline(src, order)) {

		string op;
		istringstream orderstream(order);

		orderstream >> op;
		
		if (op[0] == '#') {
			continue;
		}
		else if (op == ".i") {
			orderstream >> BDD::input_size;
			cout << "get " << BDD::input_size << " input" << endl;
		}
		else if (op == ".o") {
			orderstream >> BDD::output_size;
			cout << "get " << BDD::output_size << " output" << endl;
		}
		else if (op == ".ilb") {
			string name;
			while (orderstream >> name) {
				for (int i = 0; i < name.length(); i++) {
                         	       if (i < 65 || i > 90 && i < 97 || i > 122) {
                                	        cout << "only accept big or small english letter: " << name << endl;
                                        	return -3;
                                	}
                        	}
				BDD::name_list.push_back(name);
			}
			if (BDD::name_list.size() != BDD::input_size) {
				cout << ".ilb amount not correct" << endl;
				return -4;
			}
                }
		else if (op == ".ob") {
			orderstream >> BDD::func_name;
			cout << "set function name " << BDD::func_name << endl;
                }
		else if (op == ".p") {
			int times;
			orderstream >> times;
			for (int i = 0; i < times; i++) {
				string solution;
				getline(src, solution);
				istringstream solutionstream(solution);
				solutionstream >> solution;
				if (solution.length() != BDD::input_size) {
					cout << "not accept solution " << solution << endl;
					return -5;
				}
				BDD::solution_list.push_back(solution);
			}
		}
		else if (op == ".e") {
			cout << "compile finish" << endl;
			break;
		}
		else {
			cout << "unknow op" << endl;
			return -6;
		}
	}

	src.close();

	return 1;
}
