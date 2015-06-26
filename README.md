[![Build Status](https://travis-ci.org/aldialimucaj/perf-gear.svg?branch=master)](https://travis-ci.org/aldialimucaj/perf-gear)
[![Coverage Status](https://coveralls.io/repos/aldialimucaj/perf-gear/badge.svg)](https://coveralls.io/r/aldialimucaj/perf-gear)

## Introduction ##

## Examples ##

## Architecture ##

## Build Requirements ##

Although design decisions were to have as little dependencies on third party libraries, some are necessary for complex tasks such as HTTP/HTTPS protocol. Therefore before building make sure following libraries are installed on your system

### GNU-Linux Ubuntu ###

```
sudo apt-get install libcurl4-openssl-dev
```
## Running tests ##

Running tests in default mode
```
make && make test
```

Running tests for coverage
```
make CONF=Cov && make CONF=Cov test
```

Checking coveralls upload
```
coveralls -b. --dryrun
```

### Installing test environment ###
**CUnit** is needed to run the tests and develop new ones
```
sudo apt-get install libcunit1 libcunit1-doc libcunit1-dev
```
**cpp-coveralls** is needed to upload results to the code coverage framework.
This is not necessary if you don't want to check the coverage before pushing into github.
```
sudo apt-get install python-dev libxml2-dev libxslt-dev
sudo apt-get install libyaml-dev
sudo apt-get install -qq python-pip
sudo pip install cpp-coveralls PyYAML
```

**Valgrind** is used to check for common errors and memory leaks
```
sudo apt-get install valgrind
```
