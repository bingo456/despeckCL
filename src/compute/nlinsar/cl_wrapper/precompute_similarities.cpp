#include "precompute_similarities.h"
#include <stdio.h>
#include <iostream>

void precompute_similarities_1st_pass::run(cl::CommandQueue cmd_queue,
                                           cl::Buffer device_a1,
                                           cl::Buffer device_a2,
                                           cl::Buffer device_dp,
                                           cl::Buffer device_amp_filt,
                                           cl::Buffer device_phi_filt,
                                           cl::Buffer device_coh_filt,
                                           const int height_overlap,
                                           const int width_overlap,
                                           const int search_window_size,
                                           cl::Buffer device_similarities,
                                           cl::Buffer device_kullback_leiblers)
{
    const int height_sim = height_overlap - search_window_size + 1;
    const int width_sim  = width_overlap  - search_window_size + 1;

    const int border_max = (search_window_size - 1) / 2;

    cl_int status;

    cl::NDRange global_size {(size_t) block_size*((height_sim-1)/block_size+1), (size_t) block_size*((width_sim-1)/block_size+1)};
    cl::NDRange local_size  {block_size, block_size};

    kernel.setArg(0,  device_a1);
    kernel.setArg(1,  device_a2);
    kernel.setArg(2,  device_dp);
    kernel.setArg(3,  device_amp_filt);
    kernel.setArg(4,  device_phi_filt);
    kernel.setArg(5,  device_coh_filt);
    kernel.setArg(6,  device_similarities);
    kernel.setArg(7,  device_kullback_leiblers);
    kernel.setArg(8,  height_overlap);
    kernel.setArg(9,  width_overlap);
    kernel.setArg(10, border_max);
    kernel.setArg(11, search_window_size);

    cmd_queue.enqueueNDRangeKernel(kernel, cl::NullRange, global_size, local_size, NULL, NULL);
    cmd_queue.finish();
}

void precompute_similarities_2nd_pass::run(cl::CommandQueue cmd_queue,
                                           const int height_overlap,
                                           const int width_overlap,
                                           const int search_window_size,
                                           cl::Buffer device_similarities,
                                           cl::Buffer device_kullback_leiblers)
{
    const int height_sim = height_overlap - search_window_size + 1;
    const int width_sim  = width_overlap  - search_window_size + 1;

    const int border_max = (search_window_size - 1) / 2;

    // if the sub image is too small, all the values have already been computed in 
    // the first pass and the 2nd kerned does not have to be called.
    // For me this always resulted in a crash.
    if ( height_sim > border_max && width_sim > 2*border_max ) {

        cl::NDRange global_offset {(size_t) border_max, (size_t) border_max};
        cl::NDRange global_size   {(size_t) block_size*((height_sim-1-border_max)/block_size+1), (size_t) block_size*((width_sim-1-2*border_max)/block_size+1)};
        cl::NDRange local_size    {block_size, block_size};

        kernel.setArg( 0, device_similarities);
        kernel.setArg( 1, device_kullback_leiblers);
        kernel.setArg( 2, height_overlap);
        kernel.setArg( 3, width_overlap);
        kernel.setArg( 4, border_max);
        kernel.setArg( 5, search_window_size);

        cmd_queue.enqueueNDRangeKernel(kernel, global_offset, global_size, local_size, NULL, NULL);
        cmd_queue.finish();
    }
}
