/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 16:11:54 by wlin              #+#    #+#             */
/*   Updated: 2018/01/24 19:11:41 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.hpp"
#include "puzzle.hpp"

IntMatrix *solution = generate_solution(4);

int main()
{
	 std::srand ( unsigned ( std::time(0) ) );
	Puzzle p1(4);
	// p1.display_puzzle();
	// std::list<Puzzle*> *successors = p1.generate_successors();
	// for (std::list<Puzzle*>::iterator it = successors->begin(); it != successors->end(); it++)
	// 	(*it)->display_puzzle();
	astar(&p1);
	// std::vector<Position> tmp = p1.generate_moves(Position(0,0));
	// for (std::vector<Position>::iterator it = tmp.begin(); it != tmp.end(); it++)
	// 	std::cout << it->y << " , " << it->x << std::endl;
 }
