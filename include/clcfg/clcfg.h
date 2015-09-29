#ifndef CLCFG_H
#define CLCFG_H

#define __CL_ENABLE_EXCEPTIONS
#include <CL/cl.hpp>

#include <string>
#include <iostream>

#include "../compute/compute_env.h"
#include "../utils/easylogging++.h"

cl::Context opencl_setup(void);

std::string read_cl_file(std::string kernel_path);

template<typename Derived>
class kernel_env : public routine_env<Derived>
{
    public:
        size_t block_size;
        cl::Context context;
        cl::Program program;
        cl::Kernel kernel;
        kernel_env() {}

        kernel_env(size_t block_size,
                   cl::Context context,
                   std::string build_opts = "-Werror -cl-std=CL1.2") : block_size(block_size), context(context)
        {
            build_program(build_opts);
            build_kernel();
        }

        kernel_env(const kernel_env& other) : block_size(other.block_size), context(other.context)
        {
            program = other.program;
            build_kernel();
        }

        std::string return_default_build_opts(void)
        {
            return std::string{"-Werror -cl-std=CL1.2"};
        }

   protected:
        void build_program(std::string build_opts)
        {
            std::vector<cl::Device> devices;
            context.getInfo(CL_CONTEXT_DEVICES, &devices);

            std::string routine_name  = static_cast<Derived*>(this)->routine_name;
            std::string kernel_source = static_cast<Derived*>(this)->kernel_source;
            VLOG(0) << "Building program for: " << routine_name.c_str();
            cl::Program program{context, static_cast<Derived*>(this)->kernel_source};
            try {
                program.build(devices, build_opts.c_str());
            } catch (cl::Error error) {
                LOG(ERROR) << error.what() << "(" << error.err() << ")";
                std::string build_log;
                program.getBuildInfo(devices[0], CL_PROGRAM_BUILD_LOG, &build_log);
                LOG(ERROR) << build_log;
                std::terminate();
            }
            VLOG(0) << "done";
            this->program = program;
        }

        void build_kernel(void)
        {
            std::string routine_name = static_cast<Derived*>(this)->routine_name;
            VLOG(0) << "Building kernel for: " << routine_name.c_str();
            try {
                cl::Kernel kernel{this->program, routine_name.c_str()};
                this->kernel = kernel;
            } catch (cl::Error error) {
                LOG(ERROR) << "ERR while building kernel: " << routine_name;
                LOG(ERROR) << error.what() << "(" << error.err() << ")";
            }
            VLOG(0) << "done";
        }

   public:
        template<typename... Args>
        double timed_run(cl::CommandQueue cmd_queue, Args... args)
        {
            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            try {
                static_cast<Derived*>(this)->run(cmd_queue, args...);
            } catch (cl::Error error) {
                LOG(ERROR) << error.what() << "(" << error.err() << ")";
                LOG(ERROR) << "ERR while running kernel: " << this->routine_name;
                std::terminate();
            }

            end = std::chrono::system_clock::now();
            std::chrono::duration<double> duration = end-start;
            this->elapsed_seconds += duration;
            return duration.count();
        }
};

#endif
