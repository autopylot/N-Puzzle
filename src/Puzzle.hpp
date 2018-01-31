/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Puzzle.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 15:22:40 by wlin              #+#    #+#             */
/*   Updated: 2018/01/31 14:38:35 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUZZLE_HPP
# define PUZZLE_HPP

#include <iostream>
#include <algorithm>
#include <array>
#include <random>
#include <chrono>
#include <vector>
#include <list>
#include <iomanip>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "N_puzzle.hpp"
#include "Heuristic.hpp"

class	Puzzle {
	protected:
		const int		_size;
		const Position	_start;
		const IntMatrix	&_state;
		Puzzle			*_parent;
		int				_g;
		int				_h;
		int				_f;

	public:
		// Puzzle(int size);
		Puzzle(const IntMatrix &state, const Position start, Puzzle *parent);
		~Puzzle(void);

		void					display(void);

		IntMatrix				*clone_state(void);
		std::list<Puzzle*>		*generate_successors(void);
		std::vector<Position*>	*generate_moves(void);

		void					calculate_costs(IHeuristic &heuristic);
		int						within_bounds(Position const &pos);

		int						get_f(void) const {return this->_f;}
		int						get_g(void) const {return this->_g;}
		int						cmp_g(Puzzle const &src) const {return this->_g < src._g;}
		IntMatrix				get_state(void) const {return this->_state;}

		bool					operator < (Puzzle const &rhs) {
			return this->_f < rhs._f;}

		bool					operator == (Puzzle const &rhs) {
			return this->_state == rhs._state;}
};

Position				find_start(void);
void					move_states(IntMatrix &state, Position const &p1, Position const &p2);
IntMatrix				*generate_solution(int size);
IntMatrix				*generate_random(int size);
std::vector<Position>	*generate_solution_htbl(const IntMatrix &solution);

#endif
