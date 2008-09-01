/**\file*********************************************************************
 *                                                                     \brief
 *  KM Handles support
 *
 ****************************************************************************
 */


#ifndef NTL__KM_HANDLE
#define NTL__KM_HANDLE

#include "../nt/handle.hxx"
#include "basedef.hxx"

namespace ntl {
namespace km {

using nt::legacy_handle;
using nt::duplicate_options;
using nt::handle_attributes;


NTL__EXTERNAPI
ntstatus __stdcall
ZwDuplicateObject(
    legacy_handle   SourceProcessHandle,
    legacy_handle   SourceHandle,
    legacy_handle   TargetProcessHandle   __optional,
    legacy_handle * TargetHandle          __optional,
    access_mask     DesiredAccess,
    uint32_t        HandleAttributes,
    uint32_t        Options
    );


static __forceinline
legacy_handle
  duplicate(
    legacy_handle     source_handle,
    legacy_handle     source_process  = nt::current_process(),
    legacy_handle     target_process  = nt::current_process(),
    access_mask       desired_access  = nt::no_access,
    handle_attributes attributes      = nt::handle_flag_none,
    duplicate_options options         = nt::duplicate_same_access | nt::duplicate_same_attributes
    )
{
  legacy_handle h = { 0 };
  // returns valid handle or 0
  ZwDuplicateObject(source_process, source_handle, target_process, &h,
                    desired_access, attributes, options);
  return h;
}


NTL__EXTERNAPI
ntstatus __stdcall
  ZwClose(legacy_handle Handle);

static __forceinline
ntstatus close(legacy_handle handle)
{
  return ZwClose(handle);
}


namespace aux {

__forceinline
void close(legacy_handle handle)
{
  km::close(handle);
}

__forceinline
legacy_handle duplicate(legacy_handle handle)
{
  return km::duplicate(handle);
}

} //namespace aux

typedef basic_handle<legacy_handle, aux::close, aux::duplicate> handle;


}//namespace km
}//namespace ntl

#endif//#ifndef NTL__KM_HANDLE
