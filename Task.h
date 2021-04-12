#ifndef TASK_H
#define TASK_H

#include "boost/uuid/uuid.hpp"
#include <vector>
#include <string>
#include <functional>

class Task
{
public:
	using Key = boost::uuids::uuid;
	Task( const Key & );
private:
	Key key_;
public:
	const Key & key() const;
	std::string title;
	std::string description;
	std::string room;
	bool recurring;
	std::vector<std::string> tags;
	std::vector<Task::Key> blocking;
};

namespace Feild
{
	class Key{};
	class Title{};
	class Description{};
	class Room{};
	class Recurring{};
	class Tags{};
	class Blocking{};
};

//getters
const Task::Key & get( const Feild::Key & , const Task & );
const std::string & get( const Feild::Title & , const Task & );
std::string & get( const Feild::Title & , Task & );
const std::string & get( const Feild::Description & , const Task & );
std::string & get( const Feild::Description & , Task & );
const std::string & get( const Feild::Room & , const Task & );
std::string & get( const Feild::Room & , Task & );
bool get( const Feild::Recurring & , const Task & );
bool & get( const Feild::Recurring & , Task & );
const std::vector<std::string> & get( const Feild::Tags & , const Task & );
std::vector<std::string> & get( const Feild::Tags & , Task & );
const std::vector< Task::Key > & get( const Feild::Blocking & , const Task & );
std::vector< Task::Key > & get( const Feild::Blocking & , Task & );

//setters
template < class T , class V >
class Set
{
private:
	V value_;
public:
	Set(const V & value)
		: value_(value) {}
	Task& operator()(Task&t) const
	{
		get(T(),t) = value_ ;
		return t ;
	}
};

template < class T , class V>
std::function<Task&(Task&)> set( const T &, const V & value)
{
	return Set<T,V>(value);
}

std::function<Task&(Task&)> setTitle(const std::string &);
std::function<Task&(Task&)> setDescription(const std::string &);
std::function<Task&(Task&)> setRoom(const std::string &);
std::function<Task&(Task&)> setRecuring();
std::function<Task&(Task&)> unsetRecuring();
std::function<Task&(Task&)> addTag(const std::string &);
std::function<Task&(Task&)> addBlockingTask(const Task&);

//finders
std::function<bool(const Task &)> titleEq(const std::string &);

#endif
