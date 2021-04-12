#include "save.h"
#include "Database.h"
#include "boost/property_tree/ptree.hpp"
//#include "boost/property_tree/xml_parser.hpp"
#include "boost/property_tree/json_parser.hpp"
#include "boost/lexical_cast.hpp"
#include "boost/uuid/uuid_io.hpp"
#include <fstream>

using Tree = boost::property_tree::ptree;

static Tree create(const Task & task )
{
	Tree tree ;
	{
		tree.put("key",boost::lexical_cast<std::string>(task.key()));
		tree.put("title",task.title);
		tree.put("description",task.description);
		tree.put("room",task.room);
		tree.put("recurring",task.recurring);
		if(!task.tags.empty())
		{
			Tree tags;
			for( const auto & tag : task.tags)
			{
				Tree t;
				t.put("",tag);
				tags.push_back(std::make_pair("",t));
			}
			tree.put_child("tags",tags);
		}
		if(!task.blocking.empty())
		{
			Tree blocking;
			for( const auto & key : task.blocking)
			{
				Tree t;
				t.put("",boost::lexical_cast<std::string>(key));
				blocking.push_back(std::make_pair("",t));
			}
			tree.put_child("blocking",blocking);
		}
	}
	return tree;
}

static Tree create(const Database & db)
{
	Tree tree ;
	{
		Tree dbTree;
		for( const auto & key : db.keys())
		{
			if(const auto task = db.read(key))
			{
				dbTree.push_back(std::make_pair("",create(*task)));
			}
		}
		tree.put_child("tasks",dbTree);
	}
	return tree;
}

bool saveToFile(const std::filesystem::path &p,const Database &db)
{
	std::ofstream file(p);
	if(file.good())
	{
		const Tree tree = create(db);
		//boost::property_tree::write_xml(file,tree);
		boost::property_tree::write_json(file,tree,true);
		file.close();
		return true;
	}
	return false;
}
