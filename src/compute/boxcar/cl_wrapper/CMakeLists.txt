include_directories(${despeckCL_SOURCE_DIR}/src/compute/boxcar/cl_wrapper)
include_directories(${despeckCL_SOURCE_DIR}/src/clcfg)

set(infile      "${despeckCL_SOURCE_DIR}/src/compute/boxcar/cl_wrapper/boxcar_wrapper.h.in")
set(kernel_file "${despeckCL_SOURCE_DIR}/src/compute/boxcar/cl_kernels/boxcar_kernel.cl")
set(outfile     "${despeckCL_SOURCE_DIR}/src/compute/boxcar/cl_wrapper/boxcar_wrapper.h")
FILE(READ ${kernel_file} KERNEL_SOURCE)
STRING(REPLACE "\n" " \\n\"\n\"" KERNEL_SOURCE_EDIT "${KERNEL_SOURCE}")
SET(CMAKE_KERNEL_SOURCE "${KERNEL_SOURCE_EDIT}\\n")
configure_file(${infile} ${outfile})

add_library(boxcar_opencl_wrapper OBJECT
            boxcar_wrapper.cpp)
