/*
  	Copyright © 2012 Bastien Durel

    This file is part of deadlands.

    myDobble is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    myDobble is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with myDobble.  If not, see <http://www.gnu.org/licenses/>.
 */
package org.durel.deadlands;

/**
 * @author Bastien Durel
 * 
 */
public class Random {

	static java.util.Random rng = new java.util.Random();

	static public int roll(int nb, int ns) {
		int max = 0;
		for (int i = 0; i < nb; ++i) {
			int roll, sum = 0;
			do {
				roll = rng.nextInt(ns) + 1;
				sum += roll;
			} while (roll != ns);
			if (sum > max)
				max = sum;
		}
		return max;
	}

}
