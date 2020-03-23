# Outline
**Papercards** is an open source program which, in contrast to many other programs, is designed for creating and managing flashcards for printing.
**Papercards** is designed to make writing and managing your flashcards easy and clear.
A direct print view is irreplaceable, no matter if several cards on one sheet or all cards individually, no matter if A4 or A6, **Papercards** combines software and paper.

# Roadmap
## Version 1.0
- Creation of a basic view for creating, managing and editing cards
- Management of different decks with individual cards
- Creation of a PDF with A6 flashcards

# Compile from Source
**Papercards** is based on Qt and supports both major compiling platforms (`cmake` and `qmake`). It's desined to work and Unix based systems (MacOs and Linux) but may work on Windows as well.

Tested Platform:
- Ubuntu 18.04 (Qt 5.14.1)
- MacOs 10.15.3 (Qt 5.14.1)

### Compile with CMake (3.12+)
```shell
cd <papercards-src>
mkdir build
cd build
cmake ..
cmake --build . -j 2
```

### Compile with qmake (3.1+)
```shell
cd <papercards-src>
mkdir build
cd build
qmake ..
make -j 2
```

