#pragma once

#include <uORB/uORB.h>
#include <uORB/topics/custom_up.h>
#include <mavlink/mavlink_stream.h>

class MavlinkStreamCustomUp : public MavlinkStream
{
public:
    static MavlinkStream *new_instance(Mavlink *mavlink)
    {
        return new MavlinkStreamCustomUp(mavlink);
    }

    static constexpr const char *get_name_static() { return "CUSTOM_UP"; }
    const char *get_name() const override { return get_name_static(); }
    uint16_t get_id() override { return MAVLINK_MSG_ID_CUSTOM_UP; }

    unsigned get_size() override
    {
        return MAVLINK_MSG_ID_CUSTOM_UP_LEN + MAVLINK_NUM_NON_PAYLOAD_BYTES;
    }

private:
    explicit MavlinkStreamCustomUp(Mavlink *mavlink)
        : MavlinkStream(mavlink) {}

    uORB::Subscription _sub{ORB_ID(custom_up)};

    bool send() override
    {
        custom_up_s data{};

        if (_sub.update(&data)) {
            mavlink_custom_up_t msg{};

            msg.pressure_1 = data.pressure_1;
            msg.pressure_2 = data.pressure_2;
            msg.pressure_3 = data.pressure_3;
            msg.pressure_4 = data.pressure_4;
            msg.encoder_1 = data.encoder_1;
            msg.encoder_2 = data.encoder_2;
            msg.encoder_3 = data.encoder_3;
            msg.bms_temperature = data.bms_temperature;
	    msg.bms_voltage = data.bms_voltage;
            msg.bms_related_1 = data.bms_related_1;
            msg.bms_related_2 = data.bms_related_2;
            msg.bms_related_3 = data.bms_related_3;
            msg.state_param_1 = data.state_param_1;
            msg.state_param_2 = data.state_param_2;
            msg.state_param_3 = data.state_param_3;
            msg.state_param_4 = data.state_param_4;
            msg.state_param_5 = data.state_param_5;

            mavlink_msg_custom_up_send_struct(
                _mavlink->get_channel(), &msg);

            return true;
        }
        return false;
    }
};

