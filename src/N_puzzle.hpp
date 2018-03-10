/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   N_puzzle.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 14:37:16 by wlin              #+#    #+#             */
/*   Updated: 2018/02/05 23:16:51 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef N_PUZZLE_HPP
# define N_PUZZLE_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <fstream>
#include <sstream>
#include <regex>
#include <random>
#include <time.h>
using namespace std;

typedef vector< vector<int> > IntMatrix;

struct Position {
	int x;
	int y;
	Position(int x, int y) : x(x), y(y) {}
	Position(Position const &src) {*this = src;}
};

int						myrandom (int i);
Position				find_start(const IntMatrix &state);
IntMatrix				generate_random(int size);
IntMatrix				*generate_solution(int size);
std::vector<Position>	*generate_solution_htbl(const IntMatrix &solution);
bool 					isSolvable(IntMatrix state);
string					hash_state(const IntMatrix &state);

#endif
