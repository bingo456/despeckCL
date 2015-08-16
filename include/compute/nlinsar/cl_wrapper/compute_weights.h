#ifndef COMPUTE_WEIGHTS_H
#define COMPUTE_WEIGHTS_H

#include <CL/cl.h>

#include "clcfg.h"

class compute_weights : public kernel_env<compute_weights>
{
    public:
        using kernel_env::kernel_env;

        static constexpr const char* routine_name {"compute_weights"};

        void run(cl::CommandQueue cmd_queue,
                 cl::Buffer patch_similarities,
                 cl::Buffer patch_kullback_leiblers,
                 cl::Buffer weights,
                 const int n_elems,
                 const float h,
                 const float T);
};

#endif
