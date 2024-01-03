#include "Tests/ParserTests.h"

SRunner *default_srunner_create() {
  SRunner *sr;

  sr = srunner_create(test0());

  return sr;
}
#include <stdio.h>
#include <unistd.h>
int main(void) {
  int exit_status = 1;
  int number_failed = 0;
  SRunner *sr = NULL;

  sr = default_srunner_create();

  srunner_set_log(sr, "test.log");
  srunner_run_all(sr, CK_NORMAL);

  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return exit_status;
}

START_TEST(test0_0) {
  FILE *file = fopen("../../Tests/resources/ModelTest.obj", "r");

  double epsilon = 1e-6;

  if (file == NULL) {
    printf("FILE IS NULL\n");
    exit(1);
  }

  Vector *vertecies = create_vector(vertex_c);
  Vector *facet_cs = create_vector(facet_c);

  readFile(file, vertecies, facet_cs);
  fclose(file);

  FILE *verteciesFile = fopen("../../Tests/resources/VertexesTest.obj", "r");
  FILE *facet_csFile = fopen("../../Tests/resources/FacetsTest.obj", "r");

  char *original = NULL;
  size_t bufsize = 0;

  for (int i = 0; getline(&original, &bufsize, verteciesFile) != -1; ++i) {
    double orig_x = 0;
    double orig_y = 0;
    double orig_z = 0;

    vertex_c *vertex_c = get_by_index(vertecies, i);
    sscanf(original, "%lf %lf %lf", &orig_x, &orig_y, &orig_z);

    ck_assert_ldouble_eq_tol(vertex_c->point.x, orig_x, epsilon);
    ck_assert_ldouble_eq_tol(vertex_c->point.y, orig_y, epsilon);
    ck_assert_ldouble_eq_tol(vertex_c->point.z, orig_z, epsilon);
  }
  clear(vertecies);

  for (int i = 0; getline(&original, &bufsize, facet_csFile) != -1; ++i) {
    int orig_0 = 0;
    int orig_1 = 0;
    int orig_2 = 0;

    int *vertex_c = ((facet_c *)get_by_index(facet_cs, i))->number_of_vertecies;
    sscanf(original, "%d %d %d", &orig_0, &orig_1, &orig_2);

    ck_assert_int_eq(vertex_c[0] + 1, orig_0);
    ck_assert_int_eq(vertex_c[1] + 1, orig_1);
    ck_assert_int_eq(vertex_c[2] + 1, orig_2);
  }

  for (int i = 0; i < facet_cs->size; ++i) {
    free(((facet_c *)get_by_index(facet_cs, i))->number_of_vertecies);
  }
  clear(facet_cs);
  ck_assert_int_eq(1, 1);
}
END_TEST

Suite *test0(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("test0");
  tc = tcase_create("core");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, test0_0);

  return s;
}
