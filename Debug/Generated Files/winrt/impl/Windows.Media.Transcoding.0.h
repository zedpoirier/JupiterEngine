// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.200921.6

#ifndef WINRT_Windows_Media_Transcoding_0_H
#define WINRT_Windows_Media_Transcoding_0_H
WINRT_EXPORT namespace winrt::Windows::Foundation
{
    template <typename TProgress> struct __declspec(empty_bases) IAsyncActionWithProgress;
    template <typename TResult> struct __declspec(empty_bases) IAsyncOperation;
}
WINRT_EXPORT namespace winrt::Windows::Foundation::Collections
{
    struct IPropertySet;
}
WINRT_EXPORT namespace winrt::Windows::Media::Core
{
    struct IMediaSource;
}
WINRT_EXPORT namespace winrt::Windows::Media::MediaProperties
{
    struct MediaEncodingProfile;
}
WINRT_EXPORT namespace winrt::Windows::Storage
{
    struct IStorageFile;
}
WINRT_EXPORT namespace winrt::Windows::Storage::Streams
{
    struct IRandomAccessStream;
}
WINRT_EXPORT namespace winrt::Windows::Media::Transcoding
{
    enum class MediaVideoProcessingAlgorithm : int32_t
    {
        Default = 0,
        MrfCrf444 = 1,
    };
    enum class TranscodeFailureReason : int32_t
    {
        None = 0,
        Unknown = 1,
        InvalidProfile = 2,
        CodecNotFound = 3,
    };
    struct IMediaTranscoder;
    struct IMediaTranscoder2;
    struct IPrepareTranscodeResult;
    struct MediaTranscoder;
    struct PrepareTranscodeResult;
}
namespace winrt::impl
{
    template <> struct category<Windows::Media::Transcoding::IMediaTranscoder>{ using type = interface_category; };
    template <> struct category<Windows::Media::Transcoding::IMediaTranscoder2>{ using type = interface_category; };
    template <> struct category<Windows::Media::Transcoding::IPrepareTranscodeResult>{ using type = interface_category; };
    template <> struct category<Windows::Media::Transcoding::MediaTranscoder>{ using type = class_category; };
    template <> struct category<Windows::Media::Transcoding::PrepareTranscodeResult>{ using type = class_category; };
    template <> struct category<Windows::Media::Transcoding::MediaVideoProcessingAlgorithm>{ using type = enum_category; };
    template <> struct category<Windows::Media::Transcoding::TranscodeFailureReason>{ using type = enum_category; };
    template <> inline constexpr auto& name_v<Windows::Media::Transcoding::MediaTranscoder> = L"Windows.Media.Transcoding.MediaTranscoder";
    template <> inline constexpr auto& name_v<Windows::Media::Transcoding::PrepareTranscodeResult> = L"Windows.Media.Transcoding.PrepareTranscodeResult";
    template <> inline constexpr auto& name_v<Windows::Media::Transcoding::MediaVideoProcessingAlgorithm> = L"Windows.Media.Transcoding.MediaVideoProcessingAlgorithm";
    template <> inline constexpr auto& name_v<Windows::Media::Transcoding::TranscodeFailureReason> = L"Windows.Media.Transcoding.TranscodeFailureReason";
    template <> inline constexpr auto& name_v<Windows::Media::Transcoding::IMediaTranscoder> = L"Windows.Media.Transcoding.IMediaTranscoder";
    template <> inline constexpr auto& name_v<Windows::Media::Transcoding::IMediaTranscoder2> = L"Windows.Media.Transcoding.IMediaTranscoder2";
    template <> inline constexpr auto& name_v<Windows::Media::Transcoding::IPrepareTranscodeResult> = L"Windows.Media.Transcoding.IPrepareTranscodeResult";
    template <> inline constexpr guid guid_v<Windows::Media::Transcoding::IMediaTranscoder>{ 0x190C99D2,0xA0AA,0x4D34,{ 0x86,0xBC,0xEE,0xD1,0xB1,0x2C,0x2F,0x5B } }; // 190C99D2-A0AA-4D34-86BC-EED1B12C2F5B
    template <> inline constexpr guid guid_v<Windows::Media::Transcoding::IMediaTranscoder2>{ 0x40531D74,0x35E0,0x4F04,{ 0x85,0x74,0xCA,0x8B,0xC4,0xE5,0xA0,0x82 } }; // 40531D74-35E0-4F04-8574-CA8BC4E5A082
    template <> inline constexpr guid guid_v<Windows::Media::Transcoding::IPrepareTranscodeResult>{ 0x05F25DCE,0x994F,0x4A34,{ 0x9D,0x68,0x97,0xCC,0xCE,0x17,0x30,0xD6 } }; // 05F25DCE-994F-4A34-9D68-97CCCE1730D6
    template <> struct default_interface<Windows::Media::Transcoding::MediaTranscoder>{ using type = Windows::Media::Transcoding::IMediaTranscoder; };
    template <> struct default_interface<Windows::Media::Transcoding::PrepareTranscodeResult>{ using type = Windows::Media::Transcoding::IPrepareTranscodeResult; };
    template <> struct abi<Windows::Media::Transcoding::IMediaTranscoder>
    {
        struct __declspec(novtable) type : inspectable_abi
        {
            virtual int32_t __stdcall put_TrimStartTime(int64_t) noexcept = 0;
            virtual int32_t __stdcall get_TrimStartTime(int64_t*) noexcept = 0;
            virtual int32_t __stdcall put_TrimStopTime(int64_t) noexcept = 0;
            virtual int32_t __stdcall get_TrimStopTime(int64_t*) noexcept = 0;
            virtual int32_t __stdcall put_AlwaysReencode(bool) noexcept = 0;
            virtual int32_t __stdcall get_AlwaysReencode(bool*) noexcept = 0;
            virtual int32_t __stdcall put_HardwareAccelerationEnabled(bool) noexcept = 0;
            virtual int32_t __stdcall get_HardwareAccelerationEnabled(bool*) noexcept = 0;
            virtual int32_t __stdcall AddAudioEffect(void*) noexcept = 0;
            virtual int32_t __stdcall AddAudioEffectWithSettings(void*, bool, void*) noexcept = 0;
            virtual int32_t __stdcall AddVideoEffect(void*) noexcept = 0;
            virtual int32_t __stdcall AddVideoEffectWithSettings(void*, bool, void*) noexcept = 0;
            virtual int32_t __stdcall ClearEffects() noexcept = 0;
            virtual int32_t __stdcall PrepareFileTranscodeAsync(void*, void*, void*, void**) noexcept = 0;
            virtual int32_t __stdcall PrepareStreamTranscodeAsync(void*, void*, void*, void**) noexcept = 0;
        };
    };
    template <> struct abi<Windows::Media::Transcoding::IMediaTranscoder2>
    {
        struct __declspec(novtable) type : inspectable_abi
        {
            virtual int32_t __stdcall PrepareMediaStreamSourceTranscodeAsync(void*, void*, void*, void**) noexcept = 0;
            virtual int32_t __stdcall put_VideoProcessingAlgorithm(int32_t) noexcept = 0;
            virtual int32_t __stdcall get_VideoProcessingAlgorithm(int32_t*) noexcept = 0;
        };
    };
    template <> struct abi<Windows::Media::Transcoding::IPrepareTranscodeResult>
    {
        struct __declspec(novtable) type : inspectable_abi
        {
            virtual int32_t __stdcall get_CanTranscode(bool*) noexcept = 0;
            virtual int32_t __stdcall get_FailureReason(int32_t*) noexcept = 0;
            virtual int32_t __stdcall TranscodeAsync(void**) noexcept = 0;
        };
    };
    template <typename D>
    struct consume_Windows_Media_Transcoding_IMediaTranscoder
    {
        WINRT_IMPL_AUTO(void) TrimStartTime(Windows::Foundation::TimeSpan const& value) const;
        [[nodiscard]] WINRT_IMPL_AUTO(Windows::Foundation::TimeSpan) TrimStartTime() const;
        WINRT_IMPL_AUTO(void) TrimStopTime(Windows::Foundation::TimeSpan const& value) const;
        [[nodiscard]] WINRT_IMPL_AUTO(Windows::Foundation::TimeSpan) TrimStopTime() const;
        WINRT_IMPL_AUTO(void) AlwaysReencode(bool value) const;
        [[nodiscard]] WINRT_IMPL_AUTO(bool) AlwaysReencode() const;
        WINRT_IMPL_AUTO(void) HardwareAccelerationEnabled(bool value) const;
        [[nodiscard]] WINRT_IMPL_AUTO(bool) HardwareAccelerationEnabled() const;
        WINRT_IMPL_AUTO(void) AddAudioEffect(param::hstring const& activatableClassId) const;
        WINRT_IMPL_AUTO(void) AddAudioEffect(param::hstring const& activatableClassId, bool effectRequired, Windows::Foundation::Collections::IPropertySet const& configuration) const;
        WINRT_IMPL_AUTO(void) AddVideoEffect(param::hstring const& activatableClassId) const;
        WINRT_IMPL_AUTO(void) AddVideoEffect(param::hstring const& activatableClassId, bool effectRequired, Windows::Foundation::Collections::IPropertySet const& configuration) const;
        WINRT_IMPL_AUTO(void) ClearEffects() const;
        WINRT_IMPL_AUTO(Windows::Foundation::IAsyncOperation<Windows::Media::Transcoding::PrepareTranscodeResult>) PrepareFileTranscodeAsync(Windows::Storage::IStorageFile const& source, Windows::Storage::IStorageFile const& destination, Windows::Media::MediaProperties::MediaEncodingProfile const& profile) const;
        WINRT_IMPL_AUTO(Windows::Foundation::IAsyncOperation<Windows::Media::Transcoding::PrepareTranscodeResult>) PrepareStreamTranscodeAsync(Windows::Storage::Streams::IRandomAccessStream const& source, Windows::Storage::Streams::IRandomAccessStream const& destination, Windows::Media::MediaProperties::MediaEncodingProfile const& profile) const;
    };
    template <> struct consume<Windows::Media::Transcoding::IMediaTranscoder>
    {
        template <typename D> using type = consume_Windows_Media_Transcoding_IMediaTranscoder<D>;
    };
    template <typename D>
    struct consume_Windows_Media_Transcoding_IMediaTranscoder2
    {
        WINRT_IMPL_AUTO(Windows::Foundation::IAsyncOperation<Windows::Media::Transcoding::PrepareTranscodeResult>) PrepareMediaStreamSourceTranscodeAsync(Windows::Media::Core::IMediaSource const& source, Windows::Storage::Streams::IRandomAccessStream const& destination, Windows::Media::MediaProperties::MediaEncodingProfile const& profile) const;
        WINRT_IMPL_AUTO(void) VideoProcessingAlgorithm(Windows::Media::Transcoding::MediaVideoProcessingAlgorithm const& value) const;
        [[nodiscard]] WINRT_IMPL_AUTO(Windows::Media::Transcoding::MediaVideoProcessingAlgorithm) VideoProcessingAlgorithm() const;
    };
    template <> struct consume<Windows::Media::Transcoding::IMediaTranscoder2>
    {
        template <typename D> using type = consume_Windows_Media_Transcoding_IMediaTranscoder2<D>;
    };
    template <typename D>
    struct consume_Windows_Media_Transcoding_IPrepareTranscodeResult
    {
        [[nodiscard]] WINRT_IMPL_AUTO(bool) CanTranscode() const;
        [[nodiscard]] WINRT_IMPL_AUTO(Windows::Media::Transcoding::TranscodeFailureReason) FailureReason() const;
        WINRT_IMPL_AUTO(Windows::Foundation::IAsyncActionWithProgress<double>) TranscodeAsync() const;
    };
    template <> struct consume<Windows::Media::Transcoding::IPrepareTranscodeResult>
    {
        template <typename D> using type = consume_Windows_Media_Transcoding_IPrepareTranscodeResult<D>;
    };
}
#endif
