#include "gnl_norm.h" // Or whatever header they provide

// 1. THE ONLY HELPER YOU NEED
// This joins s1 and s2, but importantly, it FREEs s1 when it's done!
char *join_and_free(char *s1, char *s2) {
    int i = 0, j = 0;
    char *res;

    // Find lengths (treating NULL as empty)
    while (s1 && s1[i]) i++;
    while (s2 && s2[j]) j++;

    res = malloc(i + j + 1);
    if (!res) return (NULL);

    i = 0;
    j = 0;
    if (s1) {
        while (s1[i]) { res[i] = s1[i]; i++; }
    }
    while (s2[j]) {
        res[i + j] = s2[j];
        j++;
    }
    res[i + j] = '\0';
    free(s1); // <-- THE MAGIC TRICK TO AVOID LEAKS
    return (res);
}

// 2. THE BRAIN
char *get_next_line(int fd) {
    static char buffer[BUFFER_SIZE + 1]; // Remembers leftovers between calls
    char *line = NULL;
    int i = 0;
    int bytes = 1;

    // Step A: If buffer is empty, read into it
    if (buffer[0] == '\0') {
        bytes = read(fd, buffer, BUFFER_SIZE);
        if (bytes <= 0) return (NULL);
        buffer[bytes] = '\0';
    }

    // Step B: Build the line until we hit a '\n' or run out of file
    while (bytes > 0) {
        line = join_and_free(line, buffer); // Add buffer to our line
        
        // Find if there is a '\n' in what we just added
        i = 0;
        while (line[i] && line[i] != '\n') i++;

        if (line[i] == '\n') {
            // We found a newline! Now we must save the leftovers for the next call.
            int j = 0;
            i++; // move past the '\n'
            while (line[i]) {
                buffer[j++] = line[i]; // Move leftover to front of static buffer
                line[i++] = '\0';      // Cut off the returned line right after '\n'
            }
            buffer[j] = '\0';
            return (line);
        }

        // If no '\n' was found, we need to read more!
        bytes = read(fd, buffer, BUFFER_SIZE);
        if (bytes < 0) { free(line); return (NULL); }
        buffer[bytes] = '\0';
    }
    
    // Step C: End of file reached (bytes == 0)
    return (line);
}