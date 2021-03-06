/*!
    \file  usbd_int.h
    \brief usb device interrupt handler header file
*/

/*
    Copyright (C) 2016 GigaDevice

    2014-09-06, V1.0.0, firmware for GD32F150
    2016-01-15, V1.0.1, firmware for GD32F150
    2016-04-30, V3.0.0, firmware update for GD32F150
*/

#ifndef USBD_INT_H
#define USBD_INT_H

#include "usbd_core.h"
#include "usbd_std.h"
#include "usbd_pwr.h"

extern usbd_core_handle_struct usb_device_dev;

extern __IO uint8_t prev_receive_complete;


typedef struct
{
    uint8_t (*SOF) (usbd_core_handle_struct *pudev); /*!< SOF ISR callback */
}usbd_int_cb_struct;

extern usbd_int_cb_struct *usbd_int_fops;

/* function declarations */
/* USB device interrupt service routine */
void  usbd_isr (void);

#endif /* USBD_INT_H */
