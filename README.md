# danishBox - Revive your childhood
Academic project for  the oop's university course.
## Description
**danishBox** is a simple "game" developed using C++11 and Qt5.7.1 library where you can impersonate 3 type of users dealing with dealicious boxes of danish cookies.
## Purpouse
The purpouse of this project was to learn and implement the theory of Object Oriented Programming, focused on an efficient use of the polymorphism.<br>
The project could also add until 3 points to the final course evaluation.
## Development
The Development phase of this project toke place between August and early Sempteber of 2017, and was supported by Git on the Bitbucket platform.<br>
No test was required for the assignment so i haven't wrote any.<br>
Here's the configuration of the machine where i developed the code:
* Ubuntu-Gnome 16.10
* GCC 6.20
* Qt 5.7.1

## Documentation
There's very little documentation for the code and poorly it was written in italian, since i took this course in the University of Padua.<br>
You can find the specification under *specification[ITA].pdf* file and a brief description of the project design and development under *report[ITA].pdf* file, both placed in the root directory of the repository.
## Play
If you want to try the game and you own a 64 bit linux machine you can directly run the program using the *x64_linux_build* folder that contain an executable file and a ready to run "database" that store users, boxes and items information.
To run it just type:
```bash
sudo chmod +x danishBox
./danishBox
```
That will open the main window.<br>
There are 3 users you can play with:<br>

username | password
--- | ---
admin | admin
grandma | grandma
kiddo | kiddo

You can find a brief user's guide inside *report[ITA].pdf*.

## Portability
The code was compiled successfully on several linux machine but i have no clue on the behavior it would have on Windows and OSX platforms.

---
# Develop
Here's a simple guide to develop new feature yourself.
## Requirements
To compile the code you need to install:
* GCC compiler that support C++11 features
* Qt >= 5.5.1 with is qmake utility

See their own documentation to learn how to install them.
## Compile
To compile the code you have to enter in the *src* folder and type:
```bash
qmake
make
```
It will build the project and make an executable file to run the application.<br>
## Reccomended tools
If you are not familiar with the C++/Qt ecosistyem you can download and install *Qt creator* IDE that provide fast and simple ways to write and debug the application.
