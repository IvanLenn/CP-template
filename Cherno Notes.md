# C++ Notes

## Pointer

```c++
#include <iostream>
int main() {
  int var = 48;
  char* c = (char*)(&var);
  assert(*c == '0' || *c == '\0'); // big or little endianness
  
  char* buffer = new char[8];
  memset(buffer, 48, 8);
  buffer[7] = '\0';
  char** ptr = &buffer;
  printf("%s\n", *ptr);
  delete[] buffer;
}
```

## Reference

- Must initialize, and immutable

```C++
#include <iostream>
// Same as passing in int pointer. No fundemental difference, just syntactic sugar
void inc(int& value) {
  value++;
}
int main() {
  int a = 48;
	int& b = a;
  inc(b);
  inc(a); // a not &a. To pass &a we need to declare inc to pass in int pointer
  assert(a == 50);
}
```

## Class

- Only difference between class and struct is visibility
- Class member functions are automatically inlined. Get rid of inline by separating declaration and implementation.

### Static

- Static in class share memory with all instances of class
  - Static methods can't access non-static variables
  - Only non-static methods get the class itself as hidden parameters. 

```cpp
#include <iostream>
struct Entity {
    static int x;
    int y;
    static void print() {
        std::cout << x << std::endl;
        // std::cout << x << ", " << y << std::endl; // Error: y is not static
    }
};
int Entity::x;

int main() {
    Entity e1{1};
    e1.x = 2;   // Alternatively Entity::x = 2;
    Entity e2{1};
    e2.y = 2;
    e1.print(); // Alternatively Entity::print();
    e2.print();
}
```

- Static outside class: only linked internally inside translational unit
  - If a static variable is in a header file, it will exist in all files that use the header file. During preprocessing compiler will expand header files.
  - Static keyword applies to functions as well

```CPP
// File A
int s_var = 10;
// File B
int s_var = 5; // Error: already defined

// File A
static int s_var = 10;
// File B
int s_var = 5; // OK, s_var = 5

// File A
int s_var = 10;
// File B
extern s_var; // OK, s_var = 10

// File A
static int s_var = 10;
// File B
extern s_var; // Error
```

- Local static: only copy across scope

```cpp
#include <iostream>
void f() {
    static int i = 0;
    std::cout << i++ << std::endl;
}
int main() {
    f(); f(); // 0, 1
}
```

## Enum

```cpp
#include <iostream>
enum Eg : char {
    A = 5, B, C
};

int main() {
    Eg val = B;
    assert(val == 6);
    assert(Eg::C == 7);
}
```



