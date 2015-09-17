# yaml
an incredibly simple module to read yaml

gives you a [hash](https://github.com/clibs/hash) like ("app.url": "localhost")

*install:*
```bash
clib install pbrandt1/yaml
```

*example:*

_test.yaml_
```yaml
app:
  url: localhost
  port: 8080
```

in _test.c_
```c
hash_t *config = yaml_read("test.yaml");
printf("app listening on port %s\n", (char *)hash_get(config, "app.port"));
```

Uses [clibs/hash](https://github.com/clibs/hash).

some rules for writing yaml that's easy to use:
- use two space indentation
- don't use end-of-line comments like `url: localhost # comment`
- don't use dots in your keys
- don't use quotes like `url: "example.com"`k
