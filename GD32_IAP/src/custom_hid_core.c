/*!
    \file  custom_hid_core.c
    \brief custom HID class driver
*/

/*
    Copyright (C) 2016 GigaDevice

    2014-09-06, V1.0.0, firmware for GD32F150
    2016-01-15, V1.0.1, firmware for GD32F150
    2016-04-30, V3.0.0, firmware update for GD32F150
*/

#include "usbd_int.h"
#include "custom_hid_core.h"
#include <string.h>

#define USBD_VID                     0x0ACD
#define USBD_PID                     0x2030

uint8_t report_buf[64];
uint8_t usbd_customhid_report_id = 0;
uint8_t flag = 0;
__IO uint8_t prev_receive_complete = 1;


__IO unsigned char RecvBuff[64+1];
__IO unsigned char SendBuff[64+1];


static uint32_t usbd_customhid_altset = 0;
static uint32_t usbd_customhid_protocol = 0;
static uint32_t usbd_customhid_idlestate = 0;

usbd_int_cb_struct *usbd_int_fops = NULL;

usbd_core_handle_struct  usb_device_dev =
{
    .dev_desc = (uint8_t *)&device_descripter,
    .config_desc = (uint8_t *)&configuration_descriptor,
    .strings = usbd_strings,
    .class_init = custom_hid_init,
    .class_deinit = custom_hid_deinit,
    .class_req_handler = custom_hid_req_handler,
    .class_data_handler = custom_hid_data_handler
};

/* Note:it should use the C99 standard when compiling the below codes */
/* USB standard device descriptor */
const usb_descriptor_device_struct device_descripter =
{
    .Header = 
     {
         .bLength = USB_DEVICE_DESC_SIZE, 
         .bDescriptorType = USB_DESCTYPE_DEVICE
     },
    .bcdUSB = 0x0200,
    .bDeviceClass = 0x00,
    .bDeviceSubClass = 0x00,
    .bDeviceProtocol = 0x00,
    .bMaxPacketSize0 = USBD_EP0_MAX_SIZE,
    .idVendor = USBD_VID,
    .idProduct = USBD_PID,
    .bcdDevice = 0x0100,
    .iManufacturer = USBD_MFC_STR_IDX,
    .iProduct = USBD_PRODUCT_STR_IDX,
    .iSerialNumber = USBD_SERIAL_STR_IDX,
    .bNumberConfigurations = USBD_CFG_MAX_NUM
};

const usb_descriptor_configuration_set_struct configuration_descriptor = 
{
    .Config = 
    {
        .Header = 
         {
             .bLength = sizeof(usb_descriptor_configuration_struct), 
             .bDescriptorType = USB_DESCTYPE_CONFIGURATION 
         },
        .wTotalLength = CUSTOMHID_CONFIG_DESC_SIZE,
        .bNumInterfaces = 0x01,
        .bConfigurationValue = 0x01,
        .iConfiguration = 0x00,
        .bmAttributes = 0xC0,
        .bMaxPower = 0x32
    },

    .HID_Interface = 
    {
        .Header = 
         {
             .bLength = sizeof(usb_descriptor_interface_struct), 
             .bDescriptorType = USB_DESCTYPE_INTERFACE 
         },
        .bInterfaceNumber = 0x00,
        .bAlternateSetting = 0x00,
        .bNumEndpoints = 0x02,
        .bInterfaceClass = 0x03,
        .bInterfaceSubClass = 0x00,
        .bInterfaceProtocol = 0x00,
        .iInterface = 0x00
    },

    .HID_VendorHID = 
    {
        .Header = 
         {
             .bLength = sizeof(usb_hid_descriptor_hid_struct),
             .bDescriptorType = CUSTOMHID_DESC_TYPE 
         },
        .bcdHID = 0x0111,
        .bCountryCode = 0x00,
        .bNumDescriptors = 0x01,
        .bDescriptorType = CUSTOMHID_REPORT_DESCTYPE,
        .wDescriptorLength = CUSTOMHID_REPORT_DESC_SIZE,
    },

    .HID_ReportINEndpoint = 
    {
        .Header = 
         {
             .bLength = sizeof(usb_descriptor_endpoint_struct), 
             .bDescriptorType = USB_DESCTYPE_ENDPOINT 
         },
        .bEndpointAddress = CUSTOMHID_IN_EP,
        .bmAttributes = 0x03,
        .wMaxPacketSize = CUSTOMHID_IN_PACKET,
        .bInterval = 0x1
    },

    .HID_ReportOUTEndpoint = 
    {
        .Header = 
         {
             .bLength = sizeof(usb_descriptor_endpoint_struct), 
             .bDescriptorType = USB_DESCTYPE_ENDPOINT
         },
        .bEndpointAddress = CUSTOMHID_OUT_EP,
        .bmAttributes = 0x03,
        .wMaxPacketSize = CUSTOMHID_OUT_PACKET,
        .bInterval = 0x1
    }
};

/* USB language ID Descriptor */
const usb_descriptor_language_id_struct usbd_language_id_desc = 
{
    .Header = 
     {
         .bLength = sizeof(usb_descriptor_language_id_struct), 
         .bDescriptorType = USB_DESCTYPE_STRING
     },
    .wLANGID = ENG_LANGID
};

void *const usbd_strings[] = 
{
    [USBD_LANGID_STR_IDX] = (uint8_t *)&usbd_language_id_desc,
    [USBD_MFC_STR_IDX] = USBD_STRING_DESC("PayFull."),
    [USBD_PRODUCT_STR_IDX] = USBD_STRING_DESC("Encrypted Magnetic Read Head."),
    [USBD_SERIAL_STR_IDX] = USBD_STRING_DESC("EMP3001V1.3")
};

/* USB custom HID device report descriptor */
const uint8_t customhid_report_descriptor[CUSTOMHID_REPORT_DESC_SIZE] =
  {                    
    0x06, 0xFF, 0x00,      /* USAGE_PAGE (Vendor Page: 0xFF00) */                       
    0x09, 0x01,            /* USAGE (Demo Kit)               */    
    0xa1, 0x01,            /* COLLECTION (Application)       */            
    /* 6 */
    
    /* intput */        
    0x85, 0x01,            /*     REPORT_ID (1)		     */
    0x09, 0x01,            /*     USAGE (LED 1)	             */
    0x15, 0x00,            /*     LOGICAL_MINIMUM (0)        */          
    0x25, 0x01,            /*     LOGICAL_MAXIMUM (1)        */           
    0x75, 0x08,            /*     REPORT_SIZE (8)            */        
    0x95, CUSTOMHID_IN_PACKET-1,  /*     REPORT_COUNT (1)           */ 	//THREE      
    0xB1, 0x82,             /*    FEATURE (Data,Var,Abs,Vol) */     

    0x85, 0x01,            /*     REPORT_ID (1)              */
    0x09, 0x01,            /*     USAGE (LED 1)              */
    0x91, 0x82,            /*     OUTPUT (Data,Var,Abs,Vol)  */
    /* 26 */

    /* output */        
    0x85, 0x05,            /*     REPORT_ID (1)		     */
    0x09, 0x05,            /*     USAGE (LED 1)	             */
    0x15, 0x00,            /*     LOGICAL_MINIMUM (0)        */          
    0x26, 0xff, 0x00,      /*     LOGICAL_MAXIMUM (255)      */                 
    0x75, 0x08,            /*     REPORT_SIZE (8)            */        
    0x95, CUSTOMHID_OUT_PACKET-1,  /*     REPORT_COUNT (1)           */ 	//THREE      
    0x81, 0x82,             /*    FEATURE (Data,Var,Abs,Vol) */     

    0x85, 0x05,            /*     REPORT_ID (1)              */
    0x09, 0x05,            /*     USAGE (LED 1)              */
    0xb1, 0x82,            /*     OUTPUT (Data,Var,Abs,Vol)  */
    /* 26 */

    0xc0 	          /*     END_COLLECTION	             */
  }; /* CustomHID_ReportDescriptor */
//{
//    0x05, 0x01,  /* USAGE_PAGE (Generic Desktop) */
//    0x09, 0x06,  /* USAGE (Keyboard) */
//    0xa1, 0x01,  /* COLLECTION (Application) */

//    0x05, 0x07,  /* USAGE_PAGE (Keyboard/Keypad) */
//    0x19, 0xe0,  /* USAGE_MINIMUM (Keyboard LeftControl) */
//    0x29, 0xe7,  /* USAGE_MAXIMUM (Keyboard Right GUI) */
//    0x15, 0x00,  /* LOGICAL_MINIMUM (0) */
//    0x25, 0x01,  /* LOGICAL_MAXIMUM (1) */
//    0x95, 0x40,  /* REPORT_COUNT (8) */
//    0x75, 0x01,  /* REPORT_SIZE (1) */
//    0x81, 0x02,  /* INPUT (Data,Var,Abs) */

//    0x95, 0x01,  /* REPORT_COUNT (1) */
//    0x75, 0x40,  /* REPORT_SIZE (8) */
//    0x81, 0x03,  /* INPUT (Cnst,Var,Abs) */

//    0x95, 0x06,  /* REPORT_COUNT (6) */
//    0x75, 0x40,  /* REPORT_SIZE (8) */
//    0x25, 0xFF,  /* LOGICAL_MAXIMUM (255) */
//    0x19, 0x00,  /* USAGE_MINIMUM (Reserved (no event indicated)) */
//    0x29, 0x65,  /* USAGE_MAXIMUM (Keyboard Application) */
//    0x81, 0x00,  /* INPUT (Data,Ary,Abs) */

//    0x25, 0x01,  /* LOGICAL_MAXIMUM (1) */
//    0x95, 0x02,  /* REPORT_COUNT (2) */
//    0x75, 0x01,  /* REPORT_SIZE (1) */
//    0x05, 0x08,  /* USAGE_PAGE (LEDs) */
//    0x19, 0x01,  /* USAGE_MINIMUM (Num Lock) */
//    0x29, 0x02,  /* USAGE_MAXIMUM (Caps Lock) */
//    0x91, 0x02,  /* OUTPUT (Data,Var,Abs) */

//    0x95, 0x01,  /* REPORT_COUNT (1) */
//    0x75, 0x06,  /* REPORT_SIZE (6) */
//    0x91, 0x03,  /* OUTPUT (Cnst,Var,Abs) */

//    0xc0         /* END_COLLECTION */


//}; /* CustomHID_ReportDescriptor */ 


/*!
    \brief      initialize the HID device
    \param[in]  pudev: pointer to USB device instance
    \param[in]  config_index: configuration index
    \param[out] none
    \retval     USB device operation status
*/
usbd_status_enum custom_hid_init (void *pudev, uint8_t config_index)
{
    /* initialize Tx endpoint */
    usbd_ep_init(pudev, &(configuration_descriptor.HID_ReportINEndpoint));

    /* initialize Rx endpoint */
    usbd_ep_init(pudev, &(configuration_descriptor.HID_ReportOUTEndpoint));

    /* prepare receive data */
    usbd_ep_rx(pudev, CUSTOMHID_OUT_EP, report_buf, 64);

    return USBD_OK;
}

/*!
    \brief      de-initialize the HID device
    \param[in]  pudev: pointer to USB device instance
    \param[in]  config_index: configuration index
    \param[out] none
    \retval     USB device operation status
*/
usbd_status_enum  custom_hid_deinit (void *pudev, uint8_t config_index)
{
    /* deinitialize HID endpoints */
    usbd_ep_deinit (pudev, CUSTOMHID_IN_EP);
    usbd_ep_deinit (pudev, CUSTOMHID_OUT_EP);

    return USBD_OK;
}

/*!
    \brief      handle the HID class-specific requests
    \param[in]  pudev: pointer to USB device instance
    \param[in]  req: device class-specific request
    \param[out] none
    \retval     USB device operation status
*/
usbd_status_enum custom_hid_req_handler (void *pudev, usb_device_req_struct *req)
{
    uint16_t len = 0;
    uint8_t *pbuf = NULL;
    uint8_t usbd_customhid_report_length = 0;

    switch (req->bmRequestType & USB_REQ_MASK) {
    case USB_CLASS_REQ:
        switch (req->bRequest) {
        case GET_REPORT:
            /* no use for this driver */
            break;
        case GET_IDLE:
            usbd_ep_tx (pudev, EP0_IN, (uint8_t *)&usbd_customhid_idlestate, 1);
            break;
        case GET_PROTOCOL:
            usbd_ep_tx (pudev, EP0_IN, (uint8_t *)&usbd_customhid_protocol, 1);
            break;
        case SET_REPORT:
            flag = 1;
            usbd_customhid_report_id = (uint8_t)(req->wValue);
            usbd_customhid_report_length = (uint8_t)(req->wLength);
            usbd_ep_rx (pudev, EP0_OUT, report_buf, usbd_customhid_report_length);
            break;
        case SET_IDLE:
            usbd_customhid_idlestate = (uint8_t)(req->wValue >> 8);
            break;
        case SET_PROTOCOL:
            usbd_customhid_protocol = (uint8_t)(req->wValue);
            break;
        default:
            usbd_enum_error (pudev, req);
            return USBD_FAIL;
        }
        break;
    case USB_STANDARD_REQ:
        /* standard device request */
        switch(req->bRequest) {
        case USBREQ_GET_DESCRIPTOR:
            switch(req->wValue >> 8) {
            case CUSTOMHID_REPORT_DESCTYPE:
                len = MIN(CUSTOMHID_REPORT_DESC_SIZE, req->wLength);
                pbuf = (uint8_t *)customhid_report_descriptor;
				//usb_flag =1;
                break;
            case CUSTOMHID_DESC_TYPE:
                len = MIN(USB_CUSTOMHID_DESC_SIZE, req->wLength);
                pbuf = (uint8_t *)(&(configuration_descriptor.HID_VendorHID));
                break;
            default:
                break;
            }
            usbd_ep_tx (pudev, EP0_IN, pbuf, len);
            break;
        case USBREQ_GET_INTERFACE:
            usbd_ep_tx (pudev, EP0_IN, (uint8_t *)&usbd_customhid_altset, 1);
            break;
        case USBREQ_SET_INTERFACE:
            usbd_customhid_altset = (uint8_t)(req->wValue);
            break;
        }
        break;
    }

    return USBD_OK;
}

/*!
    \brief      handle data stage
    \param[in]  pudev: pointer to USB device instance
    \param[in]  rx_tx: data transfer direction:
      \arg        USBD_TX
      \arg        USBD_RX
    \param[in]  ep_id: endpoint identifier
    \param[out] none
    \retval     USB device operation status
*/
usbd_status_enum  custom_hid_data_handler (void *pudev, usbd_dir_enum rx_tx, uint8_t ep_id)
{
    if((USBD_TX == rx_tx) && ((CUSTOMHID_IN_EP & 0x7F) == ep_id)) {
        return USBD_OK;
    } else if ((USBD_RX == rx_tx) && (CUSTOMHID_OUT_EP == ep_id)) {
        usbd_ep_rx(pudev, CUSTOMHID_IN_EP, report_buf, 64);
        return USBD_OK;
    }

    return USBD_FAIL;
}

//unsigned char CalcSum(unsigned char *buff, unsigned int len)
//{
//	unsigned int i = 0;
//	unsigned char sum = 0;

//	for(i=0; i<len; i++)
//	{
//		sum ^= buff[i];		
//	}

//	return sum;
//}

/*!
    \brief      send custom HID report
    \param[in]  pudev: pointer to USB device instance
    \param[in]  report: pointer to HID report
    \param[in]  len: data length
    \param[out] none
    \retval     USB device operation status
*/
uint8_t  custom_hid_report_send (usbd_core_handle_struct *pudev, uint8_t *report, uint16_t len)
{
	unsigned int sent = 0;		//已发送的数据长度
	unsigned int rest = len;	//未发送的数据长度
	unsigned int PACKET_LEN = 61;
	
	//SendBuff
	//[0]    [1]    [2]    [3]    ...    [62]    [63]
	//05     len     d0    d1             d60     sum

	while(1)
	{
		if(rest == 0)return len;	

		if(prev_receive_complete == 0)continue;
		
		if (rest >= 61)PACKET_LEN = 61;
		else PACKET_LEN = rest;

		memset((unsigned char*)SendBuff, 0, sizeof(SendBuff));	
		//1
		SendBuff[0] = 0x05;							//REPORTID
		SendBuff[1] = PACKET_LEN;					//len
		//2
		memcpy((unsigned char*)(SendBuff+2), (report+sent), PACKET_LEN);	//61 bytes
		//3
		SendBuff[63] = CalcSum((unsigned char*)SendBuff, 63);
		
		prev_receive_complete = 0;
		
        usbd_ep_tx (pudev, CUSTOMHID_IN_EP, (uint8_t *)SendBuff, 64);
		//5
		sent += PACKET_LEN;
		rest -= PACKET_LEN;
	}	
}
