#ifndef EINSUM_IR_BACKEND_BINARY_CONTRACTION_TPP
#define EINSUM_IR_BACKEND_BINARY_CONTRACTION_TPP

#include <libxsmm.h>
#include "BinaryContraction.h"
#include "ContractionLoopsTpp.h"

namespace einsum_ir {
  namespace backend {
    class BinaryContractionTpp;
  }
}

class einsum_ir::backend::BinaryContractionTpp: public BinaryContraction {
  private:
    //! LIBXSMM-based unary first-touch TPP
    libxsmm_meltwfunction_unary m_xmm_kernel_first_touch_unary = nullptr;

    //! LIBXSMM-based binary first-touch TPP
    libxsmm_meltwfunction_binary m_xmm_kernel_first_touch_binary = nullptr;


    //! LIBXSMM-based main TPP which is called in the innermost loop
    libxsmm_xmmfunction m_xmm_kernel_main;

    //! LIBXSMM-based unary last-touch TPP
    libxsmm_meltwfunction_unary m_xmm_kernel_last_touch_unary = nullptr;

    //! LIBXSMM-based binary last-touch TPP
    libxsmm_meltwfunction_binary m_xmm_kernel_last_touch_binary = nullptr;

    //! used tensor ordering
    tenord_t m_tensor_ordering = UNDEFINED_TENORD;

    //! target blocked M dimension size of the generated standard GEMMs
    int64_t m_size_mb_gemm_target = 64;

    //! target blocked N dimension size of the generated standard GEMMs
    int64_t m_size_nb_gemm_target = 48;

    //! target blocked K dimension size of the generated standard GEMMs
    int64_t m_size_kb_gemm_target = 64;

    //! target block C dimension size of the generated packed GEMMs
    int64_t m_size_cb_packed_gemm_target = 8;

    //! number of blocked C dimensions
    int64_t m_num_dims_cb = 0;
    //! number of blocked M dimensions
    int64_t m_num_dims_mb = 0;
    //! number of blocked N dimensions
    int64_t m_num_dims_nb = 0;
    //! number of blocked K dimensions
    int64_t m_num_dims_kb = 0;

    //! contraction loop interface
    ContractionLoopsTpp m_cont_loops;

    /**
     * Converts the given native datatype to a LIBXSMM datatype.
     *
     * @param i_data_type native datatype.
     * @return corresponding LIBXSMM datatype.
     */
    static libxsmm_datatype dtype_to_libxsmm( data_t i_dtype );

  public:
    /**
     * Compiles the binary contraction.
     **/
    err_t compile();

    /**
     * Initializes the threading configuration of the contraction.
     *
     * @param i_num_tasks_target number of targeted tasks.
     **/
    void threading( int64_t i_num_tasks_target  );

    /**
     * Performs a contraction on the given input data.
     *
     * @param i_tensor_left left input tensor.
     * @param i_tensor_right right input tensor.
     * @param io_tensor_out output tensor.
     **/
    void contract( void const * i_tensor_left,
                   void const * i_tensor_right,
                   void       * io_tensor_out );

    /**
     * Performs a contraction on the given input data.
     *
     * @param i_tensor_left left input tensor.
     * @param i_tensor_right right input tensor.
     * @param i_tensor_out_aux auxiliary data w.r.t. output tensor.
     * @param io_tensor_out output tensor. 
     **/
    void contract( void const * i_tensor_left,
                   void const * i_tensor_right,
                   void const * i_tensor_out_aux,
                   void       * io_tensor_out );
};

#endif
