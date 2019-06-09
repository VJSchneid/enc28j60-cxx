#pragma once

#include <type_traits>

namespace enc28j60 {
    
template<typename NativeType>
class base_register {
    static_assert(std::is_integral_v<NativeType>,
                  "NativeType requirements not met.");
public:
    using native_type = NativeType;
    
    constexpr base_register() = default;
    constexpr base_register(native_type data) : data_(data) {}
    
    
    constexpr void data(native_type data) { data_ = data; }
    
    constexpr unsigned char data() const { return data_; }
    
protected:
    constexpr void set_bits(native_type bits, bool value = true) { 
        if (value) {
            data_ |= bits;
        } else {
            data_ &= ~bits;
        }
    }
    
    constexpr native_type get_bits(native_type bits) const {
        return data_ & bits;
    }
    
    constexpr bool check_bits(native_type bits) const {
        return bits & data_;
    }

private:
    native_type data_ = 0;
};

}
