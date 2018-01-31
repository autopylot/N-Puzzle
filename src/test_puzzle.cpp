/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_puzzle.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 12:10:50 by wlin              #+#    #+#             */
/*   Updated: 2018/01/30 15:13:14 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Puzzle.hpp"
#include "Heuristic.hpp"

int size = 4;
IntMatrix *solution = generate_solution(size);
std::vector<Position> *solution_htbl = generate_solution_htbl(*solution);

// void	display_usage(void) {
// 	std::cout
// 		<< "usage: ./n_puzzle [-mlh] size | filename"
// 		<< std::endl
// 		<< "\trequired:"
// 		<< std::endl
// 		<< "\t\t size of puzzle or input file"
// 		<< std::endl
// 		<< "\theuristics:"
// 		<< std::endl
// 		<< "\t\t-m\tManhattan distance"
// 		<< std::endl
// 		<< "\t\t-l\tLinear conflict distance"
// 		<< std::endl
// 		<< "\t\t-h\tHamming distance"
// 		<< std::endl;
// }
//
// IHeuristic *parse_heuristic(char *flag) {
// 		if (flag == "-m")
// 			return (new Manhattan());
// 		else if (flag == "-l")
// 			return (new Linear());
// 		else if (flag == "-h")
// 			return (new Hamming());
// 		else
// 			throw "error: invalid heuristic";
// }
//
// Puzzle	*which_input(char *s) {
// 	std::string input(s);
// 	std::ifstream f(input);
//
// 	try {
// 		if (f.is_open())
// 			return (parse_puzzle(f));
// 		else {
// 			int size = std::stoi(input);
// 			if (size < 3)
// 				throw "error: invalid puzzle size";
// 			return (new Puzzle(size));
// 		}
// 	}
// 	catch (char const *msg) {
// 		std::cout << msg << std::endl;
// 		exit (-1);
// 	}
// }
//
// IntMatrix	*parse_puzzle(char *filename) {
// 	int p_size = 0;
// 	std::string line;
// 	std::vector< std::vector<int> > *input = new std::vector< std::vector<int> >;
//
// 	std::set<int> numbers;
// 	std::pair<std::set<int>::iterator,bool> ret;
// 	std::ifstream f (filename);
//
// 	if (f.is_open()) {
// 		while (std::getline(f, line)) {
// 			std::vector<int> row;
// 			std::istringstream iss(line);
// 			std::istream_iterator<std::string> it(iss);
// 			std::istream_iterator<std::string> eos;
//
// 			for (; it != eos; ) {
// 				int nbr;
// 				if ((*it).find_first_of("#") != std::string::npos)
// 					break ;
// 				try {
// 					nbr = std::stoi(*it);
// 				}
// 				catch (std::exception const &e) {
// 					std::cout << "error: invalid input" << std::endl;
// 					exit(-1);
// 				}
// 				row.push_back(nbr);
// 				it++;
// 			}
// 			if (row.size() == 1) {
// 				if (p_size == 0 && row[0] >= 3)
// 					p_size = row[0];
// 				else if (p_size != 0 && row[0] >= 3)
// 					throw "error: redefinition of size";
// 				else
// 					throw "error: invalid size";
// 			}
// 			else if (row.size() >= 3 && row.size() == p_size && p_size != 0) {
// 				std::vector<int>::iterator it;
// 				for (it = row.begin(); it != row.end(); it++) {
// 					ret = numbers.insert(*it);
// 					if ((*ret.first) < 0 || (*ret.first) > (p_size*p_size-1))
// 						throw "error: invalid value";
// 					else if (!ret.second)
// 						throw "error: duplication";
// 				}
// 				input->push_back(row);
// 			}
// 			else
// 				throw "error: invalid row size";
// 		}
// 		if (input->size() == p_size) {
// 			std::cout << input->size() << std::endl;
// 			return (input);
// 		}
// 		else
// 			throw "error: invalid dimensions";
// 	}
// 	else
// 		throw "error: cannot open file";
// }

int main ()
{
	std::srand(time(NULL));

	IHeuristic *man_h = new Manhattan();
	IHeuristic *lin_h = new Linear();
	IHeuristic *ham_h = new Hamming();


	Puzzle test_rand(size);
	Puzzle test_sol(*solution, Position(0,0) , NULL);

	std::vector<Puzzle*> open;

	std::cout << (test_rand == test_sol) << std::endl;
	std::cout << (test_rand < test_sol) << std::endl;
	test_sol.display();
	test_rand.display();
	test_rand.calculate_costs(*ham_h);
	test_rand.display();
	std::list<Puzzle*> *test_child = test_rand.generate_successors();
	for (std::list<Puzzle*>::iterator it = test_child->begin(); it != test_child->end(); it++) {
		(*it)->calculate_costs(*ham_h);
		(*it)->display();
		open.push_back(*it);
	}
	Puzzle *visit = open.front();

	test_child = visit->generate_successors();
	for (std::list<Puzzle*>::iterator it = test_child->begin(); it != test_child->end(); it++) {
		(*it)->calculate_costs(*ham_h);
		(*it)->display();
		open.push_back(*it);
	}
}
