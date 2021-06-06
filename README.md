# RWL (Regular Windowing Library)

## What is RWL?

RWL is a wrapper library for XCB. Till now it can connect to the X Server and update the screen.

## How do I include it in my project?

In your root CMakeLists.txt file, add the line `add_subdirectory(RWL)`. This does everything that is neccesary for you to include `<rwl/rwl.hpp>` project and get started.

## Goals

* To be able to create and draw in Windows inside Linux and Windows.
* To be able to handle events inside Windows and Linux.

## Documentation

NOTE: All examples given here are tested on g++ version 11.1.0 with xcb version 1.41-1 on Arch Linux.

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

## General information about the screen

There are functions for getting the width in pixels and millimeters, height in pixels and millimeters and the depth of the screen. Here are their signatures:

```C++
inline uint16_t rwl::width(const rwl::Measurement &m = rwl::Measurement::Pixels);
inline uint16_t rwl::height(const rwl::Measurement &m = rwl::Measurement::Pixels);
inline uint8_t rwl::depth();
```

The width and height functions take in a type of `rwl::Measurement` which is just an enum class containing 2 vairations and those are `Pixels` and `Mm`. So to get the width in Pixels you do:

```C++
rwl::width();
```

And to get it it millimeters you do:

```C++
rwl::width(rwl::Measurement::Mm);
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

There are also 2 aliases for Vec2 for supplying the Position and Dimensions and they look like this:

```C++
using Pos = Vec2<int16_t>;
using Dim = Vec2<uint16_t>;
```

## Color

There is a class called `Color` which is used (as the name suggests) to specify a color. To instantiate it you use a enum present within it called ColorEnum which contains the names of colors you may want to use. Right now the only 2 options are White and Black.

Example of creating a Color object with Black and White colors:

```C++
rwl::Color color(rwl::Color::Black);
rwl::Color color(rwl::Color::White);
```

## Creating a window

RWL provides the Window class for creating windows. You have to initialize it with a dimension and a position. Here's the constructor signature:

```C++
rwl::Window::Window(const rwl::Dim &dim = {640, 480}, const rwl::Pos &pos = {0, 0});
```

As you can see the args do have default params so its not really necessary to specify the dimension or position.

Example Use:

```C++
rwl::Window win(rwl::Dim(1920, 1080));
```

To make the window visible you execute the `show` method on your instance of `rwl::Window` like so:

```C++
win.show();
```

There is also another option which is the `showNoUpdate()` method which doesn't update your changes by running `rwl::update()` so this is useful when you have a call to `rwl::update()` somewhere nearby as it will be more efficient.

Example to show a windo using `showNoUpdate()` method

```C++
win.showNoUpdate();
rwl::update();
```

So here's a complete program that will create a window on your screen with what we've learnt so far:

```C++
#include <rwl/rwl.hpp>

int main() {
  rwl::Window win(rwl::Dim(426, 240));

  win.showNoUpdate();

  rwl::loop([&](bool &finished) {});
}
```

I've used the `showNoUpdate()` method here because if you remember `rwl::loop()` runs `rwl::update()` on every iteration of itself.

There are also `hide()` and `hideNoUpdate()` methods which do as they name say: They hide the windows.

There are also getters and setters for the Dimensions and Position of the window called `getDim()`, `setDim()`, `getPos()` and `setPos()` respectively.

Here are their signatures:

```C++
inline const rwl::Dim &rwl::Window::getDim() const;

inline rwl::Window &rwl::Window::setDim(const Dim &other);

inline const rwl::Pos &rwl::Window::getPos() const;

inline rwl::Window &rwl::Window::setPos(const Pos &other);
```
