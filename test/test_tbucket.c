
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#include "../external/unity/unity_fixture.h"
#include "../src/tbucket.h"

static tbucket_t* bucket;

TEST_GROUP( tbucket );

TEST_SETUP( tbucket )
{
    bucket = malloc( sizeof( tbucket_t ));
    assert( bucket );
}

TEST_TEAR_DOWN( tbucket )
{
    free( bucket );
} 
 
TEST( tbucket, should_containNTokensAfterCreation)
{
    tbucket_init( bucket, 100, 60, 5);
    TEST_ASSERT_EQUAL_INT( 60, tbucket_available_tokens( bucket ));
}

TEST( tbucket, should_containNTokensAfter3Seconds)
{
    tbucket_init( bucket, 100, 60, 5);
    sleep(3);
    TEST_ASSERT_EQUAL_INT( 75, tbucket_available_tokens( bucket ));
}
 
TEST( tbucket, should_respectCapacity)
{
    tbucket_init( bucket, 100, 99, 5);
    TEST_ASSERT_EQUAL_INT( 99, tbucket_available_tokens( bucket ));
    sleep(1);
    TEST_ASSERT_EQUAL_INT( 100, tbucket_available_tokens( bucket ));
}

TEST( tbucket, should_successfullyAcquire)
{
    tbucket_init( bucket, 100, 8, 5);
    TEST_ASSERT( tbucket_acquire( bucket, 1 ));
    TEST_ASSERT_EQUAL_INT( 7, tbucket_available_tokens( bucket ));
}

TEST( tbucket, should_notAcquire)
{
    tbucket_init( bucket, 100, 8, 5);
    TEST_ASSERT( !tbucket_acquire( bucket, 10 ));
    TEST_ASSERT_EQUAL_INT( 8, tbucket_available_tokens( bucket ));
}

TEST( tbucket, should_acquireAfterAPause)
{
    tbucket_init( bucket, 100, 8, 5);
    TEST_ASSERT( !tbucket_acquire( bucket, 10 ));
    sleep(1);
    TEST_ASSERT( tbucket_acquire( bucket, 10 ));
    TEST_ASSERT_EQUAL_INT( 3, tbucket_available_tokens( bucket ));
}

TEST( tbucket, should_growCorrectlyWithFloatRate)
{
    tbucket_init( bucket, 100, 5, 0.5);
    sleep(1);
    TEST_ASSERT_EQUAL_INT( 5, tbucket_available_tokens( bucket ));
    sleep(1);
    TEST_ASSERT_EQUAL_INT( 6, tbucket_available_tokens( bucket ));
}

TEST_GROUP_RUNNER( tbucket ){
    RUN_TEST_CASE( tbucket, should_containNTokensAfterCreation);
    RUN_TEST_CASE( tbucket, should_containNTokensAfter3Seconds);
    RUN_TEST_CASE( tbucket, should_respectCapacity);
    RUN_TEST_CASE( tbucket, should_successfullyAcquire);
    RUN_TEST_CASE( tbucket, should_notAcquire);
    RUN_TEST_CASE( tbucket, should_acquireAfterAPause);
    RUN_TEST_CASE( tbucket, should_growCorrectlyWithFloatRate);
}

static void RunAllTests(void)
{
    RUN_TEST_GROUP( tbucket );
}

int main(int argc, const char * argv[])
{
    return UnityMain(argc, argv, RunAllTests);
} 
