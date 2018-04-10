
from nltk.tokenize import sent_tokenize


# Return the lines found in a string

def getLines(a):
    lines = []
    length = len(a)
    line = ""
    for i in range(length):
        # We must have found a new line
        if a[i] == "\n":
            # Test to see if the line is not empty, before we add it
            if len(line) > 0:
                lines.append(line)
                line = ""
                continue
        # Append `a[i]` at the end of the line
        line += a[i]
    # Append last line
    if len(line) > 0:
                lines.append(line)
    return lines

# Return list of substring of length n of a

def getSubstrings(a, n):
    aLength = len(a)
    substrings = []
    if(aLength < n):
        return []
    else:
        for i in range(aLength - (n - 1)):
            substrings.append(a[i : i + n])
    return substrings

# Return lines in both a and b

def lines(a, b):
    similarLines = []
    # Get list of lines in `a` and `b`
    aLines = getLines(a)
    bLines = getLines(b)
    # Save lines count in `a` and `b`
    aLinesCount = len(aLines)
    bLinesCount = len(bLines)
    # Compare lines in `a` and `b`
    for i in range(aLinesCount):
        for j in range(bLinesCount):
            # Compare to see if the two lines are egal
            if aLines[i] == bLines[j]:
                similarLines.append(aLines[i])

    return set(similarLines)

# Return sentences in both a and b

def sentences(a, b):
    similarSentences = []
    # Get list of sentences in `a` and `b`
    aSentences = sent_tokenize(a)
    bSentences = sent_tokenize(b)
    # Save sentences count in `a` and `b`
    aSentCount = len(aSentences)
    bSentCount = len(bSentences)
    # Compare sentences in `a` and `b`
    for i in range(aSentCount):
        for j in range(bSentCount):
            # Compare to see if the two lines are egal
            if aSentences[i] == bSentences[j]:
                similarSentences.append(aSentences[i])
    # return similar sentences
    return set(similarSentences)


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    aSubstrings = getSubstrings(a, n)
    bSubstrings = getSubstrings(b, n)
    # Return intersection of `a` and `b` using build-in python
    # method
    return set(aSubstrings).intersection(bSubstrings)

