## This is the CS50! Week 2

On this directory, the exercises of Week 2 are covered.

### What was week 2 all about?

Week 2 covers an introduction on data structures, covering how an array is created and manipulated in C, especially when it comes to strings.

Details can be checked [here](https://cs50.harvard.edu/x/2020/weeks/2/).

### What was the exercise here?

On this week, much like last week, there was an obligatory exercise and another having two options, that diverged on difficulty. The student has to choose only one of the options, and it was chosen the harder one. Details [here](https://cs50.harvard.edu/x/2020/psets/2/).

### Exercise 1 - Readability

Now it’s time to put all the pieces together! Recall that the Coleman-Liau index is computed using the formula:

```
index = 0.0588 * L - 0.296 * S - 15.8
```

where L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text.

Modify readability.c so that instead of outputting the number of letters, words, and sentences, it instead outputs the grade level as given by the Coleman-Liau index (e.g. "Grade 2" or "Grade 8"). Be sure to round the resulting index number to the nearest whole number!

If the resulting index number is 16 or higher (equivalent to or greater than a senior undergraduate reading level), your program should output "Grade 16+" instead of giving the exact index number. If the index number is less than 1, your program should output "Before Grade 1".

#### Grade

**11/11 100%** - as per below:

![readability grade](./readability.png)


### Exercise 2 - Substitution

Design and implement a program, substitution, that encrypts messages using a substitution cipher.

1. Implement your program in a file called substitution.c in a ~/pset2/substitution directory.
2. Your program must accept a single command-line argument, the key to use for the substitution. The key itself should be case-insensitive, so whether any character in the key is uppercase or lowercase should not affect the behavior of your program.
3. If your program is executed without any command-line arguments or with more than one command-line argument, your program should print an error message of your choice (with printf) and return from main a value of 1 (which tends to signify an error) immediately.
4. If the key is invalid (as by not containing 26 characters, containing any character that is not an alphabetic character, or not containing each letter exactly once), your program should print an error message of your choice (with printf) and return from main a value of 1 immediately.
5. Your program must output plaintext: (without a newline) and then prompt the user for a string of plaintext (using get_string).
6. Your program must output ciphertext: (without a newline) followed by the plaintext’s corresponding ciphertext, with each alphabetical character in the plaintext substituted for the corresponding character in the ciphertext; non-alphabetical characters should be outputted unchanged.
7. Your program must preserve case: capitalized letters must remain capitalized letters; lowercase letters must remain lowercase letters.
8. After outputting ciphertext, you should print a newline. Your program should then exit by returning 0 from main.

#### Grade

**15/15 100%** - as per below:

![substitution grade](./arrayExs.png)

### Comments

Studying C having JS/Python knowledge is challenging. This exercise would be a cake walk on these languages, but the constraints is C take it to the next level. The puzzling part of the solution was a miss-handle of memory when outputting the crypted text.

The solution first presented here still needs to be refactored, especially when we analyse the size of 'main'. Nonetheless, it handles every possible input and use-case as per described on the instructions.

**08/27/2020 Update:** When doing this week originally, somehow the student missed the exercise 'readability' as an obligatory exercise. It was after a course check on August that this mistake was noticed, and promptly fixed. That's why the completion date on Readability is so far ahead in time when comparing with Substitution.

###### Feedback

As always, any feedback is widely encouraged.