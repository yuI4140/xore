# DOCUMENTATION
## Index

- [**xchar Class**](#Xchar-Class)
- [**xchar view**](#Xchar-View-Class)
- [**Matrix Class**](#Matrix-Class)

---------------------------
## Xchar Class

The Xchar class is a custom implementation of a dynamic string class
that can be resized and manipulated. It is implemented as a
`std::unique_ptr` to a char array and has the following member functions:

### Member Functions

#### Constructors

- `xchar(): data(nullptr)`: 
*Constructs an empty Xchar object.*

- `xchar(const char* ch): data(std::make_unique<char[]>(charlen(ch) + 1))`: 
*Constructs an Xchar obj as a `const char*`*.

- `xchar(std::string_view str)`:
*Take the data from std::string and transform it into a Xchar Obj*

- `xchar(int i)`:
*transforms the `intiger` to a Xchar Obj*

- `xchar(char ch)`:
*Do a `std::make_unique<char[]>` and set the char into frist loc and a null term in second loc*

#### Accessors

- `const char* get() const`: Returns a pointer to the internal char array.

- `size_t size() const`: Returns the size of the internal char array, not including the null terminator.

#### Modifiers

- `void resize(size_t new_size)`: Resizes the internal char array to the specified size. If `new_size` is smaller than the current size, the contents of the internal array are truncated.

#### Private Member Variables

- `std::unique_ptr<char[]> data`: The internal char array, managed by a `std::unique_ptr`.

- `constexpr size_t npos = std::numeric_limits<size_t>::max()`: A constant representing an invalid index in the internal char array.

- `std::stringstream ss`: A `std::stringstream` used for formatting purposes.

- `void xmemcpy(void* dest, const void* src, size_t n, size_t dest_size)`: A private helper function that performs a safe memory copy operation.

- `void charcpy(char* dest, const char* src, size_t destSize) const`: A private helper function that performs a safe string copy operation.

## Xchar View Class

The Xchar View class is a lightweight, non-owning string view class that provides access to a portion of an Xchar object. It has the following member functions:

### Member Functions

#### Constructors

- `xchar_view(const xchar& str)`: Constructs an Xchar View object that provides access to the contents of `str`.

- `xchar_view(const char* str)`: Constructs an Xchar View object that provides access to the contents of `str`.

#### Modifiers

- `void remove_prefix(size_t n)`: Removes the first `n` characters from the Xchar View object.

- `void remove_suffix(size_t n)`: Removes the last `n` characters from the Xchar View object.

- `void swap(xchar_view& other)`: Swaps the contents of the Xchar View object with those of `other`.

#### Accessors

- `const char* begin() const`: Returns a pointer to the first character in the Xchar View object.

- `const char* end() const`: Returns a pointer to one past the last character in the Xchar View object.

#### Operator Overloads

- `xchar_view& operator=(const xchar& str)`: Assigns the contents of `str` to the Xchar View object.

### Private Member Variables
- `const char* data_`: A pointer to a character array holding the data of the string.
- `size_t length_`: An integer representing the length of the string.

## Matrix Class
**TODO!**