# RWL (Regular Windowing Library)

## What is RWL?

RWL is a wrapper library for XCB. Till now it can connect to the X Server and update the screen.

## How do I include it in my project?

In your root CMakeLists.txt file, add the line `add_subdirectory(RWL)`. This does everything that is neccesary for you to include `<rwl/rwl.hpp>` project and get started.

## Goals

* To be able to create and draw in Windows inside Linux and Windows.
* To be able to handle events inside Windows and Linux.

## Documentation

### rwl::update()

Signature:

```C++
inline void rwl::update();
```

`rwl::update()` updates the windows created by your program.

### rwl::end()

Signature:

```C++
inline void rwl::end();
```

`rwl::end()` does all the cleanup necessary after your program finishes.

### rwl::loop()

Signature:

```C++
void loop(std::function<void (bool &finished)> func);
```

`rwl::loop()` takes in a function as an argument called `func`. `func` should take in a `bool` reference as an argument, let's call it `finished` for now. `rwl::loop` will keep looping until `finished` is set to true.

On every iteration it updates the windows by calling `rwl::update()` so you dont have to do that.

When `finished` is set to true, it exits the loop and runs `rwl::end()` before giving control back to the caller.

Example:

NOTE: This example was tested with g++ version 11.1.0

```C++
#include <rwl/rwl.hpp>

int main() {
  // Initialization ...

  // Main loop
  rwl::loop([&](bool &finished) {});

  // Cleanup

  return EXIT_SUCCESS;
}
```

## What is Vec2?

Vec2 is simply a union for holding 2 pieces of data. Usually some form of an Int or a float. It has a union of structs that contain 2 pieces of data called x and y or width and height.

x = width

y = height.

Example of constructing a Vec2:

```C++
rwl::Vec2<float> vecf(2.f, 10.f);
```

It can also be created with argument for its constructor.

```C++
rwl::Vec2<int> veci(1);
```

In this case both x and y will be set as 1.

To access its data you can simply:

```C++
std::cout << veci.x;
std::cout << veci.height;
```

It also has an operator overload for printing to the console with std::cout and looks something like this:

```C++
std::cout << veci; // Output: 1, 1
```

You can perform all normal arithmetic operations on 2 Vec2s or a Vec2 and a primitive data type. If only a primitive is specified the operator will be done on both x and y with the same primitive.
Example:

```C++
std::cout << veci + vecf << '\n' // Output: 3, 11
          << veci + 2; // Output: 3, 3
```

Compound operator overloads are also implemented:

```C++
std::cout << veci += vecf // Output: 3, 11
std::cout << veci // Output: 3, 11
```
