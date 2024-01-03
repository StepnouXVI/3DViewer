#ifndef _PARSER_H_
#define _PARSER_H_

#include <Services/PureParser/Vector.h>
#include <pcre.h>

typedef struct point_3d_c {
  double x, y, z;
} point_3d_c;

typedef union vertex_c {
  double points[3];
  point_3d_c point;
} vertex_c;

typedef struct facet_c {
  int *number_of_vertecies;
  int size;
} facet_c;

#define SUCCESS 0
#define FAILURE 1

#define VERTEX_REGEX \
  "^[vV](\\s+[-+]?\\d+(([.]\\d+)?|([eE][-+]?\\d+))){3}(\\s)*$"
#define FACET_REGEX                             \
  "^[f]([ "                                     \
  "]([-]?)[0-9]{1,}([/])?(([-]?)[0-9]{1,})?([/" \
  "])?(([-]?)[0-9]{1,})?){2,}(\\s)*$"

int match_regex(const char *str, pcre *compiled_regex);
pcre *compile_regex(const char *regex);

void readFile(FILE *file, Vector *vertecies, Vector *polygons);
void readVertex(char *line, Vector *vertecies);
void readFacet(char *line, Vector *facets, Vector *vertecies);
int spaceCounter(char *line);

#endif  // _PARSER_H_