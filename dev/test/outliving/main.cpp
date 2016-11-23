/*
 * Testing for outliving_reference.
 */

#include <cpp_util_3/outliving.hpp>

#include <test/helpers.hpp>

using namespace cpp_util_3;

class int_consumer {
	outliving_reference_t< int > m_value;
public :
	int_consumer( outliving_reference_t< int > value ) : m_value(value) {}

	int get() const { return m_value.get(); }
	void change( int i ) { m_value.get() = i; }
};

class const_int_consumer {
	outliving_reference_t< const int > m_value;
public :
	const_int_consumer( outliving_reference_t< const int > value ) : m_value(value) {}

	int get() const { return m_value.get(); }
};

void
simple()
	{
		int v = 0;

		int_consumer m( outliving_mutable(v) );
		const_int_consumer c( outliving_const(v) );

		CHECK_CONDITION( 0 == m.get() );
		CHECK_CONDITION( 0 == c.get() );

		m.change( 42 );

		CHECK_CONDITION( 42 == m.get() );
		CHECK_CONDITION( 42 == c.get() );
	}

UNIT_TEST_MAIN(
	simple();
)

