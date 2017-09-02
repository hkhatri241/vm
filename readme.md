# VM and TIC TAC TOE


Tasks:
1.) Implement VM. DONE
2.) Implement ASsembler and instruction set. DONE
3.) Implement Tic Tac Toe game. NOT DONE.

### Prerequisites

GCC/Clang and python


### Installing


compile bit.c

gcc -c -o bit.o bit.c

compile  ram.c

gcc -c -o ram.o ram.c

compile vm 

gcc -o vm vm.c bit.o ram.o


Finally run. ./vm

Note: the assembled file is hardcoded.

To invoke  the assembler.
python assemble.py

File name is hard coded as well.


## Contributing

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.


## Authors

* **team segfault** 


## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

