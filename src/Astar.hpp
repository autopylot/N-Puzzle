/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Astar.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 18:40:26 by wlin              #+#    #+#             */
/*   Updated: 2018/01/31 14:02:33 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef A_STAR_HPP
# define A_STAR_HPP

#include <deque>
#include <queue>
#include "Puzzle.hpp"

// template<
// 		class T,
// 		class Container = std::vector<T>,
// 		class Compare = std::less<typename Container::value_type> >
// class	 AstarPQ : public std::priority_queue<T, Container, Compare> {
// 	public:
// 		typedef typename std::priority_queue<T, Container, Compare>::iterator iterator;
// 		iterator begin(void) const {
// 			return iterator(this->c.begin());
// 		};
// 		iterator end(void) const {
// 			return iterator(this->c.end());
// 		};
// 		Puzzle	*visited_state(Puzzle const &curr);
// };


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
		// void	search(Puzzle *start);
		// void	add_selected(void) {_selected_states++;}
		// void	set_max_state(int max) {
		// 	if (max > _max_states)
		// 		_max_states = max;
		// }
};


#endif
