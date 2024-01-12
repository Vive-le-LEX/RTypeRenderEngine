# Event System

## Introduction

> You do not need to create an instance of the Event System, it is already created for you and contained in the class instance of `Window`.

It is used to get the events that are happening in the window but also:

• To handle keyboard inputs

• To handle mouse inputs

• To handle window events

## Event handling logic

Contrary to what you might find in other libraries, the event system is not a polling system. It is a system that is based on callbacks. This means that you will have to register a pointer to a function that will be called when an event occurs.

> You can also register stored lambdas as callbacks for smaller functions.

## Keyboard inputs

First of all we need to get the [KeyboardHandler](classRTypeEngine_1_1KeyboardHandler.html) of the window. To do this, we can use the `getKeyboardHandler` method of the [EventHandler](classRTypeEngine_1_1EventHandler.html).

```cpp
RTypeEngine::EventHandler &eventHandler = window.getEventHandler();
RTypeEngine::KeyboardHandler &keyboardHandler = eventHandler.getKeyboardHandler();
```
> IMPORTANT:  Do not forget to get the reference (&) and not copying it.

We can now register a callback for a specific key. To do this, we can use either one of `setKeyRepeatCallback`,`setKeyPressedCallback` or `setKeyReleasedCallback` methods of the [KeyboardHandler](classRTypeEngine_1_1KeyboardHandler.html).

```cpp
keyboardHandler.setKeyPressedCallback(RTypeEngine::Qwerty::A, [&window] (const RTypeEngine::KeyState &s) {
    std::cout << "A key pressed" << std::endl;
});

keyboardHandler.setKeyReleasedCallback(RTypeEngine::Qwerty::Escape, [&window] (const RTypeEngine::KeyState &s) {
    window.close();
});
```

You can also remove a callback by using either one of `removeKeyRepeatCallback`,`removeKeyPressedCallback` or `removeKeyReleasedCallback` methods of the [KeyboardHandler](classRTypeEngine_1_1KeyboardHandler.html).

```cpp
keyboardHandler.removeKeyPressedCallback(RTypeEngine::Qwerty::A);
```

> All the callbacks are called with a [KeyState](structRTypeEngine_1_1KeyState__s.html) as parameter. This structure contains different information about the key that was pressed.

## Mouse inputs

First of all we need to get the [MouseHandler](classRTypeEngine_1_1MouseHandler.html) of the window. To do this, we can use the `getMouseHandler` method of the [EventHandler](classRTypeEngine_1_1EventHandler.html).

```cpp
RTypeEngine::EventHandler &eventHandler = window.getEventHandler();
RTypeEngine::MouseHandler &mouseHandler = eventHandler.getMouseHandler();
```

> IMPORTANT:  Do not forget to get the reference (&) and not copying it.

We can now register a callback for a specific mouse button. On a mouse there is different events that can happen:

• Buttons can be pressed/released that we can set callbacks for using `setMouseClickCallback` and remove them using `removeMouseClickCallback`

• The mouse can move and we can set a callback for this using `setMouseMovedCallback` and remove it using `removeMouseMovedCallback`

• The mouse can enter/leave the window and we can set a callback for this using `setMouseEnterCallback` and remove it using `removeMouseEnterCallback`

• The mouse can scroll and we can set a callback for this using `setMouseScrollCallback` and remove it using `removeMouseScrollCallback`

```cpp
mouseHandler.setMouseClickCallback(RTypeEngine::MouseClick::LEFT, RTypeEngine::MouseClickType::MOUSE_PRESS, [] {
    std::cout << "Left mouse button pressed" << std::endl;
});

mouseHandler.setMouseMovedCallback([](glm::vec2 offset) {
    std::cout << "Mouse offsets: " << offset.x << ", " << offset.y << std::endl;
});

mouseHandler.setMouseEnterCallback([]() {
    std::cout << "Mouse entered the window" << std::endl;
});

...
```

## Gamepad inputs


