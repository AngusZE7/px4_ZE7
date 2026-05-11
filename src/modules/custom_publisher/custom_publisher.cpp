#include <px4_platform_common/module.h>
#include <px4_platform_common/log.h>

#include <uORB/uORB.h>
#include <uORB/topics/custom_up.h>

#include <drivers/drv_hrt.h>

extern "C" __EXPORT int custom_publisher_main(int argc, char *argv[]);

int custom_publisher_main(int argc, char *argv[])
{
    PX4_INFO("Custom publisher started");

    custom_up_s msg{};
    orb_advert_t pub = orb_advertise(ORB_ID(custom_up), &msg);

    while (true) {

        msg.timestamp       = hrt_absolute_time();

        // 暫時寫死，等CAN driver完成後換成真實資料
        msg.pressure_1      = 100;
        msg.pressure_2      = 200;
        msg.pressure_3      = 300;
        msg.pressure_4      = 400;
        msg.encoder_1       = 10;
        msg.encoder_2       = 20;
        msg.encoder_3       = 30;
        msg.bms_temperature = 25;
        msg.bms_voltage     = 12;
        msg.bms_related_1   = 1;
        msg.bms_related_2   = 2;
        msg.bms_related_3   = 3;
        msg.state_param_1   = 0;
        msg.state_param_2   = 0;
        msg.state_param_3   = 0;
        msg.state_param_4   = 0;
        msg.state_param_5   = 0;

        orb_publish(ORB_ID(custom_up), pub, &msg);

        PX4_INFO("Published custom_up topic");

        px4_usleep(200000); // 5Hz
    }

    return 0;
}
