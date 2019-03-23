#include <iostream>
#include "VirtualMachine/Converter/WordToCodeConverter/WordToCodeConverter.h"
#include "VirtualMachine/Converter/CodeToWordConverter/CodeToWordConverter.h"
#include "VirtualMachine/VirtualMachine.h"
#include "VirtualMachine/Converter/ByteToCodeConverter/ByteToCodeConverter.h"
#include "VirtualMachine/FullFileReader/ReadFullFile/FullFileReader.h"
#include "VirtualMachine/Converter/CodeToByteConverter/CodeToByteConverter.h"


int main() {
//    Processor processor = Processor("Programms/Fibbonachi", Processor::WORD_COMMANDS);
//    processor.execute();
//
//
//
//    char *prog_code;
//    int length = FullFileReader::readFullFile("Byte.code", &prog_code);
//    ByteToCodeConverter::convert(prog_code, "Byte_to_code.code" , length);
//
//
//    length = FullFileReader::readFullFile("CodeProgram.code", &prog_code);
//    CodeToWordConverter::convert(prog_code, "Code_to_word.txt");

//    Processor processor2 = Processor("Code_to_word.txt", Processor::WORD_COMMANDS);
//    processor2.execute();



    Processor processor1 = Processor("Programms/Factorial", Processor::WORD_COMMANDS);
    processor1.execute();



//    char *prog_code_;
//    FullFileReader::readFullFile("Programms/Fibbonachi", &prog_code_);
//    WordToCodeConverter::convert(prog_code_, "TestCode.code");
//
//    FullFileReader::readFullFile("TestCode.code", &prog_code_);
//    CodeToByteConverter::convert(prog_code_, "TestByte.asm");
//
//    int length = FullFileReader::readFullFile("TestByte.asm", &prog_code_);
//    ByteToCodeConverter::convert(prog_code_, "TestTest.code" , length);
//
//
//    FullFileReader::readFullFile("TestTest.code", &prog_code_);
//    CodeToWordConverter::convert(prog_code_, "TestWordNew.txt");
//
//
//    Processor processor = Processor("TestWordNew.txt", Processor::WORD_COMMANDS);
//    processor.execute();

}