#include "load.h"
//#include "boost/property_tree/xml_parser.hpp"
#include "boost/property_tree/json_parser.hpp"
#include "boost/lexical_cast.hpp"
#include "boost/uuid/uuid_io.hpp"
#include <fstream>

using Tree = boost::property_tree::ptree;

static std::optional<Task> createTask( const Tree & tree )
{
	//step 1 read the key
	if( const auto keyOpt = tree.get_optional<std::string>("key") )
	{
		const Task::Key key = boost::lexical_cast< Task::Key >( *keyOpt );
		Task task(key);
		//title
		if( const auto titleOpt = tree.get_optional<std::string>("title") )
		{
			task.title = *titleOpt ;
		}
		else
		{
			return std::nullopt;
		}
		//description
		if( const auto opt = tree.get_optional<std::string>("description") )
		{
			task.description = *opt ;
		}
		else
		{
			return std::nullopt;
		}
		//room
		if( const auto opt = tree.get_optional<std::string>("room") )
		{
			task.room = *opt ;
		}
		else
		{
			return std::nullopt;
		}
		//recurring
		if( const auto opt = tree.get_optional<bool>("recurring") )
		{
			task.recurring = *opt ;
		}
		else
		{
			return std::nullopt;
		}
		
		//tags
		if( const auto opt = tree.get_child_optional("tags") )
		{
			for( auto it = opt->begin(), endIt = opt->end() ; it != endIt ; ++it )
			{
				const Tree & tag = it->second ;
				if( const auto opt2 = tag.get_optional<std::string>("") )
				{
					task.tags.push_back(*opt2);
				}
			}
		}
		
		//blocking
		if( const auto opt = tree.get_child_optional("blocking") )
		{
			for( auto it = opt->begin(), endIt = opt->end() ; it != endIt ; ++it )
			{
				const Tree & block = it->second ;
				if( const auto opt2 = block.get_optional<std::string>("") )
				{
					task.blocking.push_back(boost::lexical_cast<Task::Key>(*opt2));
				}
			}
		}
		
		return task;
	}
	return std::nullopt;
}

static std::optional<Database> createDB(const Tree & tree)
{
	if( const auto tasksTree = tree.get_child_optional("tasks"))
	{
		std::vector< Task > tasks ;
		for( auto it = tasksTree->begin() , endIt = tasksTree->end() ; it != endIt ; ++it )
		{
			if( const auto task = createTask( it->second ) )
			{
				tasks.push_back(*task);
			}
			else
			{
				return std::nullopt ;
			}
		}
		return Database(tasks);
	}
	return std::nullopt;
}

std::optional<Database> loadFromFile(const std::filesystem::path &path)
{
	if( std::filesystem::exists( path ) )
	{
		std::ifstream file(path);
		if( file.good() )
		{
			Tree tree ;
			boost::property_tree::read_json(file,tree);
			return createDB(tree);
		}
	}
	return std::nullopt;
}
