/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   N_puzzle.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 17:54:23 by wlin              #+#    #+#             */
/*   Updated: 2018/02/06 18:22:28 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "N_puzzle.hpp"

int			myrandom (int i) {
	return rand()%i;
}

Position	find_start(const IntMatrix &state) {
	for (int y = 0; y < (int)state.size(); y++) {
		for (int x = 0; x < (int)state.size(); x++) {
			if (state[y][x] == 0)
				return (Position(x,y));
		}
	}
	throw "error: no starting position found";
}

string hash_state(const IntMatrix &state) {
	string state_hash = "";

	for (int i = 0; i < (int)state.size(); i++) {
		for (int j = 0; j < (int)state.size(); j++) {
			state_hash += to_string(state[i][j]);
		}
	}
	return state_hash;
	
}

IntMatrix	generate_random(int size) {
	IntMatrix rand_puzzle = vector< vector<int> >(size, vector<int>(size, 0));
	vector<int> rvalues((size*size), 0);
	for (int i = 0; i < (size*size); i++)
		rvalues[i] = i;
	random_shuffle(rvalues.begin(), rvalues.end(), myrandom);
	vector<int>::iterator it = rvalues.begin();
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++)
			(rand_puzzle)[y][x] = *it++;
	}
	return (rand_puzzle);
}

IntMatrix	*generate_solution(int size) {
	IntMatrix *solution =  new vector< vector<int> >(size, vector<int>(size,0));
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

vector<Position> *generate_solution_htbl(const IntMatrix &solution) {
	vector<Position> *solution_htbl;
	int size = (solution.size() * solution.size());
	solution_htbl = new vector<Position>(size, Position(0,0));
	for (int y = 0; y < (int)solution.size(); y++) {
		for (int x = 0; x < (int)solution.size(); x++) {
			(*solution_htbl)[solution[y][x]] = Position(x,y);
		}
	}
	return (solution_htbl);
}

static int getInvCount(IntMatrix state, int size)  {
	int	array[size * size];
	int	n = 0;
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			array[y * size + x] = state[y][x];
		}
	}
	for (int i = 0; i < size * size; i++) {
		for (int j = i + 1; j < size * size; j++) {
			if (array[i] && array[j] && array[i] > array[j]) {
				n++;
			}
		}
	}
	return (n);
}

static int findXPosition(IntMatrix &state) {
    for (int i = state.size() - 1; i >= 0; i--) {
        for (int j = state.size() - 1; j >= 0; j--) {
            if (state[i][j] == 0)
                return state.size() - i;
		}
	}
	throw "error: no start position";
}

bool isSolvable(IntMatrix state) {

    // int invCount = getInvCount(flatten(state), flatten(solution), state.size());
	int invCount = getInvCount(state, state.size());
    if (state.size() & 1)
        return (invCount & 1);
    else
    {
        int pos = findXPosition(state);
        if (pos & 1)
            return !(invCount & 1);
        else
            return invCount & 1;
    }
}
