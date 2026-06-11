#include <array>
#include <cstddef>
#include <cstring>
class PacketWriter
{
public:

template<typename T>
bool Write(const T& value)
{
  if (writeOffset + sizeof(T) > buffer.size()) {
    return false; // Fim do buffer ou dados corrompidos
  }
    memcpy(
        buffer.data() + writeOffset,
        &value,
        sizeof(T));

    writeOffset += sizeof(T);
    return true;
}

    const char* Data() const {return reinterpret_cast<const char*>(buffer.data());};

    std::size_t Size() const {return writeOffset;};

private:

    std::array<std::byte, 1400> buffer;
    size_t writeOffset = 0;
};