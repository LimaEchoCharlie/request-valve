# request-valve

**UNDER DEVELOPMENT**

request-valve provides a mechanism to throttle requests by IP address. A valve can be used to place limits on the bandwidth and burstiness of requests.  

Known limitations
* only one valve can be used at a time
* the same limits are placed on each IP address; no whitelisting or blacklisting
* no differentiation is made between the type of request 
* a valve can only deal with a predefined number of IP addresses. A full valve will not accept a new IP addresses.
* there is no mechanism to clear or grow a valve. 

