#include "mazzy.h"

_MAZZY_FS_BEGIN_

enum Type{DIR,FILE,HLINK,DLINK};

typedef char* Name;
typedef char* Ext;

typedef icstring FileName;

class Object
{
private:
	FileName _name;
	vector<Object*> _childs;
	Object* _parent;
	Type _type;
	Object* _hlink;
	Object* _dlink;
public:
	Object(FileName, Type);
	Object(char* name, Type);
	~Object();
	virtual void Add(Object*, bool k = true);
	virtual Object* Remove(Object*);
	virtual Object* Remove(vector<Object*>::iterator);
	virtual void Unlink(Object*);
	virtual bool HasChilds();
	virtual vector<Object*> GetChilds();
	virtual FileName GetName();
	virtual void SetName(FileName);
	virtual Type GetType();
	virtual void SetType(Type);
	virtual void SetParent(Object*);
	virtual Object* GetParent();
	virtual void SetHLink(Object*);
	virtual void SetDLink(Object*);
	virtual Object* GetHLink();
	virtual Object* GetDLink();

protected:
};

_MAZZY_FS_END_
