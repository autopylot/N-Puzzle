/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Puzzle.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 15:22:40 by wlin              #+#    #+#             */
/*   Updated: 2018/02/03 18:19:59 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUZZLE_HPP
# define PUZZLE_HPP

#include <iostream>
#include <vector>
#include <list>
#include <iomanip>
#include "N_puzzle.hpp"
#include "Heuristic.hpp"

using namespace std;

class	Puzzle {
	private:
		const int		_size;
		Position		_start;
		IntMatrix		_state;
		Puzzle			*_parent;
		string			_stateHash;
		int				_g;
		int				_h;
		int				_f;

		vector<Position>		generate_moves(void);
		IntMatrix				*clone_state(void);
		bool					within_bounds(int x, int y);
		void	 				update_state(const Position &p1, const Position &p2);
		

	public:
		Puzzle(IntMatrix &state, Position start, Puzzle *parent);
		~Puzzle(void);

		void					display(void);
		void					calculate_costs(IHeuristic &heuristic, const vector<Position> &solution_htbl);
		void					trace_path(void);
		vector<Puzzle*>			*generate_successors(void);
		int						get_f(void) const {return this->_f;}
		int						get_g(void) const {return this->_g;}
		int						get_h(void) const {return this->_h;}
		Position				get_start(void) const {return this->_start;}
		IntMatrix				get_state(void) const {return this->_state;}
		Puzzle					*get_parent(void) const {return this->_parent;}
		string					get_hash(void) const {return this->_stateHash;}
};

#endif
