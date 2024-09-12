/*
 *this code write by b11215033
 *not allow and not responsible for any plagiarism
 * */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
using namespace std;

bool in(int num, vector<int> list) {
	for (int i: list) {
		if (num == i) {
			return true;
		}
	}
	return false;
}

class Node {
public:
	int num;
	int value;
	string name;
	Node* th;
	Node* el;
	Node() {
		value = -1;
		name = "";
		th = NULL;
		el = NULL;
	}
	bool operator==(Node x) {
		if (value == x.value) {
			if (name == x.name) {
				if (th == NULL && el == NULL && x.th == NULL && x.el == NULL) {
					return true;
				}
				else {
					return *th == *x.th && *el == *x.el;
				}
			}
		}
		return false;
	}
};

Node zero;
Node one;

namespace BDD {
	int num_now = 0;
	Node tree;
	int input_size;
	int output_size;
	vector<string> name_list;
	string func_name;
	vector<string> solution_list;
	int get_solution(string solution, int first_reg = 1) {
		if (first_reg) {
			if (solution.length() != input_size) {
				return 0;
			}
			for (int i = 0; i < input_size; i++) {
				if (solution[i] != '0' && solution[i] != '1' && solution[i] != '-') {
					return -1;
				}
			}
		}
		for (int i = 0; i < input_size; i++) {
			if (solution[i] == '-') {
				solution[i] = '0';
				get_solution(solution, 0);
				solution[i] = '1';
				get_solution(solution, 0);
				return 1;
			}
		}

		solution_list.push_back(solution);

		return 1;
	}
	int compute(string solution) {
		for (string i: solution_list) {
			if (i == solution) {
				return 1;
			}
		}
		return 0;
	}
	int make_tree(Node* x = NULL, int times = 0, string solution = "") {
		num_now++;
		if (!times) {
			x = &tree;
		}
		if (times < input_size - 1) {
			x->num = num_now;

			x->th = new Node();
			x->el = new Node();
			
			x->name = name_list[times];
			
			solution.push_back('0');
			make_tree(x->el, times + 1, solution);
			solution.pop_back();
			
			solution.push_back('1');
			make_tree(x->th, times + 1, solution);
		}
		if (times == input_size - 1) {
			x->name = name_list[times];
			x->num = num_now;
			solution.push_back('1');
			if (compute(solution)) {
				x->th = &one;
			}
			else {
				x->th = &zero;
			}
			solution.pop_back();
			solution.push_back('0');
			if (compute(solution)) {
				x->el = &one;
			}
			else {
				x->el = &zero;
			}
		}
		return 1;
	}
	string get_link_data(Node* x = NULL) {
		string result = "";
		if (!x) {
			x = &tree;
		}
		if (x->value != -1) {
			result.append("solusi ");
			result.append(to_string(x->value));
			result.append("\n");
			return result;
		}
		result.append(x->name);
		result.append(" 0");
		result.push_back(' ');
		result.append(to_string(x->num));
		result.append(" ");
		result.append(get_link_data(x->el));
		
		result.append(x->name);
		result.append(" 1");
		result.push_back(' ');
		result.append(to_string(x->num));
		result.append(" ");
		result.append(get_link_data(x->th));
		
		return result;
	}
	int make_easy(Node* x = NULL) {
		if (!x) {
			x = &tree;
		}
		if (x->value != -1) {
			return 0;
		}
		
		if (make_easy(x->th)) {
			Node* pointer_temp = x->th->th;
			delete x->th;
			x->th = pointer_temp;
		}
		if (make_easy(x->el)) {
			Node* pointer_temp = x->el->th;
			delete x->el;
			x->el = pointer_temp;
		}

		if (*x->th == *x->el) {
			if (x->th != &zero && x->th != &one) {
				delete x->th;
			}
			x->th = x->el;
			return 1;
		}
		return 0;
	}
	void print_out(Node* x = NULL) {
		if (!x) {
			x = &tree;
		}
		if (x->value != -1) {
			cout << x->value << endl;
			return;
		}
		cout << x->name << "->";
		print_out(x->th);
		cout << x->name << "->";
		print_out(x->el);
	}
	string transfer(string file_name) {
		string result = "digraph ";
		result.append(file_name);
		result.append(" {\n");
		
		string name_data = get_link_data();

		vector<vector<int>> rank_list(input_size, vector<int>(0));
		istringstream rankstream(name_data);
		string name;
		while (rankstream >> name) {
			int number;
			int bool_value;
			if (name == "solusi") {
				rankstream >> bool_value;
			}
			else {
				for (int i = 0; i < input_size; i++) {
					if (name_list[i] == name) {
						rankstream >> bool_value;
						rankstream >> number;
						if (!in(number, rank_list[i])) {
							rank_list[i].push_back(number);
						}
						break;
					}
				}
			}
		}

		for (vector<int> l: rank_list) {
			result.append("\t{rank=same");
			for (int i: l) {
				result.append(" ");
				result.append(to_string(i));
			}
			result.append("}\n");
		}
		
		result.push_back('\n');

		result.append("\t0 [label=\"0\", shape=box]\n");
		
		istringstream namestream(name_data);
		vector<int> create_list;
		int max_num = 0;
		while (namestream >> name) {
			int number;
			int bool_value;
			if (name == "solusi") {
				namestream >> number;
			}
			else {
				namestream >> bool_value;
				namestream >> number;
				if (number > max_num) {
					max_num = number;
				}
				if (in(number, create_list)) {
					continue;
				}
				create_list.push_back(number);
				result.append("\t");
				result.append(to_string(number));
				result.append(" [label=\"");
				result.append(name);
				result.append("\"]\n");
			}
		}

		max_num++;
		
		result.append("\t");
		result.append(to_string(max_num));
		result.append(" [label=\"1\", shape=box];\n\n");

		int last_bool_value = -1;
		int last_number = 0;
		istringstream linkstream(name_data);
		while (linkstream >> name) {
			int number;
			int bool_value;
			if (!last_number) {
				linkstream >> last_bool_value;
				linkstream >> last_number;
				continue;
			}
			result.append("\t");
			if (name == "solusi") {
				linkstream >> bool_value;
				result.append(to_string(last_number));
				result.append(" -> ");
				if (bool_value) {
					result.append(to_string(max_num));
				}
				else {
					result.append("0");
				}
				result.append(" [label=\"");
				result.append(to_string(last_bool_value));
				if (last_bool_value) {
					result.append("\", style=solid]\n");
				}
				else {
					result.append("\", style=dotted]\n");
				}
				last_bool_value = -1;
				last_number = 0;
			}
			else {
				linkstream >> bool_value;
				linkstream >> number;
				
				result.append(to_string(last_number));
				result.append(" -> ");
				result.append(to_string(number));
				result.append(" [label=\"");
				result.append(to_string(last_bool_value));
				if (last_bool_value) {
					result.append("\", style=solid]\n");
				}
				else {
					result.append("\", style=dotted]\n");
				}
				last_bool_value = bool_value;
				last_number = number;
			}
		}

		result.push_back('}');

		return result;
	}
}

int main(int argc, char* argv[]) {
	zero.value = 0;
	one.value = 1;

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
		if (!op.length()) {
			continue;
		}
		
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
                    if (name[i] < 65 || 90 < name[i] && name[i] < 97 || name[i] > 122) {
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
				if (!solution.length()) {
					i--;
					continue;
				}
				int solution_status = BDD::get_solution(solution);
				if (solution_status == 0) {
					cout << "not accept solution " << solution << endl;
					return -5;
				}
				if (solution_status == -1) {
					cout << "only accept 0 1 - : " << solution << endl;
					return -6;
				}
			}
			for (string i: BDD::solution_list){
				cout << i << " ";
			}
			cout << endl;
		}
		else if (op == ".e") {
			cout << "compile finish" << endl;
			break;
		}
		else {
			cout << "unknow op :" << op << endl;
			return -7;
		}
	}
	
	BDD::make_tree();
	BDD::make_easy();
	BDD::print_out();

	src.close();

	ofstream trg;
	trg.open(argv[2], ios::ate);
	
	string file_name = "";
	for (int i =0; i < sizeof(argv[2]) / sizeof(char); i++) {
		if (argv[2][i] == '/') {
			file_name = "";
		}
		if (argv[2][i] == '.') {
			break;
		}
		file_name.push_back(argv[2][i]);
	}

	string transfer = BDD::transfer(file_name);

	trg.write(transfer.c_str(), transfer.length());
	
	trg.close();

	return 1;
}