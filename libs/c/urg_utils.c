/*!
  \brief URG センサ用の補助関数

  \author Satofumi KAMIMURA

  $Id$
*/

#include "urg_utils.h"
#include "urg_errno.h"
#include <math.h>

#undef max


static int max(int a, int b)
{
    return (a > b) ? a : b;
}


const char *urg_error(const urg_t *urg)
{
    typedef struct
    {
        int no;
        const char* message;
    } error_messages_t;


    error_messages_t errors[] = {
        { URG_NO_ERROR, "no error." },
        { URG_UNKNOWN_ERROR, "unknown error." },
        { URG_NOT_CONNECTED, "not connected." },
        { URG_NOT_IMPLEMENTED, "not implemented." },
        { URG_INVALID_RESPONSE, "invalid response." },
        { URG_NO_RESPONSE, "no response." },

        { URG_SEND_ERROR, "send error." },
        { URG_RECEIVE_ERROR, "receive error." },
        { URG_CHECKSUM_ERROR, "checksum error." },
        { URG_INVALID_PARAMETER, "invalid parameter." },

        { URG_SERIAL_OPEN_ERROR, "could not open serial device." },
        { URG_NOT_DETECT_BAUDRATE_ERROR, "could not detect serial baudrate." },
        { URG_ETHERNET_OPEN_ERROR, "could not open ethernet port." },
        { URG_SCANNING_PARAMETER_ERROR, "scanning parameter error." },
        { URG_DATA_SIZE_PARAMETER_ERROR, "data size parameter error." },
    };

    int n = sizeof(errors) / sizeof(errors[0]);
    int i;

    for (i = 0; i < n; ++i) {
        if (errors[i].no == urg->last_errno) {
            return errors[i].message;
        }
    }

    return "Unknown error.";
}


void urg_distance_min_max(const urg_t *urg,
                          long *min_distance, long *max_distance)
{
    if (!urg->is_active) {
        *min_distance = 1;
        *max_distance = 0;
        return;
    }

    *min_distance = urg->min_distance;

    // urg_set_communication_data_size() を反映した距離を返す
    *max_distance =
        (urg->range_data_byte == URG_COMMUNICATION_2_BYTE) ?
        max(urg->max_distance, 4095) : urg->max_distance;
}


void urg_step_min_max(const urg_t *urg, int *min_index, int *max_index)
{
    if (!urg->is_active) {
        *min_index = 1;
        *max_index = 0;
        return;
    }

    *min_index = urg->first_data_index - urg->front_data_index;
    *max_index = urg->last_data_index - urg->front_data_index;
}


long urg_scan_usec(const urg_t *urg)
{
    if (!urg->is_active) {
        return URG_NOT_CONNECTED;
    }

    return urg->scan_usec;
}


int urg_max_index(const urg_t *urg)
{
    if (!urg->is_active) {
        return URG_NOT_CONNECTED;
    }

    return urg->last_data_index;
}


double urg_index2rad(const urg_t *urg, int index)
{
    if (!urg->is_active) {
        return URG_NOT_CONNECTED;
    }

    (void)urg;
    (void)index;
    // !!!
    return 0.0;
}


double urg_index2deg(const urg_t *urg, int index)
{
    return urg_index2rad(urg, index) * 180.0 / M_PI;
}


int urg_rad2index(const urg_t *urg, double radian)
{
    if (!urg->is_active) {
        return URG_NOT_CONNECTED;
    }

    (void)urg;
    (void)radian;

    // !!!

    return 0;
}


int urg_deg2index(const urg_t *urg, double degree)
{
    return urg_rad2step(urg, degree * M_PI / 180.0);
}


int urg_rad2step(const urg_t *urg, double radian)
{
    if (!urg->is_active) {
        return URG_NOT_CONNECTED;
    }

    (void)urg;
    (void)radian;

    // !!!

    return 0;
}


int urg_deg2step(const urg_t *urg, double degree)
{
    if (!urg->is_active) {
        return URG_NOT_CONNECTED;
    }

    (void)urg;
    (void)degree;

    // !!!

    return 0;
}


double urg_step2rad(const urg_t *urg, int step)
{
    if (!urg->is_active) {
        return URG_NOT_CONNECTED;
    }

    (void)urg;
    (void)step;

    // !!!

    return 0.0;
}


double urg_step2deg(const urg_t *urg, int step)
{
    return urg_step2rad(urg, step) * 180.0 / M_PI;
}


int urg_step2index(const urg_t *urg, int step)
{
    if (!urg->is_active) {
        return URG_NOT_CONNECTED;
    }

    (void)urg;
    (void)step;
    // !!!

    return 0;
}
