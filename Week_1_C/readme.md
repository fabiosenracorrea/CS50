## This is the CS50! Week 1

On this directory, the exercises of Week 1 are covered.

### What was week 1 all about?

Week 1 covers an introduction on the programming language C.

It covered:

* Compilers
* Types, formats, operations
* Conditions, Loops
* Memory, imprecision and overflow

Details can be checked [here](https://cs50.harvard.edu/x/2020/notes/1/#memory-imprecision-and-overflow).

### What was the exercise here?

On this week, an introduction task (which was basically a Hello World, but with user input.) and two exercises were given, each having two options, that diverged on difficulty. The student has to choose only one of each exercise, and it was chosen always the harder one. Details [here](https://cs50.harvard.edu/x/2020/psets/1/).

#### Exercise 1 - Mario

Toward the beginning of World 1-1 in Nintendo’s Super Mario Brothers, Mario must hop over adjacent pyramids of blocks, per the below.

![Mario](/Week_1_C/pyramids.png)

Let’s recreate those pyramids in C, albeit in text, using hashes (#) for bricks. Each hash is a bit taller than it is wide, so the pyramids themselves are also be taller than they are wide.

The program we’ll write will be called mario. And let’s allow the user to decide just how tall the pyramids should be by first prompting them for a positive integer between, say, 1 and 8, inclusive.

If the user doesn’t, in fact, input a positive integer between 1 and 8, inclusive, when prompted, the program should re-prompt the user until they cooperate.

##### Grade

**10/10 100%** - as per below:

![mario grade](/Week_1_C/mario10.png)

#### Exercise 2 - Credit

A credit (or debit) card, of course, is a plastic card with which you can pay for goods and services. Printed on that card is a number that’s also stored in a database somewhere, so that when your card is used to buy something, the creditor knows whom to bill. There are a lot of people with credit cards in this world, so those numbers are pretty long: American Express uses 15-digit numbers, MasterCard uses 16-digit numbers, and Visa uses 13- and 16-digit numbers. And those are decimal numbers (0 through 9), not binary, which means, for instance, that American Express could print as many as 10^15 = 1,000,000,000,000,000 unique cards! (That’s, um, a quadrillion.)

Actually, that’s a bit of an exaggeration, because credit card numbers actually have some structure to them. All American Express numbers start with 34 or 37; most MasterCard numbers start with 51, 52, 53, 54, or 55 (they also have some other potential starting numbers which we won’t concern ourselves with for this problem); and all Visa numbers start with 4. But credit card numbers also have a “checksum” built into them, a mathematical relationship between at least one number and others. That checksum enables computers (or humans who like math) to detect typos (e.g., transpositions), if not fraudulent numbers, without having to query a database, which can be slow. Of course, a dishonest mathematician could certainly craft a fake number that nonetheless respects the mathematical constraint, so a database lookup is still necessary for more rigorous checks.

###### Luhn’s Algorithm

So what’s the secret formula? Well, most cards use an algorithm invented by Hans Peter Luhn of IBM. According to Luhn’s algorithm, you can determine if a credit card number is (syntactically) valid as follows:

1. Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together.
2. Add the sum to the sum of the digits that weren’t multiplied by 2.
3. If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!

That’s kind of confusing, so let’s try an example with David’s Visa: 4003600000000014.

For the sake of discussion, let’s first underline every other digit, starting with the number’s second-to-last digit:

4003600000000014

Okay, let’s multiply each of the underlined digits by 2:

1•2 + 0•2 + 0•2 + 0•2 + 0•2 + 6•2 + 0•2 + 4•2

That gives us:

2 + 0 + 0 + 0 + 0 + 12 + 0 + 8

Now let’s add those products’ digits (i.e., not the products themselves) together:

2 + 0 + 0 + 0 + 0 + 1 + 2 + 0 + 8 = 13

Now let’s add that sum (13) to the sum of the digits that weren’t multiplied by 2 (starting from the end):

13 + 4 + 0 + 0 + 0 + 0 + 0 + 3 + 0 = 20

Yup, the last digit in that sum (20) is a 0, so David’s card is legit!

So, validating credit card numbers isn’t hard, but it does get a bit tedious by hand. Let’s write a program.

In a file called credit.c in a ~/pset1/credit/ directory, write a program that prompts the user for a credit card number and then reports (via printf) whether it is a valid American Express, MasterCard, or Visa card number, per the definitions of each’s format herein. So that we can automate some tests of your code, we ask that your program’s last line of output be AMEX\n or MASTERCARD\n or VISA\n or INVALID\n, nothing more, nothing less. For simplicity, you may assume that the user’s input will be entirely numeric

#### Grade

**15/15 100%** - as per below:

![credit grade](/Week_1_C/credit_grade.png)

### Comments

C is a very constrained language, and learning a bit better how to interact with it helps to improve my overall algorithm logic.

###### Feedback

As always, any feedback is widely encouraged.