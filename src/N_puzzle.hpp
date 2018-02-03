/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   N_puzzle.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 14:37:16 by wlin              #+#    #+#             */
/*   Updated: 2018/02/02 18:03:16 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef N_PUZZLE_HPP
# define N_PUZZLE_HPP

#include <vector>
#include <iostream>
#include <fstream>
#include <ios>
#include <string>
#include <cstring>
#include <set>
#include <exception>
#include <sstream>
#include <iomanip>
#include <regex>

typedef std::vector< std::vector<int> > IntMatrix;

struct Position {
	int x;
	int y;
	Position(int x, int y) : x(x), y(y) {}
	Position(Position const &src) {*this = src;}
};

extern IntMatrix *solution;
extern std::vector<Position> *solution_htbl;

void	display_solutions(void);

int						myrandom (int i);
void	 				move_states(IntMatrix &state, const Position &p1, const Position &p2);
Position				find_start(const IntMatrix &state);
IntMatrix				*generate_random(int size);
IntMatrix				*generate_solution(int size);
std::vector<Position>	*generate_solution_htbl(const IntMatrix &solution);
IntMatrix				*parse_puzzle(char *filename);

#endif
