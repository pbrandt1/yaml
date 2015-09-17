#include "yaml.h"
#include "stdio.h"

hash_t * yaml_read(char *file) {
  printf("file %s\n", file);
  char* yaml = file;
  char* this_line;
  char* next_line;
  char tmp[256];
  char tmp2[256];
  FILE *f = fopen(file, "r");

  if (f == NULL) {
    perror(file);
  }

  hash_t *current_hash = hash_new();
  char key[256];
  strcpy(key, "");
  int previous_indent = 0;
  int arrayIndex = 0;
  size_t len;
  while ((this_line = fgets(tmp2, 256, f))) {
    tmp[0] = '\0';

    // compute the indentation level
    int indent = 0;
    int p;
    for (p = 0; p < strlen(this_line); p++) {
      if (this_line[p] != ' ') {
        break;
      } else {
        indent++;
      }
    }

    // check if comment
    if (this_line[p+1] == '#') {
      continue;
    }

    // rewind the key to the current indentation level
    int indentsFound = 0;
    for (p = 0; p < strlen(key); p++) {
      if (indentsFound == indent) {
        key[p] = '\0';
        break;
      }
      if (key[p] == '.') {
        indentsFound += 2;
      }
    }

    // ugh c.  make sure keys don't start with "." or have double dots ".."
    if (key[0] != '\0' && key[p-1] != '.') {
      key[p] = '.';
      key[p+1] = '\0';
    }

    // get the current key
    if (this_line[indent] == '-') {
      // array element
      sprintf(tmp, "%i", arrayIndex);
      strcat(key, tmp);
      arrayIndex++;
      p = indent;
    } else {
      arrayIndex = 0;

      for (p = indent; p < strlen(this_line); p++) {
        if (this_line[p] == ':') {
          break;
        } else {
          //strcat(key, this_line[p]);
          len = strlen(key);
          key[len] = this_line[p];
          key[len + 1] = '\0';

        }
      }
    }

    int i = 0;
    p += 2; // scan past ": " or "- "
    for (p = p; p < strlen(this_line); p++) {
      if (this_line[p] == '\n') {
        tmp[i] = '\0';
        break;
      } else {
        tmp[i] = this_line[p];
        i++;
      }
    }


    if (0) {
      printf("line length: %zu", strlen(this_line));
      printf(", indents: %i", indent);
      printf(", key: %s", key);
      printf(", value: '%s'", tmp);
    }

    char *hashkey;
    hashkey = malloc(sizeof(char) * strlen(key));
    strcpy(hashkey, key);

    char *hashval;
    hashval = malloc(sizeof(char) * strlen(tmp));
    strcpy(hashval, tmp);

    if (strcmp(tmp, "") != 0) {
      hash_set(current_hash, hashkey, hashval);
    }
  }
  return current_hash;
}


