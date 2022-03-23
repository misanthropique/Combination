# Combination

A utility class for enumerating over the combinatoric subsets of a combination.
For a collection of N elements, choosing K elements, there are a total of N choose K subsets.
The enumeration of those subsets is a collection of offsets into the original collection.
Enumeration starts at [ 0, 1, 2, ..., K - 1 ], and ends at [ N - k, ..., N - 2, N - 1 ].
For cases where N < K, or N = 0, or K = 0, then there is no enumeration.
