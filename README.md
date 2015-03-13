[![Build Status](https://travis-ci.org/aldialimucaj/perf-gear.svg?branch=master)](https://travis-ci.org/aldialimucaj/perf-gear)
[![Coverage Status](https://coveralls.io/repos/aldialimucaj/perf-gear/badge.svg)](https://coveralls.io/r/aldialimucaj/perf-gear)

## Introduction ##

## Examples ##

## Architecture ##

## Running tests ##

Runing tests in default mode
```
make && make test
```

Runing tests for coverage
```
make CONF=Cov && make CONF=Cov test
```

Checking coveralls upload 
```
coveralls -b. --dryrun
```

### Installting test environment ###
**CUnit** is needed to run the tests and develop new ones
```
sudo apt-get install libcunit1 libcunit1-doc libcunit1-dev
```
**cpp-coveralls** is needed to upload results to the code coverage framework.
This is not necessary if you dont want to check the coverage before pushing into github.
```
sudo apt-get install -qq python-pip
sudo pip install cpp-coveralls PyYAML
```

**Valgrind** is used to check for common errors and memory leaks
```
sudo apt-get install valgrind
```
