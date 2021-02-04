# CompletePureShuffle

A simulator to determine how many items you need to pull from an infinite random set until you have the entire set

## Running

Compile with

```shell
gcc shuffler.c -o shuffler
```

To debug, use

```shell
gcc shuffler.c -o shuffler -DDEBUG
```

Run the program with

```shell
./shuffler n i
```

where `n` is the number of different random items to choose from and `i` is the number of times to run the test.