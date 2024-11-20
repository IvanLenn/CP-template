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

### Function pointer

- Assign a function to variable; pass functions into other functions as parameters.
- Function-to-Pointer Decay: In C++, when you use a function name in most contexts, it automatically decays (converts) to a pointer to that function.

```cpp
#include <iostream>

void HelloWorld() {
    static int i = 1;
    std::cout << i++ << std::endl;
}

int main() {
    // In all examples, with or without & doesn't matter b/c of function-to-pointer decay
    // #1
    void(*f1)();
    f1 = &HelloWorld;
    // #2
    auto f2 = &HelloWorld;
    // #3
    void (*f3)() = HelloWorld;
    // #4
    typedef void(*add)();
    add f4 = &HelloWorld;
    // #5
    std::function<void()> f5 = HelloWorld;
    f1(); f2(); f3(); f4(); f5(); // 1 2 3 4 5
}
```

- `std::function` is more flexible and can work with various callable objects, not just function pointers.

```cpp
#include <iostream>
#include <vector>

void ForLoop(const std::vector<int>& values, void(*func)(int)) {
    for (int value : values) {
        func(value);
    }
}

void ForLoop2(const std::vector<int>& values, std::function<void(int)> func) {
    for (int value : values) {
        func(value);
    }
}

int main() {
    std::vector<int> val = {1, 5, 4, 1, 8};
    ForLoop(val, [](int val){ std::cout << val << std::endl; });
    ForLoop2(val, [](int val){ std::cout << val << std::endl; });
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

#### Initializer list

- Makes constructor logic clear. Separate variable initialization with meaningful code.
- Avoid constructing members twice. The default initializer list will intialize everything by default.

```cpp
#include <iostream>

class Entity {
public:
    int x;
    Entity() = delete;
    Entity(int x) : x(x) {}
};

class T {
public:
    Entity X;
    // T() { // Not OK. Default constructor of Entity not found
    //     X = Entity(1);
    // }
    T(Entity& e) : X(e) {
        X.x = 1;
    }
};

int main() {
    Entity e(2);
    T t(e);
    assert(e.x = 2); // Due to default copy constructor, value of e.x is unchanged
}
```

### Copy Constructor

- Default copy constructor only "shallow" copies everything. Especially, only pointer itself but not the content at the pointer address.

```cpp
#include <iostream>
#include <memory>

class String {
    char* m_Buffer;
    unsigned int m_Size;
public:
    String(const char* string) {
        m_Size = strlen(string);
        m_Buffer = new char[m_Size + 1];
        memcpy(m_Buffer, string, m_Size + 1);
        m_Buffer[m_Size] = 0;
    }
    ~String() {
        delete[] m_Buffer;
    }
    // What default copy constructor does
    // String(const String& other) {
    //     memcpy(this, &other, sizeof(String));
    // }
    char& operator[](unsigned int index) {
        return m_Buffer[index];
    }

    friend std::ostream& operator<<(std::ostream& stream, const String& s);
};

std::ostream& operator<<(std::ostream& stream, const String& s) {
    stream << s.m_Buffer;
    return stream;
}

int main() {
    String string = "Apple";
    String second = string;
    second[0] = 'B';
    std::cout << string << std::endl; // Bpple
    std::cout << second << std::endl; // Bpple
    // Will Crash here. Double free in destructor
}
```

- Alternatively, define the copy constructor to initialize a new buffer memory.

```cpp
String(const String& other) : m_Size(other.m_Size) {
    std::cout << "Copied" << std::endl;
    m_Buffer = new char[m_Size + 1];
    memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
}
```

- If we define a print function by passing in ```String``` or ```String&``` type:

```cpp
void Print(const String& string) { // Will call copy constructor 2 times more if only passing in String
    std::cout << string << std::endl;
}

int main() {
    String string = "Apple";
    String second = string;
    second[0] = 'B';
    Print(string);
    Print(second);
    // This is possible if the type is const String& instead of String&. Can't bind rvalue to lvalue reference
    Print("A");
}
```





### *this

- Only present inside methods. Is a pointer to the current object itself.
- Type of ***this*** is ```class*``` or ```const class*``` depending on whether the method has const. It is ***never*** ```class* const``` or ```const class* const```.
- Pointer ***this*** is not an lvalue.
- **Question: Why can't modify value of this if it's not const after \*? This makes sense intuitively, but not logically. Perhaps same as 5 = 3 is incorrect although 5 is not const int? **

```cpp
#include <iostream>

void PrintEntity(const Entity& e);

class Entity {
    public:
    int x, y;
    Entity(int x, int y) {
        // Entity* e = this;        // Ok.
        // Entity* const& e = this; // Ok. Making sure we can't modify this directly
        this->x = x;
        this->y = y;
        PrintEntity(*this);
    }
    int GetX() const {
        // const Entity* e = this; // Ok. Review const :)
        return this->x;
    }
};

void PrintEntity(const Entity& e) {
    // Print
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

- Derived class need to call base class contructor in the initializer list.
- If using pointers, we need to define virtual constructor for base classes with virtual functions. The reason is potentially we might cast it to base pointers and then the destructors can't be correctly called.
- When a derived class object is destroyed, the destructors are called in reverse order of the inheritance hierarchy. The derived class destructor is called first, followed by the base class destructor.

```cpp
#include <iostream>

class BaseClass {
protected:
    int x = 0;
public:
    BaseClass(int x) : x(x) {
        std::cout << "Base created" << std::endl;
    }
    virtual void Test() = 0;
    virtual ~BaseClass() {
        std::cout << "Base deleted" << std::endl;
    }

};

class TestClass : public BaseClass {
public:
    TestClass(int x) : BaseClass(x) {
        std::cout << "Test created" << std::endl;
    }
    void Test() override {
        std::cout << x << std::endl;
    }
    ~TestClass() override {
        std::cout << "Test deleted" << std::endl;
    }
};

class ProduceClass : public BaseClass {
public:
    ProduceClass(int x) : BaseClass(x) {
        std::cout << "Produce created" << std::endl;
    }
    void Test() override {
        // Nothing
    }
    ~ProduceClass() override {
        std::cout << "Produce deleted" << std::endl;
    }
};

int main() {
    TestClass* T = new TestClass(5);
    ProduceClass* F = new ProduceClass(5);
    T->Test(); F->Test();
    delete T; delete F;
}
```



### Visibility

- Default visibility is private for class, and public for struct.
- Private: only this entity class or classes or functions with friend keyword can access private members.
- Protected: this entity class and all subclasses along the hierarchy can also access members.
- Nothing to do with performance or computer understanding. Purely for human-understandability.
  - Eg. User should ***not*** use private members and only stick with interface

### Static

- Static in class share memory with all instances of class
  - Static methods can't access non-static variables
  - Only non-static methods get the class itself as hidden parameters. 
  - Extend lifetime of static variables insid class functions.

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

## Smart Pointer

### Unique pointer

- A scoped pointer: when out of scope will get deleted.
- Can't copy a ***unique*** pointer. Can move a unique pointer.
- Constructor of unique pointer is explicit.

```cpp
#include <iostream>
#include <memory>

class Entity {
public:
    Entity() {
        std::cout << "Created Entity" << std::endl;
    }
    ~Entity() {
        std::cout << "Destroyed Entity" << std::endl;
    }
    void Print() {}
};

int main() {
    {
        // std::unique_ptr<Entity> entity(new Entity());
        std::unique_ptr<Entity> entity = std::make_unique<Entity>(); // Better for exception handling
        // std::unique_ptr<Entity> e0 = entity; // Error. Copy constructor is deleted
        entity->Print();
    }
    // entity no longer valid
}
```

### Shared pointer

- Uses reference counting: keep track of how many reference count exists to the object.
- Can copy or move.

```cpp
#include <iostream>
#include <memory>

class Entity {
public:
    Entity() {
        std::cout << "Created Entity" << std::endl;
    }
    ~Entity() {
        std::cout << "Destroyed Entity" << std::endl;
    }
    void Print() { std::cout << "Random" << std::endl; }
};

int main() {
    std::shared_ptr<Entity> e0;
    {
        std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>();
        // std::shared_ptr<Entity> sharedEntity(new Entity()); // Ok, but not efficient.
        e0 = sharedEntity;
    }
    e0 -> Print();
}
```

### Weak pointer

- Assign shared pointer to weak pointer will not increase reference count.
- Great for if we don't want take ownership of object.
- Can break circular dependency caused by ```shared_ptr```.
- ```e0.lock()``` returns a rvalue of type ```std::shared_ptr<Entity>```

```cpp
#include <iostream>
#include <memory>

class Entity {
public:
    Entity() {
        std::cout << "Created Entity" << std::endl;
    }
    ~Entity() {
        std::cout << "Destroyed Entity" << std::endl;
    }
    void Print() { std::cout << "Random" << std::endl; }
};

int main() {
    std::weak_ptr<Entity> e0;
    {
        std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>();
        e0 = sharedEntity;
        if (auto sharedE0 = e0.lock()) {
            sharedE0 -> Print();
        }
    }
    assert(!e0.lock());
}
```

## Standard template library

- Data type that the container contains is for users to decide.

### Vector

- `push_back()` creates a temporary object and then moves or copies it into the vector.
- `emplace_back()` constructs the object directly inside the vector, avoiding the creation of a temporary object.
- `reserve` will allocate memory but doesn't construct any objects.

```cpp
#include <iostream>
#include <vector>

struct Vec3 {
    float x, y, z;
    Vec3(int x, int y, int z) : x(x), y(y), z(z) {
        std::cout << "Constructed" << std::endl;
    }
    Vec3(const Vec3& other) : x(other.x), y(other.y), z(other.z) {
        std::cout << "Copied" << std::endl;
    }
};

int main() {
    {
        std::vector<Vec3> v; // 3 default constructor + 6 copy constructor
        v.push_back(Vec3(7, 8, 9));
        v.push_back(Vec3(7, 8, 9));
        v.push_back(Vec3(7, 8, 9));
    }
    {
        std::vector<Vec3> v;
        v.reserve(3); // Can save 3 copy constructs b/c no need to resize & copy
        v.push_back(Vec3(7, 8, 9));
        v.push_back(Vec3(7, 8, 9));
        v.push_back(Vec3(7, 8, 9));
    }
    {
        std::vector<Vec3> v;
        v.reserve(3);
        v.emplace_back(7, 8, 9); // No copy construct at all
        v.emplace_back(7, 8, 9);
        v.emplace_back(7, 8, 9);
    }
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

- ```Const F*``` or ```F const*```: a pointer to type of const F. Can change the pointer itself but not the value it is pointing to.
- ```F* const```: The pointer itself is const. Can change the value the pointer points to.

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
#include <vector>

struct Vec3 {
    float x, y, z;
    Vec3(int x, int y, int z) : x(x), y(y), z(z) {
        std::cout << "Constructed" << std::endl;
    }
    Vec3(const Vec3& other) : x(other.x), y(other.y), z(other.z) {
        std::cout << "Copied" << std::endl;
    }
};

int main() {
    {
        std::vector<Vec3> v; // 3 default constructor + 6 copy constructor
        v.push_back(Vec3(7, 8, 9));
        v.push_back(Vec3(7, 8, 9));
        v.push_back(Vec3(7, 8, 9));
    }
    {
        std::vector<Vec3> v;
        v.reserve(3); // Can save 3 copy constructs b/c no need to resize & copy
        v.push_back(Vec3(7, 8, 9));
        v.push_back(Vec3(7, 8, 9));
        v.push_back(Vec3(7, 8, 9));
    }
    {
        std::vector<Vec3> v;
        v.reserve(3);
        v.emplace_back(7, 8, 9); // No copy constructor at all b/c we are constructing them directly
        v.emplace_back(7, 8, 9);
        v.emplace_back(7, 8, 9);
    }
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

## Template

- Get the compiler to write code given the rules (types).
- `template<typename T>` and `template<class T>` are interchangable.
- If we didn't use template function, the compiler does nothing. Even not compilation error.
- Otherwise, the compiler will create multiple versions of template functions for each type we used.

```cpp
#include <iostream>
#include <vector>

template<typename T> // Almost interchangable with template<class T>
void Foo(T value) {
    Not used. Not even compilation error.
}

template<typename T> // Almost interchangable with template<class T>
void Print(T value) {
    std::cout << value << std::endl;
}

int main() {
    Print<int>(5);
    Print("Apple"); 
}
```

- Non-type template parameters must be compile-time constants. This means their values must be known at compile time.

```cpp
#include <iostream>
#include <vector>

// Not only can we pass in types
template<typename T, int N>
class Array {
private:
    T m_Array[N];
public:
    int GetSize() const { return N; }
};

int main() {
    Array<std::string, 5> array;
    std::cout << array.GetSize() << std::endl;
}
```

## Lambda functions

- Whenever we have a function pointer, we can use lambda.
- Raw function pointers cannot capture state or context. Need to use `std::function`instead.

```cpp
#include <iostream>
#include <vector>

void ForLoop(const std::vector<int>& values, void(*func)(int)) {
    for (int value : values) {
        func(value);
    }
}

void ForLoop2(const std::vector<int>& values, std::function<void(int)> func) {
    for (int value : values) {
        func(value);
    }
}

int main() {
    std::vector<int> val = {1, 5, 4, 1, 8};
    int a = 5;
    ForLoop(val, [](int val){ std::cout << val << std::endl; });
    // ForLoop(val, [=](int val){ std::cout << val << std::endl; }); // Not OK
    ForLoop2(val, [](int val){ std::cout << val << std::endl; });
    ForLoop2(val, [=](int val){ std::cout << val << std::endl; }); // OK
}
```

## Auto

- Compiler will automatically deduct the type of variables for you.
- Useful in case of changing API doesn't need to change client code.
- It's not going to capture `const` or `reference`. Need to use them explicitly for example `const auto&`.

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

class A{};
class AManager{
private: 
    std::unordered_map<std::string, std::vector<A*>> mp;
public:
    const std::unordered_map<std::string, std::vector<A*>>& Get() { return mp; }
};

int main() {
    std::vector<std::string> str;
    str.push_back("Apple");
    str.push_back("Orange");
    // Use auto instead of std::vector<std::string>::iterator
    for (auto it = str.begin(); it < str.end(); it++) {
        std::cout << *it << std::endl;
    }

    AManager T;
    const auto& mp = T.Get();
    assert(mp.empty());
}
```



## Thread

- Calling join() waits for the thread to finish execution before continuing. If you don't join or detach a thread, and the std::thread object is destroyed, the program will terminate (`std::terminate` is called).
- Threads can communicate via shared memory, message queues, signals, etc,.

```cpp
#include <iostream>
#include <thread>
#include <vector>

static bool s_Finished = false;
int t;

void DoWork() {
    using namespace std::literals::chrono_literals;
    std::cout << "Thread id=" << std::this_thread::get_id() << std::endl;
    while (!s_Finished) {
        std::cout << "Working...\n";
        std::this_thread::sleep_for(1s);
    }
}

void Work(int i) {
    std::cout << t++ << std::endl;
}

int main() {
    std::thread worker(DoWork);
    std::cin.get();
    s_Finished = true;
    worker.join(); // Main process will block until thread returns.
    std::cout << "Finished." << std::endl;

    std::vector<std::thread> threads;
    for (int i = 0; i < 5; i++) {
        threads.emplace_back(Work, i);
    }
    for (auto& thread : threads) thread.join();
    std::cout << "Finished" << std::endl;
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

## Memory

- Stack allocation: 
  - Easier, faster, no need to free. Literally just moving stack pointer for memory allocated.
  - Limited size, will be invalidated when out of scope (end of block, etc,)
  - Useful in case of timer / smart pointer that does automatic heap delete when out of scope.
- Heap allocation:
  - Larger size possible, lifetime can be as long as possible
  - A lot CPU cycles. Need to go through the free list and allocate memory.

```cpp
#include <iostream>
#include <string>

class Entity {
    std::string m_Name;
public:
    Entity() : m_Name("Unknown") {}
    Entity(const std::string& name) : m_Name(name) {}
    const std::string& GetName() const {return m_Name;}
};

int main() {
    Entity *a, *b;
    {
        a = new Entity("Apple"); // Heap allocation
        Entity e;                // Stack allocation
        b = &e;
    }
    // std::cout << b->GetName() << std::endl; // Undefined behavior
    std::cout << a->GetName() << std::endl;
    delete a;
}
```

- Both stack and heap memory are in RAM, just stack is usually smaller (~2MB).

### New

- New will allocate memory using malloc (sizeof(class) * len) and call the class constructor.
- Must use delete for every new with exactly the same pointer.
- In C++11 or later, if the argument list is shorter than allocated length, all the rest are default constructed.

```cpp
#include <iostream>
#include <cassert>

class Entity {
    std::string m_Name;
public:
    Entity() : m_Name("Unknown") {}
    Entity(const std::string& name) : m_Name(name) {}
    const std::string& GetName() const {return m_Name;}
};

int main() {
    Entity *a = new Entity[2];
    assert(a[1].GetName() == "Unknown");
    delete[] a;

    Entity *b = new Entity[2]{std::string("Apple"), std::string("Banana")};
    assert(b[0].GetName() == "Apple");
    assert(b[1].GetName() == "Banana");
    delete[] b;
}
```

## Operator (overloading)

```cpp
#include <iostream>
#include <cassert>

struct Vec2 {
    float x, y;
    Vec2(float x, float y) : x(x), y(y) {}
    Vec2 operator+(const Vec2& other) const {
        return Vec2(x + other.x, y + other.y);
    }
    Vec2 operator*(const float mul) const {
        return Vec2(x * mul, y * mul);
    }
    bool operator==(const Vec2& other) const {
        return x == other.x && y == other.y;
    }
    bool operator!=(const Vec2& other) const {
        return !operator==(other);
    }
};

std::ostream& operator<<(std::ostream& stream, const Vec2& other) {
    stream << other.x << ", " << other.y;
    return stream;
}

int main() {
    Vec2 pos(1.0f, 1.0f);
    Vec2 speed(0.5f, 1.5f);
    Vec2 res = pos + speed * 2.0f;
    std::cout << res << std::endl;
    assert(res != Vec2(2.1f, 4.0f));
}
```

- Overloading the arrow operator
  - `entity->Print()` is interpreted by the compiler as `(entity.operator->())->Print();`

```cpp
#include <iostream>
#include <memory>

class Entity {
public:
    int x;
    void Print() const { std::cout << "Hi" << std::endl;}
};

class ScopedPtr {
private:
    Entity* m_Obj;
public:
    ScopedPtr(Entity* obj) : m_Obj(obj) {}
    ~ScopedPtr() { delete m_Obj; }
    Entity* operator->() const { return m_Obj; }
};

int main() {
    const ScopedPtr entity = new Entity();
    entity->Print();
}
```



## Conversion

### Implicit conversion

- Compiler automatially converts types

- Compiler will only perform implicit conversion ***once*** at a time. See example below:

```cpp
#include <iostream>
#include <cassert>

class Entity {
    std::string m_Name;
    int m_Age;
public:
    Entity(int age) : m_Name("Unknown"), m_Age(age) {}
    Entity(const std::string& name) : m_Name(name), m_Age(-1) {}
};

void PrintEntity(const Entity& e) {
    // Print
}

int main() {
    Entity a("Apple"); // Ok. 1 implicit conversion: const char* to std::string
    Entity b(5);
    PrintEntity(10); // OK. Converts 10 to Entity b/c of constructor
    // Error. "Apple" : const char* can't convert to Entity. 2 implicit conversions required.
    // PrintEntity("Hi");
}
```

### Explicit

- Put in front of constructor so that it must be explicitly called. See example below:

```cpp
#include <iostream>
#include <cassert>

class Entity {
    std::string m_Name;
    int m_Age;
public:
    explicit Entity(int age) : m_Name("Unknown"), m_Age(age) {}
    Entity(const std::string& name) : m_Name(name), m_Age(-1) {}
};

void PrintEntity(const Entity& e) {
    // Print
}

int main() {
    // PrintEntity(10); // Error. This constructor is explicit
    PrintEntity(Entity(10)); // Ok. 
    // Ok. This constructor can perform implicit conversion from std::string to Entity
    PrintEntity(std::string("Apple"));
} 
```

## Macro

- During preprocess compiler expands macros. Can replace text in out code ***before compilation***.

- Can separate debug and release mode.

```cpp
#include <iostream>
#include <string>

#ifdef DEBUG
#define LOG(x) std::cout << x << std::endl
#else
#define LOG(X)
#endif

// Run with g++ ${file}.cpp -o ${file} -std=c++17 -Wall -Wextra -O3 -DDEBUG
//  Or with g++ ${file}.cpp -o ${file} -std=c++17 -Wall -Wextra -O3
int main() {
    LOG("Hello");
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

### Static array

- Size need to know during compiler time. No performance code, and can keep track of size.

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

## Arraw operator

- Getting offset location

```cpp
#include <iostream>
#include <memory>

struct Vec3 {
    float x, y, z;
};

int main() {
    long long offset = (long long)&((Vec3*)nullptr)->z;
    std::cout << offset << std::endl; // 8
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