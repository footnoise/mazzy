#include "mazzy.h"

_MAZZY_FS_BEGIN_

class Path
{
private:
	string		  _drive;
	vector<FileName> _path;
	FileName	  _file;
public:
	Path(string, vector<FileName>, FileName);
	Path();
	string GetDrive();
	vector<FileName>* GetPath();
	FileName GetFile();
	void SetDrive(string);
	void SetFile(FileName);
	void AddPath(FileName);
};

class Dir:	public Object
{
public:
	Dir(FileName name);
};

class File:	public Object
{
public:
	File(FileName);
};

class HLink:	public   Object
{
public:
	HLink(Object*);
};

class DLink:	public Object
{
public:
	DLink(Object*);
};

class FileSystem
{
private:
	Object* _root;
	queue<Object*> _queue;
	bool _isDelTree;
	
public:
	FileSystem(Object*);
	bool IsExist(Object*);
	bool IsExistIn(Object*, FileName);
	bool IsRoot(Object*);
	bool IsDir(Object*);
	bool IsFile(Object*);
	bool IsHardLink(Object*);
	bool IsDynLink(Object*);
	bool HasHardLinks(Object*);
	bool HasDynLinks(Object*);
	void SetRoot(Object*);
	Object* GetRoot();
	Object* ChangeDir(Object*, Path*, size_t level = 0);
	bool MakeDir(Object*, Path*);
    Object* RemoveDir(Object*);
	bool Del(Object*);
	void Move(Object*, Object*);
	void Copy(Object*, Object*);
	bool DelTree(Object*, bool isFirst = true);
	void MakeFile(Object*, Path*);
	void MakeHardLink(Object*, Object*);
	void MakeDynLink(Object*, Object*);
};

_MAZZY_FS_END_
