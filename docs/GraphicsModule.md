# Graphics Module

## Introduction

The Graphics Module is a module that allows you to create and manage graphics.

## Opening a window

To open a window, you need to create a `Window` object and call the `open` method.

```cpp
#include <RType/Graphics/Window.hpp>

int main()
{
    int windowWidth = 1920;
    int windowHeight = 1080;
    RTypeEngine::Window window(windowWidth, windowHeight, "My Window Name");
    return 0;
}
```

By doing this, you will create a window with the given width and height and with the given name. The window automatically opens when you create it.

## Bringing it to life

### Keeping the window open

To keep this window alive, we need to have a loop that will keep the window open until we close it. To do this, we can use the `isOpen` method.

```cpp
#include "RTypeEngine/System.hpp"
#include "RTypeEngine/Window.hpp"

int main()
{
    int windowWidth = 1920;
    int windowHeight = 1080;
    RTypeEngine::Window window(windowWidth, windowHeight, "My Window Name");
    while (window.isOpen()) {
        // Our main loop
    }
    return 0;
}
```

And that's it, we now have a window that stays open until we close it. To close the window, we can use the `close` method.

```cpp
    while (window.isOpen()) {
        if (pressedEscape()) {
            window.close();
        }
    }
    return 0;
```

### The event system

Now that we have a window that stays open, we need to be able to interact with it. To do this, we **HAVE** to use the `pollEvent` method.

```cpp
    while (window.isOpen()) {
        window.clear(glm::vec4(0.3f, 0.3f, 0.3f, 1.0f));

        window.pollEvents();

        window.display();
    }
    return 0;
```

Without this method, the window will not be able to receive any event. On multiple platforms, this will result in the window being unresponsive and the user will have to force close it.


<div class="section_buttons">
| Previous          |                              Next |
|:------------------|----------------------------------:|
| [Get Started](GettingStarted.md) | [Event handling](EventSystem.md) |
</div>
