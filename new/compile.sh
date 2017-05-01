#!/bin/bash

g++ -Wall -pthread -o foo *.cc -lpigpio -lrt -std=c++11
