#ifndef PRECOMPUTE_PATCH_SIMILARITIES_H
#define PRECOMPUTE_PATCH_SIMILARITIES_H

#include <CL/cl.h>

#include "clcfg.h"

class precompute_patch_similarities : public kernel_env<precompute_patch_similarities>
{

    public:
        const int window_width;
        const int output_block_size;

        static constexpr const char* routine_name {"precompute_patch_similarities"};

        precompute_patch_similarities(const size_t block_size, cl::Context context, const int window_width);
        precompute_patch_similarities(const precompute_patch_similarities& other);

        std::string return_build_options(void);

        void run(cl::CommandQueue cmd_queue,
                 cl::Buffer similarities,
                 cl::Buffer kullback_leiblers,
                 const int height_sim,
                 const int width_sim,
                 const int search_window_size,
                 const int patch_size,
                 cl::Buffer patch_similarities,
                 cl::Buffer patch_kullback_leiblers);
};

#endif
