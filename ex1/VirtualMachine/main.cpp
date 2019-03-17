#include <iostream>
#include "VirtualMachine/Converter/WordToCodeConverter/WordToCodeConverter.h"
#include "VirtualMachine/Converter/CodeToWordConverter/CodeToWordConverter.h"
#include "VirtualMachine/VirtualMachine.h"


int main() {
    Processor processor = Processor("../Programms/Fibbonachi", Processor::WORD_COMMANDS);
    processor.execute();

    Processor processor1 = Processor("../Programms/Factorial", Processor::WORD_COMMANDS);
    processor1.execute();

}