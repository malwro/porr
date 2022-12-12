# PORR
## Files
The _files_ directory contains an example file and the shortest file used in tests.
## Sequential solution
From _sequential_ directory:
### Compile
```
g++ -o seq seq.hpp seq.cpp main.cpp
```

### Run
```
./seq ../files/file.txt
```

## Parallel solution
From _parallel_ directory:
### Compile
```
g++ -o par par.hpp par.cpp main.cpp -fopenmp
```

### Run
```
./par ../files/file.txt
```