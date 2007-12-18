/**\file*********************************************************************
 *                                                                     \brief
 *  NT Status codes
 *
 ****************************************************************************
 */

#ifndef NTL__NT_STATUS
#define NTL__NT_STATUS


namespace ntl {
namespace nt {

/**\addtogroup  native_types_support *** NT Types support library ***********
 *@{*/

struct status
{
  enum type
  {
    success               = 0,
    pending               = 0x00000103,

    guard_page_violation      = (int)0x80000001,
    datatype_misalignment     = (int)0x80000002,
    breakpoint                = (int)0x80000003,
    single_step               = (int)0x80000004,
    buffer_overflow           = (int)0x80000005,

    no_more_entries           = (int)0x8000001A,

    unsuccessful              = (int)0xC0000001,
    not_implemented           = (int)0xC0000002,

    info_length_mismatch      = (int)0xC0000004,
    access_violation          = (int)0xC0000005,
    invalid_handle            = (int)0xC0000008,

    invalid_device_request    = (int)0xC0000010,

    more_processing_required  = (int)0xC0000016,
    conflicting_addresses     = (int)0xC0000018,

    buffer_too_small          = (int)0xC0000023,
    noncontinuable_exception  = (int)0xC0000025,
    invalid_disposition       = (int)0xC0000026,
    object_name_collision     = (int)0xC0000035,

    privileged_instruction    = (int)0xC0000096,
    insufficient_resources    = (int)0xC000009A,

    illegal_instruction       = (int)0xC000001D,
    stack_overflow            = (int)0xC00000FD,
    invalid_image_not_mz      = (int)0xC000012F,
    entrypoint_not_found      = (int)0xC0000139,

    device_configuraton_error = (int)0xC0000182,
    driver_entrypoint_not_found = (int)0xC0000263,
    invalid_image_win_32      = (int)0xC0000359,

  };
};

static __forceinline
bool success(const status::type & s)
{
  return s >= 0;
}

/**@} native_types_support */

typedef nt::status::type ntstatus;

}//namespace nt

using nt::ntstatus;

}//namespace ntl

#endif//#ifndef NTL__NT_BASEDEF
