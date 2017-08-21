#ifndef __INC_H__
#define __INC_H__

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cassert>
#include <cmath>
#include <climits>

#include <vector>
#include <algorithm>
#include <forward_list>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <tuple>
#include <functional>
#include <chrono>
#include <iostream>
//#include <limits>

using namespace std;
typedef vector<forward_list<int>> tVFLI;
struct tII{int x;int y;};
struct tIII{int x;int y;int z;};
struct tIID{int x;int y;double w;};
struct tLL{int val;tLL*next;};
typedef function<int()> tFUNIV;
typedef long long int LLI;
typedef int* pI;
enum tModes{NONE,PARTIAL,FULL,INIT,CUSTOM,MEAN,MEDIAN,SPARSE,DENSE,iRDC,dRDC,d2RDC,SIMPLE,PATH,INQUEUE,VISITED,ACTIVE};

#endif
