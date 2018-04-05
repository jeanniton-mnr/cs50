# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

 Is a word invented by the president of the National Puzzlers' League as a
 synonym for the disease known as silicosis. It is the longest word in the English.

## According to its man page, what does `getrusage` do?

`getrusage` determines the ressources used by a process.

## Per that same man page, how many members are in a variable of type `struct rusage`?

They are sixteen (16) members in a variable of type `struct rusage`. Here they are:
	struct timeval ru_utime;	/* user time used */
	struct timeval ru_stime;	/* system time used */
	long	ru_maxrss;		/* max resident set size */
#define	ru_first	ru_ixrss
	long	ru_ixrss;		/* integral shared memory size */
	long	ru_idrss;		/* integral unshared data " */
	long	ru_isrss;		/* integral unshared stack " */
	long	ru_minflt;		/* page reclaims */
	long	ru_majflt;		/* page faults */
	long	ru_nswap;		/* swaps */
	long	ru_inblock;		/* block input operations */
	long	ru_oublock;		/* block output operations */
	long	ru_msgsnd;		/* messages sent */
	long	ru_msgrcv;		/* messages received */
	long	ru_nsignals;		/* signals received */
	long	ru_nvcsw;		/* voluntary context switches */
	long	ru_nivcsw;		/* involuntary " */
#define	ru_last		ru_nivcsw

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

Passing a variable by value to a function required the copy of this variable value to the heap memory of the fonction.
And struct can be a large data. Thus, passing `before` and `after` to memory can take large ressources of
memory and processing time as well (for the copy to the heap).

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

Inside the `for` loop, we read every character of the test file one by one.
We account a word, if it has only alphabetical character and/or apostrophes.
Thus, we check if the char `c` meets that condition, so we can it as a char
of a word. Inside the `for` loop, we also keep track of the length of the word
being proceed. If it is longer then `LENGTH` we consume (cancel the processing
of this word). In the second condition, we evaluate if the char is a digit.
Again, if it is the the case, we cancel the the processing of this word.
Finally, if none of this above condition, we consider the we have reach the last
character of the word and check this word in the dictionary.
After, we start the same process for another word.
PS: We also calcalte the ressources usage everytime we call a function from our
dictionary.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?
The purpose of `fscanf` is to read a block of char as string. We cannot do that here. Cause we
need to need to know things like will the block of a chars in the stream won;t have any
space or a digit. And only way to know that is to evaluate every char of the stream individualy.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?
We declared the parameters for `check` and `load` as `const` to make sure that the program cannot change them.
There are not to be changed by the function either. But just to be used as input for the computation of other
operation.
