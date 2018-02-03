/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Astar.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 13:02:49 by wlin              #+#    #+#             */
/*   Updated: 2018/02/02 19:23:36 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Astar.hpp"

AstarPQ::AstarPQ(void) : std::priority_queue<Puzzle*, std::vector<Puzzle*> >() {

}

AstarPQ::~AstarPQ(void) {

}

AstarPQ::iterator AstarPQ::visited_state(Puzzle &curr)
{
	AstarPQ::iterator it;

	for (it = this->begin(); it != this->end(); it++)
	{
		if (curr.get_state() == (*it)->get_state())
			return (it);
	}
	return (it);
}

Astar::Astar(void) :
_selected_states(0),
_max_states(0),
_total_moves(0),
_heuristic(NULL) {}

Astar::~Astar(void) {

}

void	Astar::search(Puzzle *start) {
	AstarPQ open;
	AstarPQ closed;

	start->calculate_costs(*_heuristic);
	open.push(start);
	while (!open.empty()) {
		Puzzle *curr = open.top();
		open.pop();
		closed.push(curr);
		if (curr->get_state() == (*::solution)) {
			std::cout << "solution found" << std::endl;
			return ;
		}
		std::list<Puzzle*> *successors = curr->generate_successors();
		std::list<Puzzle*>::iterator it;
		for (it = successors->begin(); it != successors->end(); it++) {
			AstarPQ::iterator in_open;
			AstarPQ::iterator in_closed;
			(*it)->calculate_costs(*_heuristic);
			in_open = open.visited_state(**it);
			in_closed = closed.visited_state(**it);
			(*it)->display();
			// if (visited_closed != closed.end())
			// 	continue;
			// std::cout << "done with closed" << std::endl;
			// if (open.visited_state(*it) == open.end())
			// 	open.push(*it);
			// std::cout << "done with open" << std::endl;
			// if (open.visited_state(*it) != open.end()) {
			// 	std::cout << "found" << std::endl;
			// 	if ((*it)->cmp_g(*(open.visited_state(*it)))) {
			// 		open.erase(visited_open);
			// 		open.push(*it);
			// 	}
			// }
			if (in_open != open.end() && (*it)->cmp_g(*in_open)) {
				std::cout << "child g cost lower than open state" << std::endl;
				open.erase(in_open);
				// *visited_open = *it;
				// open.insert()
			}
			if (in_closed != closed.end() && (*it)->cmp_g(*in_closed)) {
				std::cout << "child g cost lower than closed state" << std::endl;
				// *visited_closed = *it;
				// open.push(*visited_closed);
				closed.erase(in_closed);
				in_closed = closed.end();
			}
			if (in_open == open.end() && in_closed == closed.end())
				open.push(*it);
			std::cout << "done with childrens" << std::endl;
		}

		delete successors;
	}
	std::cout << "error: failure" << std::endl;
}
