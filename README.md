SqliteDatabase
==============

SqliteDatabase is a basic C++ wrapper around the SQLite database library.

Build
-----

You need a recent version of [Microsoft Visual Studio](https://visualstudio.com/) to build the project.

Download the latest version of the [SQLite amalgamation sources](https://www.sqlite.org/download.html)
and put them in the project directory.

Now you should be able to build the project. You may need to retarget your solution.


Using the library
-----------------

Include `SqliteDB.cpp` and `SqliteDB.h` in your project, as well as the SQLite
amalgamation sources, and you should be ready to go.
