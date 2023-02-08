#ifndef _XCHAR
#define _XCHAR
#include "core.h"
namespace core
{class xcharIterator: public std::iterator<std::forward_iterator_tag, char>
    {
    public:
        // constructors
        //------------------------------------------------------------------------
        xcharIterator(char* p): ptr_(p) {}
        // overloaded operators
        //------------------------------------------------------------------------
        char& operator*() { return *ptr_; }
        char* operator->() { return ptr_; }

        xcharIterator& operator++() {
            ptr_++;
            return *this;
        }
        xcharIterator operator++(int) {
            xcharIterator tmp(*this);
            operator++();
            return tmp;
        }

        bool operator==(const xcharIterator& other) const { return ptr_ == other.ptr_; }
        bool operator!=(const xcharIterator& other) const { return ptr_ != other.ptr_; }

    private:
        char* ptr_;
    };// end of the iterator class for xchar
    //class that serves as an alternative to the built-in const char* 
    //data type offering a variety of functions and transformations 
    //for const char* and char* data typess.
    class xchar
    {  // extra members of the class
		using xcharIterator = core::xcharIterator;
        xcharIterator begin() { return xcharIterator(data.get()); }
        xcharIterator end()
    {  // extra members of the class
        core::xcharIterator begin() { return xcharIterator(data.get()); }
        core::xcharIterator end() { return xcharIterator(data.get() + std::strlen(data.get())); }
        // constructors
        //------------------------------------------------------------------------
        //------------------------------------------------------------------------     return xcharIterator(data.get() + std::strlen(data.get())); }
        // constructors
        //------------------------------------------------------------------------
        //------------------------------------------------------------------------    
    public:
        xchar():data(nullptr) {}
        xchar(const char* ch):data(std::make_unique<char[]>(charlen(ch) + 1)) {
            ss << data.get();
            auto dlen = std::size(ss.str());
            xmemcpy(data.get(), ch, charlen(ch), dlen);
        }
        xchar(std::string_view str) {
            auto len = str.length();
            data = std::make_unique<char[]>(len);
            ss << data.get();auto dlen = std::size(ss.str());
            xmemcpy(data.get(), str.data(), len, dlen);
        }
        xchar(char ch) {
            std::string lc = &ch;
            auto len = lc.length();
            ss << data.get();
            auto dlen = std::size(ss.str());
            xmemcpy(data.get(), &lc, len, dlen);
        }
        xchar(int i) {
            ss << i;
            auto ndata = ss.str().c_str();
            auto len = std::size(ss.str());
            ss << data.get();
            auto dlen = std::size(ss.str());
            xmemcpy(data.get(), &ndata, len, dlen);
        }
        void append(std::initializer_list<const char*>& list) {
            auto len = list.size();
            ss << data.get();auto dlen = std::size(ss.str());
            for (auto i : list) {
                xmemcpy(data.get(), i, len, dlen);
            }
        }
        friend std::ostream& operator<<(std::ostream& os, const xchar& xc) {
            os << xc.data.get();
            return os;
        }
        xchar& operator=(const xchar& other) {
            auto ndata = other.data.get();
            auto _data = data.get();
            if (this != &other) {
                _data = std::move(ndata);
                xchar(_data);
            }
            return *this;
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
