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
        xchar substr(const char* start, size_t len) noexcept {
            size_t data_len = std::strlen(data.get());
            if (start < data.get() || start >= data.get() + data_len) {
                return xchar();
            }
            if (start + len > data.get() + data_len) {
                return xchar();
            }
            std::string_view sub_string(start, len);
            return xchar(sub_string);
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
        friend std::ostream& operator<<(std::ostream& os, const xchar& xc) {
            os << xc.data.get();
            return os;
        }
        size_t get_size(const char* str) {
            return std::strlen(str);
        }
        size_t get_size(std::string_view str) {
            return str.length();
        }
        size_t get_size(char ch) {
            return 1;
        }
        size_t get_size(int i) {
            std::stringstream ss;
            ss << i;
            return ss.str().length();
        }
        const char* get() const {
            return data.get();
        }
        // returns the maximum number of characters the xchar can hold
        size_t max_size() const { return std::numeric_limits<size_t>::max(); }

        // resizes the xchar to the given size, adding null characters if necessary
        void resize(size_t new_size) {
            if (new_size > max_size()) {
                throw std::length_error("new size is too large");
            }
            auto new_data = std::make_unique<char[]>(new_size + 1);
            std::memcpy(new_data.get(), data.get(), std::min(new_size, size()));
            data = std::move(new_data);
            data[new_size] = '\0';
        }

        // returns the size of the allocated storage
        size_t capacity() const { return data.get() ? std::strlen(data.get()) : 0; }

        // requests the xchar to reduce its capacity to fit its size
        void shrink_to_fit() {
            resize(size());
        }

        // clears the contents of the xchar
        void clear() {
            data.reset();
        }
        void remove(const char* old_part, const char* new_part) {
            std::string temp(data.get());
            size_t pos = temp.find(old_part);
            if (pos != std::string::npos) {
                temp.replace(pos, std::strlen(old_part), new_part);
            }
            data = std::make_unique<char[]>(temp.length() + 1);
            std::strcpy(data.get(), temp.c_str());
        }
    private:
        std::unique_ptr<char[]> data;
        size_t size() const { return data.get() ? std::strlen(data.get()) : 0; }
        std::stringstream ss;
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
    };// end of the xchar class
} // namespace core
