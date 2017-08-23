# Prefix-Trie-Matching-CPP
Prefix Trie data structure with Pattern Matching, in C++

https://en.wikipedia.org/wiki/Trie

It has been made to work with alphabet "A, C, G, T" for human genome, but the alphabet can be easily modified.

This example collects the so called Reads (samples), which is a collection of strings, named "Patterns", and we want to match them against a reference genome named "Text".
The algorithm finds whether any string in Patterns matches a prefix of Text.
It is able to handle cases where one of the patterns is a prefix of another pattern.

This example uses the next input and output formats:
Input Format: The first line of the input contains a string Text, the second line contains an integer 𝑛,
each of the following 𝑛 lines contains a pattern from Patterns = {𝑝1, . . . , 𝑝𝑛}.
Output Format: All starting positions in Text where a string from Patterns appears as a substring in
increasing order (assuming that Text is a 0-based array of symbols). If more than one pattern appears starting at position 𝑖, outputs 𝑖 once.

Sample 1:
Input:
AAA
1
AA
Output:
0 1
Explanation: The pattern AA appears at positions 0 and 1. Note that these two occurrences of the pattern overlap.

Sample 2:
Input:
ACATA
3
AT
A
AG
Output:
0 2 4
Explanation: Text contains occurrences of A at positions 0, 2, and 4, as well as an occurrence of AT at position 2.
