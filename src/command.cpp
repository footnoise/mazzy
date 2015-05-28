#include "mazzy.h"

_MAZZY_COMMAND_BEGIN_

class MakeDir: public Command
{
public:
	MakeDir(CommandName name);
	virtual bool Action();
};

MakeDir::MakeDir(CommandName name):
Command(name)
{

}

bool MakeDir::Action()
{
	if (!GetParams()->empty())
	{
		Cmd* cmd = Cmd::Instance();
		Fs::Path path = GetParams()->at(0);
		
		path.SetFile(path.GetPath()->back());
		path.GetPath()->pop_back();
		
		cmd->GetFs()->MakeDir(cmd->GetWorkPath(&path), &path);
	}
	
	return true;
};

class Tree: public Command
{
public:
	Tree(CommandName name);
	virtual bool Action();
};

Tree::Tree(CommandName name):
Command(name)
{

}

bool Tree::Action()
{
	Cmd* cmd = Cmd::Instance();
	
	Display display;
	display.Tree(cmd->GetFs()->GetRoot(), 0, "|   ");
	return true;

}
class ChangeDir: public Command
{
public:
	ChangeDir(CommandName name);
	virtual bool Action();
};

ChangeDir::ChangeDir(CommandName name):
Command(name)
{

}

bool ChangeDir::Action()
{
	Cmd* cmd = Cmd::Instance();
	
	if (!GetParams()->empty())
	{
		Fs::Path path = GetParams()->front();
		Fs::Object* obj = cmd->GetCurrentPath();
		
		obj = cmd->GetWorkPath(&path);
		
		if (obj)
			cmd->SetCurrentPath(obj);
	}
	
	return true;

}

class RemoveDir: public Command
{
public:
	RemoveDir(CommandName name);
	virtual bool Action();
};

RemoveDir::RemoveDir(CommandName name):
Command(name)
{

}

bool RemoveDir::Action()
{
	if (!GetParams()->empty())
	{
		Cmd* cmd = Cmd::Instance();
		cmd->GetFs()->RemoveDir(cmd->GetWorkPath(&GetParams()->front()));
	}
	
	return true;

}

class MakeFile: public Command
{
public:
	MakeFile(CommandName name);
	virtual bool Action();
};

MakeFile::MakeFile(CommandName name):
Command(name)
{

}

bool MakeFile::Action()
{
	if (!GetParams()->empty())
	{
		Cmd* cmd = Cmd::Instance();
	
		cmd->GetFs()->MakeFile(cmd->GetWorkPath(&GetParams()->front()), &GetParams()->front());
	}
	
	return true;

}

class DelTree: public Command
{
public:
	DelTree(CommandName name);
	virtual bool Action();
};

DelTree::DelTree(CommandName name):
Command(name)
{

}

bool DelTree::Action()
{
	if (!GetParams()->empty())
	{
		Cmd* cmd = Cmd::Instance();
		cmd->GetFs()->DelTree(cmd->GetWorkPath(&GetParams()->front()));
	}
	
	return true;

}
class Del: public Command
{
public:
	Del(CommandName name);
	virtual bool Action();
};

Del::Del(CommandName name):
Command(name)
{

}

bool Del::Action()
{
	if (!GetParams()->empty())
	{
		Cmd* cmd = Cmd::Instance();
		Fs::Object* obj = cmd->GetWorkPath(&GetParams()->front());
		
		if (!GetParams()->front().GetFile().empty())
		{
			for (size_t i = 0; i < obj->GetChilds().size(); i++)
			{
				if (obj->GetChilds()[i]->GetName() == GetParams()->front().GetFile())
				{
					cmd->GetFs()->Del(obj->GetChilds()[i]);
					break;
				}
			}
		}
	}
	
	return true;

}

class Move: public Command
{
public:
	Move(CommandName name);
	virtual bool Action();
};

Move::Move(CommandName name):
Command(name)
{

}

bool Move::Action()
{
	if (GetParams()->size() < 2)
	{
		return false;
	}	
	
	Cmd* cmd = Cmd::Instance();
	Fs::Path path1 = GetParams()->at(0);
	Fs::Path path2 = GetParams()->at(1);

	Fs::Object* obj = cmd->GetWorkPath(&path1);
	if (obj)
	{
		if (!path1.GetFile().empty())
		{
			for (size_t i = 0; i < obj->GetChilds().size(); i++)
			{
				if (cmd->GetFs()->IsFile(obj->GetChilds()[i]) && (obj->GetChilds()[i]->GetName() == path1.GetFile()))
				{
					cmd->GetFs()->Move(obj->GetChilds()[i], cmd->GetWorkPath(&path2));
					break;
				}
			}
		}
		else
		{
			cmd->GetFs()->Move(obj, cmd->GetWorkPath(&path2));
		}
	}
	
	return true;

}

class Copy: public Command
{
public:
	Copy(CommandName name);
	virtual bool Action();
};

Copy::Copy(CommandName name):
Command(name)
{

}

bool Copy::Action()
{
	if (GetParams()->size() < 2)
	{
		return false;
	}	
    else
	{
		Cmd* cmd = Cmd::Instance();
		Fs::Path path1 = GetParams()->at(0);
		Fs::Path path2 = GetParams()->at(1);

		Fs::Object* obj = cmd->GetWorkPath(&path1);
		if (obj)
		{
			if (!path1.GetFile().empty())
			{
				for (size_t i = 0; i < obj->GetChilds().size(); i++)
				{
					if (cmd->GetFs()->IsFile(obj->GetChilds()[i]) && (obj->GetChilds()[i]->GetName() == path1.GetFile()))
					{
						cmd->GetFs()->Copy(obj->GetChilds()[i], cmd->GetWorkPath(&path2));
						break;
					}
				}
			}
			else
			{
				cmd->GetFs()->Copy(obj, cmd->GetWorkPath(&path2));
			}
		}
	}
	return true;

}

class MakeHardLink: public Command
{
public:
	MakeHardLink(CommandName name);
	virtual bool Action();
};

MakeHardLink::MakeHardLink(CommandName name):
Command(name)
{

}

bool MakeHardLink::Action()
{
	if (GetParams()->size() < 2)
	{
		return false;
	}	
    else
	{
		Cmd* cmd = Cmd::Instance();
		Fs::Path path1 = GetParams()->at(0);
		Fs::Path path2 = GetParams()->at(1);

		Fs::Object* obj = cmd->GetWorkPath(&path1);
		if (obj)
		{
			if (!path1.GetFile().empty())
			{
				for (size_t i = 0; i < obj->GetChilds().size(); i++)
				{
					if (cmd->GetFs()->IsFile(obj->GetChilds()[i]) && (obj->GetChilds()[i]->GetName() == path1.GetFile()))
					{
						cmd->GetFs()->MakeHardLink(obj->GetChilds()[i], cmd->GetWorkPath(&path2));
						break;
					}
				}
			}
			else
			{
				cmd->GetFs()->MakeHardLink(obj, cmd->GetWorkPath(&path2));
			}
		}
	}
	return true;

}

class MakeDynLink: public Command
{
public:
	MakeDynLink(CommandName name);
	virtual bool Action();
};

MakeDynLink::MakeDynLink(CommandName name):
Command(name)
{

}

bool MakeDynLink::Action()
{
	if (GetParams()->size() < 2)
	{
		return false;
	}	
    else
	{
		Cmd* cmd = Cmd::Instance();
		Fs::Path path1 = GetParams()->at(0);
		Fs::Path path2 = GetParams()->at(1);

		Fs::Object* obj = cmd->GetWorkPath(&path1);
		if (obj)
		{
			if (!path1.GetFile().empty())
			{
				for (size_t i = 0; i < obj->GetChilds().size(); i++)
				{
					if (cmd->GetFs()->IsFile(obj->GetChilds()[i]) && (obj->GetChilds()[i]->GetName() == path1.GetFile()))
					{
						cmd->GetFs()->MakeDynLink(obj->GetChilds()[i], cmd->GetWorkPath(&path2));
						break;
					}
				}
			}
			else
			{
				cmd->GetFs()->MakeDynLink(obj, cmd->GetWorkPath(&path2));
			}
		}
	}
	return true;

}
_MAZZY_COMMAND_END_
