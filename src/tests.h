/*
 * tests.h
 *
 *  Created on: 02/04/2017
 *      Author: User
 */

#ifndef SRC_TESTS_H_
#define SRC_TESTS_H_

#include "Graph.h"
#include "utils.cpp"

class tests {
public:
	tests();
	virtual ~tests();
	void static testFloidWarshal_med(Graph<NoInfo>& data, GraphViewer*& gv);
};

#endif /* SRC_TESTS_H_ */
