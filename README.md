# COMP3230-Mointor

This is an utility program (linux) to obtain the execution statistics of a program or sequence of programs connected by pipes.

### Usage:
```
./monitor <prog1> <prog1 flag1> <prog1 flag2> ! <prog2> <prog2 flag1> ...

e.g.1
./monitor cat c3230a.txt ! grep kernel ! wc -w
e.g.2
./monitor firefox
```
