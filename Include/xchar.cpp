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
            strcpy(data.get(), ch);
        }
        xchar(std::string_view str){
            auto len=str.length();
            data=std::make_unique<char[]>(len);
            memcpy(data.get(), str.data(), len);
        }
        xchar(char ch){
            std::string lc=&ch;
            auto len=lc.length();
            memcpy(data.get(), &lc,len);
        }
        xchar(int i){
           std::stringstream ss;ss <<i;
           auto ndata=ss.str().c_str();
        xmemcpy(data.get(), &ndata,sizeof(ndata));
        }
    private:
        std::unique_ptr<char[]> data;
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
void xmemcpy(void* dest, const void* src, size_t n) {
    if (!dest || !src) return; // check for null pointers
    if (n == 0) return; // check for zero byte copy
    if (dest == src) return; // check for overlapping memory
    if (n > std::numeric_limits<size_t>::max()/2) return; // check for too large size

    // Use std::memcpy() to perform the copy
    std::memcpy(dest, src, n);
}
} // namespace core
