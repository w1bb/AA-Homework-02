# Octavian's Saga

This repository is intended to store a set-cover implementation written in
modern C++. A copy of the assignment shall be provided as well.

**Full completion date:** 06 / 01 / 2023

**Soft deadline:** 19 / 01 / 2023

**Hard deadline:** 19 / 01 / 2023

This project will be made available
[on Github](https://github.com/w1bb/AA-Homework-02) once the hard deadline
passes.

## License

Once the hard deadline passes, this project will be available under the **MIT
license**. For more info about the author of the code, please check out
[my personal website](https://v-vintila.com). Other interesting projects are
made available on [my GitHub page](https://github.com/w1bb) (a follow would be
greatly appreciated!).

## Documentation

The following subsections will provide an in-depth explanation of how the
algorithms actually operate. Please check out the code as well!

### File structure

The project is split into multiple parts, following this file structure:

```
src = The current folder containing the checker and the implementation;
├── Makefile = The Makefile that will be used in order to build & run the
¦              algorithms correctly;
├── README = The original README file;
├── redemption.cpp = The algorithm that solves the 'redemption' task;
├── rise.cpp = The algorithm that solves the 'rise' task;
├── SAT.cpp = The SAT communication protocol code;
├── SAT.hpp = The SAT communication protocol header;
└── trial.cpp = The algorithm that solves the 'trial' task;

assignment.zip = The original assignment archive;
assignment.pdf = The original assignment;
README.md = This file.
```

The checker details were left out intentionally.

### Running the checker

In order to run the automated checker, please run `./check` from the `src`
folder. If a single task should be tested, you can run `./check --task TASK`,
where `TASK` can be `trial`, `rise` or `redemption`.

More info can be found in the original archive (`assignment.zip`).

### Task 1. Trial

The first task can be easily solved by considering the fact that each card can
only be found in zero or more of the $M$ provided sets. This means that, if one
of the cards is part of the $s_1,..,s_t$ sets (with $t\in\mathbb{N}$), a condition
asking for at least one of them to be included in the final purchase must be
set. This can be accomplished using the following formula:

$$s_1\vee s_2\vee ... \vee s_t$$

By doing this for each card, we make sure that each card will be included at
least once in the final pack:

$$(s_{c_1,1}\vee ... \vee s_{c_1,t_1})\,\wedge\,...\,\wedge\,(s_{c_n,1}\vee ... \vee s_{c_n,t_n})$$

 However, this condition is not enough, since we
are interested to check if the problem can be solved using exactly $k$ sets.

By changing the problem and asking for *at most* $k$ sets instead, one could
encode the "at most $k$ constraint" in the SAT query. This can be accomplished
in many ways, but my algorithm implements the **sequential** encoder.

Further information about such encoders can be read here:
- [SAT Encodings of the At-Most-k Constraint](https://www.it.uu.se/research/group/astra/ModRef10/papers/Alan%20M.%20Frisch%20and%20Paul%20A.%20Giannoros.%20SAT%20Encodings%20of%20the%20At-Most-k%20Constraint%20-%20ModRef%202010.pdf)
  (by Alan M. Frisch and Paul A. Giannaros) - this paper contains information
  about a lot more algorithms and summarizes the Sequential Encoder;
- [Towards an Optimal CNF Encoding of Boolean Cardinality Constraints](https://www.carstensinz.de/papers/CP-2005.pdf)
  (by Carsten Sinz) - this is the original paper about Sequential Encoders.

Of course, this will result in *at most* $k$ sets, but since choosing any
unchosen sets would still yield a correct answer, such a method can be applied
to get the requested number of sets instead.

### Task 2. Rise

By using a `map`, one could convert strings to integers with ease and solve the
problem using the algorithm implemented above.

Since a "*at most* $k$ sets" algorithm has already been written, one could
perform a linear / binary search to find the optimal $k$ that solves the
problem.

> Note: The examples provided yield better results using a linear search, but,
>       in order to generalize for harder tests, the implementation uses binary
>       search instead.

### Task 3. Redemption

The approximation makes use of two distinct algorithms, chosen based on the pack
size provided at the input stage. If $p$ is small enough, a brute force
algorithm can be used to provide an exact answer in a small amount of time.
However, if $p$ is big, a greedy approach that always chooses the pack that
contains the most cards that weren't already chosen and are required will
provide a good enough approximation.

More information can be found bellow:
- [Wikipedia - Set Cover / Greedy algorithm](https://en.wikipedia.org/wiki/Set_cover_problem#Greedy_algorithm);
- [Jeremy Kun's article - The Many Faces of Set Cover](https://jeremykun.com/2015/05/04/the-many-faces-of-set-cover/).
