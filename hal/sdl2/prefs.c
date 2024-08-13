

#include "prefs.h"



void savePref(const char *key, const char *value)
{
    FILE *file = fopen(PREF_FILE, "r+"); // Open file for reading and writing
    if (file == NULL)
    {
        // If the file does not exist, create it
        file = fopen(PREF_FILE, "w+");
        if (file == NULL)
        {
            printf("Error opening file!\n");
            return;
        }
    }

    char line[MAX_LINE_LENGTH];
    long pos = 0;
    bool found = false;

    while (fgets(line, sizeof(line), file))
    {
        char currentKey[50];
        sscanf(line, "%[^:]:", currentKey);

        if (strcmp(currentKey, key) == 0)
        {
            found = true;
            break;
        }
        pos = ftell(file);
    }

    if (found)
    {
        fseek(file, pos, SEEK_SET);
        fprintf(file, "%s:%s\n", key, value);
    }
    else
    {
        fseek(file, 0, SEEK_END);
        fprintf(file, "%s:%s\n", key, value);
    }

    fclose(file);
}

void savePrefBool(const char *key, bool value)
{
    savePrefInt(key, value ? 1 : 0); // Convert boolean to string
}

void savePrefInt(const char *key, uint32_t value)
{
    char strValue[50];
    sprintf(strValue, "%08d", value); // Convert integer to string
    savePref(key, strValue);
}

bool readPref(const char *key, char *value)
{
    FILE *file = fopen(PREF_FILE, "r"); // Open file for reading
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return false;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file))
    {
        char currentKey[50], currentValue[50];
        sscanf(line, "%[^:]:%s", currentKey, currentValue);

        if (strcmp(currentKey, key) == 0)
        {
            strcpy(value, currentValue);
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}

bool readPrefInt(const char *key, uint32_t *value)
{
    char strValue[50];
    if (readPref(key, strValue))
    {
        *value = atoi(strValue); // Convert string to integer
        return true;
    }
    return false;
}

bool readPrefBool(const char *key, bool *value)
{
    char strValue[50];
    if (readPref(key, strValue))
    {
        *value = atoi(strValue) != 0; // Convert string to integer
        return true;
    }
    return false;
}