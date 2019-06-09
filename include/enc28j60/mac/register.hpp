#pragma once

#include <enc28j60/detail/base_register.hpp>

namespace enc28j60::mac {

class control_register_1 : public base_register<unsigned char> {
    using base = base_register<unsigned char>;
    
    struct bits {
        enum : unsigned char {
            loopback = 0x10,
            tx_pause = 0x08,
            rx_pause = 0x04,
            pass_all = 0x02,
            rx_enable = 0x01
        };
    };
    
public:
    constexpr control_register_1() {
        loopback(false);
        transmit_pause_frames(true);
        receive_pause_frames(true);
        pass_all(false);
        receive(true);
    }
    
    constexpr control_register_1(unsigned char data) : base(data) {}
    
    constexpr control_register_1 &loopback(bool enable) {
        base::set_bits(bits::loopback, enable);
        return *this;
    }
    
    constexpr bool loopback() const {
        return base::check_bits(bits::loopback);
    }
    
    constexpr control_register_1 &transmit_pause_frames(bool enable) {
        base::set_bits(bits::tx_pause, enable);
        return *this;
    }
    
    constexpr bool transmit_pause_frames() const {
        return base::check_bits(bits::tx_pause);
    }
    
    constexpr control_register_1 &receive_pause_frames(bool enable) {
        base::set_bits(bits::rx_pause, enable);
        return *this;
    }
    
    constexpr bool receive_pause_frames() const {
        return base::check_bits(bits::rx_pause);
    }
    
    constexpr control_register_1 &pass_all(bool enable) {
        base::set_bits(bits::pass_all, enable);
        return *this;
    }
    
    constexpr bool pass_all() const {
        return base::check_bits(bits::pass_all);
    }
    
    constexpr control_register_1 &receive(bool enable) {
        base::set_bits(bits::rx_enable);
        return *this;
    }
    
    constexpr bool receive(bool enable) const {
        return base::check_bits(bits::rx_enable);
    }
};

class control_register_2 : public base_register<unsigned char> {
    using base = base_register<unsigned char>;
    
    struct bits {
        enum : unsigned char {
            reset = 0x80,
            rng_reset = 0x40,
            rx_reset = 0x08,
            rx_function_reset = 0x04,
            tx_reset = 0x02,
            tx_function_reset = 0x01
        };
    };
    
public:
    constexpr control_register_2() {
        reset(false);
        reset_random_number_generator(false);
        reset_receive_logic(false);
        reset_receive_function(false);
        reset_transmit_logic(false);
        reset_transmit_function(false);
    }
    
    constexpr control_register_2(unsigned char data) : base(data) {}
    
    constexpr control_register_2 &reset(bool enable) {
        base::set_bits(bits::reset, enable);
        return *this;
    }
    
    constexpr bool reset() const {
        return base::check_bits(bits::reset);
    }
    
    constexpr control_register_2 &reset_random_number_generator(bool enable) {
        base::set_bits(bits::rng_reset, enable);
        return *this;
    }
    
    constexpr bool reset_random_number_generator() const {
        return base::check_bits(bits::rng_reset);
    }
    
    constexpr control_register_2 &reset_receive_logic(bool enable) {
        base::set_bits(bits::rx_reset, enable);
        return *this;
    }
    
    constexpr bool reset_receive_logic() const {
        return base::check_bits(bits::rx_reset);
    }
    
    constexpr control_register_2 &reset_receive_function(bool enable) {
        base::set_bits(bits::rx_function_reset, enable);
        return *this;
    }
    
    constexpr bool reset_receive_function() const {
        return base::check_bits(bits::rx_function_reset);
    }
    
    constexpr control_register_2 &reset_transmit_logic(bool enable) {
        base::set_bits(bits::tx_reset, enable);
        return *this;
    }
    
    constexpr bool reset_transmit_logic() const {
        return base::check_bits(bits::tx_reset);
    }
    
    constexpr control_register_2 &reset_transmit_function(bool enable) {
        base::set_bits(bits::tx_function_reset, enable);
        return *this;
    }
    
    constexpr bool reset_transmit_function() const {
        return base::check_bits(bits::tx_function_reset);
    }
};

class control_register_3 : public base_register<unsigned char> {
    using base = base_register<unsigned char>;
    
    struct bits {
        enum : unsigned char {
            pad_crc = 0x80 + 0x40 + 0x20,
            tx_crc = 0x10,
            proprietary_header = 0x08,
            huge_frame = 0x04,
            frame_length_check = 0x02,
            full_duplex = 0x01
        };
    };
    
public:
    enum pad_conf : unsigned char {
        /**
         * MAC will automatically detect VLAN Protocol frames
         * which have a 8100h type field and automatically pad
         * to 64 bytes. If the frame is not a VLAN frame, it
         * will be padded to 60 bytes. After padding, a valid
         * CRC will be appended.
         */
        pad_60_vlan_64 = 0x80 + 0x20,
        
        /**
         * All short frames will be zero padded to 64 bytes and
         * a valid CRC will then be appended.
         */
        pad_64 = 0x40 + 0x20,
        
        /**
         * All short frames will be zero padded to 60 bytes and
         * a valid CRC will then be appended.
         */
        pad_60 = 0x20,
        
        /**
         * No automatic padding of short frames.
         */
        no_pad = 0
    };
    
    constexpr control_register_3() {
        auto_padding(pad_60_vlan_64);
        transmit_crc(false);
        proprietary_header(false);
        huge_frame(false);
        check_frame_length(true);
        full_duplex(true);
    }
    
    constexpr control_register_3(unsigned char data) : base(data) {}
    
    constexpr control_register_3 &transmit_crc(bool enable) {
        base::set_bits(bits::tx_crc, enable);
        return *this;
    }
    
    constexpr bool transmit_crc() const {
        return base::check_bits(bits::tx_crc);
    }
    
    constexpr control_register_3 &proprietary_header(bool enable) {
        base::set_bits(bits::proprietary_header, enable);
        return *this;
    }
    
    constexpr bool proprietary_header() const {
        return base::check_bits(bits::proprietary_header);
    }
    
    constexpr control_register_3 &huge_frame(bool enable) {
        base::set_bits(bits::huge_frame, enable);
        return *this;
    }
    
    constexpr bool huge_frame() const {
        return base::check_bits(bits::huge_frame);
    }
    
    constexpr control_register_3 &check_frame_length(bool enable) {
        base::set_bits(bits::frame_length_check, enable);
        return *this;
    }
    
    constexpr bool check_frame_length() const {
        return base::check_bits(bits::frame_length_check);
    }
    
    constexpr control_register_3 &full_duplex(bool enable) {
        base::set_bits(bits::full_duplex, enable);
        return *this;
    }
    
    constexpr bool full_duplex() const {
        return base::check_bits(bits::full_duplex);
    }
    
    constexpr control_register_3 &auto_padding(pad_conf conf) {
        base::set_bits(bits::pad_crc, 0);
        base::set_bits(conf, 1);
        return *this;
    }
    
    constexpr pad_conf auto_padding() const {
        return pad_conf{base::get_bits(bits::pad_crc)};
    }
};

class control_register_4 : public base_register<unsigned char> {
    using base = base_register<unsigned char>;
    
    struct bits {
        enum : unsigned char {
            defer_transmission = 0x40,
            no_backoff_on_back_pressure = 0x20,
            no_backoff = 0x10,
            long_preamble_enforcement = 0x02,
            pure_preamble_enforcement = 0x01
        };
    };
    
public:
    constexpr control_register_4() {
        defer_transmission(false);
        no_backoff_on_back_pressure(false);
        no_backoff(false);
        long_preamble_enforcement(false);
        pure_preamble_enforcement(false);
    }
    
    constexpr control_register_4(unsigned char data) : base(data) {}
    
    constexpr control_register_4 defer_transmission(bool enable) {
        base::set_bits(bits::defer_transmission, enable);
        return *this;
    }
    
    constexpr bool defer_transmission() const {
        return base::check_bits(bits::defer_transmission);
    }
    
    constexpr control_register_4 no_backoff_on_back_pressure(bool enable) {
        base::set_bits(bits::no_backoff_on_back_pressure, enable);
        return *this;
    }
    
    constexpr bool no_backoff_on_back_pressure() const {
        return base::check_bits(bits::no_backoff_on_back_pressure);
    }
    
    constexpr control_register_4 no_backoff(bool enable) {
        base::set_bits(bits::no_backoff, enable);
        return *this;
    }
    
    constexpr bool no_backoff() const {
        return base::check_bits(bits::no_backoff);
    }
    
    constexpr control_register_4 long_preamble_enforcement(bool enable) {
        base::set_bits(bits::long_preamble_enforcement, enable);
        return *this;
    }
    
    constexpr bool long_preamble_enforcement() const {
        return base::check_bits(bits::long_preamble_enforcement);
    }
    
    constexpr control_register_4 pure_preamble_enforcement(bool enable) {
        base::set_bits(bits::pure_preamble_enforcement, enable);
        return *this;
    }
    
    constexpr bool pure_preamble_enforcement() const {
        return base::check_bits(bits::pure_preamble_enforcement);
    }
};

class btb_inter_package_gap : public base_register<unsigned char> {
    using base = base_register<unsigned char>;
    
    struct bits {
        enum : unsigned char {
            delay = 0xff - 0x80
        };
    };
    
public:
    constexpr btb_inter_package_gap() {
        delay(0x15);
    }
    
    constexpr btb_inter_package_gap(unsigned char data) : base(data) {}
    
    constexpr btb_inter_package_gap &delay(unsigned char time) {
        base::set_bits(bits::delay, 0);
        base::set_bits(time & bits::delay, 1);
        return *this;
    }
    
    constexpr unsigned char delay() const {
        return base::get_bits(bits::delay);
    }
};

class phy_support : public base_register<unsigned char> {
    using base = base_register<unsigned char>;
    
    struct bits {
        enum : unsigned char {
            interface_reset = 0x80,
            reserved_4 = 0x10,
            rmii_reset = 0x08,
            reserved_0 = 0x01
        };
    };
    
public:
    constexpr phy_support() {
        init_reserved();
        interface_reset(false);
        rmii_reset(false);
    }
    
    constexpr phy_support &interface_reset(bool enable) {
        base::set_bits(bits::interface_reset, enable);
        return *this;
    }
    
    constexpr bool interface_reset() const {
        return base::check_bits(bits::interface_reset);
    }
    
    constexpr phy_support &rmii_reset(bool enable) {
        base::set_bits(bits::rmii_reset, enable);
        return *this;
    }
    
    constexpr bool rmii_reset() const {
        return base::check_bits(bits::rmii_reset);
    }
    
private:
    constexpr void init_reserved() {
        base::set_bits(bits::reserved_4, 1);
        base::set_bits(bits::reserved_0, 0);
    }
};

}
