#ifndef MOCKS_INTERNAL_HEADER
#define MOCKS_INTERNAL_HEADER

#include <cgreen/internal/mock_table.h>
#include <cgreen/internal/function_macro.h>
#include <cgreen/constraint.h>
#include <cgreen/reporter.h>
#include <cgreen/vector.h>
#include <stdint.h>


#ifdef __GNUC__
#define WARN_UNUSED_RESULT __attribute__((warn_unused_result))
#else
#define WARN_UNUSED_RESULT
#endif

#ifdef __cplusplus
namespace cgreen {
    extern "C" {
#endif

void expect_(TestReporter *test_reporter, const char *function, const char *test_file, int test_line, ...);
void always_expect_(TestReporter *test_reporter, const char *function, const char *test_file, int test_line, ...);
void never_expect_(TestReporter *test_reporter, const char *function, const char *test_file, int test_line, ...);
intptr_t mock_(TestReporter *test_reporter, const char *function, const char *mock_file, int mock_line, const char *parameters, ...);


/* Warning for unused results from 'when()' helps detecting slip-ups in the expect():

    expect(mocked_function, will_return(true)),
        when(param, is_equal_to(5));

   Note the extra parenthesis at the end of the first line. Thanks to
   the comma operator, this effectively creates a mock expectation
   which silently ignores the constraints on its parameter(s), and
   passes the test case. /@awilke

*/
Constraint *when_(const char *parameter, Constraint *constraint) WARN_UNUSED_RESULT;

void clear_mocks(void);
void tally_mocks(TestReporter *reporter);

#ifdef __cplusplus
    }
}
#endif

#endif
