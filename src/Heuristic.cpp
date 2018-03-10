/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Heuristic.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 12:06:56 by wlin              #+#    #+#             */
/*   Updated: 2018/02/03 18:22:22 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Heuristic.hpp"
using namespace std;

int	Manhattan::distance(const IntMatrix &state, const vector<Position> &solution_htbl) {
	int h = 0;

	for (int y = 0; y < (int)state.size(); y++) {
		for (int x = 0; x < (int)state.size(); x++) {
			if (state[y][x] == 0)
				continue;
			Position end = solution_htbl[state[y][x]];
			h += (abs(x - end.x) + abs(y - end.y));
		}
	}
	return (h);
}

int Hamming::distance(const IntMatrix &state, const vector<Position> &solution_htbl) {
	int h = 0;

	for (int y = 0; y < (int)state.size(); y++) {
		for (int x = 0; x < (int)state.size(); x++) {
			if (state[y][x] == 0)
				continue;
			Position goalPos = solution_htbl[state[y][x]];
			if (goalPos.y != y && goalPos.x != x)
				h++;
		}
	}
	return (h);
}

int	row_conflict(const Position &p_curr, const IntMatrix &state, const vector<Position> &solution_htbl) {
	int row_conflict = 0;
	Position p_goal = solution_htbl[state[p_curr.y][p_curr.x]];

	for (int x = p_curr.x + 1;  x < (int)state.size(); x++) {
		if (state[p_curr.y][x] == 0)
			continue;
		Position r_curr = Position(x,p_curr.y);
		Position r_goal = solution_htbl[state[r_curr.y][r_curr.x]];
		if ((p_curr.y == r_curr.y) && (p_goal.y == r_goal.y)) {
			if ((r_goal.x <= p_curr.x) && (p_curr.x <= r_curr.x))
				row_conflict++;
		}
	}
	return (row_conflict);
}

int	col_conflict(const Position &p_curr, const IntMatrix &state, const vector<Position> &solution_htbl) {
	int col_conflict = 0;
	Position p_goal = solution_htbl[state[p_curr.y][p_curr.x]];

	for (int y = p_curr.y + 1;  y < (int)state.size(); y++) {
		if (state[y][p_curr.x] == 0)
			continue;
		Position c_curr = Position(p_curr.x,y);
		Position c_goal = solution_htbl[state[c_curr.y][c_curr.x]];
		if ((p_curr.x == c_curr.x) && (p_goal.x == c_goal.x)) {
			if ((c_goal.y <= p_curr.y) && (p_curr.y <= c_curr.y)) {
				col_conflict++;
			}
		}
	}
	return (col_conflict);
}

int Linear::distance(const IntMatrix &state, const vector<Position> &solution_htbl) {
	int conflicts = 0;
	Manhattan man_h;

	for (int y = 0; y < (int)state.size(); y++) {
		for (int x = 0; x < (int)state.size(); x++) {
			if (state[y][x] == 0)
				continue;
			Position curr = Position(x,y);
			conflicts += row_conflict(curr, state, solution_htbl);
			conflicts += col_conflict(curr, state, solution_htbl);
		}
	}
	return (man_h.distance(state, solution_htbl) + (2 * conflicts));
}
