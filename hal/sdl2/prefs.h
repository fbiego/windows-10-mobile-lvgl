#ifndef PREFS_H
#define PREFS_H

#ifdef __cplusplus
extern "C" {
#endif


#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_LINE_LENGTH 100

#define PREF_FILE "prefs.txt"

void savePref(const char *key, const char *value);
void savePrefBool(const char *key, bool value);
void savePrefInt(const char *key, uint32_t value);

bool readPref(const char *key, char *value);
bool readPrefInt(const char *key, uint32_t *value);
bool readPrefBool(const char *key, bool *value);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif