
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#include "../external/unity/unity_fixture.h"
#include "../src/valve.h"

TEST_GROUP( valve );

TEST_SETUP( valve )
{
    valve_create();
}

TEST_TEAR_DOWN( valve )
{
    valve_destroy();
} 
 
TEST( valve, should_notContainAnythingAfterCreation)
{
    char* ip_addr0 =  "111.111.111.111";
    TEST_ASSERT( !valve_search(ip_addr0));
}

TEST( valve, should_allowSimpleAcquire)
{
    char* ip_addr0 =  "111.111.111.111";
    TEST_ASSERT( valve_acquire(ip_addr0));
}

TEST( valve, should_containAddressAfterCreation)
{
    char* ip_addr0 =  "111.111.111.112";
    TEST_ASSERT( valve_acquire(ip_addr0));
    TEST_ASSERT( valve_search(ip_addr0));
}

TEST( valve, should_beProperlyDestroyed)
{
    char* ip_addr0 =  "111.111.111.111";
    TEST_ASSERT( valve_acquire(ip_addr0));
    TEST_ASSERT( valve_search(ip_addr0));
    valve_destroy();
    valve_create();
    TEST_ASSERT( !valve_search(ip_addr0));
}

TEST( valve, should_failToAcquieAfterNRequests)
{
    char* ip_addr0 =  "111.111.111.111";
    valve_set( 10, 2, 0);
    TEST_ASSERT( valve_acquire(ip_addr0));
    TEST_ASSERT( valve_acquire(ip_addr0));
    TEST_ASSERT( !valve_acquire(ip_addr0));
}

TEST( valve, should_allowRequestsFromTwoIPAddresses)
{
    char* ip_addr0 =  "111.111.111.111";
    char* ip_addr1 =  "111.111.111.112";
    valve_set( 10, 2, 0);
    TEST_ASSERT( valve_acquire(ip_addr0));
    TEST_ASSERT( valve_acquire(ip_addr1));
}

TEST( valve, should_failToAcquieFor2AddressesAfterNRequests)
{
    char* ip_addr0 =  "111.111.111.111";
    char* ip_addr1 =  "111.111.111.112";
    valve_set( 10, 2, 0);
    TEST_ASSERT( valve_acquire(ip_addr0));
    TEST_ASSERT( valve_acquire(ip_addr1));
    TEST_ASSERT( valve_acquire(ip_addr0));
    TEST_ASSERT( !valve_acquire(ip_addr0));
    TEST_ASSERT( valve_acquire(ip_addr1));
    TEST_ASSERT( !valve_acquire(ip_addr1));
}

TEST( valve, should_failToAcquireFromAnEmptyValve)
{
    char* ip_addr0 =  "111.111.111.111";
    valve_set( 10, 0, 0);
    TEST_ASSERT( !valve_acquire(ip_addr0));
}

TEST( valve, should_allowRequestAfterPause)
{
    char* ip_addr0 =  "111.111.111.111";
    valve_set( 10, 0, 1);
    TEST_ASSERT( !valve_acquire(ip_addr0));
    sleep(1);
    TEST_ASSERT( valve_acquire(ip_addr0));
}

TEST( valve, should_allowRequestAfterLongerPause)
{
    char* ip_addr0 =  "111.111.111.111";
    valve_set( 10, 0, 0.5);
    TEST_ASSERT( !valve_acquire(ip_addr0));
    sleep(1);
    TEST_ASSERT( !valve_acquire(ip_addr0));
    sleep(1);
    TEST_ASSERT( valve_acquire(ip_addr0));
}

TEST_GROUP_RUNNER( valve ){
    RUN_TEST_CASE( valve, should_notContainAnythingAfterCreation);
    RUN_TEST_CASE( valve, should_allowSimpleAcquire);
    RUN_TEST_CASE( valve, should_containAddressAfterCreation);
    RUN_TEST_CASE( valve, should_beProperlyDestroyed);
    RUN_TEST_CASE( valve, should_failToAcquieAfterNRequests);
    RUN_TEST_CASE( valve, should_allowRequestsFromTwoIPAddresses);
    RUN_TEST_CASE( valve, should_failToAcquieFor2AddressesAfterNRequests);
    RUN_TEST_CASE( valve, should_failToAcquireFromAnEmptyValve);
    RUN_TEST_CASE( valve, should_allowRequestAfterPause);
    RUN_TEST_CASE( valve, should_allowRequestAfterLongerPause);
}

static void RunAllTests(void)
{
    RUN_TEST_GROUP( valve );
}

int main(int argc, const char * argv[])
{
    return UnityMain(argc, argv, RunAllTests);
} 
