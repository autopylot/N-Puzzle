/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Heuristic.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 11:40:22 by wlin              #+#    #+#             */
/*   Updated: 2018/02/03 18:22:16 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEURISTIC_HPP
# define HEURISTIC_HPP

#include <vector>
#include "N_puzzle.hpp"
using namespace std;
struct Position; 

class	IHeuristic {
	public:
		IHeuristic(void) {}
		virtual ~IHeuristic(void) {}
		virtual int	distance(const IntMatrix &state, const vector<Position> &solution_htbl) = 0;
};

class	Manhattan : public IHeuristic {
	public:
		Manhattan(void) {}
		~Manhattan(void) {}
		int	distance(const IntMatrix &state, const vector<Position> &solution_htbl);
};

class	 Hamming : public IHeuristic {
	public:
		Hamming(void) {}
		~Hamming(void) {}
		int	distance(const IntMatrix &state, const vector<Position> &solution_htbl);

};

class	 Linear : public IHeuristic {

	public:
		Linear(void) {}
		~Linear(void) {}
		int distance(const IntMatrix &state, const vector<Position> &solution_htbl);
};

int	row_conflict(const Position &p_curr, const IntMatrix &state, const vector<Position> &solution_htbl);
int	col_conflict(const Position &p_curr, const IntMatrix &state, const vector<Position> &solution_htbl);

#endif
