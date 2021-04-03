# CompletePureShuffle

A simulator to determine how many items you need to pull from an infinite random set until you have the entire set.
For example, this can be used to work out how many times you need to roll a fair six-sided die until you see each number at least once.

This code offers two different solutions: the mean and the mode.
The mean can be thought of as a situation where you have thousands of people all rolling dice until they see each face once.
The mean will be the average of the counts for each person.  
The mode tells you the most common number of rolls you need to do to finish.
This appears to always be less than the mean.

The [Results](#Results) section has the results for some common cases.
`n=2` is for a fair coin, `n=4, 6, 8, 10, 12, 20` are for standard dice with 4 through to 20 faces, `n=54` and `n=52` are for decks of cards with and without jokers, respectively.

## Compiling

Compile with

```shell
gcc shuffler.c -o shuffler
```

### Compiler Flags

There are several compiler flags that can be used to modify the behaviour of the program.

| Flag | Effect |
| --- | --- |
| `MEAN` | Returns the mean value of all the runs |
| `MODE` | Returns the mode of the run |
| `FREQ_TABLE` | Returns the count of each value when used in conjunction with MODE |
| `DEBUG` | Prints debug output while running |
| `VERBOSE` or `V` | Prints verbose debug output when used in conjunction with DEBUG |
| `TOTAL_PRINT` | Prints the total of each run |

At least one of `MEAN` or `MODE` must be used otherwise no result will be printed.
All other flags are optional.

```shell
gcc shuffler.c -o shuffler -DFLAG1 -DFLAG2
```

For example, if you want to print the mean, mode, and the frequency table for the mode, you would use:

```shell
gcc shuffler.c -o shuffler -DMEAN -DMODE -DFREQ_TABLE
```

The order of the flags does not matter.

## Running

Run the program with

```shell
./shuffler n i
```

where `n` is the number of different random items to choose from and `i` is the number of times to run the test.

## Results

You may be curious about the results for some numbers.
Each of these tests was done for one million runs `./shuffler n 1000000`, however, results may still vary between runs.

| `n` | Mean | Mode |
| --- | --- | --- |
| 2 | 2 | 3 |
| 3 | 5.5 | 4 |
| 4 | 8.333 | 6 |
| 5 | 11.417 | 8 |
| 6 | 14.700 | 11 |
| 8 | 21.743 | 17 |
| 10 | 29.290 | 23 |
| 12 | 37.239 | 28 |
| 20 | 71.955 | 59 |
| 52 | 235.978 | 209 |
| 54 | 247.073 | 217 |

As `n` increases, the mode (and, to a lesser extent, the mean) begins to vary significantly between runs.

## Mathematical Expression

There is a mathematical way to find a solution to this problem, which is great because it's so much faster to solve than taking millions of samples.

### Mean

Without going into the details of how this expression was found (hint: it uses probabilities and expected values), the equation for the mean is given below:

<img src="https://render.githubusercontent.com/render/math?math=n\sum_{k=1}^n \frac{1}{k}">

The beauty of this is that it is simply the [Harmonic number (<img src="https://render.githubusercontent.com/render/math?math=H_{n}">)](https://en.wikipedia.org/wiki/Harmonic_number) multiplied by `n`.

It can even be approximated for large `n` with:

<img src="https://render.githubusercontent.com/render/math?math=n\left(\ln(n)%2B\gamma\right)">

where <img src="https://render.githubusercontent.com/render/math?math=\gamma=0.57721\ldots"> is the [Euler-Mascheroni constant](https://en.wikipedia.org/wiki/Euler%E2%80%93Mascheroni_constant).

### Code

There is also a software implementation for this so you can compare the speed for yourself.
The time complexity is `O(n)` as opposed to `O(ni)` for the non-mathematical implementation, where `i` is the number of iterations.

As with the non-mathematical implementation, the code can be compiled the same way (but using the `math_shuffler.c` file instead) with the following compiler flags:

| Flag | Effect |
| --- | --- |
| MEAN | Returns the equivalent of MEAN in the original implementation |

This version only requires one argument (`n`) as it only ever needs to run one iteration.
