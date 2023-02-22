#ifndef _XCHAR_
#define _XCHAR_
#include "core.h"
namespace core
{   class xchar{
    public:
	class xchar_iterator {
	public:
		using iterator_category = std::random_access_iterator_tag;
		using value_type = char;
		using difference_type = std::ptrdiff_t;
		using pointer = char*;
		using reference = char&;

		explicit xchar_iterator(pointer ptr) : m_ptr(ptr) {}

		reference operator*() const {
			return *m_ptr;
		}

		pointer operator->() const {
			return m_ptr;
		}

		xchar_iterator& operator++() {
			++m_ptr;
			return *this;
		}

		xchar_iterator operator++(int) {
			xchar_iterator temp = *this;
			++m_ptr;
			return temp;
		}

		xchar_iterator& operator--() {
			--m_ptr;
			return *this;
		}

		xchar_iterator operator--(int) {
			xchar_iterator temp = *this;
			--m_ptr;
			return temp;
		}

		xchar_iterator& operator+=(difference_type n) {
			m_ptr += n;
			return *this;
		}

		xchar_iterator& operator-=(difference_type n) {
			m_ptr -= n;
			return *this;
		}

		xchar_iterator operator+(difference_type n) const {
			xchar_iterator temp = *this;
			return temp += n;
		}

		xchar_iterator operator-(difference_type n) const {
			xchar_iterator temp = *this;
			return temp -= n;
		}

		difference_type operator-(const xchar_iterator& other) const {
			return m_ptr - other.m_ptr;
		}

		bool operator==(const xchar_iterator& other) const {
			return m_ptr == other.m_ptr;
		}

		bool operator!=(const xchar_iterator& other) const {
			return !(*this == other);
		}

		bool operator<(const xchar_iterator& other) const {
			return m_ptr < other.m_ptr;
		}

		bool operator>(const xchar_iterator& other) const {
			return other < *this;
		}

		bool operator<=(const xchar_iterator& other) const {
			return !(other < *this);
		}

		bool operator>=(const xchar_iterator& other) const {
			return !(*this < other);
		}

		reference operator[](difference_type n) const {
			return *(m_ptr + n);
		}

	private:
		pointer m_ptr;
	};// end of iterator class
	xchar_iterator begin() {
		return xchar_iterator(data);
	}

	xchar_iterator end() {
		return xchar_iterator(data + charlen(data));
	}
	xchar() : data(nullptr), m_capacity(0) {}
    xchar(const char* ch) : m_capacity(charlen(ch) + 1) {
        for(int i = 0; i < m_capacity;++i){
            xmemcpy(data,(char*)ch[i],m_capacity,capacity()*2);

        }     
    }
    xchar(std::string& str) : m_capacity(str.length() + 1) {
        data = new char[m_capacity];
         memmove(data, str.data(), m_capacity);
    }

    xchar(int i) {
        std::string str = std::to_string(i);
        m_capacity = str.length() + 1;
        data = new char[m_capacity];
        memmove(data, str.c_str(), m_capacity);
    }

    xchar(char& ch) : m_capacity(2) {
        data = new char[m_capacity];
        data[0] =ch;
        data[1] = '\0';
    }

    xchar(const xchar& other) : m_capacity(other.m_capacity) {
        data = new char[m_capacity];
        xmemcpy(data, other.data, other.m_capacity,capacity()*2);
    }

    xchar(xchar&& other) : data(other.data), m_capacity(other.m_capacity) {
        other.data = nullptr;
        other.m_capacity = 0;
    }

    ~xchar() {
        delete[] data;
    }
    size_t copy(char* dest, size_t count, size_t pos = 0) const {
            size_t data_len = std::strlen(data);
            if (pos > data_len) {
                return 0;
            }
            size_t len = std::min(data_len - pos, count);
            charcpy(dest, data + pos, len);
            return len;
        }
    size_t capacity() const {
        return m_capacity;
    }

    const char* get() const {
        return data;
    }

    size_t charlen(const char* str) {
        size_t length = 0;
        while (*str++) {
            length++;
        }
        return length;
    }
    void swap(xchar& other) {
            std::swap(data, other.data);
        }
    void reserve(size_t new_capacity) {
            if (new_capacity > m_capacity) {
                char* new_data(new char[new_capacity]);
                std::memcpy(new_data, data,capacity()*2);
                data = std::move(new_data);
                m_capacity = new_capacity;
            }
        }
private:
    char* data;
    size_t m_capacity;
    static constexpr size_t npos = std::numeric_limits<size_t>::max();
  void xmemcpy(void* dest, const void* src, size_t n, size_t dest_size)
        {
            if (!dest || !src)
                throw std::invalid_argument("dest and src pointers must not be null");
            if (n == 0)
                return;
            if (dest == src)
                throw std::runtime_error("dest and src pointers must not be the same");
            if (n > dest_size)
                throw std::length_error("n is larger than the size of dest buffer");
            if (std::less<const void*>()(dest, src) && std::less<const void*>()(src, static_cast<const char*>(dest) + n))
                throw std::runtime_error("dest and src memory regions overlap");
            std::memmove(dest, src, n);
        }
        void charcpy(char* dest, const char* src, size_t destSize) const {
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
    };
}// namespace core
namespace LV {
    class xchar_view {
        using xchar = core::xchar;
    public:
        xchar_view(const xchar& str): data_(str.get()), length_(str.size()) {}
        xchar_view(const char* str): data_(str), length_(std::strlen(str)) {}
        const char* get() { return data_; }
        void remove_prefix(size_t n) {
            data_ += n;
            length_ -= n;
        }
        void remove_suffix(size_t n) {
            length_ -= n;
        }
        void swap(xchar_view& other) {
            std::swap(data_, other.data_);
            std::swap(length_, other.length_);
        }
        const char* begin() const { return data_; }
        const char* end() const { return data_ + length_; }

        xchar_view& operator=(const xchar& str) {
            data_ = str.get();
            length_ = str.size();
            return *this;
        }
    private:
        const char* data_;
        size_t length_;
    };// end for xchar_view
}
#endif