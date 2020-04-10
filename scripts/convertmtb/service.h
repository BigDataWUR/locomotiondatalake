/*
Author              : J. Vandenplas
Date                : 16 November 2018
*/

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdarg>
#include <vector>

bool checkFileIsAvailable(std::string filename, bool needExit = false)
{
    std::ifstream file(filename.c_str());
    if(file.good())
    {
        return true;
    }
    else
    {
        std::cout << "Can't open file " << filename << std::endl;
        if(needExit)
        {
            exit(1);
        }
        return false;
    }
}

void checkArguments(int argc, char *argv[], int count, ...)
{
    std::string **filelist = new std::string*[count];
    va_list ap;
    va_start(ap, count);
    for (int i = 0; i < count; i++)
    {
        filelist[i] = va_arg(ap, std::string *);
    }
    va_end(ap);
    if(argc == 1)
    {
        for (int i = 0; i < count; i++)
        {
            checkFileIsAvailable(*(filelist[i]), true);
        }
    }
    else if(argc == (count + 1))
    {
        bool isAllCorrect = true;
        for (int i = 0; i < count; i++)
        {
            if(!checkFileIsAvailable(argv[i + 1]))
            {
                isAllCorrect = false;
                break;
            }
        }
        if(isAllCorrect == true)
        {
            for(int i = 0; i < count; i++)
            {
                (*filelist[i]) = argv[i + 1];
            }
        }
        else
        {
            std::cout << "Warning: Try to open default datasetFileNames" << std::endl;
            for (int i = 0; i < count; i++)
            {
                checkFileIsAvailable(*(filelist[i]), true);
            }
        }
    }
    else
    {
        std::cout << "Usage: " << argv[0] << " [ ";
        for(int i = 0; i < count; i++)
        {
            std::cout << "<filename_" << i << "> ";
        }
        std::cout << "]" << std::endl;
        std::cout << "Warning: Try to open default datasetFileNames" << std::endl;
        for (int i = 0; i < count; i++)
        {
            checkFileIsAvailable(*(filelist[i]), true);
        }
    }
    delete [] filelist;
}

