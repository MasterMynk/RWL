# RWL (Regular Windowing Library)

## What is RWL?

RWL is a wrapper library for XCB. Till now it can create Windows and draw Rectangles on the screen

## How do I include it in my project?

In your root CMakeLists.txt file, add the line `add_subdirectory(RWL)`. This does everything that is neccesary for you to include `<rwl/rwl.hpp>` project and get started.

## Goals

* To be able to create and draw in Windows inside Linux and Windows.
* To be able to handle events inside Windows and Linux.
