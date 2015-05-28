#include "mazzy.h"
#include "object.h"

_MAZZY_FS_BEGIN_

Object::Object(FileName name, Type type):
_name(name),
_type(type)
{
	_parent = 0;
}

Object::Object(char* name, Type type):
_name(name),
_type(type)
{
	_parent = 0;
	_hlink = 0;
	_dlink = 0;
}

Object::~Object()
{
    
    if ((_type != HLINK) && (_type != DLINK))
    {
	for (size_t i = 0; i < _childs.size(); i++)
	{
	    if ((_childs[i]->GetType() == DLINK) || (_childs[i]->GetType() == HLINK))
	    {	
		
		if (_childs[i]->GetParent() == this)
		{
		    
		    delete _childs[i];
		}
		else
		{
		    _childs[i]->Unlink(this);
		}
	    }
	    else
	    {
		delete _childs[i];
	    }
	
	}
    }
    else
    {
	for (size_t i = 0; i < _childs.size(); i++)
	{
	    _childs[i]->Unlink(this);
	}
    }
    
}

void Object::Add(Object* obj, bool k)
{
	if (k) {obj->SetParent(this);}
	_childs.push_back(obj);
}

Object* Object::Remove(Object* obj)
{
	Unlink(obj);
	delete obj;
	return this;
}

void Object::Unlink(Object* obj)
{
	for (vector<Object*>::iterator i = _childs.begin(); i != _childs.end(); i++)
	{
		if ((*i) == obj)
		{
			_childs.erase(i);
			break;
		}
	}
}

Object* Object::Remove(vector<Object*>::iterator i)
{
	try
	{	
		_childs.erase(i);
	}
	catch (...)
	{
		std::cerr << "Can't Delete object" << std::endl;;
	}
	return this;
}

bool Object::HasChilds()
{
	return (!_childs.empty());
}

FileName Object::GetName()
{
	return _name;
}

void Object::SetName(FileName name)
{
	_name = name;
}

Type Object::GetType()
{
	return _type;
}

void Object::SetType(Type type)
{
	_type = type;
}

void Object::SetParent(Object* obj)
{
	_parent = obj;
}

Object* Object::GetParent()
{
	return _parent;
}

void Object::SetDLink(Object* obj)
{
	_dlink = obj;
}

void Object::SetHLink(Object* obj)
{
	_hlink = obj;
}

Object* Object::GetDLink()
{
	return _dlink;
}

Object* Object::GetHLink()
{
	return _hlink;
}

vector<Object*> Object::GetChilds()
{
	return _childs;
}

_MAZZY_FS_END_
