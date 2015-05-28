#include "mazzy.h"

_MAZZY_BEGIN_

class Cmd
{
private:
	vector<Command::Command*> _commands;
	Command::Command* _commandOnQuit;
	Fs::FileSystem* _fs;
	Fs::Object*     _current;
	Parser _parser;
	queue<Command::CommandName> _userInput;
	static Cmd* _instance;
	bool _isQuit;

public:
	~Cmd();
	static Cmd* Instance();
	void Add(Command::Command*);
	void ShowError(string);
	void Run();
	void Read();
	void SetFs(Fs::FileSystem*);
	Fs::FileSystem* GetFs();
	void SetCurrentPath(Fs::Object*);
	Fs::Object* GetCurrentPath();
	Fs::Object*	GetWorkPath(Fs::Path*);	
	void Execute();
	void SetCommandOnQuit(Command::Command*);

protected:
	Cmd(Fs::FileSystem*);
};

_MAZZY_END_
