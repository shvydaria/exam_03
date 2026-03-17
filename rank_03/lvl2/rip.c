// #include "rip.h"
// #ifndef RIP_H
// # define RIP_H

// # include <stdio.h>

// void solve(char *str, int i, int l, int r, int bal);

// #endif
// The Backtracking Machine
void solve(char *str, int i, int l, int r, int bal) {
    // 1. Prune invalid paths (more closing brackets than opening ones)
    if (bal < 0)
        return;

    // 2. Base Case: Reached the end of the string
    if (str[i] == '\0') {
        // If our budget is exactly 0 and the string is perfectly balanced
        if (l == 0 && r == 0 && bal == 0)
            puts(str);
        return;
    }

    char c = str[i];

    // CHOICE 1: "Remove" it (Replace with space)
    // We only do this if we still have budget (l or r > 0)
    if (c == '(' && l > 0) {
        str[i] = ' ';
        solve(str, i + 1, l - 1, r, bal);
        str[i] = c; // Backtrack! Put it back.
    } else if (c == ')' && r > 0) {
        str[i] = ' ';
        solve(str, i + 1, l, r - 1, bal);
        str[i] = c; // Backtrack! Put it back.
    }

    // CHOICE 2: Keep it
    // We update the balance based on what bracket we are keeping
    if (c == '(')
        solve(str, i + 1, l, r, bal + 1);
    else if (c == ')')
        solve(str, i + 1, l, r, bal - 1);
}

int main(int ac, char **av) {
    if (ac != 2)
        return (0);

    // Using a local buffer so we don't mess up memory, and because malloc is banned
    char str[2048];
    int i = 0;
    
    // Budgets for how many '(' and ')' we MUST remove
    int l_remove = 0; 
    int r_remove = 0;

    // The Scout Loop: Calculate our removal budgets and copy string
    while (av[1][i]) {
        str[i] = av[1][i];
        if (str[i] == '(') {
            l_remove++;
        } else if (str[i] == ')') {
            if (l_remove > 0)
                l_remove--; // We found a matching pair!
            else
                r_remove++; // Unmatched right bracket found
        }
        i++;
    }
    str[i] = '\0';

    // Start the magic: index 0, with our calculated budgets, and a starting balance of 0
    solve(str, 0, l_remove, r_remove, 0);

    return (0);
}