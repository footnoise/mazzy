/*
    Mazzy - File Emulator Manager
 */
#include "icstring.h"
#include "mazzy.h"
#include "object.cpp"
#include "fs.cpp"
#include "command.h"
#include "parser.cpp"
#include "cmd.cpp"
#include "display.cpp"
#include "command.cpp"

int main(int argc, char* argv[])
{
	Mazzy::Cmd* cmd = Mazzy::Cmd::Instance();
	cmd->SetCommandOnQuit(new Mazzy::Command::Tree("ls"));
	cmd->Add(new Mazzy::Command::MakeDir("md"));
	cmd->Add(new Mazzy::Command::ChangeDir("cd"));
	cmd->Add(new Mazzy::Command::RemoveDir("rd"));
	cmd->Add(new Mazzy::Command::MakeFile("mf"));
	cmd->Add(new Mazzy::Command::DelTree("deltree"));
	cmd->Add(new Mazzy::Command::Del("del"));
	cmd->Add(new Mazzy::Command::Copy("copy"));
	cmd->Add(new Mazzy::Command::Move("move"));
	cmd->Add(new Mazzy::Command::MakeHardLink("mhl"));
	cmd->Add(new Mazzy::Command::MakeDynLink("mdl"));
	cmd->Run();

	delete cmd;

	return 0;
}

