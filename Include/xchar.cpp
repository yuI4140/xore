#include "core.h"
namespace core
{
    //class that serves as an alternative to the built-in const char* 
    //data type offering a variety of functions and transformations 
    //for const char* and char* data typess.
    class xchar {
    public:
        xchar():data(nullptr) {}
        xchar(const char* ch):data(std::make_unique<char[]>(charlen(ch) + 1)) {
            strcpy(data.get(), ch);
        }
        xchar(std::string_view str) {
            auto len = str.length();
            data = std::make_unique<char[]>(len + 1);
            charcpy(data.get(), str.data(), len + 1);
        }
        xchar(char ch) {
            try
            {
                data = std::make_unique<char[]>(2);
                data[0] = ch;
                data[1] = '\0';
            }
            catch (const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        xchar(int i) {
            std::string str = std::to_string(i);
            data = std::make_unique<char[]>(str.length() + 1);
            charcpy(data.get(), str.c_str(), str.length() + 1);
        }
        template<typename... Args>
        void append(Args&&... args) {
            std::initializer_list<const char*> list{ std::forward<Args>(args)... };
            std::string temp;
            temp.append(data.get());
            for (auto i : list) {
                temp.append(i);
            }
            auto len = temp.length();
            data = std::make_unique<char[]>(len + 1);
            charcpy(data.get(), temp.c_str(), len + 1);
        }

        void charcpy(char* dest, const char* src, size_t destSize) {
            if (dest == nullptr || src == nullptr) {
                return;
            }

            if (src < dest && src + destSize > dest) {
                // overlapping
                return;
            }

            if (std::strlen(src) >= destSize) {
                // destSize is not large enough
                return;
            }

            size_t i;
            for (i = 0; i < destSize && src[i] != '\0'; i++) {
                dest[i] = src[i];
            }
            dest[i] = '\0';
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
        void xmemcpy(void* dest, const void* src, size_t n, size_t dest_size) {
            if (!dest || !src) throw std::invalid_argument("dest and src pointers must not be null");
            if (n == 0) return;
            if (dest == src) throw std::runtime_error("dest and src pointers must not be the same");
            if (n > dest_size) throw std::length_error("n is larger than the size of dest buffer");
            if (std::less<const void*>()(dest, src) && std::less<const void*>()(src, static_cast<const char*>(dest) + n))
                throw std::runtime_error("dest and src memory regions overlap");
            std::memmove(dest, src, n);
        }
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
        friend std::ostream& operator<<(std::ostream& os, const xchar& xc) {
            os << xc.data.get();
            return os;
        }
    private:
        std::unique_ptr<char[]> data;
        std::stringstream ss;
    };// end of the xchar class
} // namespace core
