/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Astar.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 18:40:26 by wlin              #+#    #+#             */
/*   Updated: 2018/02/05 14:06:15 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef A_STAR_HPP
# define A_STAR_HPP

#include <queue>
#include <map>
#include <vector>
#include <algorithm>
#include "Puzzle.hpp"
#include "N_puzzle.hpp"
using namespace std;

class IHeuristic;

struct cmpHash {
	bool operator() (const Puzzle *lhs, const Puzzle *rhs) const {
		return lhs->get_hash() < rhs->get_hash();
	}
};

struct cmpPuzzle {
	bool operator() (const Puzzle *p1, const Puzzle *p2) const {
		if (p1->get_f() != p2->get_f())
			return p1->get_f() > p2->get_f();
		else
			return p1->get_g() > p2->get_g();
	}
};

class	 AstarPQ : public priority_queue<Puzzle*, vector<Puzzle*>, cmpPuzzle > {
	public:
		typedef vector<Puzzle*>::iterator iterator;
		AstarPQ(void) : priority_queue<Puzzle*, vector<Puzzle*>, cmpPuzzle >() {};
		~AstarPQ(void) {};

		iterator	find_state(Puzzle &curr);
		iterator	begin(void) {
			return iterator(this->c.begin());
		}
		iterator	end(void) {
			return iterator(this->c.end());
		}
		iterator	erase(iterator p) {
			return (this->c.erase(p));
		}
		
};

class	Astar {
	private:
		int			_selected_states;
		int			_max_states;
		IHeuristic	*_heuristic;
	public:
		Astar(void) : _selected_states(0), _max_states(0), _heuristic(NULL) {};
		~Astar(void) {delete _heuristic;}


		void			add_selected(void) {_selected_states++;}
		void			set_max_state(int max) {
			if (max > _max_states)
				_max_states = max;
		}

		void			set_heuristic(IHeuristic *h) {_heuristic = h;}
		IHeuristic		*get_heuristic(void) {return _heuristic;}
		void			search(Puzzle *start, IntMatrix &solution, vector<Position> &solution_htbl);
};

#endif
