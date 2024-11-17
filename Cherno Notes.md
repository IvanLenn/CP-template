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

- A reference is the content itself. If pass into function by reference, you are the object itself.
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

### Constructor

- A special type of method that runs every time we instantiaze a class instance.
- Can delete constructor or hide in private

```cpp
#include <iostream>
class Log {
    int x;
public:
    Log() = delete;
    Log(int x) : x(x) {}
};

int main() {
    Log T(1); // Log T(); will error
}
```

### Inheritance

- Mostly useful to avoid code duplication
- Derived class is always a superset of base class
- Where we use the base class types, we can always pass in derived classes, because it contains every methods and variables of the base class. The other way around will error because the base class doesn't necessarily have everything from derived class.

```cpp
#include <iostream>
class Entity {
public:
    float X, Y;
    void Move(float xa, float ya) {
        X += xa; Y += ya;
    }
};
class Player : public Entity {
    const char* Name;
};
void f(Entity e) {
    std::cout << e.X << std::endl;
}

int main() {
    Player T;
    T.Move(1, 1);
    f(T);
}
```

### (Pure) Virtual Functions

- One virtual table for every class instance, and will have exactly one entry for every virtual functions in each vtable.
- Good practice: adding both virtual keyword in base class methods and override keyword in derived class methods.
- Overhead: additional memory to store vtable; and dynamic dispatch to retrieve the correct function to call each time.

```cpp
#include <iostream>
class Entity {
public:
    std::string GetName() {return "Entity";} // Change to virtual std::string GetName() {return "Entity";}
};
class Player : public Entity {
private:
    std::string m_Name;
public:
    Player(const std::string& name) : m_Name(name) {}
    std::string GetName() {return m_Name;} // Change to std::string GetName() override {return m_Name;}
};

void PrintName(Entity* entity) {
    std::cout << entity->GetName() << std::endl;
}

int main() {
    Entity* e = new Entity();
    PrintName(e); // Entity, OK
    Player* T = new Player("Apple");
    PrintName(T); // Entity, Wrong
    delete e; delete T;
}
```

- Pure virtual functions force derived classes to overload the virtual functions because sometime it doesn't make sense to define in base class.
- AKA interface in Java.
- Classes with pure virtual functions are abstract class. Can't create an object of an abstract class.

```cpp
#include <iostream>
class Printable {
public:
    virtual void print() = 0;
};

class Entity : public Printable{
public:
    void print() override {std::cout << "Entity" << std::endl;}
};
class Player : public Entity {
public:
    void print() override {std::cout << "Player" << std::endl;}
};

void PrintClassname(Printable* p) {
    p->print();
}

int main() {
    // Printable* p = new Printable; // Impossible
    Entity* e = new Entity;
    Player* p = new Player;
    PrintClassname(e); // Entity
    PrintClassname(p); // Player
    // delete e; delete p; // Can't do that. Need virtual destructor.
    // Because an object of a derived class may be destroyed through a pointer to the base.
}
```

### Visibility

- Default visibility is private for class, and public for struct.
- Private: only this entity class or classes or functions with friend keyword can access private members.
- Protected: this entity class and all subclasses along the hierarchy can also access members.
- Nothing to do with performance or computer understanding. Purely for human-understandability.
  - Eg. User should NOT use private members and only stick with interface

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

## Const

### General usage

- Can get away const restrictions. Example below:

```cpp
#include <iostream>
int main() {
    const int MX = 100;
    int* a = (int*)&MX;
    // *a = 1; // Undefined behavior. Likely compiler will optimize and substitute 100 for all MX occurence
    printf("%d\n%d\n", *a, MX); // Could output 1, 100
}
```

- Const F* / F const*: a pointer to type of const F. Can change the pointer itself but not the value it is pointing to.
- F* const: The pointer itself is const. Can change the value the pointer points to.

```cpp
int main() {
    const int* a = new int(5);
    int const* b = new int(5);
    // *a = 1; *b = 1; // Not OK
    a = nullptr; b = nullptr;

    int* const c = new int(5);
    *c = 1;
    // c = nullptr; // Not OK

    const int* const d = new int(5);
    // *d = 1; d = nullptr; // Not OK

    delete a; delete b; delete c; delete d;
}
```

### Class usage

- Const after method: the method will not modify members of class. The const will also prevent all potential modifications. Example below:

```cpp
#include <iostream>
class Entity {
public:
    int X;
    int* Y;
    // This also doesn't compile because the returned reference can potentially modify X
    // int& GetX() const {
    //     return X;
    // }
    const int& GetX() const {  // OK
        return X;
    }
    const int* GetX2() const { // OK
        return &X;
    }
		
  	// It's okay as long as not modifying Y directly. But client can still modify *Y
    // Not good
    // int* GetY2() const {
    //     return Y;
    // }
  
    const int* GetY() const {
        return Y;
    }
};

int main() {
    Entity T;
    T.X = 1;
    T.Y = new int(1);
    // Can get away with const though. But it's bad practice
    int* y = (int*)T.GetY();
    *y = 2;
    printf("%d", *T.Y);
}
```

- Similarly, can't call non-const class methods for a const reference to a class (or any other similar cases).

```cpp
#include <iostream>
class Entity {
public:
    int X;
    int getX() {return X;}
    int getX2() const {return X;}
};

void PrintEntity(const Entity& e) {
    // std::cout << e.getX() << std::endl; Can't do. Must declare Entity::getX const
    std::cout << e.getX2() << std::endl; // OK
}
```

## Mutable

### Class scenario

- Can change mutable variables in const member methods
- Similarly, can return reference / pointers to mutable objects

```cpp
class Entity {
private:
    std::string m_Name;
    mutable int m_DebugCount = 0;
public:
    const std::string& GetName() {
        m_DebugCount++;
        return m_Name;
    }
};
```

### General scenario

- Rare case: lambda capture variables by value. Need mutable to change the copy of variables captured by value.

```cpp
#include <iostream>

int main() {
    int x = 8;
    // This lambda captures everything by value, so all external variables will mark as const
    // auto f = [=]() {
    //     x++;
    //     std::cout << x << std::endl;
    // };

    // By marking lambda as mutable, we can modify the copy of x. Original x is not changed.
    auto f = [=]() mutable {
        x++;
        std::cout << x << std::endl;
    };
    f();
    assert(x == 8);
}
```



## Array

- Allocate arrays on stack or heap

```cpp
#include <iostream>
#include <cassert>
#include <array>

int main() {
    int a[5];
    int* b = new int[5];
    std::array<int, 5> c;
    std::cout << sizeof(a) << ' ' << sizeof(b) << ' ' << sizeof(c) << std::endl; // 20, 8, 20
    delete[] b;
}
```



```cpp
#include <iostream>
#include <cassert>

int main() {
  int a[5];
  for (int i = 0; i < 5; i++) a[i] = i;
  int* ptr = a;
  assert(*(ptr + 2) == 2); // Equivalently, assert(*(int*)((char*)ptr + 8) == 2);
}
```

## String (literal)

- Any strings with quota are string literals. String literal always stores in read-only memory. Undefined behavior to modify it.
- Utf-32 char, for example, has type char32_t.
- wchar_t occupies 2 or 4 bytes depending on systems.

```cpp
#include <iostream>
int main() {
    char s[6] = "Apple";
    s[0] = 'B';
    printf("%s", s); // OK, Bpple

    char* t = "Apple";
    t[0] = 'B'; // Undefined behavior. Dependent on compiler
    printf("%s", t); 
  
  	const wchar_t* x = L"Apple";
    const char16_t* y = u"Apple";
    const char32_t* z = U"Apple";

    // const char* r = "Apple";
    // r[0] = 'B'; // Can't modify const char
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