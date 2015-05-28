#include "fs.h"

_MAZZY_FS_BEGIN_

Dir::Dir(FileName name): 
Object(name, DIR)
{};

File::File(FileName name): 
Object(name, FILE)
{};

HLink::HLink(Object* obj):
Object("hlink", HLINK)
{
	Add(obj, false);
};

DLink::DLink(Object* obj):
Object("dlink", DLINK)
{
	Add(obj, false);
};

Path::Path(string drive, vector<FileName> path, FileName file):
_drive(drive),
_path(path),
_file(file)
{
}

Path::Path()
{}
void Path::SetDrive(string name)
{
	_drive = name;
}

string Path::GetDrive()
{
	return _drive;
}

vector<FileName>* Path::GetPath()
{
	return &_path;
}

void Path::SetFile(FileName name)
{
	_file = name;
}

FileName Path::GetFile()
{
	return _file;
}

void Path::AddPath(FileName path)
{
	_path.push_back(path);
}


/*
 *
 *	FileSystem
 *
 */
FileSystem::FileSystem(Object* obj): 
_root(obj)
{
    _isDelTree = true;
}

bool FileSystem::HasHardLinks(Object* obj)
{
	for (size_t i = 0; i < obj->GetChilds().size(); i++)
	{
		if (IsHardLink(obj->GetChilds()[i]))
		{
			return true;
		}
	}
	return false;
}

bool FileSystem::HasDynLinks(Object* obj)
{
	for (size_t i = 0; i < obj->GetChilds().size(); i++)
	{
		if (IsDynLink(obj->GetChilds()[i]))
		{
			return true;
		}
	}
	return false;
}

void FileSystem::SetRoot(Object* obj)
{
	_root = obj;
}

Object* FileSystem::GetRoot()
{
	return _root;
}

bool FileSystem::IsDir(Object* obj)
{
	if (!obj)
		return	false; 
	else
		return (obj->GetType() == DIR);
}

bool FileSystem::IsRoot(Object* obj)
{
	if (!obj)
		return false;
	else
		return (obj->GetParent())?false:true;
}

bool FileSystem::IsExist(Object* obj)
{
	if (!obj)
		return false;
	else
		return true;
}

bool FileSystem::IsExistIn(Object* obj, FileName name )
{
	for (size_t i = 0; i < obj->GetChilds().size(); i++)
	{
		if (obj->GetChilds()[i]->GetName() == name)
		{
			return true;
		}
	}

	return false;
}

bool FileSystem::IsFile(Object* obj)
{
	if (!obj)
		return false;
	else
		return (obj->GetType() == FILE);
}

bool FileSystem::IsHardLink(Object* obj)
{
	if (!obj)
		return false;
	else
		return (obj->GetType() == HLINK);
}

bool FileSystem::IsDynLink(Object* obj)
{
	if (!obj)
		return false;
	else
		return (obj->GetType() == DLINK);
}

Object* FileSystem::ChangeDir(Object* obj, Path* path, size_t level)
{
	if (!path->GetPath()->size() || (level == path->GetPath()->size()))
	{
		return obj;
	}
	
	if (obj->HasChilds())
	{
		for (size_t i = 0; i < obj->GetChilds().size(); i++)
		{
			if (obj->GetChilds()[i]->GetName() == path->GetPath()->at(level))
			{
				return ChangeDir(obj->GetChilds()[i], path, level+1);
			}
		}
	}
	
	return 0;
}

bool FileSystem::MakeDir(Object* obj, Path* path)
{
	
	if (!IsDir(obj))
	{
		return false;
	}
	if (!path->GetFile().empty() && !IsExistIn(obj, path->GetFile()))
	{
		obj->Add(new Dir(path->GetFile()));
		return true;
	}
	return true;
}

Object* FileSystem::RemoveDir(Object* obj)
{
	if (!IsDir(obj) || IsRoot(obj))
	{
		return 0;
	}

	if (!obj->HasChilds())
	{
		return obj->GetParent()->Remove(obj);
	}

	return 0;
}

void FileSystem::Move(Object* obj1, Object* obj2)
{
	if (IsDir(obj1) && IsDir(obj2))
	{
		if (!HasHardLinks(obj1))
		{
			obj1->GetParent()->Unlink(obj1);
			obj2->Add(obj1);
		}
	}
}

bool FileSystem::Del(Object* obj)
{
	bool result = true;

	if (!IsDir(obj))
	{
		if (IsFile(obj))
		{
			if (!HasHardLinks(obj))
			{
				for (vector<Fs::Object*>::iterator i = obj->GetChilds().begin(); i != obj->GetChilds().end(); i++)
				{
					obj->Remove((*i));
				}
				
				if (_isDelTree)
				{
				    _queue.push(obj); 
				}
				else
				{
				    obj->GetParent()->Remove(obj);
				}
				result = true;
			}
			else
			{
				result = false;
			}
		}
		else
		{
			obj->GetParent()->Remove(obj);
			result = true;
		}
	}
	else
	{
		result = false;
	}

	return result;
}

void FileSystem::MakeFile(Object* obj, Path* path)
{
	if (IsDir(obj))
	{
		if (!path->GetFile().empty() && !IsExistIn(obj, path->GetFile()))
		{
			obj->Add(new File(path->GetFile()));
		}
	}
}

void FileSystem::MakeHardLink(Object* from, Object* to)
{
	if ((IsDir(from) || IsFile(from)) && IsDir(to))
	{
		if (!HasHardLinks(to))
		{
			Fs::Object* link = new HLink(from);
			to->Add(link);
			from->SetHLink(link);
			from->Add(link, false);
		}
	}
}

void FileSystem::MakeDynLink(Object* from, Object* to)
{
	if (IsDir(from) || IsFile(from) && IsDir(to))
	{
		if (!HasDynLinks(to))
		{
			Fs::Object* link = new DLink(from);
			to->Add(link);
			from->SetDLink(link);
			from->Add(link, false);
		}
	}
}

bool FileSystem::DelTree(Object* obj, bool isFirst)
{
	if (isFirst)
	{
	    _isDelTree = true;
	}
	
	bool result = true;
	
	if (IsDir(obj) && !IsRoot(obj))
	{
		for (size_t i = 0; i < obj->GetChilds().size(); i++)
		{
			if (IsDir(obj->GetChilds()[i]))
			{
				if (!DelTree(obj->GetChilds()[i]), false)
				result = false;
			}
			else
			{
			    if (!Del(obj->GetChilds()[i]))
			    {
				result = false;
			    };	
			}
		}
		_queue.push(obj);
		result =  true;
	}
	else
	{
	    result = false;
	}
	
	if (isFirst)
	{
	    _isDelTree = false;
	    
	    while (!_queue.empty())
	    {
		if (IsDir(_queue.front()))
		{
		    if (RemoveDir(_queue.front()))
		    {
			_queue.pop();
		    }
		}
		else
		{
		    if (Del(_queue.front()))
		    {
			_queue.pop();
		    }
		    
		}
	    }
	    
	}
	
	return result;
}

void FileSystem::Copy(Object* from, Object* to)
{
	
	if (IsExist(from) && IsDir(to) && !IsExistIn(to, from->GetName()))
	{
		switch(from->GetType())
		{
			case DIR:
			{
				Object* obj3 = new Dir(from->GetName());
				to->Add(obj3);
				
				for (size_t i = 0; i != from->GetChilds().size(); i++)
				{
					Copy(from->GetChilds()[i], obj3);
				}
				break;
			}
			case FILE:
			{
				to->Add(new File(from->GetName()));
				break;
			}
			
			case HLINK:
			{
				for (vector<Object*>::iterator i = from->GetChilds().begin(); i!= from->GetChilds().end(); i++)
				{
					to->Add(new HLink((*i)));
				}
				break;
			}

			case DLINK:
			{
				for (vector<Object*>::iterator i = from->GetChilds().begin(); i!= from->GetChilds().end(); i++)
				{
					to->Add(new DLink((*i)));
				}
				break;
			}
		}
	}
}


_MAZZY_FS_END_
