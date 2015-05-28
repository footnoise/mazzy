#include "mazzy.h"

_MAZZY_BEGIN_

enum Token {NAME, SPACE, SLASH, PRINT, END};

class Parser
{
private:
	Token _currentToken;
	Command::CommandName _name;
	queue<Command::CommandName> _queue;
	std::istream* _input;
	
public:
	Parser(std::istream*);
	Token GetToken();
	queue<Command::CommandName> Run();
	Fs::Path PathParse(Command::CommandName);
	void ClearQueue();
};

queue<Command::CommandName> Parser::Run()
{
	while(_input)
	{
		_currentToken = GetToken();
		
		if (_currentToken == END)
		{
			_queue.push("q");
			break;
		}
		else
		{
			switch (_currentToken)
			{
				
				case NAME:
				{
					break;
				}
				case SPACE:
				{
					break;
				}
				case PRINT:
				{
					return _queue;
					break;
				}

			}
		}
	}
	return _queue;
}

Parser::Parser(std::istream* i):
_input(i)
{
}

Token Parser::GetToken()
{
	char ch = 0;

	_input->get(ch);

	switch (ch)
	{
		case 0:
		{
			return END;
		}
		case '\n':
		{
			return PRINT;
		}
		case '\\':
		{
			return SLASH;
		}
		
		default:
		{
			if (isspace(ch))
			{
				return SPACE;
			}
		
			if (isalpha(ch) || isdigit(ch))
			{
				_input->putback(ch);
				(*_input) >> _name;
				_queue.push(_name);
				return NAME;
			}
			else
			{
				return PRINT;
			}
			
			break;
		}
	}
}

void Parser::ClearQueue()
{
	while (!_queue.empty())
	{
		_queue.pop();
	}
}

Fs::Path Parser::PathParse(Command::CommandName path)
{
	Fs::FileName value;
	Fs::Path result;

	bool isDir = true;
	for (size_t i = 0; i < path.length(); i++)
	{
		if (isalpha(path[i]) || isdigit(path[i]) || path[i] == ':')
		{
			if ((isDir && (value.size() < 8)) || (!isDir && (value.size() < 12)))
			{
				value += path[i];
			}
		}
		else
		{
			if (path[i] == '\\')
			{
				transform (value.begin(), value.end(), value.begin(), toupper); 
				if (isDir)
					result.AddPath(value);
				value = "";
			}
			else if (path[i] == '.')
			{
				value += path[i];
				isDir = false;
			}
		}
	}
	
	if (isDir && !value.empty())
	{
		transform (value.begin(), value.end(), value.begin(), toupper);
		result.AddPath(value);
	}
	else
	{
		transform (value.begin(), value.end(), value.begin(), tolower);
		result.SetFile(value);
	}
	return result;
}

_MAZZY_END_
