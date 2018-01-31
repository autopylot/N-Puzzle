/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Heuristic.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 12:06:56 by wlin              #+#    #+#             */
/*   Updated: 2018/01/31 14:01:00 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Heuristic.hpp"

int	Manhattan::distance(const IntMatrix &state) {
	int h = 0;
	for (int y = 0; y < state.size(); y++)
	{
		for (int x = 0; x < state.size(); x++) {
			if (state[y][x] == 0)
				continue;
			Position end = (*::solution_htbl)[state[y][x]];
			h += (abs(x - end.x) + abs(y - end.y));
		}
	}
	return (h);
}

int Hamming::distance(const IntMatrix &state) {
	int h = 0;
	for (int y = 0; y < state.size(); y++) {
		for (int x = 0; x < state.size(); x++) {
			if (state[y][x] == 0)
				continue;
			else if (state[y][x] != (*::solution)[y][x])
				h++;
		}
	}
	return (h);
}

int	row_conflict(const Position &p_curr, const IntMatrix &state) {
	int row_conflict = 0;
	Position p_goal = (*::solution_htbl)[state[p_curr.y][p_curr.x]];
	for (int x = p_curr.x + 1;  x < state.size(); x++) {
		if (state[p_curr.y][x] == 0)
			continue;
		Position r_curr = Position(x,p_curr.y);
		Position r_goal = (*::solution_htbl)[state[r_curr.y][r_curr.x]];
		if ((p_curr.y == r_curr.y) && (p_goal.y == r_goal.y)) {
			if ((r_goal.x <= p_curr.x) && (p_curr.x <= r_curr.x))
				row_conflict++;
		}
	}
	return (row_conflict);
}

int	col_conflict(const Position &p_curr, const IntMatrix &state) {
	int col_conflict = 0;
	Position p_goal = (*::solution_htbl)[state[p_curr.y][p_curr.x]];
	for (int y = p_curr.y + 1;  y < state.size(); y++) {
		if (state[y][p_curr.x] == 0)
			continue;
		Position c_curr = Position(p_curr.x,y);
		Position c_goal = (*::solution_htbl)[state[c_curr.y][c_curr.x]];
		if ((p_curr.x == c_curr.x) && (p_goal.x == c_goal.x)) {
			if ((c_goal.y <= p_curr.y) && (p_curr.y <= c_curr.y)) {
				col_conflict++;
			}
		}
	}
	return (col_conflict);
}

int Linear::distance(const IntMatrix &state) {
	int h = 0;
	int conflicts = 0;
	Manhattan man_h;
	for (int y = 0; y < state.size(); y++) {
		for (int x = 0; x < state.size(); x++) {
			if (state[y][x] == 0)
				continue;
			Position curr = Position(x,y);
			conflicts += row_conflict(curr, state);
			conflicts += col_conflict(curr, state);
		}
	}
	return (man_h.distance(state) + (2 * conflicts));
}
