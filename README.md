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
**class that serves as an alternative to the built-in const char* data type offering a variety of functions and transformations for**:
- **xchar to char***
- **const char* to char**
- **xchar to std::string**
#### Example:
```cpp
using xch=core::xchar;
xch var="Ex";
    xch array[5]={"hello",var,"world",5,std::string("hello world")};
    for (int i=0; i<4;++i){
        std::cout <<array[i] << std::endl;
    }
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