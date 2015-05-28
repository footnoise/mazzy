_MAZZY_COMMAND_BEGIN_

typedef icstring CommandName;

class Command
{
private:
	CommandName _cmd; 
	vector<Fs::Path> _params;
public:
	Command(CommandName);
	~Command();
	virtual bool Action();
	virtual CommandName GetCmd();
	virtual void SetParam(Fs::Path);
	virtual vector<Fs::Path>* GetParams();
	virtual void ClearParams();
};

Command::Command(CommandName cmd):
_cmd(cmd)
{}

Command::~Command()
{}

bool Command::Action()
{
	return true;
}

CommandName Command::GetCmd()
{
	return _cmd;
}

void Command::SetParam(Fs::Path p)
{
	_params.push_back(p);
}

vector<Fs::Path>* Command::GetParams()
{
	return &_params;
}

void Command::ClearParams()
{
	_params.clear();
}

_MAZZY_COMMAND_END_
