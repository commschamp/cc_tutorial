#pragma once

namespace tutorial14
{

namespace frame
{

namespace checksum
{

/// @brief Summary of all bytes' values + 1 checksum calculator.
class PlusOneSum
{
public:
    /// @brief Return type
    using ResultType = std::uint16_t;

    /// @brief Operator that is invoked to calculate the checksum value
    /// @param[in, out] iter Input iterator,
    /// @param[in] len Number of bytes to summarise.
    /// @return The checksum value.
    /// @post The iterator is advanced by number of bytes read (len).
    template <typename TIter>
    ResultType operator()(TIter& iter, std::size_t len) const
    {
        using ByteType = typename std::make_unsigned<
            typename std::decay<decltype(*iter)>::type
        >::type;

        ResultType checksum = 0;
        for (auto idx = 0U; idx < len; ++idx) {
            checksum = static_cast<ResultType>(checksum + (static_cast<ByteType>(*iter) + 1U));
            ++iter;
        }
        return checksum;
    }
};

} // namespace checksum

} // namespace frame

} // namespace tutorial14
