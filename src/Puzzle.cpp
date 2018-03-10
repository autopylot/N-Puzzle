/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Puzzle.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 16:12:00 by wlin              #+#    #+#             */
/*   Updated: 2018/02/05 14:36:42 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Puzzle.hpp"

Puzzle::Puzzle(IntMatrix &state, Position start, Puzzle *parent) :
	_size(state.size()),
	_start(start),
	_state(state),
	_parent(parent),
	_stateHash(hash_state(state)) {
	_g = (_parent != NULL ? _parent->get_g() + 1 : 0);
	_h = _f = 0;
}

Puzzle::~Puzzle(void) {
	
}


void Puzzle::trace_path(void) {
	Puzzle *trace = _parent;

	this->display();
	while (trace) {
		trace->display();
		trace = trace->get_parent();
	}
}

void	Puzzle::calculate_costs(IHeuristic &heuristic, const vector<Position> &solution_htbl) {
	_h = heuristic.distance(_state, solution_htbl);
	_f = _g + _h;
}

void	Puzzle::display(void) {
	for (int y = 0; y < _size; y++) {
		for (vector<int>::iterator it = _state[y].begin(); it != _state[y].end(); it++) {
			cout << setw(3) << *it;
		}
		cout << endl;
	}
	cout << endl;
	cout << "( " << _start.y << " , " << _start.x << " ); "
				<< "g cost: " << _g << "; "
				<< "h cost: " << _h << "; "
				<< "f cost: " << _f << endl;
	cout << endl;
}

bool		Puzzle::within_bounds(int x, int y) {
	return ((x > -1 && x < _size) && (y > -1 && y < _size));
}

vector<Position> Puzzle::generate_moves(void) {
	vector<Position> child_moves;
	vector<Position> nextPosition;

	nextPosition.push_back(Position(1,0));
	nextPosition.push_back(Position(-1,0));
	nextPosition.push_back(Position(0,1));
	nextPosition.push_back(Position(0,-1));

	for (vector<Position>::iterator move = nextPosition.begin(); move != nextPosition.end(); move++) {
		if (this->within_bounds(_start.x + (*move).x, _start.y + (*move).y))
			child_moves.push_back(Position(_start.x + (*move).x, _start.y + (*move).y));
	}
	return (child_moves);
}

IntMatrix *Puzzle::clone_state(void) {
	IntMatrix *clone = new vector< vector<int> >(_size, vector<int>(_size, 0));

	for (int y = 0; y < _size; y++) {
		for (int x = 0; x < _size; x++) {
			(*clone)[y][x] = _state[y][x];
		}
	}
	return (clone);
}

void	 	Puzzle::update_state(const Position &p1, const Position &p2) {
 		int tmp = _state[p1.y][p1.x];
 		_state[p1.y][p1.x] = _state[p2.y][p2.x];
 		_state[p2.y][p2.x] = tmp;
		_stateHash = hash_state(_state);
}

vector<Puzzle*> *Puzzle::generate_successors(void) {
	vector<Puzzle*> *successors = new vector<Puzzle*>;
	vector<Position> moves = this->generate_moves();

	for (vector<Position>::iterator nextMove = moves.begin(); nextMove != moves.end(); nextMove++) {
		// IntMatrix *child_state = this->clone_state();
		// Puzzle *child_puzzle =  new Puzzle(*child_state, *nextMove, this);
		Puzzle *child_puzzle =  new Puzzle(_state, *nextMove, this);
		child_puzzle->update_state(_start, *nextMove);
		successors->push_back(child_puzzle);
	}
	return (successors);
}
