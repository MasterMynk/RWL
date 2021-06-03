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
void rwl::update();
```

`rwl::update()` updates the windows created by your program.

### rwl::end()

Signature:

```C++
void rwl::end();
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
