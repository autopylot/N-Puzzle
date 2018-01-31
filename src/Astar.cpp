/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Astar.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 13:02:49 by wlin              #+#    #+#             */
/*   Updated: 2018/01/30 15:31:55 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <deque>
#include <queue>
#include "Puzzle.hpp"
#include "Astar.hpp"

// Puzzle	*AstarPQ::visited_state(Puzzle *curr)
// {
// 	std::deque<Puzzle*>::iterator it = this->begin();
//
// 	for (it; it != this->end(); it++)
// 	{
// 		if (curr->_state == (*it)->_state)
// 			return (*it);
// 	}
// 	return (NULL);
// }
//
Astar::Astar(void) : _selected_states(0), _max_states(0), _total_moves(0) {}

Astar::~Astar(void) {

}

// void	Astar::search(Puzzle *start) {
// 	std::AstarPQ<Puzzle*, std::vector<Puzzle*> > open;
// 	std::AstarPQ<Puzzle*, std::vector<Puzzle*> > closed;
//
// 	open.push(start);
// 	while (!open.empty()) {
// 		Puzzle *curr = open.top();
// 		this->add_selected();
// 		this->set_max_states(open.size() + closed.size());
// 		open.pop();
// 		closed.push(curr);
//
// 		std::list<Puzzle*> *successors = curr->generate_successors();
// 		std::list<Puzzle*>::iterator it;
//
// 		for (it = successors->begin(); it != successors->end(); it++) {
// 			Puzzle *visited;
//
// 			(*it)->calculate_costs(*_heuristic);
//
// 			if (*it == ::solution)
// 				this->set_total_mv(*it->trace_path());
//
// 			if ((visited = open.visited_state(*it)) && (*it)->cmp_g(visited)) {
// 				open.erase(visited);
// 			}
// 			if ((visited = closed.visited_state(*it) && (*it)->cmp_g(visited)) {
// 				closed.erase(visited);
// 			}
// 			if (!open.visited_state(*it) && !closed.visited_state(*it))
// 				open.push(*it);
// 			}
//
// 	}
// 	throw "error: failure";
// }
