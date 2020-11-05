/* Important if we want to define some portion of code, ex. class, which will act as
header only library, which also has static element.

Normally, if we have some static element and include the header many times, we will
get many instantiations of static element, instead of one.

We can handle that using inline in cpp17.

Not like classic inline, that tells compiler to skip function call, here the inline will
result taking only first found instance of static object for linking. The compiler will assume, that
all other instances, taken from including many times th same header, are exat copies so can be skipped. The
compiler will link the first instance each time.

However, the compiler will not guarantee that all symbols will have the same exact body. It is on
programmer side to handle that. If it will not be the same, the compiler will not tell us about it.

*/

//Example of inline class (like header only lib)

#include <iostream>

class inline_class{
public:
    static const inline int variable{2};
};

inline inline_class oInlineClass;