/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 15:29:01 by wlin              #+#    #+#             */
/*   Updated: 2018/02/06 18:23:43 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "N_puzzle.hpp"
#include "Puzzle.hpp"
#include "Heuristic.hpp"
#include "Astar.hpp"


void		display_usage(void) {
	cout
		<< "usage: ./n_puzzle [-mlh] [-sf] [size | filepath]" << endl << endl
		<< "\theuristics:" << endl
		<< "\t\t-m\tManhattan distance" << endl
		<< "\t\t-l\tLinear conflict distance" << endl
		<< "\t\t-h\tHamming distance" << endl
		<< "\tinput:" << endl
		<< "\t\t-s\tsize of puzzle" << endl
		<< "\t\t-f\tinput file path" << endl;
}

IHeuristic	*parse_heuristic(char *flag) {
	string h_flag(flag);
	if (h_flag == "-m")
		return (new Manhattan());
	else if (h_flag == "-l")
		return (new Linear());
	else if (h_flag == "-h")
		return (new Hamming());
	else
		throw "error: invalid heuristic";
}

IntMatrix	parse_puzzle(char *filename) {
	regex row_regex("([0-9]+[space| ]){4}([\n]|([#](.*)?))");
	regex size_regex("-?[0-9]+");
	regex cmnt_regex("[#](.*)?");

	size_t p_size = 0;
	string line;
	vector<vector<int> > input;;
	set<int> numbers;
	pair<set<int>::iterator,bool> ret;
	ifstream f (filename);

	if (!f.is_open())
		throw "error: cannot open file";
	else {
		while (getline(f, line)) {
			vector<int> row;
			istringstream iss(line);
			istream_iterator<string> it(iss);
			istream_iterator<string> eos;
			if (regex_search(line, row_regex) || regex_search(line, size_regex)) {
				for (; it != eos; ) {
					if (it->front() == '#')
						break ;
					int nbr = stoi(*it++);
					row.push_back(nbr);
				}
			}
			else if (regex_search(line, cmnt_regex) || line.find_first_not_of("\t\n ") == string::npos)
				continue;
			else
				throw "error: invalid syntax";
			if (row.size() == 1 && p_size == 0) {
				if (row.front() >= 3)
					p_size = row[0];
				else
					throw "error: invalid size definition";
			}
			else if (row.size() >= 3 && row.size() == p_size && p_size != 0) {
				vector<int>::iterator it;
				for (it = row.begin(); it != row.end(); it++) {
					ret = numbers.insert(*it);
					if ((*ret.first) < 0 || (*ret.first) > (int)(p_size*p_size-1))
						throw "error: invalid value";
					else if (!ret.second)
						throw "error: duplication";
				}
				input.push_back(row);
			}
			else
				throw "error: invalid row size";
		}
		if (input.size() == p_size) {
			f.close();
			return (input);
		}
		else
			throw "error: invalid dimensions";
	}
}

Puzzle		*input_mode(char *flag, char *input) {
	regex		nbr_regex("-?[0-9]+");
	string		mode(flag);
	string		mode_arg(input);
	IntMatrix	input_puzzle;

	if (mode == "-s" && regex_match(mode_arg, nbr_regex)) {
		int p_size = stoi(mode_arg);
		if (p_size < 3)
			throw "error: invalid size";
		cout << "Generating random puzzle..." << endl;
		input_puzzle = generate_random(p_size);
	}
	else if (mode == "-f")
		input_puzzle = parse_puzzle(input);
	else
		throw "error: invalid input mode";
	return (new Puzzle(input_puzzle, find_start(input_puzzle), NULL));
}

int main (int argc, char **argv) {
	Astar					a_star;
	Puzzle					*start;
	IntMatrix				*solution;
	vector<Position>		*solution_htbl;

	srand (time(NULL));
	if (argc != 4) {
		display_usage();
		return (0);
	}
	
	else {
		try {
			a_star.set_heuristic(parse_heuristic(argv[1]));
			start = input_mode(argv[2], argv[3]);
		}
		catch (char const *msg) {
			cout << msg << endl;
			return (-1);
		}
	}
	
	solution = generate_solution(start->get_state().size());
	solution_htbl = generate_solution_htbl(*solution);

	if (!isSolvable(start->get_state())) {
		cout << "error: cannot solve" << endl;
		return (0);
	}
	else
		a_star.search(start, *solution, *solution_htbl);
	delete solution;
	delete solution_htbl;
	delete start;
	return 0;
}
