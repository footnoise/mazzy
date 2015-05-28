#include "cmd.h"

_MAZZY_BEGIN_

Cmd* Cmd::_instance = 0;

Cmd* Cmd::Instance()
{
	if (!_instance)
	{
		_instance = new Cmd(new Fs::FileSystem(new Fs::Dir("C:")));
	}

	return _instance;
}

Cmd::Cmd(Fs::FileSystem* root):
_fs(root),
_parser(&std::cin)
{
	_isQuit = false;
	_current = _fs->GetRoot();
	_commandOnQuit = 0;
}

Cmd::~Cmd()
{
	for(size_t i = 0; i < _commands.size(); i++)
	{
		delete _commands[i];
	}

	delete _commandOnQuit;
	delete _fs;
	delete _current;
}
	
void Cmd::Add(Command::Command* command)
{
	try
	{
		_commands.push_back(command);
	}
	catch (...)
	{
		ShowError("Error");			
	}
}

void Cmd::ShowError(string message)
{
	std::cerr << message;
	abort();
}

void Cmd::Run()
{
	while (!_isQuit)
	{
		try
		{
			Read();
		}
		catch (...)
		{
			ShowError("Error");
		}
	}

	if (_commandOnQuit)
	{
		_commandOnQuit->Action();
	}
}

void Cmd::Read()
{
	
	_parser.ClearQueue();
	_userInput = _parser.Run();

	try
	{
		Execute();
	}
	catch (...)
	{
		ShowError("Can't execute command");
	}
}

void Cmd::SetFs(Fs::FileSystem* root)
{
	_fs = root;
}

Fs::FileSystem* Cmd::GetFs()
{
	return _fs;
}

void Cmd::SetCurrentPath(Fs::Object* path)
{
	_current = path;
}

Fs::Object* Cmd::GetCurrentPath()
{
	return _current;
}

Fs::Object* Cmd::GetWorkPath(Fs::Path* path)
{
	if (!path->GetPath()->empty())
	{
		if (_fs->GetRoot()->GetName() == path->GetPath()->at(0))
		{
			return _fs->ChangeDir(_fs->GetRoot(), path, 1);	
		}
		else
		{
			return _fs->ChangeDir(_current, path);
		}
	}
	else
	{
		return _current;
	}
}
void Cmd::Execute()
{
	Command::CommandName cmd;
	
	if (!_userInput.empty())
	{
		cmd = _userInput.front();
	}
	if (cmd == "q")
	{
		_isQuit = true;
	}
	else
	{
		for (vector<Command::Command*>::iterator i = _commands.begin(); i != _commands.end(); i++)
		{
			if (cmd == (*i)->GetCmd())
			{
				_userInput.pop();
				while (!_userInput.empty())
				{
					(*i)->SetParam(_parser.PathParse(_userInput.front()));
					_userInput.pop();
				}
				(*i)->Action();
				(*i)->ClearParams();
				break;
			}
		}
	}  	
}

void Cmd::SetCommandOnQuit(Command::Command* command)
{
	_commandOnQuit = command;
}

_MAZZY_END_
