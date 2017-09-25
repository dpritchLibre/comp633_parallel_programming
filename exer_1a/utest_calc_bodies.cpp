#include <stddef.h>
#include "cppunit/ui/text/TestRunner.h"
#include "cppunit/extensions/HelperMacros.h"


// declare vector struct and all-pair body sim fcn -----------------------------

struct vec_2d {
    double x1;
    double x2;
};

extern "C" void calc_bodies(struct vec_2d *r,
			    struct vec_2d *v,
			    const double *m,
			    double g,
			    double dt,
			    size_t n,
			    size_t k);

#define EPSILON 0.000001




// define test class -----------------------------------------------------------

class CalcBodiesTest : public CppUnit::TestFixture {

private:

    double* m;
    vec_2d* r;
    vec_2d* v;
    double g;
    double dt;
    size_t n;


public:

    void setUp() {

	m = new double[3];
	r = new vec_2d[3];
	v = new vec_2d[3];
	n = 3;
	g  = 1.0;
	dt = 0.000001;

	m[0] = m[1] = m[2] = 1;

	r[0].x1 = -0.97000436;  r[0].x2 =  0.24308753;
	r[1].x1 =  0.97000436;  r[1].x2 = -0.24308753;
	r[2].x1 =  0.0;         r[2].x2 =  0.0;

	v[0].x1 = -0.46620368;  v[0].x2 = -0.43236573;
	v[1].x1 = -0.46620368;  v[1].x2 = -0.43236573;
	v[2].x1 =  0.93240737;  v[2].x2 =  0.86473146;
    }


    void tearDown() {
	delete m;
	delete r;
	delete v;
    }


    void test_calc_bodies_step1() {

	// exercise function
	calc_bodies_k_step(3162957);

	// check results.  These results were provided by Jan Prins on the class
	// website.

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.97000754, r[0].x1, EPSILON);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.24311667, r[0].x2, EPSILON);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.97003188, r[1].x1, EPSILON);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.24309202, r[1].x2, EPSILON);

	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.000024340532, r[2].x1, EPSILON);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.000024652558, r[2].x2, EPSILON);

	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.46624203, v[0].x1, EPSILON);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.43234625, v[0].x2, EPSILON);

	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.46616351, v[1].x1, EPSILON);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.43236621, v[1].x2, EPSILON);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.93240554, v[2].x1, EPSILON);
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.86471246, v[2].x2, EPSILON);
    }


    void test_calc_bodies_step2() {

	// exercise function
	calc_bodies_k_step(6325914);

	// check results.  These results were provided by Jan Prins on the class
	// website.

	CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.96997182, r[0].x1, EPSILON);
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.24313017, r[0].x2, EPSILON);

	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.97010190, r[1].x1, EPSILON);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.24301235, r[1].x2, EPSILON);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.00013007996, r[2].x1, EPSILON);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.00011781508, r[2].x2, EPSILON);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.46636412, v[0].x1, EPSILON);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.43232847, v[0].x2, EPSILON);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.46601452, v[1].x1, EPSILON);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.43241200, v[1].x2, EPSILON);

	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.93237864, v[2].x1, EPSILON);
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.86474047, v[2].x2, EPSILON);
    }


    void calc_bodies_k_step(size_t k) {
	calc_bodies(r, v, m, g, dt, n, k);
    }


    CPPUNIT_TEST_SUITE(CalcBodiesTest);
    CPPUNIT_TEST(test_calc_bodies_step1);
    CPPUNIT_TEST(test_calc_bodies_step2);
    CPPUNIT_TEST_SUITE_END();
};




// main function ---------------------------------------------------------------

int main() {

    CppUnit::TextUi::TestRunner runner;
    runner.addTest(CalcBodiesTest::suite());

    return runner.run() ? 0 : 1;
}
