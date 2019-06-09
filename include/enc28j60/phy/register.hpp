#pragma once

#include <cstdint>
#include <enc28j60/detail/base_register.hpp>

namespace enc28j60::phy {

class control_register_1 : public base_register<std::uint16_t> {
    using base = base_register<std::uint16_t>;
    
    struct bits {
        enum : std::uint16_t {
            software_reset = 0x8000,
            loopback = 0x4000,
            power_down = 0x0800,
            duplex_mode = 0x0100,

            reserved_0 = 0x0400,
            reserved_1 = 0x0080
        };
    };
    
public:
    constexpr control_register_1() {
        init_reserved();
        software_reset(false);
        loopback(false);
        power_down(false);
        full_duplex(true);
    }
    
    constexpr control_register_1(std::uint16_t data) : base(data) {}
    
    constexpr control_register_1 &software_reset(bool enable) {
        base::set_bits(bits::software_reset, enable);
        return *this;
    }
    
    constexpr bool software_reset() const {
        return base::check_bits(bits::software_reset);
    }
    
    constexpr control_register_1 &loopback(bool enable) {
        base::set_bits(bits::loopback, enable);
        return *this;
    }
    
    constexpr bool loopback() const {
        return base::check_bits(bits::loopback);
    }
    
    constexpr control_register_1 &power_down(bool enable) {
        base::set_bits(bits::power_down, enable);
        return *this;
    }
    
    constexpr bool power_down() const {
        return base::check_bits(bits::power_down);
    }
    
    constexpr control_register_1 &full_duplex(bool enable) {
        base::set_bits(bits::duplex_mode, enable);
        return *this;
    }
    
    constexpr bool full_duplex() const {
        return base::check_bits(bits::duplex_mode);
    }
    
private:
    constexpr void init_reserved() {
        base::set_bits(bits::reserved_0, 0);
        base::set_bits(bits::reserved_1, 1);
    }
};


class control_register_2 : public base_register<std::uint16_t> {
    using base = base_register<std::uint16_t>;
    
    struct bits {
        enum : std::uint16_t {
            force_linkup = 0x4000,
            twisted_pair_transmitter_disable = 0x2000,
            jabber_correction = 0x0400,
            half_duplex_loopback_disable = 0x0100,

            reserved_0 = 0x1000 + 0x0800 + 0x0200 + 0x00ff
        };
    };

public:
    constexpr control_register_2() {
        init_reserved();
        force_linkup(false);
        disable_twisted_pair_transmitter(false);
        jabber_correction(false);
        disable_half_duplex_loopback(false);
    }
    
    constexpr control_register_2(std::uint16_t data) : base(data) {}
    
    constexpr control_register_2 &force_linkup(bool enable) {
        base::set_bits(bits::force_linkup, enable);
        return *this;
    }
    
    constexpr bool force_linkup() const {
        return base::check_bits(bits::force_linkup);
    }
    
    constexpr control_register_2 &disable_twisted_pair_transmitter(bool enable) {
        base::set_bits(bits::twisted_pair_transmitter_disable, enable);
        return *this;
    }
    
    constexpr bool disable_twisted_pair_transmitter() const {
        return base::check_bits(bits::twisted_pair_transmitter_disable);
    }
    
    constexpr control_register_2 &jabber_correction(bool enable) {
        base::set_bits(bits::jabber_correction, enable);
        return *this;
    }
    
    constexpr bool jabber_correction() const {
        return base::check_bits(bits::jabber_correction);
    }
    
    constexpr control_register_2 &disable_half_duplex_loopback(bool enable) {
        base::set_bits(bits::half_duplex_loopback_disable, enable);
        return *this;
    }
    
    constexpr bool disable_half_duplex_loopback() const {
        return base::check_bits(bits::half_duplex_loopback_disable);
    }
    
private:
    constexpr void init_reserved() {
        base::set_bits(bits::reserved_0, 0);
    }
};

class device_id_1 : public base_register<std::uint16_t> {
    using base = base_register<std::uint16_t>;
    
    struct bits {
        enum : std::uint16_t {
            identifier = 0xffff
        };
    };

public:
    constexpr device_id_1(std::uint16_t data) : base(data) {}
    
    constexpr std::uint16_t upper_identifier() const {
        return base::get_bits(bits::identifier);
    }
};

class device_id_2 : public base_register<std::uint16_t> {
    using base = base_register<std::uint16_t>;
    
    struct bits {
        enum : std::uint16_t {
            identifier = 0xf000 + 0x0800 + 0x0400,
            part_number = 0x00f0 + 0x0200 + 0x0100,
            revision = 0x000f
        };
    };
    
    struct shifts {
        enum {
            identifier = 10,
            part_number = 4,
            revision = 0
        };
    };

public:
    constexpr device_id_2(std::uint16_t data) : base(data) {}
    
    constexpr std::uint16_t lower_identifier() const {
        return base::get_bits(bits::identifier) >> shifts::identifier;
    }
    
    constexpr std::uint16_t part_number() const {
        return base::get_bits(bits::part_number) >> shifts::part_number;
    }
    
    constexpr std::uint8_t revision_level() const {
        return base::get_bits(bits::revision) >> shifts::revision;
    }
};

class device_id : device_id_1, device_id_2 {
    struct length {
        enum {
            lower_identifier = 6
        };
    };
public:
    constexpr device_id(device_id_1 id1, device_id_2 id2)
        : device_id_1(id1), device_id_2(id2) {}; 
    
    constexpr std::uint32_t identifier() const {
        return device_id_2::lower_identifier() + 
            (device_id_1::upper_identifier() >> length::lower_identifier);
    }
    
    constexpr std::uint16_t part_number() const {
        return device_id_2::part_number();
    }
    
    constexpr std::uint16_t revision_level() const {
        return device_id_2::revision_level();
    }
    
    const device_id_1 &id_1() const {
        return *this;
    }
    
    const device_id_2 &id_2() const {
        return *this;
    }
};

class interrupt_request;

class interrupt_enable : public base_register<std::uint16_t> {
    using base = base_register<std::uint16_t>;
    
    friend interrupt_request;
    
    struct bits {
        enum : std::uint16_t {
            link_change = 0x0010,
            global = 0x0002,
            reserved_0 = 0xffff - global - link_change
        };
    };

public:
    constexpr interrupt_enable() {
        init_reserved();
    }
    
    constexpr interrupt_enable(std::uint16_t data) : base(data) {}
    
    constexpr interrupt_enable &link_change(bool enable) {
        base::set_bits(bits::link_change, enable);
        return *this;
    }
    
    constexpr bool link_change() const {
        return base::check_bits(bits::link_change);
    }
    
    constexpr interrupt_enable &global(bool enable) {
        base::set_bits(bits::global, enable);
        return *this;
    }
    
    constexpr bool global() const {
        return base::check_bits(bits::global);
    }
    
private:
    constexpr void init_reserved() {
        base::set_bits(bits::reserved_0, 0);
    }
};

class interrupt_request: public base_register<std::uint16_t> {
    using base = base_register<std::uint16_t>;
    
    using bits = interrupt_enable::bits;

public:
    constexpr interrupt_request(std::uint16_t data) : base(data) {}
    
    constexpr bool link_change() const {
        return base::check_bits(bits::link_change);
    }
    
    constexpr bool global() const {
        return base::check_bits(bits::global);
    }
};

class led_control: public base_register<std::uint16_t> {
    using base = base_register<std::uint16_t>;
    
    struct bits {
        enum : std::uint16_t {
            led_a = 0x0f00,
            led_b = 0x00f0,
            pulse_stretch_time = 0x0008 + 0x0004,
            pulse_stretch = 0x0002,
            reserved_0 = 0xf000 + 0x0001
        };
    };
    
    struct shifts {
        enum {
            led_a = 16,
            led_b = 8,
            pulse_stretch_time = 2
        };
    };

public:
    enum led_conf : std::uint8_t {
        display_tx_activity = 0b0001,
        display_rx_activity = 0b0010,
        display_collision_activity = 0b0011,
        display_link_status = 0b0100,
        display_duplex_status = 0b0101,
        display_rx_tx_activity = 0b0111,
        on = 0b1000,
        off = 0b1001,
        blink_fast = 0b1010,
        blink_slow = 0b1011,
        display_link_status_and_rx_activity = 0b1100,
        display_link_status_and_tx_rx_activity = 0b1101,
        display_duplex_status_and_collision_acitvity = 0b1110
    };
    
    enum time_conf {
        ms_139 = 0b10,
        ms_73 = 0b01,
        ms_40 = 0b00
    };
    
    constexpr led_control() {
        init_reserved();
        led_a(display_link_status);
        led_b(display_rx_activity);
        pulse_stretch_time(ms_40);
        pulse_stretching(true);
    }
    
    constexpr led_control(std::uint16_t data) : base(data) {}
    
    constexpr led_control &led_a(led_conf conf) {
        base::set_bits(bits::led_a, 0);
        base::set_bits(conf << shifts::led_a, 1);
        return *this;
    }
    
    constexpr led_conf led_a() const {
        return led_conf{
                static_cast<uint8_t>(
                    base::get_bits(bits::led_a) >> shifts::led_a)};
    }
    
    constexpr led_control &led_b(led_conf conf) {
        base::set_bits(bits::led_b, 0);
        base::set_bits(conf << shifts::led_b, 1);
        return *this;
    }
    
    constexpr led_conf led_b() const {
        return led_conf{
                static_cast<uint8_t>(
                    base::get_bits(bits::led_b) >> shifts::led_b)};
    }
    
    constexpr led_control &pulse_stretch_time(time_conf conf) {
        base::set_bits(bits::pulse_stretch_time, 0);
        base::set_bits(conf << shifts::pulse_stretch_time, 1);
        return *this;
    }
    
    constexpr led_conf pulse_stretch_time() const {
        return led_conf{
                static_cast<uint8_t>(
                    base::get_bits(bits::pulse_stretch_time) >>
                        shifts::pulse_stretch_time)};
    }
    
    constexpr led_control &pulse_stretching(bool enable) {
        base::set_bits(bits::pulse_stretch, enable);
        return *this;
    }
    
    constexpr bool pulse_stretching() const {
        return base::check_bits(bits::pulse_stretch);
    }
    
private:
    constexpr void init_reserved() {
        base::set_bits(bits::reserved_0, 0);
    }
};

class status_1: public base_register<std::uint16_t> {
    using base = base_register<std::uint16_t>;
    
    struct bits {
        enum : std::uint16_t {
            full_duplex_cap = 0x1000,
            half_duplex_cap = 0x0800,
            latching_link = 0x0004,
            latching_jabber = 0x0002
        };
    };

public:
    constexpr status_1(std::uint16_t data) : base(data) {}
    
    constexpr bool full_duplex_capable() const {
        return base::check_bits(bits::full_duplex_cap);
    }
    
    constexpr bool half_duplex_capable() const {
        return base::check_bits(bits::half_duplex_cap);
    }
    
    constexpr bool link_up_latched() const {
        return base::check_bits(bits::latching_link);
    }
    
    constexpr bool jabber_latched() const {
        return base::check_bits(bits::latching_jabber);
    }
};

class status_2: public base_register<std::uint16_t> {
    using base = base_register<std::uint16_t>;

    struct bits {
        enum : std::uint16_t {
            tx_status = 0x2000,
            rx_status = 0x1000,
            collision_status = 0x0800,
            link_status = 0x0400,
            duplex_status = 0x0200,
            polarity_status = 0x0010
        };
    };
    
public:
    constexpr status_2(std::uint16_t data) : base(data) {}
    
    constexpr bool transmitting() const {
        return base::check_bits(bits::tx_status);
    }
    
    constexpr bool receiving() const {
        return base::check_bits(bits::rx_status);
    }
    
    constexpr bool collision_occured() const {
        return base::check_bits(bits::collision_status);
    }
    
    constexpr bool link_up() const {
        return base::check_bits(bits::link_status);
    }
    
    constexpr bool full_duplex() const {
        return base::check_bits(bits::duplex_status);
    }
    
    constexpr bool reversed_polarity() const {
        return base::check_bits(bits::polarity_status);
    }
};

}
