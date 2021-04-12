#include "Database.h"
#include <algorithm>
#include "boost/uuid/uuid_generators.hpp"

static boost::uuids::random_generator generator ;

static const Task::Key & getKey(const Task &t)
{
	return t.key();
}

template < class Iter >
static std::vector<std::reference_wrapper<const Task::Key>> getKeys( const Iter begin , const Iter end )
{
	std::vector<std::reference_wrapper<const Task::Key>> keys ;
	keys.reserve(std::distance(begin,end));
	std::transform(begin,end,std::back_inserter(keys),getKey);
	return keys;
}

std::vector<std::reference_wrapper<const Task::Key>> Database::keys() const
{
	return getKeys(tasks_.begin(),tasks_.end());
}

Database::Database( const std::vector<Task> & tasks)
	: tasks_(tasks){}

const Task::Key & Database::create()
{
	//step 1 generate a key
	Task::Key key = generator();
	//step 2 make sure it's not already in use
	while( read(key) )
	{
		key = generator();
	}
	//step 3 add a new task to the database
	const auto it = tasks_.insert( tasks_.end(), Task(key));
	return it->key();
}

std::optional<std::reference_wrapper<const Task>> Database::read(const Task::Key & key) const
{
	const auto it = std::find_if( tasks_.begin() , tasks_.end(),[&](const Task & t){ return t.key() == key ;});
	return it != tasks_.end() ? std::optional<std::reference_wrapper<const Task>>(*it) : std::nullopt;
}

bool Database::update(const Task::Key & key,const std::function<Task&(Task&)> &updater)
{
	const auto it = std::find_if( tasks_.begin() , tasks_.end(),[&](const Task & t){ return t.key() == key ;});
	if( it != tasks_.end() )
	{
		updater(*it);
		return true;
	}
	return false;
}

bool Database::remove(const Task::Key & key)
{
	const auto it = std::find_if( tasks_.begin() , tasks_.end(),[&](const Task & t){ return t.key() == key ;});
	if( it != tasks_.end() )
	{
		tasks_.erase(it);
		return true;
	}
	return false;
}

std::vector<std::reference_wrapper<const Task::Key>> Database::findBy(const std::function<bool(const Task &)> & f) const
{
	std::vector<std::reference_wrapper< const Task >> copy;
	copy.reserve(tasks_.size());
	std::copy(tasks_.begin(),tasks_.end(),std::back_inserter(copy));
	const auto it = std::partition(copy.begin(),copy.end(),f);
	return getKeys(copy.begin(),it);
}
