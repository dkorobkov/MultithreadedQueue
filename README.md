# MultithreadedQueue
A fucking stupid C++ multithreaded class on top of std::queue that just builds and works without all bells and whistles of C++&lt;type_in_year_digits>

# Preface
I was exhausted while searching for a <u>usable</u> template for a simple multithreaded queue for my tiny Linux project. 
After trying a number of projects with C++ templates, autos, lambdas and all that newborne crap that even could not be 
built with my g++ me the oldfag gave up and wrote this simple implementation, as I did many times before Github became available.

# About code
I needed a queue that is filled on one end and fetched from the other end, possibly by multiple threads. So it has size(), push(), 
front() (returns oldest item without deleting from queue) and pop_front() (deletes from queue and returns the oldest item). 

Actually I needed a queue of pointers. You can modify per your needs.
