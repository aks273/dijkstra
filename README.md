# Dijkstra's Algorithm
An old implementation of Dijkstra's algorithm


The input file format is as follows:

- One line containing a single integer N, the number of places.
- N lines each containing a place name (upper- and lower-case letters only).
- One line containing a single integer P, the number of direct paths between places.
- P lines each containing a two place names and an integer, denoting the two ends of that path and its length.
- One or more lines containing test cases, each a pair of places to find the distance between.
- There may blank lines anywhere in the input.

Example:

```
2
Cambridge
London

1
Cambridge London 59

Cambridge London
London Cambridge
```

This describes two places, "Cambridge" and "London", a single path between them with length 59 (miles), and then two problems asking for the distance between the two places in each direction.


The output file should contain one line for each input test case, describing the distance between the two places named.

For the example above:

```
Cambridge -> London: 59
London -> Cambridge: 59
```


Note that paths need not be unique or useful - there could be multiple paths between two places, and there could be a path from a place to itself.  Also note that the whole graph need not be connected together, and you could be asked for the distance between two places which have no path at all between them.
