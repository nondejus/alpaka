# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/).


## [Unreleased]


## [0.5.0] - 2020-06-26
### Compatibility Changes:
- the minimum required C++ version has been raised from C++11 to C++14 #900
- drop support for CUDA 8.0 (does not support c++14)
- drop support for gcc 4.9 (does not support c++14)
- drop support for CMake versions lower than 3.15 (3.11, 3.12, 3.13 and 3.14)
- raise minimum supported boost version from 1.62.0 to 1.65.1 #906
- require HIP version to 3.3.0 #1006
- drop HIP-hcc support #945

### Bug Fixes:
- fix CMake error #941
- fix HIP math includes #947
- fix: missing hipRand and rocRand library #948
- fix VS 2017 CUDA builds #953
- fix uninitialized pitch #963
- fix windows CI builds #965
- fix conversion warning in TinyMT #997

### New Features:
- add automated gh-pages deployment for branch develop #916
- unify CUDA/HIP backend #928 #904 #950 #980 #981
- add support for Visual Studio 2019 #949
- simplify vector operator construction #977
- example heat-equation #978
- extend supported compiler combinations gcc-8+nvcc 10.1-10.2 #985
- add support for CMake 3.17 #988
- adds initial files for sphinx/rst and readthedocs. #990 #1017 #1048
- add support for clang 10 #998
- add popcount intrinsic #1004
- emulate hip/cuda-Memcpy3D with a kernel #1014
- simplify alpaka usage #1017


## [0.4.0] - 2020-01-14
### Compatibility Changes:
- added support for CUDA 10.0, 10.1 and 10.2
- dropped support for CUDA 7.0 and 7.5
- added official support for Visual Studio 2017 on Windows with CUDA 10 (built on Travis CI instead of appveyor now)
- added support for xcode10.2-11.3 (no official CUDA support yet)
- added support for Ubuntu 18.04
- added support for gcc 9
- added support for clang 7.0, 8.0 and 9.0
- dropped support for clang 3.5, 3.6, 3.7, 3.8 and 3.9
- added support for CMake 3.13, 3.14, 3.15 and 3.16
- dropped support for CMake 3.11.3 and lower, 3.11.4 is the lowest supported version
- added support for Boost 1.69, 1.70 and 1.71
- added support for usage of libc++ instead of libstdc++ for clang builds
- removed dependency to Boost.MPL and BOOST_CURRENT_FUNCTION
- replaced Boost.Test with Catch2 using an internal version of Catch2 by default but allowing to use an external one

### Bug Fixes:
- fixed some incorrect host/device function attributes
- fixed warning about comparison unsigned < 0
- There is no need to disable all other backends manually when using ALPAKA_ACC_GPU_CUDA_ONLY_MODE anymore
- fixed static block shared memory of types with alignemnt higher than defaultAlignment
- fixed race-condition in HIP/NVCC queue
- fixed data races when a GPU updates host memory by aligning host memory buffers always to 4kib

### New Features:
- Added a new alpaka Logo!
- the whole alpaka code has been relicensed to MPL2 and the examples to ISC
- added ALPAKA_CXX_STANDARD CMake option which allows to select the C++ standard to be used
- added ALPAKA_CUDA_NVCC_SEPARABLE_COMPILATION option to enable separable compilation for nvcc
- added ALPAKA_CUDA_NVCC_EXPT_EXTENDED_LAMBDA and ALPAKA_CUDA_NVCC_EXPT_RELAXED_CONSTEXPR CMake options to enable/disable those nvcc options (they were always ON before)
- added headers for standalone usage without CMake (alpaka/standalone/GpuCudaRt.h, ...) which set the backend defines
- added experimental HIP back-end with using nvcc (HIP >= 1.5.1 required, latest rocRand). More on HIP setup: doc/markdown/user/implementation/mapping/HIP.md
- added sincos math function implementations
- allowed to copy and move construct ViewPlainPtr
- added support for CUDA atomics using "unsigned long int"
- added compile-time error for atomic CUDA ops which are not available due to sm restrictions
- added explicit errors for unsupported types/operations for CUDA atomics
- replaced usages of assert with ALPAKA_ASSERT
- replaced BOOST_VERIFY by ALPAKA_CHECK and returned success from all test kernels
- added alpaka::ignore_unused as replacement for boost::ignore_unused

### Breaking changes:
- renamed Queue*Async to Queue*NonBlocking and Queue*Sync to Queue*Blocking
- renamed alpaka::size::Size to alpaka::idx::Idx, alpaka::size::SizeType to alpaka::idx::IdxType (and TSize to TIdx internally)
- replaced ALPAKA_FN_ACC_NO_CUDA by ALPAKA_FN_HOST
- replaced ALPAKA_FN_ACC_CUDA_ONLY by direct usage of __device__
- renamed ALPAKA_STATIC_DEV_MEM_CONSTANT to ALPAKA_STATIC_ACC_MEM_CONSTANT and ALPAKA_STATIC_DEV_MEM_GLOBAL to ALPAKA_STATIC_ACC_MEM_GLOBAL
- renamed alpaka::kernel::createTaskExec to alpaka::kernel::createTaskKernel
- QueueCpuSync now correctly blocks when called from multiple threads
  - This broke some previous use-cases (e.g. usage within existing OpenMP parallel regions)
  - This use case can now be handled with the support for external CPU queues as can bee seen in the example QueueCpuOmp2CollectiveImpl
- previously it was possible to have kernels return values even though they were always ignored. Now kernels are checked to always return void
- renamed all files with *Stl suffix to *StdLib
- renamed BOOST_ARCH_CUDA_DEVICE to BOOST_ARCH_PTX
- executors have been renamed due to the upcoming standard C++ feature with a different meaning. All files within alpaka/exec/ have been moved to alpaka/kernel/ and the files and classes have been renamed from Exec* to TaskKernel*. This should not affect users of alpaka but will affect extensions.

## [0.3.6] - 2020-01-06
### Bug Fixes:
- fix cuda stream race condition #850
- fix: cuda exceptions #844
- math/abs: Added trait specialisation for double. #862
- alpaka/math Overloaded float specialization #837
- Fixes name conflicts in alpaka math functions. #784


## [0.3.5] - 2018-11-18
### New Features:
- used OpenMP atomics instead of critical sections


## [0.3.4] - 2018-10-17
### Compatibility Changes:
- added support for boost-1.68.0
- added support for CUDA 10
- support for glibc < 2.18 (fix missing macros)
- added checks for available OpenMP versions

### Bug Fixes:
- fixed empty(StreamCpuAsync) returning true even though the last task is still in progress
- fixed integer overflows in case of int16_t being used as accelerator index type
- made some throwing destructors not throwing to support clang 7
- fixed broken alpaka::math::min for non-integral types

### New Features:
- added prepareForAsyncCopy which can be called to enable async copies for a specific buffer (if it is supported)
- allowed to run alpaka OpenMP 2 block accelerated kernels within existing parallel region
- added alpaka::ignore_unused which can be used in kernels


## [0.3.3] - 2018-08-10
### New Features:
- added CPU random number generators based on std::random_device and TinyMT32
- made TinyMT32 the default random number generator
- added alpaka::ignore_unused


## [0.3.2] - 2018-10-17
### New Features:
- Enhanced the compiler compatibility checks within the CMake scripts

### Bugs Fixed:
- fixed missing error in case of wrong OpenMP thread count being used by the runtime that was not triggered when not in debug mode
- fixed CUDA driver API error handling
- fixed CUDA memcpy and memset for zero sized buffers (division by zero)
- fixed OpenMP 4 execution
- fixed the VS2017 CUDA build (not officially supported)
- fixed CUDA callback execution not waiting for the task to finish executing
- fixed cudaOnly test being part of make test when cuda only mode is not enabled

### Compatibility Changes:
- added support for CUDA 9.2


## [0.3.1] - 2018-06-11
### New Features:
- CMake: added option to control tests BUILD_TESTING
- CMake: unified requirement of CMake 3.7.0+
- CMake: used targets for Boost dependencies
- CMake: made alpaka a pure interface library

### Bugs Fixed:
- fixed getDevCount documentation
- fixed undefined define warnings
- fixed self containing header check for CUDA


## [0.3.0] - 2018-03-15
### Bugs Fixed:
- fixed multiple bugs where CPU streams/events could deadlock or behaved different than the native CUDA events
- fixed a bug where the block synchronization of the Boost.Fiber backend crashed due to uninitialized variables

### New Features / Enhancements:
- added support for stream callbacks allowing to enqueue arbitrary host code using alpaka::stream::enqueue(stream, [&](){...});
- added support for compiling for multiple architectures using e.g. ALPAKA_CUDA_ARCH="20;35"
- added support for using __host__ constexpr code within __device__ code
- enhanced the CUDA error handling
- enhanced the documentation for mapping CUDA to alpaka

### Compatibility Changes:
- added support for CUDA 9.0 and 9.1
- added support for CMake 3.9 and 3.10
- removed support for CMake 3.6 and older
- added support for boost-1.65.0
- removed support for boost-1.61.0 and older
- added support for gcc 7
- added support for clang 4 and 5
- removed support for VS2015


## [0.2.0] - 2017-06-19
### Compatibility fixes and small enhancements:
- the documentation has been greatly enhanced
- adds support for CUDA 8.0
- adds support for CMake versions 3.6, 3.7 and 3.8
- adds support for Boost 1.62, 1.63 and 1.64
- adds support for clang-3.9
- adds support for Visual Studio 2017
- alpaka now compiles clean even with clang -Weverything
- re-enabled the boost::fiber accelerator backend which was disabled in the last release

### API changes:
- mapIdx is moved from namespace alpaka::core to alpaka::idx
- Vec is moved from namespace alpaka to alpaka::vec
- vec::Vec is now allowed to be zero-dimensional (was previously forbidden)
- added vec::concat
- added element-wise operator< for vec::Vec which returns a vector of bool
- CPU accelerators now support arbitrary dimensionality (both kernel execution as well as memory operations)
- added support for syncBlockThreadsPredicate with block::sync::op::LogicalOr, block::sync::op::LogicalAnd and block::sync::op::Count
- memory allocations are now aligned optimally for the underlying architecture (16 bit for SSE, 32 bit for AVX, 64 bit for AVX512) instead of 16 bit for all architectures in the previous release
- 