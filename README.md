# Coding Style
---

The style of this project is based off the Google C++ style (https://google.github.io/styleguide/cppguide.html) with the following variations:

1. The base indentation is 4 spaces.
2. Global variables start with "g_", typedefs with "t_", and member variables with "m_".
3. Instead of prepending a constant variable name with "k", they will be in UPPER CASE like in the C style
4. camelCase is used instead of snake_case
5. Curly braces open in next line for functions, classes, enums or structs. For conditional flow, switch cases and loops, they open in the same line!
6. Commenting style for functions is the QT creator supplied commenting.

# Creational Design Pattern
---

The creational design pattern used is the Builder pattern
There is an abtract builder, a concrete one and a director that returns the built level.

# Object Oriented Design
---

Every level is an object, every stickman is an object. Level consists of a stickman. Dialog is a frame that contains a level to begin with.
Classes used are as follows:
1. __Level (level.h and level.cpp)__:
    * Stickman
    * offset (for scrolling the background)
    * background (image)
    * screen velocity
    * music playlist and music player
    * frame height, width and base
2. __Stickman (stickman.h and stickman.cpp)__:
    * size
    * image height
    * image itself
    * X and Y position of the stickman
3. __Dialog (dialog.h and dialog.cpp)__:
    * level
4. __Newconfiguration (newconfiguration.h and newconfiguration.cpp)__:
    * dialog (which is the game itself)
    * Labels and push buttons
5. __SaveForm (saveform.h and saveform.cpp)__:
    * labels, input fields and push buttons
6. __GameBuilder, Mario and MarioCreator__:
    * Abstract builder class, concrete builder and director respectively

# Config File
---

The config file is of filetype json. The configuration like size, background etc are stored as keys and the data as values.
Error checking is done for invalid config files.
