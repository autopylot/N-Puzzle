/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   N_puzzle.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 17:54:23 by wlin              #+#    #+#             */
/*   Updated: 2018/02/02 12:55:03 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "N_puzzle.hpp"

int			myrandom (int i) {
	return std::rand()%i;
}

void	 	move_states(IntMatrix &state, const Position &p1, const Position &p2) {
 		int tmp = state[p1.y][p1.x];
 		state[p1.y][p1.x] = state[p2.y][p2.x];
 		state[p2.y][p2.x] = tmp;
 }

Position	find_start(const IntMatrix &state) {
	for (int y = 0; y < state.size(); y++) {
		for (int x = 0; x < state.size(); x++) {
			if (state[y][x] == 0)
				return (Position(x,y));
		}
	}
	throw "error: no starting position found";
}

IntMatrix	*generate_random(int size) {
	IntMatrix *rand_puzzle =  new std::vector< std::vector<int> >(size, std::vector<int>(size, 0));
	std::vector<int> rvalues((size*size), 0);
	for (int i = 0; i < (size*size); i++)
		rvalues[i] = i;
	std::random_shuffle(rvalues.begin(), rvalues.end(), myrandom);
	std::vector<int>::iterator it = rvalues.begin();
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++)
			(*rand_puzzle)[y][x] = *it++;
	}
	return (rand_puzzle);
}

IntMatrix	*generate_solution(int size) {
	IntMatrix *solution =  new std::vector< std::vector<int> >(size, std::vector<int>(size,0));
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
