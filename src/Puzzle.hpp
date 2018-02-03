/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Puzzle.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 15:22:40 by wlin              #+#    #+#             */
/*   Updated: 2018/02/02 18:02:42 by wlin             ###   ########.fr       */
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
#include <unistd.h>
#include "N_puzzle.hpp"
#include "Heuristic.hpp"

class	Puzzle {
	private:
		const int		_size;
		Position		_start;
		IntMatrix		&_state;
		Puzzle			*_parent;
		int				_g;
		int				_h;
		int				_f;
		std::vector<Position>	*generate_moves(void);
		IntMatrix				*clone_state(void);
		int						within_bounds(Position const &pos);

	public:
		// static IntMatrix				*solution;
		// static  std::vector<Position>	*solution_htbl;
		// Puzzle(int size);
		Puzzle(IntMatrix &state, Position start, Puzzle *parent);
		~Puzzle(void);
		Puzzle					&operator = (const Puzzle &src);
		bool					operator < (const Puzzle &rhs);

		void					display(void);
		void					calculate_costs(IHeuristic &heuristic);
		std::list<Puzzle*>		*generate_successors(void);
		void					trace_path(void);

		int						get_f(void) const {return this->_f;}
		int						get_g(void) const {return this->_g;}
		int						get_h(void) const {return this->_h;}
		Position				get_start(void) const {return this->_start;}
		IntMatrix				&get_state(void) const {return this->_state;}
		Puzzle					*get_parent(void) const {return this->_parent;}
		bool					cmp_g(Puzzle *rhs) {return this->_g < rhs->_g;}
};

#endif
