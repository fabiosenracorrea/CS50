## This is the CS50! Week 4

On this directory, the exercises of Week 4 are covered.

### What was week 4 all about?

It covers hexadecimal notation of memory, how we can build strings using char* and not actually the 'string' type provided in the cs50 library, pointers, how to allocate and free up memory after use, what is a b

* Hexadecimal notation
* Memory Pointers (*) and addresses (&)
* Building strings with char*
* Allocating and freeing up memory with our programs
* Accessing, Appending and Writing on a file
* Basic Image filtering

Details can be checked [here](https://cs50.harvard.edu/x/2020/weeks/4/).

### What was proposed here?

On this week, much like weeks 1 and 3, there was an obligatory exercise and a split, having two options, that diverged on difficulty. The student has to choose only one of the options, and it was chosen the harder one. Details [here](https://cs50.harvard.edu/x/2020/psets/4/).

### Exercise 1 - Filter

This exercise was the 'harder choice' of the week and it covers a creation of 4 algorithms to alter images, applying 'filters' to them:

* Greyscale
* Blur
* Reverse (or mirror)
* Edge

```
In anticipation of this problem, we spent the past several days taking photos of people we know, all of which were saved on a digital camera as JPEGs on a memory card. (Okay, it’s possible we actually spent the past several days on Facebook instead.) Unfortunately, we somehow deleted them all! Thankfully, in the computer world, “deleted” tends not to mean “deleted” so much as “forgotten.” Even though the camera insists that the card is now blank, we’re pretty sure that’s not quite true. Indeed, we’re hoping (er, expecting!) you can write a program that recovers the photos for us!

Even though JPEGs are more complicated than BMPs, JPEGs have “signatures,” patterns of bytes that can distinguish them from other file formats. Specifically, the first three bytes of JPEGs are

0xff 0xd8 0xff

from first byte to third byte, left to right. The fourth byte, meanwhile, is either 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, or 0xef. Put another way, the fourth byte’s first four bits are 1110.

Odds are, if you find this pattern of four bytes on media known to store photos (e.g., my memory card), they demarcate the start of a JPEG. To be fair, you might encounter these patterns on some disk purely by chance, so data recovery isn’t an exact science.

Fortunately, digital cameras tend to store photographs contiguously on memory cards, whereby each photo is stored immediately after the previously taken photo. Accordingly, the start of a JPEG usually demarks the end of another. However, digital cameras often initialize cards with a FAT file system whose “block size” is 512 bytes (B). The implication is that these cameras only write to those cards in units of 512 B. A photo that’s 1 MB (i.e., 1,048,576 B) thus takes up 1048576 ÷ 512 = 2048 “blocks” on a memory card. But so does a photo that’s, say, one byte smaller (i.e., 1,048,575 B)! The wasted space on disk is called “slack space.” Forensic investigators often look at slack space for remnants of suspicious data.

The implication of all these details is that you, the investigator, can probably write a program that iterates over a copy of my memory card, looking for JPEGs’ signatures. Each time you find a signature, you can open a new file for writing and start filling that file with bytes from my memory card, closing that file only once you encounter another signature. Moreover, rather than read my memory card’s bytes one at a time, you can read 512 of them at a time into a buffer for efficiency’s sake. Thanks to FAT, you can trust that JPEGs’ signatures will be “block-aligned.” That is, you need only look for those signatures in a block’s first four bytes.

Realize, of course, that JPEGs can span contiguous blocks. Otherwise, no JPEG could be larger than 512 B. But the last byte of a JPEG might not fall at the very end of a block. Recall the possibility of slack space. But not to worry. Because this memory card was brand-new when I started snapping photos, odds are it’d been “zeroed” (i.e., filled with 0s) by the manufacturer, in which case any slack space will be filled with 0s. It’s okay if those trailing 0s end up in the JPEGs you recover; they should still be viewable.

Now, I only have one memory card, but there are a lot of you! And so I’ve gone ahead and created a “forensic image” of the card, storing its contents, byte after byte, in a file called card.raw. So that you don’t waste time iterating over millions of 0s unnecessarily, I’ve only imaged the first few megabytes of the memory card. But you should ultimately find that the image contains 50 JPEGs.


The function grayscale should take an image and turn it into a black-and-white version of the same image.

The reflect function should take an image and reflect it horizontally.

The blur function should take an image and turn it into a box-blurred version of the same image.

The edges function should take an image and highlight the edges between objects, according to the Sobel operator.
```
#### Grade

**23/23 100%** - as per below:

![filter grade](./filter_grade.png)

### Exercise 2 - Recover

```
Implement your program in a file called recover.c in a directory called recover.

Your program should accept exactly one command-line argument, the name of a forensic image from which to recover JPEGs.

If your program is not executed with exactly one command-line argument, it should remind the user of correct usage, and main should return 1.

If the forensic image cannot be opened for reading, your program should inform the user as much, and main should return 1.

Your program, if it uses malloc, must not leak any memory.
```

#### Grade

**6/6 100%** - as per below:

![filter grade](./recover_grade.png)

### Comments

**Filter**: Here the student started to make use of 'check50', a command available to check correctness of the code before actually submitting. That's why it only has one submission recorded, since every correction to the code was done on the same day. The student wanted to 'keep every function as a whole', which is why every function was kept as a huge 1 piece. This code was also use to explain the simple logic behind the problem to other fellow programmers, which is another reasons as to why it's in a single piece.

The problem itself was really nice, requiring good matrix knowledge and awareness.

**Recover**: The goal of this exercise was to recover jpg photos from a raw data file. While the constraints of the project were not very high, understanding how to handle files made this exercise very fun. The general ideia of the solution took some ideas of the pre-written code we had on Filter, but the a-ha! moment was find out i could create a single file pointer and, from there, do the naming, opening, writing and closing logic.


###### Feedback

As always, any feedback is widely encouraged.