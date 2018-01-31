/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   N_puzzle.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 14:37:16 by wlin              #+#    #+#             */
/*   Updated: 2018/01/30 15:28:39 by wlin             ###   ########.fr       */
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

typedef std::vector< std::vector<int> > IntMatrix;

struct Position {
	int x;
	int y;
	Position(int x, int y) : x(x), y(y) {}
	Position(Position const &src) {*this = src;}
};

IntMatrix	*parse_puzzle(char *filename);

extern IntMatrix *solution;
extern std::vector<Position> *solution_htbl;

#endif
