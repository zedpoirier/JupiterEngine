// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.200921.6

#ifndef WINRT_Windows_Graphics_Effects_1_H
#define WINRT_Windows_Graphics_Effects_1_H
#include "winrt/impl/Windows.Graphics.Effects.0.h"
WINRT_EXPORT namespace winrt::Windows::Graphics::Effects
{
    struct __declspec(empty_bases) IGraphicsEffect :
        Windows::Foundation::IInspectable,
        impl::consume_t<IGraphicsEffect>,
        impl::require<Windows::Graphics::Effects::IGraphicsEffect, Windows::Graphics::Effects::IGraphicsEffectSource>
    {
        IGraphicsEffect(std::nullptr_t = nullptr) noexcept {}
        IGraphicsEffect(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) IGraphicsEffectSource :
        Windows::Foundation::IInspectable,
        impl::consume_t<IGraphicsEffectSource>
    {
        IGraphicsEffectSource(std::nullptr_t = nullptr) noexcept {}
        IGraphicsEffectSource(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
    };
}
#endif
