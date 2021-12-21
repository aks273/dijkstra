#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#include "dijkstra.h"

#define MAX_VERTICES (100 * 1000)
#define MAX_EDGES    (1000 * 1000)

// Usage: read in the input file as stdin
// $ cat input_file | ./read_input > output_file
int main(void)
{
    char tmp[256];
    int i, ret;

    // Open the file and read the number of vertices (1st line of file)
    ret = read_next_line(tmp, sizeof(tmp));
    if (ret < 0) {
        fprintf(stderr, "File is empty?\n");
        return 1;
    }
    sscanf(tmp, "%d", &number_of_vertices);

    if (number_of_vertices > MAX_VERTICES) {
        fprintf(stderr, "Too many vertices!\n");
        return 1;
    }
    // printf("There are %d vertices.\n", number_of_vertices);

    // Setup the matrix and the array of names
    int ** matrix = malloc(sizeof(int*) * number_of_vertices);
    char *names[number_of_vertices];

    // Make the matrix an 2D array of -1s
    for (int j = 0; j < number_of_vertices; j++){
        matrix[j] = malloc(sizeof(int) * number_of_vertices);
        for (int k = 0; k < number_of_vertices; k++){
            matrix[j][k] = -1;
        }
    }

    // Get the names of each of the vertices
    for (i = 0; i < number_of_vertices; i++) {
        ret = read_next_line(tmp, sizeof(tmp));
        if (ret < 0) {
            fprintf(stderr, "Unexpected end of file reading vertex %d!\n", i);
            return 1;
        }

        names[i] = malloc(strlen(tmp) + 1);
        strcpy(names[i], tmp);
        // printf("Vertex %d is called '%s'.\n", i, names[i]);
    }

    // Get the number of edges (second number in file after a newline)
    ret = read_next_line(tmp, sizeof(tmp));
    if (ret < 0) {
        fprintf(stderr, "Unexpected end of file reading number of edges!\n");
        return 1;
    }
    sscanf(tmp, "%d", &number_of_edges);
    if (number_of_edges > MAX_EDGES) {
        fprintf(stderr, "Too many edges!\n");
        return 1;
    }
    // printf("There are %d edges.\n", number_of_edges);

    // Get the weights for each of the edges
    for (i = 0; i < number_of_edges; i++) {
        ret = read_next_line(tmp, sizeof(tmp));
        if (ret < 0) {
            fprintf(stderr, "Unexpected end of file reading edge %d.\n", i);
            return 1;
        }

        char *next;
        char *from = strtok_r(tmp, " ", &next);
        if (!from) {
            fprintf(stderr, "No 'from' vertex name at edge %d.\n", i);
            return 1;
        }

        char *to = strtok_r(next, " ", &next);
        if (!to) {
            fprintf(stderr, "No 'to' vertex name at edge %d.\n", i);
            return 1;
        }

        // gets the indices of the two vertices connecting the edge (from, to)
        int j = index_for_name(from, names);
        int k = index_for_name(to, names);

        char *dist_string = strtok_r(next, " ", &next);
        if (!dist_string) {
            fprintf(stderr, "No distance for edge %d.\n", i);
            return 1;
        }

        // Gets the weight of the edge
        int dist = -1;
        sscanf(dist_string, "%d", &dist);
        if (dist < 0) {
            fprintf(stderr, "Invalid distance %d.\n", dist);
            return 1;
        }
        // printf("Edge %d between '%s' and '%s' has length %d.\n",
            //    i, from, to, dist);

        // Puts the weight of the edge into the matrix, if that matrix element
        // is empty (-1) or it is lower than the current path.
        if (
            (matrix[j][k] < 0 && matrix[k][j] < 0) || 
            (dist < matrix[k][j] && dist < matrix[j][k])
        ) {
            matrix[k][j] = dist;
            matrix[j][k] = dist;
        } else {
            // printf("\tNot inserting this distance into the matrix, we already have a shorter path!\n");
        }
    }

    // print_matrix(matrix);

    // The file now only has vertices that we want to find the minimum distance
    // between (e.g. "A B\n")
    // This gets the to and from names of the question lines of the text file
    // and then calculates the minimum path between them using dijkstra.
    while ((ret = read_next_line(tmp, sizeof(tmp))) > 0)
    {
        char *next;
        char *from = strtok_r(tmp, " ", &next);
        if (!from) {
            fprintf(stderr, "No 'from' in the question %d.\n", i);
            return 1;
        }

        char *to = strtok_r(next, " ", &next);
        if (!to) {
            fprintf(stderr, "No 'to' in the question %d.\n", i);
            return 1;
        }

        int dij = dijkstra(matrix, from, to, number_of_vertices, names);
        if (dij < INT_MAX) {
            printf("%s -> %s: %i\n", from, to, dij);
        } else {
            printf("%s and %s are not connected\n", from, to);
        }     
    }

    // Cleanup
    for (int i = 0; i < number_of_vertices; i++) {
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}


