/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Astar.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 18:40:26 by wlin              #+#    #+#             */
/*   Updated: 2018/02/02 18:25:53 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef A_STAR_HPP
# define A_STAR_HPP

#include <deque>
#include <queue>
#include "Puzzle.hpp"


class	 AstarPQ : public std::priority_queue<Puzzle*, std::vector<Puzzle*> > {
	public:
		typedef std::vector<Puzzle*>::iterator iterator;
		AstarPQ(void);
		~AstarPQ(void);

		iterator visited_state(Puzzle &curr);
		iterator begin(void) {
			return iterator(this->c.begin());
		};
		iterator end(void) {
			return iterator(this->c.end());
		};
		iterator	erase(iterator p) {
			return (this->c.erase(p));
		}
};

class	Astar {
	private:
		int			_selected_states;
		int			_max_states;
		int			_total_moves;
		IHeuristic	*_heuristic;
	public:
		Astar(void);
		~Astar(void);

		void			set_heuristic(IHeuristic *h) {this->_heuristic = h;}
		IHeuristic		*get_heuristic(void) {return this->_heuristic;}
		void			search(Puzzle *start);

		// void	add_selected(void) {_selected_states++;}
		// void	set_max_state(int max) {
		// 	if (max > _max_states)
		// 		_max_states = max;
		// }
};


#endif
