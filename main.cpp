#include <iostream>

#include "console.hpp"

int main() {
    console::welcome();
    while(true) {
        console::menu();
    }
}
