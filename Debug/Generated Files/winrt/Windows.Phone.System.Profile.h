// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.200921.6

#ifndef WINRT_Windows_Phone_System_Profile_H
#define WINRT_Windows_Phone_System_Profile_H
#include "winrt/base.h"
static_assert(winrt::check_version(CPPWINRT_VERSION, "2.0.200921.6"), "Mismatched C++/WinRT headers.");
#define CPPWINRT_VERSION "2.0.200921.6"
#include "winrt/Windows.Phone.System.h"
#include "winrt/impl/Windows.Phone.System.Profile.2.h"
namespace winrt::impl
{
    template <typename D> WINRT_IMPL_AUTO(bool) consume_Windows_Phone_System_Profile_IRetailModeStatics<D>::RetailModeEnabled() const
    {
        bool value{};
        check_hresult(WINRT_IMPL_SHIM(Windows::Phone::System::Profile::IRetailModeStatics)->get_RetailModeEnabled(&value));
        return value;
    }
#ifndef WINRT_LEAN_AND_MEAN
    template <typename D>
    struct produce<D, Windows::Phone::System::Profile::IRetailModeStatics> : produce_base<D, Windows::Phone::System::Profile::IRetailModeStatics>
    {
        int32_t __stdcall get_RetailModeEnabled(bool* value) noexcept final try
        {
            typename D::abi_guard guard(this->shim());
            *value = detach_from<bool>(this->shim().RetailModeEnabled());
            return 0;
        }
        catch (...) { return to_hresult(); }
    };
#endif
}
WINRT_EXPORT namespace winrt::Windows::Phone::System::Profile
{
    inline auto RetailMode::RetailModeEnabled()
    {
        return impl::call_factory_cast<bool(*)(IRetailModeStatics const&), RetailMode, IRetailModeStatics>([](IRetailModeStatics const& f) { return f.RetailModeEnabled(); });
    }
}
namespace std
{
#ifndef WINRT_LEAN_AND_MEAN
    template<> struct hash<winrt::Windows::Phone::System::Profile::IRetailModeStatics> : winrt::impl::hash_base {};
    template<> struct hash<winrt::Windows::Phone::System::Profile::RetailMode> : winrt::impl::hash_base {};
#endif
}
#endif
