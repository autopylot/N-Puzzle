/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Puzzle.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 16:12:00 by wlin              #+#    #+#             */
/*   Updated: 2018/02/02 18:11:23 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Puzzle.hpp"

// Puzzle::Puzzle(int size) : _size(size),
// 	_state(*(generate_random(size))),
// 	_start(*(this->find_start())) {
// 	std::cout << "construct okay" << std::endl;
// 	_parent = NULL;
// 	_g = _h = _f = 0;
// }

Puzzle::Puzzle(IntMatrix &state, Position start, Puzzle *parent) :
	_size(state.size()),
	_start(start),
	_state(state),
	_parent(parent) {
	_g = _h = _f = 0;
}

Puzzle::~Puzzle(void) {
	// free ref _state
}

Puzzle	&Puzzle::operator = (const Puzzle &src) {
	_start = src._start;
	_state = src._state;
	_parent = src._parent;
	_g = src._g;
	_h = src._h;
	_f = src._f;
	return (*this);
}

bool	Puzzle::operator < (const Puzzle &rhs) {
	return this->_f < rhs._f;
}

void Puzzle::trace_path(void) {
	Puzzle *trace = _parent;

	while (trace) {
		trace->display();
		trace = trace->get_parent();
	}
}

void	Puzzle::calculate_costs(IHeuristic &heuristic) {
	_g = (_parent ? _parent->_g + 1 : 0);
	_h = heuristic.distance(_state);
	_f = _g + _h;
}

void	Puzzle::display(void) {
	for (int y = 0; y < _size; y++) {
		for (int x = 0; x < _size; x++) {
			std::cout << std::setw(3) << _state[y][x];
		}
		std::cout << std::endl;
	}
	std::cout << "Starting position: " << _start.y << " , " << _start.x << std::endl;
	std::cout << "g cost: " << _g << std::endl;
	std::cout << "h cost: " << _h << std::endl;
	std::cout << "f cost: " << _f << std::endl;
	std::cout << std::endl;
 }

std::vector<Position> *Puzzle::generate_moves(void) {
	std::vector<Position> *child_moves = new std::vector<Position>;

	child_moves->push_back(Position(_start.x + 1, _start.y));
	child_moves->push_back(Position(_start.x - 1, _start.y));
	child_moves->push_back(Position(_start.x, _start.y + 1));
	child_moves->push_back(Position(_start.x, _start.y - 1));
	return (child_moves);
}

int		Puzzle::within_bounds(Position const &pos) {
	return ((pos.x > -1 && pos.x < _size) && (pos.y > -1 && pos.y < _size));
}

IntMatrix *Puzzle::clone_state(void) {
	IntMatrix *clone = new std::vector< std::vector<int> >(_size, std::vector<int>(_size, 0));

	for (int y = 0; y < _size; y++) {
		for (int x = 0; x < _size; x++) {
			(*clone)[y][x] = _state[y][x];
		}
	}
	return (clone);
}

std::list<Puzzle*> *Puzzle::generate_successors(void) {
	std::list<Puzzle*> *successors = new std::list<Puzzle*>;
	std::vector<Position> *moves = this->generate_moves();
	std::vector<Position>::iterator it;

	for (it = moves->begin(); it != moves->end(); it++) {
		if (this->within_bounds((*it)))
		{
			IntMatrix *child_state = this->clone_state();
			move_states(*child_state, _start, *it);
			Puzzle *child_puzzle =  new Puzzle(*child_state, *it, this);
			successors->push_back(child_puzzle);
		}
	}
	delete moves;
	return (successors);
}
