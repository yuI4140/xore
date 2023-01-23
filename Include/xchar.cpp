#include "core.h"
namespace core
{
    //class that serves as an alternative to the built-in const char* 
    //data type offering a variety of functions and transformations 
    //for const char* and char* data typess.
    class xchar {
    public:
        xchar():data(nullptr){}
        xchar(const char* ch):data(std::make_unique<char[]>(charlen(ch) + 1)){
            ss<<data.get();
            auto dlen=std::size(ss.str());
            xmemcpy(data.get(), ch, charlen(ch),dlen);
        }
        xchar(std::string_view str){
            auto len=str.length();
            data=std::make_unique<char[]>(len);
            ss<<data.get();auto dlen=std::size(ss.str());
            xmemcpy(data.get(), str.data(),len,dlen);
        }
        xchar(char ch){
            std::string lc=&ch;
            auto len=lc.length();
            ss<<data.get();
            auto dlen=std::size(ss.str());
            xmemcpy(data.get(), &lc,len,dlen);
        }
        xchar(int i){
           ss <<i;
           auto ndata=ss.str().c_str();
           auto len=std::size(ss.str());
           ss<<data.get();
           auto dlen=std::size(ss.str());
        xmemcpy(data.get(), &ndata,len,dlen);
        }
        void append(std::initializer_list<const char*>& list){
            auto len=list.size();
            ss<<data.get();auto dlen=std::size(ss.str());
            for( auto i:list ){
                xmemcpy(data.get(),i,len,dlen);
            }
        }
    private:
        std::unique_ptr<char[]> data;
        std::stringstream ss;
    };// end of the xchar class
size_t charlen(const char** str) {
    size_t length = 0;
    while (**str++) {
        length++;
    }
    return length;
}
size_t charlen(const char* str) {
    size_t length = 0;
    while (*str++) {
        length++;
    }
    return length;
}
void xmemcpy(void* dest, const void* src, size_t n, size_t dest_size) {
    if (!dest || !src) throw std::invalid_argument("dest and src pointers must not be null");
    if (n == 0) return;
    if (dest == src) throw std::runtime_error("dest and src pointers must not be the same");
    if (n > dest_size) throw std::length_error("n is larger than the size of dest buffer");
    if (std::less<const void*>()(dest, src) && std::less<const void*>()(src, static_cast<const char*>(dest) + n))
        throw std::runtime_error("dest and src memory regions overlap");
    std::memmove(dest, src, n);
}

} // namespace core
