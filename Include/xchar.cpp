#pragma once
#include "core.h"
namespace core
{
	class xcharIterator : public std::iterator<std::forward_iterator_tag, char>
	{
	public:
		// constructors
		//------------------------------------------------------------------------
		xcharIterator(char *p) : ptr_(p) {}
		// overloaded operators
		//------------------------------------------------------------------------
		char &operator*() { return *ptr_; }
		char *operator->() { return ptr_; }


		xcharIterator &operator++()
		{
			ptr_++;
			return *this;
		}
		xcharIterator operator++(int)
		{
			xcharIterator tmp(*this);
			operator++();
			return tmp;
		}


		bool operator==(const xcharIterator &other) const { return ptr_ == other.ptr_; }
		bool operator!=(const xcharIterator &other) const { return ptr_ != other.ptr_; }


	private:
		char *ptr_;
	}; // end of the iterator class for xchar
	// class that serves as an alternative to the built-in const char*
	// data type offering a variety of functions and transformations
	// for const char* and char* data typess.
	class xchar
	{ // extra members of the class
		using xcharIterator = core::xcharIterator;
		xcharIterator begin() { return xcharIterator(data.get()); }
		xcharIterator end() { return xcharIterator(data.get() + std::strlen(data.get())); }
		// constructors
		//------------------------------------------------------------------------
		//------------------------------------------------------------------------
	public:
		xchar() : data(nullptr) {}
		xchar(const char *ch) : data(std::make_unique<char[]>(charlen(ch) + 1))
		{
			strcpy(data.get(), ch);
		}
		xchar(std::string_view str)
		{
			auto len = str.length();
			data = std::make_unique<char[]>(len + 1);
			charcpy(data.get(), str.data(), len + 1);
		}
		xchar(int i)
		{
			auto ch = to_string(i);
			auto len = xchar(ch).size();
			data = std::make_unique<char[]>(len + 1);
			charcpy(data.get(), ch, len + 1);
		}
		xchar(const char16_t& ch);
		xchar(char32_t ch);
		xchar(wchar_t ch);
		xchar(char ch)
		{
			try
			{
				data = std::make_unique<char[]>(2);
				data[0] = ch;
				data[1] = '\0';
			}
			catch (const std::exception &e)
			{
				std::cerr << e.what() << '\n';
			}
		}
		// additional functions
		//------------------------------------------------------------------------
		//------------------------------------------------------------------------
		// searches a part of xchar object and returns a boolean value
		bool search(const char *str) const
		{
			return std::strstr(data.get(), str) != nullptr;
		}
		const char* to_cchar(const char16_t *str16)
		{
			constexpr int len = std::char_traits<char16_t>::length(str16);
			char *str8 = new char[len * 4 + 1];
			int pos = 0;

			for (int i = 0; i < len; i++) {
				char16_t c = str16[i];
				if (c <= 0x7F) {
					str8[pos++] = static_cast<char>(c);
				} else if (c <= 0x7FF) {
					str8[pos++] = static_cast<char>(0xC0 | ((c >> 6) & 0x1F));
					str8[pos++] = static_cast<char>(0x80 | (c & 0x3F));
				} else {
					str8[pos++] = static_cast<char>(0xE0 | ((c >> 12) & 0x0F));
					str8[pos++] = static_cast<char>(0x80 | ((c >> 6) & 0x3F));
					str8[pos++] = static_cast<char>(0x80 | (c & 0x3F));
				}
			}

			str8[pos] = '\0';
			return str8;
		}
		// replaces a part of xchar object
		// it's in test yet
		void replace(const char *old_str, const char *new_str)
		{
			size_t old_len = strlen(old_str);
			size_t new_len = strlen(new_str);
			char *temp = data.get();
			char *pos = temp;
			while ((pos = std::strstr(pos, old_str)) != nullptr)
			{
				size_t remaining_len = strlen(pos + old_len) + 1; // +1 to include the null terminator
				if (new_len > old_len)
				{
					// New string is larger than old string, need to increase size of buffer
					size_t new_buffer_size = strlen(temp) + new_len - old_len + 1; // +1 to include the null terminator
					std::unique_ptr<char[]> new_buffer = std::make_unique<char[]>(new_buffer_size);
					// Copy data before the old string to the new buffer
					charcpy(new_buffer.get(), temp, pos - temp);
					// Copy the new string to the new buffer
					charcpy(new_buffer.get() + (pos - temp), new_str, new_len);
					// Copy the data after the old string to the new buffer
					charcpy(new_buffer.get() + (pos - temp) + new_len, pos + old_len, remaining_len);
					data = std::move(new_buffer);
				}
				else
				{
					// New string is smaller or equal in size to old string, can do in-place replacement
					std::memmove(pos + new_len, pos + old_len, remaining_len);
					charcpy(pos, new_str, new_len);
				}
				pos += new_len;
			}
		}
		// remove the null terminator of xhcar object
		void rmNullTerm()
		{
			int len = size();
			for (int i = 0; i < len; ++i)
			{
				if (data[i] == '\0')
				{
					data[i] = ' '; // or remove this line to remove the null terminator
				}
			}
		}
		// calculate the length of the a const char*
		size_t lchar(const char *str)
		{
			size_t length = 0;
			while (*str++)
				++length;
			return length;
		}
		template <typename... Args>
		void append(Args &&...args)
		{
			std::initializer_list<const char *> list{std::forward<Args>(args)...};
			std::string temp;
			if (data != nullptr)
			{
				temp.append(data.get());
			}
			for (auto i : list)
			{
				temp.append(i);
			}
			auto len = temp.length();
			data = std::make_unique<char[]>(len + 1);
			charcpy(data.get(), temp.c_str(), len + 1);
		}
		xchar substr(const char *start, size_t len) noexcept
		{
			size_t data_len = std::strlen(data.get());
			if (start < data.get() || start >= data.get() + data_len)
			{
				return xchar();
			}
			if (start + len > data.get() + data_len)
			{
				return xchar();
			}
			std::string_view sub_string(start, len);
			return xchar(sub_string);
		}
		xchar &operator=(const xchar &other)
		{
			char *ndata = other.data.get();
			char *data_ = data.get();
			if (this != &other)
			{
				data_ = std::move(ndata);
				core::xchar data_;
			}
			return *this;
		}
		size_t copy(char *dest, const char *src) const
		{
			if (dest == nullptr || src == nullptr)
			{
				return 0;
			}


			size_t src_len = std::strlen(src);
			if (src < dest && src + src_len > dest)
			{
				// overlapping
				return 0;
			}


			charcpy(dest, src, src_len + 1);
			return src_len;
		}
		friend std::ostream &operator<<(std::ostream &os, const xchar &xc)
		{
			os << xc.data.get();
			return os;
		}
		friend std::istream &operator>>(std::istream &is, xchar &xc)
		{
			std::string temp;
			is >> temp;
			xc.data = std::make_unique<char[]>(temp.length() + 1);
			xc.charcpy(xc.data.get(), temp.c_str(), xc.size());
			return is;
		}
		size_t get_size(const char *str)
		{
			return std::strlen(str);
		}
		size_t get_size(std::string_view str)
		{
			return str.length();
		}
		size_t get_size(int i)
		{
			std::stringstream ss;
			ss << i;
			return ss.str().length();
		}
		const char *get() const
		{
			return data.get();
		}
		// returns the maximum number of characters the xchar can hold
		size_t max_size() const { return std::numeric_limits<size_t>::max(); }
		// resizes the xchar to the given size, adding null characters if necessary
		void resize(size_t new_size)
		{
			if (new_size > max_size())
			{
				throw std::length_error("new size is too large");
			}
			auto new_data = std::make_unique<char[]>(new_size + 1);
			std::memcpy(new_data.get(), data.get(), std::min(new_size, size()));
			data = std::move(new_data);
			data[new_size] = '\0';
		}


		char *toChar(xchar &xc)
		{
			return xc.data.get();
		}
		// returns the size of the allocated storage
		size_t capacity() const { return data.get() ? std::strlen(data.get()) : 0; }


		// requests the xchar to reduce its capacity to fit its size
		void shrink_to_fit()
		{
			resize(size());
		}


		// clears the contents of the xchar
		void clear()
		{
			data.reset();
		}
		void remove(const char *old_part, const char *new_part)
		{
			std::string temp(data.get());
			size_t pos = temp.find(old_part);
			if (pos != std::string::npos)
			{
				temp.replace(pos, std::strlen(old_part), new_part);
			}
			data = std::make_unique<char[]>(temp.length() + 1);
			std::strcpy(data.get(), temp.c_str());
		}
		// A function that safely executes a block of code
		void catcher(void (*func)())
		{
			try
			{
				func();
			}
			catch (const std::exception &e)
			{
				std::cerr << e.what() << '\n';
			}
		}
		template <typename F>
		F catcher(F (*func)())
		{
			try
			{
				func();
			}
			catch (const std::exception &e)
			{
				std::cerr << e.what() << '\n';
			}
		}
		bool empty() const noexcept
		{
			auto array = data.get();
			if (array == nullptr || array[0] == 0)
				return true;
			else
				return false;
		}
		const char *at(size_t index)
		{
			if (index >= size())
			{
				throw std::out_of_range("Index out of range");
			}
			return data.get() + index;
		}
		std::string to_string()
		{
			std::string result(data.get());
			return result;
		}
		std::string to_string(std::string_view &view)
		{
			return std::string(view.data(), view.size());
		}
		std::string to_string() const
		{
			std::string result(data.get());
			return result;
		}
		std::string to_string(std::string_view &view) const
		{
			return std::string(view.data(), view.size());
		}
		const char *to_string(int value) const
		{
			static char buffer[32];
			memset(buffer, 0, sizeof(buffer));
			int result = snprintf(buffer, sizeof(buffer), "%d", value);
			if (static_cast<long long unsigned int>(result) < 0 || result >= sizeof(buffer))
			{
				return "ERROR";
			}
			return buffer;
		}
		size_t charlen(const char **str)
		{
			size_t length = 0;
			while (**str++)
			{
				length++;
			}
			return length;
		}
		size_t charlen(const char *str)
		{
			size_t length = 0;
			while (*str++)
			{
				length++;
			}
			return length;
		}
		char front() const
		{
			if (empty())
			{
				throw std::out_of_range("xchar is empty");
			}
			return data[0];
		}
		void WARNING(size_t newDataSize, size_t reservedMemory)
		{
			assert(newDataSize <= reservedMemory && "WARNING: Not enough reserved memory for new data!");
		}
		void WARNING(size_t reservedMemory)
		{
			auto len = std::strlen(data.get());
			if (reservedMemory > len)
			{
				throw std::out_of_range("WARNING: out of reserved memory");
			}
		}
		char back() const
		{
			if (empty())
				throw std::out_of_range("xchar is empty");
			return data[std::strlen(data.get()) - 1];
		}
		void pop_back()
		{
			// Get the current length of the string
			size_t length = lchar(data.get());
			// Check if the string is already empty
			if (length == 0)
			{
				return;
			}
			// Set the last character to '\0' to remove it
			data[length - 1] = '\0';
		}
		void push_back(const xchar &other)
		{
			insert(std::strlen(data.get()), other);
		}
		xchar &operator+=(const xchar &other)
		{
			push_back(other);
			return *this;
		}
		void erase(size_t pos, size_t len)
		{
			auto pos_newdata = data.get()[pos];
			WARNING(pos_newdata, len);
			if (pos > std::strlen(data.get()))
			{
				return;
			}
			std::unique_ptr<char[]> new_data(new char[std::strlen(data.get()) - len + 1]);
			std::strncpy(new_data.get(), data.get(), pos);
			std::strcpy(new_data.get() + pos, data.get() + pos + len);
			data = std::move(new_data);
		}
		const char &at(size_t pos) const
		{
			if (pos >= size())
			{
				throw std::out_of_range("Index out of range");
			}
			return data[pos];
		}


		char &operator[](size_t pos)
		{
			return data[pos];
		}


		const char &operator[](size_t pos) const
		{
			return data[pos];
		}
		void insert(size_t pos, const xchar &other)
		{
			auto pos_newdata = data.get()[pos];
			auto len = get_size(pos_newdata);
			WARNING(pos_newdata, len);
			if (pos > std::strlen(data.get()))
			{
				return;
			}
			std::unique_ptr<char[]> new_data(new char[std::strlen(data.get()) + std::strlen(other.data.get()) + 1]);
			std::strncpy(new_data.get(), data.get(), pos);
			std::strcpy(new_data.get() + pos, other.data.get());
			std::strcpy(new_data.get() + pos + std::strlen(other.data.get()), data.get() + pos);
			data = std::move(new_data);
		}
		void reserve(size_t new_capacity)
		{
			WARNING(new_capacity);
			if (new_capacity > capacity())
			{
				auto new_data = std::make_unique<char[]>(new_capacity);
				size_t len = std::strlen(data.get());
				xmemcpy(new_data.get(), data.get(), len, new_capacity);
				data = std::move(new_data);
			}
		}
		bool starts_with(const char *prefix) const noexcept
		{
			size_t prefix_len = std::strlen(prefix);
			if (std::strncmp(data.get(), prefix, prefix_len) == 0)
			{
				return true;
			}
			return false;
		}
		bool ends_with(const char *suffix) const noexcept
		{
			size_t suffix_len = std::strlen(suffix);
			size_t data_len = std::strlen(data.get());
			if (data_len < suffix_len)
			{
				return false;
			}
			if (std::strncmp(data.get() + data_len - suffix_len, suffix, suffix_len) == 0)
			{
				return true;
			}
			return false;
		}
		int compare(const xchar &other) const noexcept
		{
			auto com=std::strcmp(data.get(), other.data.get());
			if (com==-1){
				com=1;
				return com;
			}
			return com;
		}
		bool contains(const char *str) const noexcept
		{
			const char *found = std::strstr(data.get(), str);
			if (found != nullptr)
			{
				return true;
			}
			return false;
		}
		size_t copy(char *dest, size_t count, size_t pos = 0) const
		{
			size_t data_len = std::strlen(data.get());
			if (pos > data_len)
			{
				return 0;
			}
			size_t len = std::min(data_len - pos, count);
			charcpy(dest, data.get() + pos, len);
			return len;
		}
		size_t find(const char *str, size_t pos = 0) const
		{
			const char *found = std::strstr(data.get() + pos, str);
			if (found)
			{
				return found - data.get();
			}
			return npos;
		}
		size_t rfind(const char *str, size_t pos = npos) const
		{
			if (pos == npos)
			{
				pos = std::strlen(data.get()) - 1;
			}
			for (size_t i = pos; i != npos; i--)
			{
				if (std::strncmp(data.get() + i, str, std::strlen(str)) == 0)
				{
					return i;
				}
			}
			return npos;
		}
		size_t find_first_of(const char *str, size_t pos = 0) const
		{
			const char *found = std::strpbrk(data.get() + pos, str);
			if (found)
			{
				return found - data.get();
			}
			return npos;
		}
		size_t find_first_not_of(const char *str) const
		{
			size_t i = 0;
			while (i < std::strlen(data.get()) && std::strchr(str, data.get()[i]))
			{
				i++;
			}
			return i;
		}
		size_t find_last_not_of(const char *str) const
		{
			size_t i = std::strlen(data.get());
			while (i > 0 && std::strchr(str, data.get()[i - 1]))
			{
				i--;
			}
			return i;
		}
		void swap(xchar &other)
		{
			std::swap(data, other.data);
		}
		void resize_and_overwrite(size_t new_size, char new_value)
		{
			if (new_size <= 0)
			{
				throw std::invalid_argument("new_size must be greater than 0");
			}
			std::unique_ptr<char[]> new_data = std::make_unique<char[]>(new_size);
			for (size_t i = 0; i < new_size; i++)
			{
				new_data[i] = new_value;
			}
			size_t copy_size = std::min(new_size, std::strlen(data.get()));
			xmemcpy(new_data.get(), data.get(), copy_size, new_size);
			data = std::move(new_data);
		}
		size_t size() const { return data.get() ? std::strlen(data.get()) : 0; }


	private:
		std::unique_ptr<char[]> data;
		static constexpr size_t npos = std::numeric_limits<size_t>::max();
		std::stringstream ss;
		void xmemcpy(void *dest, const void *src, size_t n, size_t dest_size)
		{
			if (!dest || !src)
				throw std::invalid_argument("dest and src pointers must not be null");
			if (n == 0)
				return;
			if (dest == src)
				throw std::runtime_error("dest and src pointers must not be the same");
			if (n > dest_size)
				throw std::length_error("n is larger than the size of dest buffer");
			if (std::less<const void *>()(dest, src) && std::less<const void *>()(src, static_cast<const char *>(dest) + n))
				throw std::runtime_error("dest and src memory regions overlap");
			std::memmove(dest, src, n);
		}
		void charcpy(char *dest, const char *src, size_t destSize) const
		{
			if (dest == nullptr || src == nullptr)
			{
				return;
			}


			if (src < dest && src + destSize > dest)
			{
				// overlapping
				return;
			}


			if (std::strlen(src) >= destSize)
			{
				// destSize is not large enough
				return;
			}


			size_t i;
			for (i = 0; i < destSize && src[i] != '\0'; i++)
			{
				dest[i] = src[i];
			}
			dest[i] = '\0';
		}
	}; // end of the xchar class
	// THIS CLASS IS NOT SAME AS STD::STRING_VIEW
	// ONLY SERVE FOR NOT COPY NOR MOVE OBJECTS
	class xchar_view
	{
	public:
		xchar_view(const xchar &str) : data_(str.get()), length_(str.size()) {}
		xchar_view(const char *str) : data_(str), length_(std::strlen(str)) {}


		void remove_prefix(size_t n)
		{
			data_ += n;
			length_ -= n;
		}
		void remove_suffix(size_t n)
		{
			length_ -= n;
		}
		void swap(xchar_view &other)
		{
			std::swap(data_, other.data_);
			std::swap(length_, other.length_);
		}
		const char *begin() const { return data_; }
		const char *end() const { return data_ + length_; }


		xchar_view &operator=(const xchar &str)
		{
			data_ = str.get();
			length_ = str.size();
 
		}


	private:
		const char *data_;
		size_t length_;
	};
}; // namespace core