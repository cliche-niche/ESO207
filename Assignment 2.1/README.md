This is the submission for "Programming Assignment-2.1" in the course "ESO207A: Data Structure & Algorithm" by Aditya Tanwar (200057) and Akhil Agrawal (200076).

The only `C++` file in this directory is [Q1.cpp](./Q1.cpp) which has code for the given problem statement. The other file is [Analysis.pdf](./Analysis.pdf) which contains pseudo-code and its complexity analysis.

For implementational purposes, some auxiliary functions as well as class had to be created in addition to `Merge` and `Test`.

+ The code for `Extract` starts from line#23
+ The code for `MakeSingleton` starts from line#62
+ The code for `Test` starts at line #109. Please only change the limits in the for-loop, and the initial MakeSingleton lines.
+ The code for `Merge` is broken down into two parts due to implementational constraints, `Merge` calls `MergeNode`.
    + `Merge` starts from line #70.
    + `MergeNode` is declared at line#68, but the definition starts from line#136.
+ The code for `main` starts from line#129 and it contains only the `Test` function.