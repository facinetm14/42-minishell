# Minishell

A C implementation of a Unix shell built for the 42 curriculum. Follow [the main loop](main.c) into [command parsing](parsing/) and [pipeline execution](pipex_v/). These are the two places to look when diagnosing a command that parses correctly but produces unexpected output.

Start with the [build targets and readline dependencies](Makefile). A useful interactive check is `echo hello | wc -c`, which exercises both command execution and piping.
