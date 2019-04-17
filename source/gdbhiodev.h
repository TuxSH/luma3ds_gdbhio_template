#pragma once

#include <stdbool.h>

struct timeval;

// 0 on success, -1 on failure
int gdbHioDevInit(void);
void gdbHioDevExit(void);

int gdbHioDevGetStdin(void);
int gdbHioDevGetStdout(void);
int gdbHioDevGetStderr(void);

int gdbHioDevRedirectStdStreams(bool in, bool out, bool err);

int gdbHioDevGettimeofday(struct timeval *tv, void *tz);
int gdbHioDevIsatty(int fd);
int gdbHioDevSystem(const char *command);