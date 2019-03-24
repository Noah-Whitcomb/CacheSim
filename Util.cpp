//John Gaboriault-Whitcomb
#include "Util.h"

// defining number of arguments so it can be changed in the future
#define NUM_ARGS 7

// Verify arguments are valid and return pointer to a map if they are
map<string, int>* verify_args(int argc, char **argv)
{
    if(argc != NUM_ARGS)
    {
        return nullptr;
    }
    vector<string> options;
    vector<int> values;

    // make sure options are valid
    for(size_t i = 1;i <= NUM_ARGS-1; i+=2)
    {
        // using nested if to ensure no errors come from multiple strcmp calls
        if(strcmp(argv[i],  "-s") != 0)
        {
            if(strcmp(argv[i], "-a") != 0)
            {
                if (strcmp(argv[i], "-b") != 0)
                {
                    return nullptr;
                }
            }
        }
        options.emplace_back(argv[i]);
    }
    // make sure numbers are valid
    for(size_t i = 2;i <= NUM_ARGS; i+=2)
    {
        char* temp;
        int num = strtol(argv[i], &temp, 0);
        if (temp == argv[i] || *temp)
        {
            return nullptr;
        }
        // TODO: verify args are powers of 2
        // TODO: verify associativity vs size (?)
        values.push_back(num);
    }

    map<string, int>* args = new map<string, int>;
    for(size_t i = 0;i<values.size();i++)
    {
        args->emplace(options[i], values[i]);
    }
    if(args->size() == NUM_ARGS/2)
    {
        return args;
    }
    return nullptr;
}