#include <iostream>
#include "save.h"
#include "boost/uuid/uuid_io.hpp"
#include "Database.h"
#include "load.h"

int main(int argc, char **argv)
{
	if( const auto x = loadFromFile("test.json") )
	{
		std::cout << "--------------------" << std::endl ;
	const Database & db = *x ;  
	
	/*const Task::Key helloKey = db.create();
	{
		const auto & key = helloKey;
		db.update(key,set(Feild::Title(),std::string("Hello")));
		db.update(key,set(Feild::Description(),std::string("Test task")));
		db.update(key,set(Feild::Recurring(),false));
		db.update(key,set(Feild::Room(),std::string("Test")));
		db.update(key,set(Feild::Tags(),std::vector<std::string>{"tag1","tag2","tag3"}));
	}
	{
		const auto key = db.create();
		db.update(key,set(Feild::Title(),std::string("Goodbye")));
		db.update(key,set(Feild::Description(),std::string("Test task")));
		db.update(key,set(Feild::Recurring(),false));
		db.update(key,set(Feild::Room(),std::string("Test")));
		db.update(key,set(Feild::Blocking(),std::vector<Task::Key>(1,helloKey)));
	}*/
	
	for(const auto & key : db.keys())
	{
		std::cout << '\t' << "key : " << key << std::endl ;
		if( const auto entry = db.read(key) )
		{
			std::cout << '\t' << '\t' << "title : " << entry->get().title << std::endl ;
			std::cout << '\t' << '\t' << "description : " << entry->get().description << std::endl ;
			std::cout << '\t' << '\t' << "room : " << entry->get().room << std::endl ;
			std::cout << '\t' << '\t' << "recuring : " << entry->get().recurring << std::endl ;
			std::cout << '\t' << '\t' << "tags : " << std::endl ;
			for( const auto & tag : entry->get().tags )
			{
				std::cout << '\t' << '\t' << '\t' << tag << std::endl ;
			}
			std::cout << '\t' << '\t' << "blocking : " << std::endl ;
			for( const auto & block : entry->get().blocking )
			{
				std::cout << '\t' << '\t' << '\t' << block << std::endl ;
			}
		}
		else
		{
			std::cout << '\t' << '\t' << "NOT FOUND" << std::endl ;
		}
	}
	
	std::cout << "--------------------" << std::endl ;
	{
		for(const auto & entry : db.findBy(titleEq("Goodbye")))
		{
			std::cout << "found key : " << entry.get() << std::endl ;
		}
	}
}
	//saveToFile("test.json",db);
	return 0;
}
