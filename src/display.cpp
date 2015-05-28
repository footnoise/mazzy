#include "mazzy.h"

_MAZZY_BEGIN_

/**
 *	Alphabet sorting of nodes. Sorting ONLY for first character.
 */
bool alphabet (Fs::Object* a, Fs::Object* b)
{
   return (a->GetName()[0] < b->GetName()[0]);
}

class Display
{
protected:
	void _File (Fs::Object*);
	void _DLink(Fs::Object*);
	void _HLink(Fs::Object*);
	void _Dir  (Fs::Object*);
	Fs::FileName _FullPath(Fs::Object*);
public:	
	Display();
	~Display();
	void Tree(Fs::Object*, int level = 0, char* space = "");

};

Display::Display()
{}

Display::~Display()
{}

void Display::_File(Fs::Object* obj)
{
	std::cout << obj->GetName() << std::endl;
}

void Display::_Dir(Fs::Object* obj)
{
	std::cout << obj->GetName() << std::endl;
}

void Display::_HLink(Fs::Object* obj)
{
	std::cout << obj->GetName() << " [" <<  _FullPath(obj->GetChilds()[0]) << "]" << std::endl;
}

void Display::_DLink(Fs::Object* obj)
{
	std::cout << obj->GetName() << " [" <<  _FullPath(obj->GetChilds()[0]) << "]" << std::endl;
}

Fs::FileName Display::_FullPath(Fs::Object* obj)
{
	if (obj->GetParent())
	{
		return _FullPath(obj->GetParent()) + "/" + obj->GetName();
	}
	else
	{
		return obj->GetName();
	}
}

void Display::Tree(Fs::Object* obj, int level, char* space)
{
	
	for (int j = 0; j < (level - 1); j++)
	{
		std::cout << space;
	}
	
	if (level)
	{
		std::cout << "|_";
	}
	
	switch (obj->GetType())
	{
		case Fs::DIR:
		{
			_Dir(obj);
				
			if (obj->HasChilds())
			{
				level++;
				vector<Fs::Object*> childs = obj->GetChilds();
				std::sort(childs.begin(), childs.end(), alphabet);
				for (size_t i = 0; i < childs.size(); i++)
				{
					if (obj->GetHLink() != childs[i] && obj->GetDLink() != childs[i])
					Tree(childs[i], level, space);
				}
			}
			
			break;
		}
		case Fs::FILE:
		{
			_File(obj);
			break;
		}
		case Fs::HLINK:
		{
			_HLink(obj);
			break;
		}
		case Fs::DLINK:
		{
			_DLink(obj);
			break;
		}
	}

}
_MAZZY_END_
