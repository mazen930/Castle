#pragma once

template<class t1,class t2,class t3>
class Tuple 
{
	t1 first;
	t2 second;
	t3 third;
public:
	//	*constructors*	//
	Tuple(const t1&, const t2&, const t3&);
	Tuple();
	//	*setters & getters*	//
	void set_tuple(const t1&, const t2&, const t3&);
	t1 get_first()const;
	t2 get_second()const;
	t3 get_third()const;
	//	*overloaded operators*	//
	bool operator==(const Tuple<t1,t2,t3>&)const;
	bool operator<(const Tuple<t1,t2,t3>&)const;
};

////////////////constructors//////////////

template<class t1,class t2,class t3>
Tuple<t1,t2,t3>::Tuple()
{
}

template<class t1,class t2,class t3>
Tuple<t1,t2,t3>::Tuple(const t1& k, const t2& v,const t3& d)
{
	set_tuple(k,v,d);
}

///////////////setters & getters/////////////////

template<class t1,class t2,class t3>
void Tuple<t1,t2,t3>::set_tuple(const t1& k, const t2& v,const t3& d)
{
	first=k;
	second=v;
	third=d;
}

template<class t1,class t2,class t3>
t1 Tuple<t1,t2,t3>::get_first()const
{
	return first;
}

template<class t1,class t2,class t3>
t2 Tuple<t1,t2,t3>::get_second()const
{
	return second;
}

template<class t1,class t2,class t3>
t3 Tuple<t1,t2,t3>::get_third()const
{
	return third;
}

//////////////////overloaded operators/////////////

template<class t1,class t2,class t3>
bool Tuple<t1,t2,t3>::operator==(const Tuple<t1,t2,t3>&p)const
{
	return (first==p.first&&second==p.second&&third==p.third);
}

template<class t1,class t2,class t3>
bool Tuple<t1,t2,t3>::operator<(const Tuple<t1,t2,t3>&p)const
{
	if(first<p.first) return true;
	if(first==p.first)
		return second<=p.second;
	return false;
}
