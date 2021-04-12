#ifndef DATABASE_H
#define DATABASE_H

#include "Task.h"
#include <optional>
#include <functional>

class Database
{
private:
	std::vector<Task> tasks_;
public:
	Database() = default ;
	Database( const std::vector<Task> & tasks);
	std::vector<std::reference_wrapper<const Task::Key>> keys() const;
	const Task::Key & create();
	std::optional<std::reference_wrapper<const Task>> read(const Task::Key &) const;
	bool update(const Task::Key &,const std::function<Task&(Task&)> &);
	bool remove(const Task::Key &);
	
	std::vector<std::reference_wrapper<const Task::Key>> findBy(const std::function<bool(const Task &)> &) const ;
};
#endif
