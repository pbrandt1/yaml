#include "stdio.h"
#include "yaml.h"

int main(int argc, char *argv[]) {
  hash_t *yaml = yaml_read("test.yaml");
  hash_each(yaml, {
    printf("%s: %s\n", key, (char *) val);
  });

  printf("mongodb.url: %s\n", (char *)hash_get(yaml, "mongodb.url"));

  hash_free(yaml);

  return 0;
}
