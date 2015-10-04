despeckCL
=========

A C++ library for despeckling SAR images using OpenCL with Python and Octave bindings.

Implemented Filters
-------------------

So far only the following filters are implemented:

* **Boxcar**: The simple boxcar filter
* **NLInSAR**: A nonlocal InSAR filter, introduced in *Deledalle, C.-A.; Denis, L.; Tupin, F., "NL-InSAR: Nonlocal Interferogram Estimation," Geoscience and Remote Sensing, IEEE Transactions on , vol.49, no.4, pp.1441,1452, April 2011*
* **NLSAR (still WIP)**: A nonlocal filter for InSAR and PolSAR, introduced in *Deledalle, C.-A.; Denis, L.; Tupin, F.; Reigber, A.; Jäger, M., "NL-SAR: A Unified Nonlocal Framework for Resolution-Preserving (Pol)(In)SAR Denoising," Geoscience and Remote Sensing, IEEE Transactions on , vol.53, no.4, pp.2021,2038, April 2015*


Requirements
------------

1. A compiler with C++14 and at least OpenMP 3.0 support. So far development is done using gcc. But clang is to be tested.
2. An OpenCL Runtime:
    * <a href="http://www.freedesktop.org/wiki/Software/Beignet/">Beignet</a> for Intel GPUs under Linux
    * <a href="http://developer.amd.com/tools-and-sdks/opencl-zone/amd-accelerated-parallel-processing-app-sdk/">AMD APP SDK</a>
    * <a href="https://developer.nvidia.com/cuda-toolkit">CUDA Toolkit</a> from NVIDIA which also has OpenCL support
3. <a href="https://cmake.org/">CMake</a>
4. <a href="https://www.gnu.org/software/gsl/">GNU Scientific Library</a>
5. <a href="http://swig.org/">SWIG</a> for generating Python and Octave bindings (optional)
6. <a href="http://sphinx-doc.org/">Sphinx</a> for building the documentation (optional)
7. despeckCL uses <a href="https://github.com/philsquared/Catch">Catch</a> for unit testing and <a href="https://github.com/easylogging/easyloggingpp/">Easylogging++</a> for logging, both are shipped with the source.

Building and Installation
-------------------------

```shell

$ git clone git@gitlab.lrz.de:gbaier/despeckCL.git

$ cd despeckCL

$ mkdir build

$ cd build

$ cmake -DCMAKE_INSTALL_PREFIX:PATH=/opt/despeckcl/ ../

$ make -j4

$ make install
```
