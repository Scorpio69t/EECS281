/* 
 * cycle.cpp 
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 Lab 9 Written.
 * SUBMIT ONLY THIS FILE TO GRADESCOPE.
 */

// Common #includes for convience.
// No need to use them. 
// Remove any of them if you want.
#include <algorithm>
#include <deque>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <math.h>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "cycle.h"

using namespace std;

bool is_graph_cyclic(const vector<vector<int>> &adj_list) {

  vector<bool> discovered;
  discovered.resize(adj_list.size());

  return search(adj_list, 0, discovered, -1);
  // TODO

}

bool search(const vector<vector<int>> &adj_list, int start, vector<bool> &discovered, int first){

    discovered[start] = true;
 
    for (int next: graph.adjList[start])
    {
        if (!discovered[next])
        {
            if (search(adj_list, next, discovered, start)) {
                return true;
            }
        }
 
        else if (next != first)
        {
            return true;
        }
    }
    return false;
}
