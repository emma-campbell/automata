# Automata

In the spirit of self-enlightenment and an urge to gain an understanding of how theory translates to practice; I present my deep dive into finite automata, more specifically, Deterministic and Non-Deterministic Finite Automata.

The task at hand is to write out some DFA's that recognize
    * Exactly the string `csc173`
    * Any string that starts with `cat`
    * Binary input with an even number of 0's
    * Binary input with an even number of both 1's and 0's

and some NFA's that recognize
    * Strings ending in `code`
    * Strings containing `code`
    * strings with more than one `a`, `g`, `h`, `i`, `o`, `s`, `t`, or `w` and more than two `n`'s

To round it all off, let's make a function that takes an instance of an NFA and returns an instance of a DFA that is equivalent to the original NFA, _meaning it accepts the same language_.

# Build Instructions

As long as you have `make` installed on your system, all you need to do is run

```
make
```

to create the executable. From there, call `./auto` to run the program.

If you need to see the valgrind report, run `make memcheck` and navigate to `/bin`, where you find the generated report.