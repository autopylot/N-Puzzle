/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Puzzle.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 16:12:00 by wlin              #+#    #+#             */
/*   Updated: 2018/01/31 14:40:43 by wlin             ###   ########.fr       */
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

Puzzle::Puzzle(IntMatrix const &state, Position const start, Puzzle *parent) :
	_size(state.size()),
	_start(start),
	_state(state) {
	_parent = parent;
	_g = _h = _f = 0;
}

Puzzle::~Puzzle(void) {

}

void	Puzzle::calculate_costs(IHeuristic &heuristic) {
	_g = (_parent ? _parent->get_g() + 1 : 0);
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
	std::vector<Position*> *child_moves = new std::vector<Position*>;

	child_moves->push_back(Position(_start.x + 1, _start.y));
	child_moves->push_back(Position(_start.x - 1, _start.y));
	child_moves->push_back(Position(_start.x, _start.y + 1));
	child_moves->push_back(Position(_start.x, _start.y - 1));
	return (child_moves);
}

int		Puzzle::within_bounds(Position const &pos) {
	return ((pos.x > -1 && pos.x < _size) && (pos.y > -1 && pos.y < _size));
}

void	 move_states(IntMatrix &state, Position const &p1, Position const &p2) {
 		int tmp = state[p1.y][p1.x];
 		state[p1.y][p1.x] = state[p2.y][p2.x];
 		state[p2.y][p2.x] = tmp;
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
	std::vector<Position*> *moves = this->generate_moves();
	std::vector<Position*>::iterator ite = moves->end();

	for (std::vector<Position*>::iterator it = moves->begin(); it != ite; it++) {
		if (this->within_bounds(*(*it)))
		{
			IntMatrix *child_state = this->clone_state();
			move_states(*child_state, _start, *(*it));
			Puzzle *child_puzzle =  new Puzzle(*const_cast<IntMatrix*>(child_state), *(*it), this);
			successors->push_back(child_puzzle);
		}
		else
			delete *it;
	}
	delete moves;
	return (successors);
}

static int			myrandom (int i) {
	return std::rand()%i;
}

IntMatrix *generate_random(int size) {
	IntMatrix *rand_puzzle =  new std::vector< std::vector<int> >(size, std::vector<int>(size, 0));
	std::vector<int> rvalues((size*size), 0);
	for (int i = 0; i < (size*size); i++)
		rvalues[i] = i;
	std::random_shuffle(rvalues.begin(), rvalues.end(), myrandom);
	std::vector<int>::iterator it = rvalues.begin();
	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
			(*rand_puzzle)[y][x] = *it++;
	}
	return (rand_puzzle);
}

IntMatrix *generate_solution(int size) {
	IntMatrix *solution =  new std::vector< std::vector<int> >(size, std::vector<int>(size));

	int number = 1;
	int loop = 0;
	int layers = size - 1;
	while (1) {
		if (layers-- > 0) {
			for (int rx = 0 + loop; rx < size - loop; rx++)
				(*solution)[loop][rx] = number++;
			for (int ry = loop + 1; ry < size - loop; ry++)
				(*solution)[ry][size - loop - 1] = number++;
		}
		if (layers-- > 0) {
			for (int lx = size - loop - 2; lx > -1 + loop; lx--)
				(*solution)[size - loop - 1][lx] = number++;
			for (int ly = size - loop - 2; ly > loop; ly--)
				(*solution)[ly][loop] = number++;
		}
		if (layers > 0)
			loop++;
		else
			break;
	}
	return (solution);
}

Position	find_start(void) {
	for (int y = 0; y < _size; y++) {
		for (int x = 0; x < _size; x++) {
			if (_state[y][x] == 0)
				return (Position(x,y));
		}
	}
	throw "error: no starting position found";
}

std::vector<Position> *generate_solution_htbl(const IntMatrix &solution) {
	std::vector<Position> *solution_htbl;
	int size = (solution.size() * solution.size());
	solution_htbl = new std::vector<Position>(size, Position(0,0));
	for (int y = 0; y < solution.size(); y++) {
		for (int x = 0; x < solution.size(); x++) {
			(*solution_htbl)[solution[y][x]] = Position(x,y);
		}
	}
	return (solution_htbl);
}
