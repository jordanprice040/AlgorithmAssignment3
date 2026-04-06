# Programming Assignment 3: Dynamic Programming & HVLCS

Jordan Price (UFID 77967971) \
Collin Williams (UFID 73358805)

## Compiling

There is only one source file, `main.cpp`, which can be compiled
with your C++ compiler of choice. Its only dependencies are
within the standard library. We used C++17 to compile it, but earlier
versions might work as well. A `CMakeLists.txt` has also been provided.

## Executing

After compiling the program, you can run it by passing a file path
as the first command line argument.

ex. `AlgorithmAssignment3.exe ".\tests\test1.txt"`

The runtime of the algorithm can also be measured by passing
the `--measure-runtime` flag:

ex. `AlgorithmAssignment3.exe ".\tests\test1.txt" --measure-runtime`

## Assumptions

The input format matches the format provided in the assignment instructions.

The weights are non-negative integer values.

## Question 1: Empirical Comparison

The results below show the average runtimes of the 16 test files. To compare the runtime of various input sizes, the code was averaged
across 5 separate runs of the algorithm.
The runtimes shown are measured in microseconds.
As demonstrated below in **Question 3**, the runtimes scale
proportionally to `len(A) × len(B)`, even for large inputs.

![](/results/hvcls_runtime.png)

## Question 2: Recurrence Relation

For the following inputs:
```
string A = a[1], a[2], ..., a[n]
string B = b[1], b[2], ..., b[m]
values V[a], v[b], ..., v[z]
```

A recurrence relation is given by:

![](/results/opt_latex.png)

To demonstrate this is correct, first note that evaluating `OPT(n, m)`
will evaluate `OPT` for every combination of `(i, j)` at least once.
Each iteration does at least 2 checks: removing the last
character of `A` (`OPT(i-1, j)`) and removing the last
character of `B` (`OPT(i, j-1)`). Any possible
`i ∈ [0, n], j ∈ [0, m]` can be reached by subtracting from `i` and `j`
a certain number of times, thus this will iterate over the entire domain of `OPT`.

Next, note that in the case where both strings end with the same character,
we also evaluate `OPT(i-1, j-1)` and add the weight `V[A[i]]` to the result.
This represents removing the end of each string and collecting the relevant value.
Since this is inside the `max` function, the weight will only be collected if
we can't find a more valuable subsequence by waiting until later
to remove the final characters.

## Question 3: Big-Oh

The following pseudocode calculates the length of the HVCLS
of strings `A` and `B`:

```
Input: Same as question (2)

for i ∈ [0, n], j ∈ [0, m]
    M[i, j] = 0

for i ∈ [1, n], j ∈ [1, m]
{
    M[i, j] = max{ M[i-1, j], M[i, j-1] }
    if (A[i] == B[j])
        M[i, j] = max{ M[i, j], M[i-1, j-1] + v[A[i]] }
}

return M[n, m]
```

This pseudocode has runtime `O(nm)`, where `n` is the length of `A`
and `m` is the length of `B`. This is because the for loop must
iterate over the entire domain of `M` (of size `m × n`), including
values that don't factor into the largest substring. Since the
results of each iteration are memorized, the runtime cannot exceed
`O(nm)`.