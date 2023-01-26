# Some hints

## For macOS users

Since all you work are required to compile and run in the DICE environment, so essentially, we only provide support in DICE setup. But we would provide as much support as we can.
Unfortunately, we don't have access to the macOS environment, so we cannot to provide support in environment setup.

## Installing opencv

1. DICE: already installed
2. Windows WSL/Linux: 

        sudo apt update 
        sudo apt install libopencv-dev
3. macOS: maybe try 

        brew install opencv

## Compile

        mkdir bin
        g++ helloworld.cpp -o bin/helloworld
Details can be found in the makefile

## Running the program

        ./bin/helloworld
        // or
        make run

## About makefile

Makefile is a useful tool in managing your projects, but all commands needs to be defined.

        make life
        make run
        make clean

## C++ print

        #include<iostream>
        std::cout<<"print sth";
        std::cout<<"print sth\t"; // tab
        std::cout<<"print sth\n"; // newline
        std::cout<<"print sth"<<std::endl; // newline
If you specify 'using namespace std', then no need for 'std::'
