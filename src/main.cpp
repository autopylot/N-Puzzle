/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 15:29:01 by wlin              #+#    #+#             */
/*   Updated: 2018/01/31 14:36:31 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "N_puzzle.hpp"
#include "Puzzle.hpp"
#include "Heuristic.hpp"
#include "Astar.hpp"
#include <regex>

int g_size = 0;
IntMatrix *solution = NULL;
std::vector<Position> *solution_htbl = NULL;


void	display_usage(void) {
	std::cout
		<< "usage: ./n_puzzle [-mlh] size | filename"
		<< std::endl
		<< "\trequired:"
		<< std::endl
		<< "\t\t size of puzzle or input file"
		<< std::endl
		<< "\theuristics:"
		<< std::endl
		<< "\t\t-m\tManhattan distance"
		<< std::endl
		<< "\t\t-l\tLinear conflict distance"
		<< std::endl
		<< "\t\t-h\tHamming distance"
		<< std::endl;
}

IHeuristic *parse_heuristic(char *flag) {
		std::string h_flag(flag);
		if (h_flag == "-m")
			return (new Manhattan());
		else if (h_flag == "-l")
			return (new Linear());
		else if (h_flag == "-h")
			return (new Hamming());
		else
			throw "error: invalid heuristic";
}

IntMatrix	*parse_puzzle(char *filename) {
	int p_size = 0;
	std::string line;
	std::vector< std::vector<int> > *input = new std::vector< std::vector<int> >;
	std::set<int> numbers;
	std::pair<std::set<int>::iterator,bool> ret;
	std::ifstream f (filename);
	if (!f.is_open())
		throw "error: cannot open file";
	else {
		while (std::getline(f, line)) {
			std::vector<int> row;
			std::istringstream iss(line);
			std::istream_iterator<std::string> it(iss);
			std::istream_iterator<std::string> eos;
			std::regex row_regex("([0-9]+[space| ]){4}([\n]|([#](.*)?))");
			std::regex size_regex("-?[0-9]+");
			std::regex cmnt_regex("[#](.*)?");

			if (std::regex_search(line, row_regex) || std::regex_search(line, size_regex)) {
				for (; it != eos; ) {
					if (it->front() == '#')
						break ;
					int nbr = std::stoi(*it++);
					row.push_back(nbr);
				}
			}
			else if (std::regex_search(line, cmnt_regex) || line.find_first_not_of("\t\n ") == std::string::npos)
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
				std::vector<int>::iterator it;
				for (it = row.begin(); it != row.end(); it++) {
					ret = numbers.insert(*it);
					if ((*ret.first) < 0 || (*ret.first) > (p_size*p_size-1))
						throw "error: invalid value";
					else if (!ret.second)
						throw "error: duplication";
				}
				input->push_back(row);
			}
			else
				throw "error: invalid row size";
		}
		if (input->size() == p_size) {
			g_size = p_size;
			f.close();
			return (input);
		}
		else
			throw "error: invalid dimensions";
	}
}

Puzzle	*input_mode(char *s) {
	std::string	input(s);
	std::regex	nbr_regex("-?[0-9]+");
	IntMatrix	*input_puzzle;

	if (std::regex_search(input, nbr_regex)) {
		g_size = std::stoi(input);
		if (g_size < 3)
			throw "error: invalid size";
		// return (new Puzzle(g_size));
		input_puzzle = generate_solution(g_size);
	}
	else
		input_puzzle = parse_puzzle(s);
	return (new Puzzle(*input_puzzle, find_start(*input_puzzle), NULL));

}

int main (int argc, char **argv)
{
	Astar	a_star;
	Puzzle	*start;

	std::srand ( unsigned ( std::time(0) ) );
	if (argc != 3) {
		display_usage();
		return (0);
	}
	else {
		try {
			a_star.set_heuristic((parse_heuristic(argv[1])));
			start = input_mode(argv[2]);
		}
		catch (char const *msg) {
			std::cout << msg << std::endl;
			return (-1);
		}
	}
	solution = generate_random(g_size);
	solution_htbl = generate_solution_htbl(*solution);
	start->calculate_costs(*(a_star.get_heuristic()));
	start->display();

	// a_start.search(start);
}
