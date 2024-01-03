#include <Services/PureParser/Parser.h>
#include <string.h>

int match_regex(const char *str, pcre *compiled_regex) {
  return pcre_exec(compiled_regex, NULL, str, strlen(str), 0, 0, NULL, 0) < 0
             ? FAILURE
             : SUCCESS;
}

pcre *compile_regex(const char *regex) {
  const char *error = NULL;
  int error_offset = 0;

  return pcre_compile(regex, 0, &error, &error_offset, NULL);
  ;
}

void readFile(FILE *file, Vector *vertecies, Vector *facets) {
  pcre *vertex_regex = compile_regex(VERTEX_REGEX);
  pcre *facet_regex = compile_regex(FACET_REGEX);

  char *line = NULL;
  size_t bufsize = 0;

  while (getline(&line, &bufsize, file) != -1) {
    if (match_regex(line, vertex_regex) == SUCCESS) {
      readVertex(line, vertecies);
    } else if (match_regex(line, facet_regex) == SUCCESS) {
      readFacet(line, facets, vertecies);
    }
  }

  free(line);
  pcre_free(vertex_regex);
  pcre_free(facet_regex);
}

void readVertex(char *line, Vector *vertecies) {
  vertex_c *vertex = (vertex_c *)malloc(sizeof(vertex_c));

  sscanf(line, "v %lf %lf %lf", &vertex->point.x, &vertex->point.y,
         &vertex->point.z);
  push_back(vertecies, vertex);
}

void readFacet(char *line, Vector *facets, Vector *vertecies) {
  facet_c *facet = (facet_c *)malloc(sizeof(facet_c));

  facet->size = spaceCounter(line);
  facet->number_of_vertecies = (int *)malloc(facet->size * sizeof(int));

  char *it = line + 2;
  for (int i = 0; i < facet->size; i++) {
    facet->number_of_vertecies[i] = atoi(it);
    facet->number_of_vertecies[i] < 0
        ? facet->number_of_vertecies[i] += vertecies->size - 1
        : facet->number_of_vertecies[i]--;

    do {
      it++;
    } while (*it != ' ' && *it != '\0');
  }

  push_back(facets, facet);
}

int spaceCounter(char *line) {
  int count = 0;

  for (int i = 1; line[i] != '\0'; i++) {
    if (line[i - 1] == ' ' && strchr(" \n\0", line[i]) == NULL) {
      count++;
    }
  }
  return count;
}
