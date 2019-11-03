#ifndef PUBLIC_FUNCTIONS_H
#define PUBLIC_FUNCTIONS_H
#include "Enemies\Enemy.h"
#include "DataStructures\List_iterator.h"
#include "DataStructures\tuple.h"


static bool asc(Enemy* a,Enemy* b)
{
	return (*a)<(*b);
}

static bool desc(Enemy* a,Enemy* b)
{
	return (!((*a)<(*b)));
}
static bool tuple_cmp(Tuple<int,int,Tuple<int,int,int>>a,Tuple<int,int,Tuple<int,int,int>>b)
{
	return a<b;
}
template<class T>
static bool less_than(const T& l, const T& r)
{
	return l<r;
}
#endif