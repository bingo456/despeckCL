#ifndef COMPUTE_INSAR_H
#define COMPUTE_INSAR_H

#include <CL/cl.h>

#include "clcfg.h"

class compute_insar : public kernel_env<compute_insar>
{
    private:
        const int search_window_size;

    public:
        std::string return_build_options(void);

        static constexpr const char* routine_name {"compute_insar"};

        compute_insar(const size_t block_size,
                      cl::Context context,
                      const int search_window_size);

        compute_insar(const compute_insar& other);

        void run(cl::CommandQueue cmd_queue,
                 cl::Buffer device_filter_values_a,
                 cl::Buffer device_filter_values_x_real,
                 cl::Buffer device_filter_values_x_imag,
                 cl::Buffer device_amp_filt,
                 cl::Buffer device_phi_filt,
                 cl::Buffer device_coh_filt,
                 const int height_overlap,
                 const int width_overlap,
                 cl::Buffer device_weights,
                 const int search_window_size,
                 const int patch_size);
};

#endif
