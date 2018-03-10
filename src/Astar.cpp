/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Astar.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 13:02:49 by wlin              #+#    #+#             */
/*   Updated: 2018/02/06 15:07:30 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Astar.hpp"
using namespace std;

AstarPQ::iterator AstarPQ::find_state(Puzzle &curr) {
	AstarPQ::iterator it;

	for (it = this->begin(); it != this->end(); it++) {
		if (curr.get_hash() == (*it)->get_hash())
			return (it);
	}
	return (it);
}

void	Astar::search(Puzzle *start, IntMatrix &solution, vector<Position> &solution_htbl) {
	AstarPQ					open;
	set<Puzzle*, cmpHash>	closed;
	map<string, int> 		visitedOpen;
	map<string, int>		visitedClosed;

	cout << "Starting search..." << endl;
	
	start->calculate_costs(*_heuristic, solution_htbl);
	open.push(start);
	visitedOpen[start->get_hash()] = 0;

	while (!open.empty()) {
		Puzzle *curr = open.top();
		open.pop();
		closed.insert(curr);
		visitedClosed[curr->get_hash()] = curr->get_g();
		this->add_selected();
		this->set_max_state(open.size() + closed.size());

		if (curr->get_state() == solution) {
			curr->trace_path();
			cout << "Total number of selected states: " << _selected_states << endl;
			cout << "Maximum number of states: " << _max_states << endl;
			cout << "Number of moves required: " << curr->get_g() << endl;
			for (AstarPQ::iterator it = open.begin(); it != open.end(); it++)
				delete *it;
			for (set<Puzzle*, cmpHash>::iterator it = closed.begin(); it != closed.begin(); it++)
				delete *it;
			return ;
		}

		vector<Puzzle*> *successors = curr->generate_successors();
		for (vector<Puzzle*>::iterator neighbor = successors->begin(); neighbor != successors->end(); neighbor++) {
			(*neighbor)->calculate_costs(*_heuristic, solution_htbl);
			
			if ((*neighbor)->get_g() < visitedOpen[(*neighbor)->get_hash()]) {
				visitedOpen[(*neighbor)->get_hash()] = 0;
				if (open.find_state(**neighbor) != open.end())
					open.erase(open.find_state(**neighbor));
			}

			if ((*neighbor)->get_g() < visitedClosed[(*neighbor)->get_hash()]) {
				visitedClosed[(*neighbor)->get_hash()] = 0;
				closed.erase(closed.find(*neighbor));
			}
			
			if (visitedOpen[(*neighbor)->get_hash()] == 0 && visitedClosed[(*neighbor)->get_hash()] == 0) {
				open.push(*neighbor);
				visitedOpen[(*neighbor)->get_hash()] = (*neighbor)->get_g();
			}

			else
				delete *neighbor;
		}
		delete successors;
	}
	cout << "error: failure" << endl;
}
