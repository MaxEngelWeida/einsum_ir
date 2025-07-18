#ifndef EINSUM_IR_BINARY_CONSTANTS
#define EINSUM_IR_BINARY_CONSTANTS

#include <cstdint>
#include "../constants.h"

namespace einsum_ir {
  namespace binary{
    typedef enum {
      OMP =  0, // OMP parallelized dim
      SEQ =  1, // Sequential dimension
      SFC =  2, // SFC dimension (always is omp parallelized)
      PRIM = 3, // Primitive dimension 
      UNDEFINED_EXECTYPE = 99
    } exec_t;

    struct iter_property {
      dim_t   dim_type       = dim_t::UNDEFINED_DIM;
      exec_t  exec_type      = exec_t::SEQ;
      int64_t size           = 0;
      int64_t stride_left    = 0;
      int64_t stride_right   = 0;
      int64_t stride_out_aux = 0;
      int64_t stride_out     = 0;
    };

    typedef uint8_t sfc_t;

    struct thread_info {
      int64_t offset_left = 0;
      int64_t offset_right = 0;
      int64_t offset_out_aux = 0;
      int64_t offset_out = 0;
      std::vector<sfc_t> movement_ids;
    };
  }
}

#endif