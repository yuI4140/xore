#include "core.h"
#include "xchar.cpp"
#include "DataType.h"
class packet{
public:	
packet() = default;
	template<typename ... Args>
	packet(std::initializer_list<Args...> list){}
	packet(size_t size,DataType _type){
		size_t effective_size =0;
		if(_type==INT){effective_size =size*sizeof(int);}
		else if(_type==FLOAT){effective_size =size*sizeof(float);}
		else if(_type==STRING){effective_size =size*sizeof(std::string);}
		else if(_type==CHAR){effective_size =size*sizeof(char);}
		else if(_type==XCHAR){effective_size =size*sizeof(core::xchar);}
		else if(_type==DOUBLE){effective_size=size*sizeof(double);}
		else if(_type==SIZE_T){effective_size=size*sizeof(size_t);}
		else if(_type==WCHAR_T){effective_size=size*sizeof(wchar_t);}
		else if(_type==BOOLEAN){effective_size=size*sizeof(bool);}
		size=size;
		data=std::make_unique<void*>(effective_size);
	}
	void get(core::xchar Arg){}
private:
DataType type;
size_t size;
std::unique_ptr<void*> data;
};