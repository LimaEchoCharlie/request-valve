
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
 
TEST( tbucket, init_should_containNTokensAfterCreation)
{
    tbucket_init( bucket, 100, 60, 5);
    TEST_ASSERT_EQUAL_INT( 60, tbucket_available_tokens( bucket ));
}

TEST( tbucket, init_should_containNTokensAfter3Seconds)
{
    tbucket_init( bucket, 100, 60, 5);
    sleep(3);
    TEST_ASSERT_EQUAL_INT( 75, tbucket_available_tokens( bucket ));
}
 
TEST_GROUP_RUNNER( tbucket ){
    RUN_TEST_CASE( tbucket, init_should_containNTokensAfterCreation);
    RUN_TEST_CASE( tbucket, init_should_containNTokensAfter3Seconds);
}

static void RunAllTests(void)
{
    RUN_TEST_GROUP( tbucket );
}

int main(int argc, const char * argv[])
{
    return UnityMain(argc, argv, RunAllTests);
} 
