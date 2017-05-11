/*
 * string_find.h
 *
 *  Created on: 11/05/2017
 *      Author: Xavier Fontes
 */

#ifndef SRC_STRING_FIND_H_
#define SRC_STRING_FIND_H_

#include<vector>

using namespace std;

vector<unsigned int> computePrefix(string toSearch) {
	unsigned int m = toSearch.size();
	vector<unsigned int> pi(m + 1, 0);

	unsigned int k = 0;

	for (size_t q = 2; q <= m; q++) {
		while (k > 0 && toSearch.at(k) != toSearch.at(q - 1)) {
			k = pi.at(k);
		}
		if (toSearch.at(k) == toSearch.at(q - 1)) {
			k++;
		}
		pi.at(q) = k;
	}

	return pi;
}

unsigned int kmpStringMatch(string input, string toSearch) {
	unsigned int occ = 0;
	unsigned int n = input.size();
	unsigned int m = toSearch.size();
	vector<unsigned int> pi = computePrefix(toSearch);
	unsigned int q = 0;
	for (size_t i = 1; i <= n; i++) {
		while (q > 0 && toSearch.at(q) != input.at(i - 1)) {
			q = pi.at(q);
		}
		if (toSearch.at(q) == input.at(i - 1)) {
			q++;
		}
		if (q == m) {
			occ++;
			q = pi.at(q);
		}
	}
	return occ;
}

int distancia_entre_palavras(string pattern, string texto){
	vector<vector<int>> D(pattern.size()+1,vector<int>(texto.size()+1,0));

	for(unsigned int i = 0; i <= pattern.size(); i++)
		D[i][0] = i;
	for(unsigned int j = 0; j <= texto.size(); j++)
			D[0][j] = j;

	for(unsigned int i = 1; i <= pattern.size(); i++){
		for(unsigned int j = 1; j <= texto.size(); j++){
			if(pattern[i-1] == texto[j-1]){
				D[i][j] = D[i-1][j-1];
			}
			else {

				D[i][j] = 1 + min(min(D[i-1][j-1], D[i-1][j]), D[i][j-1]);
			}
		}
	}


	return D[pattern.size()][texto.size()];

}


#endif /* SRC_STRING_FIND_H_ */
