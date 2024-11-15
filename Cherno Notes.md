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

### Array

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