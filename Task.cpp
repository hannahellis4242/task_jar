#include "Task.h"

Task::Task( const Key & x )
	: key_(x){}
	
const Task::Key & Task::key()const
{
	return key_ ;
}

const Task::Key & get( const Feild::Key & , const Task & t )
{
	return t.key();
}

const std::string & get( const Feild::Title & , const Task &t )
{
	return t.title;
}
std::string & get( const Feild::Title & , Task & t)
{
	return t.title;
}
const std::string & get( const Feild::Description & , const Task &t )
{
	return t.description;
}
std::string & get( const Feild::Description & , Task & t)
{
	return t.description;
}
const std::string & get( const Feild::Room & , const Task & t)
{
	return t.room;
}
std::string & get( const Feild::Room & , Task & t)
{
	return t.room;
}
bool get( const Feild::Recurring & , const Task & t)
{
	return t.recurring;
}
bool & get( const Feild::Recurring & , Task & t)
{
	return t.recurring;
}
const std::vector<std::string> & get( const Feild::Tags & , const Task & t)
{
	return t.tags;
}
std::vector<std::string> & get( const Feild::Tags & , Task & t)
{
	return t.tags;
}
const std::vector< Task::Key > & get( const Feild::Blocking & , const Task & t)
{
	return t.blocking;
}
std::vector< Task::Key > & get( const Feild::Blocking & , Task & t)
{
	return t.blocking;
}

/*
template <class T>
class Set
{
private:
	T value_ ;
	const std::function< T&(Task &t) > & getter_;
public:
	Set( const std::function< T&(Task &t) > & getter , const T & value )
		: value_(value),getter_(getter){}
	Task & operator()(Task &t) const
	{
		getter_(t) = value_ ;
		return t ;
	}
};

std::function<Task&(Task&)> setTitle(const std::string &s)
{
	return Set<std::string>(foo,s);
}*/


class TitleEqual
{
private:
	std::string s_ ;
public:
	TitleEqual(const std::string & s)
		:s_(s){}
	bool operator()(const Task & t) const
	{
		return t.title == s_ ;
	}
};

std::function<bool(const Task &)> titleEq(const std::string &s)
{
	return TitleEqual(s);
}
