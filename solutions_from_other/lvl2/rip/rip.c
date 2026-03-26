#include <unistd.h>
#include <string.h>

typedef struct
{
    int open_exc;
    int close_exc;
} ExcessCounts;

ExcessCounts count_excess(char *s)
{
    int open = 0;
    int open_exc = 0;
    int close_exc = 0;

    for (int i = 0; s[i]; i++)
    {
        if (s[i] == '(')
            open++;
        else if (s[i] == ')')
        {
            if (open > 0)
                open--;
            else
                close_exc++;
        }
    }
    open_exc = open;
    return (ExcessCounts){open_exc, close_exc};
}

void solve(char *s, int pos, int len, int open_rem, int close_rem, int balance)
{
    if (pos == len)
    {
        if (balance == 0)
        {
            write(1, s, len);
            write(1, "\n", 1);
        }
        return;
    }

    if (s[pos] == '(')
    {
        if (open_rem > 0)
        {
            s[pos] = ' '; // "Remove" it by replacing with a space.
            solve(s, pos + 1, len, open_rem - 1, close_rem, balance);
            s[pos] = '('; // Backtrack: restore the character for other recursive paths.
        }
        solve(s, pos + 1, len, open_rem, close_rem, balance + 1);
    }
    else if (s[pos] == ')')
    {
        if (close_rem > 0)
        {
            s[pos] = ' '; // "Remove" it.
            solve(s, pos + 1, len, open_rem, close_rem - 1, balance);
            s[pos] = ')'; // Backtrack.
        }
        if (balance > 0)
        {
            solve(s, pos + 1, len, open_rem, close_rem, balance - 1);
        }
    }
    else
        solve(s, pos + 1, len, open_rem, close_rem, balance);
}

int main(int ac, char **av)
{
    if (ac != 2)
    {
        write(2, "Usage: ./rip \"(()...)\"\n", 23);
        return 1;
    }

    char s[1024];
    strncpy(s, av[1], 1023);
    s[1023] = '\0';

    int len = 0;
    while (s[len])
        len++;

    ExcessCounts excess = count_excess(s);
    solve(s, 0, len, excess.open_exc, excess.close_exc, 0);

    return 0;
}

// ./rip "()())()()()()())()"

// it should always start with '('  even after spaces and end with ')'