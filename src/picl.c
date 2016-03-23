#include "picl-driver.h"
#include "picl-ast.h"
#include "picl-vm.h"

int main(int argc, char *argv[])
{
    bool dump = false;
    bool eval = false;
    struct PiclDriver *driver = PiclDriver_new();

    for (++argv; argv[0]; ++argv){
        if (strncmp(*argv, "-p", 2) == 0){
            driver->trace_parsing = true;
        }
        else if (strncmp(*argv, "-s", 2) == 0){
            driver->trace_scanning = true;
        }
        else if (strncmp(*argv, "-d", 2) == 0){
            dump = true;
        }
        else if (strncmp(*argv, "-e", 3) == 0){
            eval = true;
        }
        else if (Picl_parse(driver, *argv) != true){
            if(dump){
                Picl_dump_program(driver->nodes);
            }
            else if(eval){
                Picl_eval_program(driver->nodes);
            }
            else{
                Picl_compile_program(driver->nodes);
            }
        }
    }
    exit(1);
}


