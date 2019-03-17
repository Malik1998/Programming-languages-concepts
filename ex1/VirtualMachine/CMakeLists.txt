cmake_minimum_required(VERSION 3.12)
project(VirtualMachine)

set(CMAKE_CXX_STANDARD 14)


include_directories(FullFileReader/ReadFullFile)



add_executable(VirtualMachine main.cpp VirtualMachine/VirtualMachine.cpp VirtualMachine/VirtualMachine.h
        VirtualMachine/SafeStack/SafeStack.h
        VirtualMachine/Converter/WordToCodeConverter/WordToCodeConverter.cpp VirtualMachine/Converter/WordToCodeConverter/WordToCodeConverter.h
        VirtualMachine/CommandService/CommandService.cpp VirtualMachine/CommandService/CommandService.h
        VirtualMachine/Converter/CodeToWordConverter/CodeToWordConverter.cpp VirtualMachine/Converter/CodeToWordConverter/CodeToWordConverter.h
        VirtualMachine/FullFileReader/ReadFullFile/FullFileReader.cpp VirtualMachine/FullFileReader/ReadFullFile/FullFileReader.h
        VirtualMachine/Converter/CodeToByteConverter/CodeToByteConverter.cpp VirtualMachine/Converter/CodeToByteConverter/CodeToByteConverter.h
        VirtualMachine/Converter/ByteToCodeConverter/ByteToCodeConverter.cpp VirtualMachine/Converter/ByteToCodeConverter/ByteToCodeConverter.h)


target_link_libraries(VirtualMachine)
