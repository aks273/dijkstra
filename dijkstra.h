// filled in when we read the input file
static int number_of_vertices;
static int number_of_edges;

void print_matrix(int ** matrix) {
    for (int p = 0; p < number_of_vertices; p++)
    {
        for (int q = 0; q < number_of_vertices; q++)
        {
            printf("%i\t", matrix[p][q]);
        }
        printf("\n");
    }
}

// function that reads the next line of stdin
static int read_next_line(char *buf, size_t size)
{
    while (1) {
        char *s = fgets(buf, size, stdin);
        if (!s)
            return -1;
        if (buf[0] == '\0' || buf[0] == '\n')
            continue;

        size_t len = strlen(buf);
        if (buf[len - 1] == '\n')
            buf[--len] = '\0';
        return len;
    }
}



// function that gets the index for a particular vertex name
int index_for_name(char *from, char **names)
{
    for (int j = 0; j < number_of_vertices; j++)
    {
        if (strcmp(names[j], from) == 0)
        {
            return j;
        }
    }
    return -1;
}

// program that returns the index with the smallest integer in an integer array,
// that has not been visited
int minimum_index(int array[number_of_vertices], bool visited[number_of_vertices])
{
    int j = 0;
    while (visited[j] == true)
    {
        j++;
    }
    
    for (int i = j; i < number_of_vertices; i++)
    {
        if ((array[i] < array[j]) && !visited[i])
        {        
            j = i;
        }
    }
    return j;
}



// Dijkstra algorithm
int dijkstra(int ** matrix, char * from, char * to, int number_of_vertices, char ** names)
{
    int distances[number_of_vertices];
    for (int i = 0; i < number_of_vertices; i++)
    {
        distances[i] = INT_MAX;
    }

    int start_index = index_for_name(from, names);
    int end_index = index_for_name(to, names);
    bool visited[number_of_vertices];
    for (int i = 0; i < number_of_vertices; i++)
    {
        visited[i] = false;
    }
    

    int min_ind;

    distances[start_index] = 0;

    for (int j = 0; j < number_of_vertices; j++)
    {
        min_ind = minimum_index(distances, visited);

        if (min_ind == end_index)
        {
            return distances[min_ind];
        }
        else
        {  
            for  (int i = 0; i < number_of_vertices; i++)
            {
                if (matrix[min_ind][i] > 0)
                {
                    if (distances[i] > distances[min_ind] + matrix[min_ind][i])
                    {
                        distances[i] = distances[min_ind] + matrix[min_ind][i];
                    }
                }
            }
        }
        visited[min_ind] = true;
    }
    return distances[end_index];
}