# Computer Store Manager

C++ inventory system for a computer store, built for 159.234 Object-Oriented Programming (Massey University, 2025).

- Polymorphic class hierarchy: a `Computer` base class with `Desktop`, `Laptop` and `Tablet` derived classes
- `computers.txt` is parsed on startup into `vector<Computer*>` through a factory function that builds the matching derived class from each row
- Virtual `displayinfo()` prints the fields specific to each item type
- Search the inventory by several criteria
- Staff can add, delete and update records, with try/catch error handling
- A virtual destructor and a final delete loop free every object on exit

## Files

| File | What it is |
|---|---|
| `oldmain.cpp` | The whole program in one file: classes, functions and `main()` |
| `main.cpp` | The refactored entry point, which uses `includes/functions.h` and `includes/classes.cpp` |
| `computers.txt` | Inventory loaded on startup |
| `computer_updated.txt` | Inventory after a run of staff changes |

## Build

```
g++ main.cpp includes/functions.cpp includes/classes.cpp -Iincludes -o main.exe
./main.exe
```
