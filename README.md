![Xore](xore.png)
## what's the library about?
**It's a multipurpose library.**
**see [features](#features) for know what has got the library!**
### Usage
download it from **github.com/** or do a git clone 

```bat
  git clone --recursive https://github.com/yuI4140/xore.git 
```
*and include in your project.*
## features ↹↔
### xchar class
**class that serves as an alternative to the built-in const char data type offering a variety of functions and transformations for**:
- **xchar to char***
- **const char* to char**
- **xchar to std::string**
#### Example:
```cpp
// 01/25/2023-EXAMPLE
core::xchar var0("hello");
core::xchar var1(143123);//now supports int stable version
core::xchar var2(std::string("hello"));
core::xchar var3('h');
core::xchar arrayOfXchar[200]={var0,var1,var2,var3};
void xfunc(core::xchar_view& view ){
   if(view.size()>5){
       char* data=const_cast<char*>(view.data());
       strcpy(data,"hello");
   }
}
xfunc(arrayOfXchar[2]);
```
### Matrix class
*A matrix dataType that replace the classic C-style matrix*
#### Example:
```cpp
using Matrix=core::Matrix;
Matrix var1={
  {1,2,4},{1,2,5},{1,6,7},{11,3,43,5}
  };
var1.priint();
```
## FAQ
#### can xchar support differents data types?
*Yes. It supports*:
- **std::string**
- **char**
- **const char**
- **also suppports int but it's not stable yet.(01-20-2023)**
## Documentation and futures features
**TODO!**