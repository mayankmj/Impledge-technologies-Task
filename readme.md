#WORD COMPOSITION PROBLEM
Impledge Technologies interview coding test 2023

#CODE EXECUTION STEPS:
> Download / Clone the repo into your System.
> Just open the Sample.cpp file
> Make sure the input files should be in the same folder
> Just hit the compiler and run option and get the output

 #Problem Statement understanding:
 > The probelm is asking to find a string that is formed by the Concatenation of the smaller strings present in the input
> Output the longest and second longest string we can get by concentenation of smaller strings
> Also the output the Time taken in the compilation of the problem in milliseconds

#Approach
> My fav lang is C++ , so devise the solution in this language
> First thing was to choose an appropiate Data structure , Recursive approach can also be used but it have an exponential time complexity, not be fit for larger strings
> Next thing we can think of is the DSU? but dsu is used to find the ultimate and immediate parent , which is not too much appropiate
> So, finally we decided to use TRIE , data structure , which helps us to find the string pattern matching function due to its effective graph structure
> We, implemented Trie which have following functions -> Insert ,  check for contain , getPrefixes(Returns all the possible prefixes already present in the trie)
> The main funtion is findLongestCompoundWords , It checks if the suffix exists in the Trie as a complete word and if the current word's length is greater than the longest length foundso 
 far (word.length() > longest_length).
> If both conditions are true, it updates the longest_word and longest_length variables with the information from the current word.
and it updates the second_longest variable with the previously longest word (second_longest = longest_word) to keep track of the second longest word.
