/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * This class is based on QLCFTDI class from
 *
 * Q Light Controller
 * qlcftdi.h
 *
 * Copyright (C) Heikki Junnila
 *
 * Only standard CPP conversion was changed and function name changed
 * to follow OLA coding standards.
 *
 * by Rui Barreiros
 *
 * Additional modifications to enable support for multiple outputs and
 * additional devices ids did change the original structure.
 *
 * by E.S. Rosenberg a.k.a. Keeper of the Keys 5774/2014
 */

#ifndef PLUGINS_FTDIDMX_FTDIWIDGET_H_
#define PLUGINS_FTDIDMX_FTDIWIDGET_H_

#include <ftdi.h>
#include <string.h>

#include <string>
#include <vector>

#include "ola/DmxBuffer.h"

namespace ola {
namespace plugin {
namespace ftdidmx {

/**
 * This class holds information about an attached ftdi chip
 */
class FtdiWidgetInfo {
 public:
    FtdiWidgetInfo(const std::string &name,
                   const std::string &serial,
                   unsigned int id,
                   const uint16_t vid = FtdiWidget::default_vid,
                   const uint16_t pid = FtdiWidget::default_pid
                  )
      : m_name(name),
        m_serial(serial),
        m_id(id),
        m_vid(vid),
        m_pid(pid) {
    }

    FtdiWidgetInfo(const FtdiWidgetInfo &info)
      : m_name(info.Name()),
        m_serial(info.Serial()),
        m_id(info.Id()),
        m_vid(info.Vid()),
        m_pid(info.Pid()) {
    }

    ~FtdiWidgetInfo() {}

    std::string Name() const { return m_name; }
    std::string Serial() const { return m_serial; }

    unsigned int Id() const { return m_id; }
    uint16_t Vid() const { return m_vid; }
    uint16_t Pid() const { return m_pid; }

    std::string Description() const {
      return m_name + " with serial number : " + m_serial + " ";
    }

    FtdiWidgetInfo& operator=(const FtdiWidgetInfo &other) {
      if (this != &other) {
        m_name = other.Name();
        m_serial = other.Serial();
        m_id = other.Id();
        m_vid = other.Vid();
        m_pid = other.Pid();
      }
      return *this;
    }

 private:
    std::string m_name;
    std::string m_serial;

    unsigned int m_id;
    uint16_t m_vid;
    uint16_t m_pid;
};

/**
 * An FTDI widget
 */
class FtdiWidget {
 public:
    /**
     * Construct a new FtdiWidget instance for one widget.
     * @param serial The widget's USB serial number
     * @param name The widget's USB name (description)
     * @param id The ID of the device (used only when FTD2XX is the backend)
     * @param vid The VendorID of the device, defaults to old value of FtdiWidget::VID
     * @param pid The ProductID of the device, defaults to old value of FtdiWidget::PID
     */
    FtdiWidget(const std::string &serial,
               const std::string &name,
               uint32_t id = 0,
               const uint16_t vid = FtdiWidget::default_vid,
               const uint16_t pid = FtdiWidget::default_pid);

    /** Destructor */
    virtual ~FtdiWidget();

    /** Get the widget's USB serial number */
    std::string Serial() const { return m_serial; }

    /** Get the widget's USB name */
    std::string Name() const { return m_name; }
    uint16_t Vid() const { return m_vid; }
    uint16_t Pid() const { return m_pid; }

    /** Get the widget's FTD2XX ID number */
    uint32_t Id() const { return m_id; }

    std::string Description() const {
      return m_name + " with serial number : " + m_serial +" ";
    }

    /** @brief Get Widget available interface count **/
    int GetInterfaceCount();

    /**
     * @brief Build a list of available ftdi widgets.
     * @param widgets a pointer to a vector of FtdiWidgetInfo objects.
     **/
    static void Widgets(std::vector<FtdiWidgetInfo> *widgets);

    /**
     * From reading libftdi docs it seems they may reuse error codes, which is
     * why I chose to name this const lib_function_error.
     **/
    static const int libftdi_ftdi_usb_get_strings_get_serial_failed = -9;

    static bool m_missing_serial;

    static const int default_vid = 0x0403;
    static const int default_pid = 0x6001;

 private:
    std::string m_serial;
    std::string m_name;
    uint32_t m_id;
    const uint16_t m_vid;
    const uint16_t m_pid;
};

class FtdiInterface {
 public:
    FtdiInterface(const FtdiWidget * parent,
                  const ftdi_interface interface);

    virtual ~FtdiInterface();

    std::string Description() const {
      return m_parent->Description();
    }

    /** Set interface on the widget */
    bool SetInterface();
    /** Open the widget */
    bool Open();

    /** Close the widget */
    bool Close();

    /** Check if the widget is open */
    bool IsOpen() const;

    /** Reset the communications line */
    bool Reset();

    /** Setup communications line for 8N2 traffic */
    bool SetLineProperties();

    /** Set 250kbps baud rate */
    bool SetBaudRate();

    /** Disable flow control */
    bool SetFlowControl();

    /** Clear the RTS bit */
    bool ClearRts();

    /** Purge TX & RX buffers */
    bool PurgeBuffers();

    /** Toggle communications line BREAK condition on/off */
    bool SetBreak(bool on);

    /** Write data to a previously-opened line */
    bool Write(const ola::DmxBuffer &data);

    /** Read data from a previously-opened line */
    bool Read(unsigned char* buff, int size);

    /** Setup device for DMX Output **/
    bool SetupOutput();

 private:
    const FtdiWidget * m_parent;
    struct ftdi_context m_handle;
    const ftdi_interface m_interface;
};  // FtdiInterface
}  // namespace ftdidmx
}  // namespace plugin
}  // namespace ola
#endif  // PLUGINS_FTDIDMX_FTDIWIDGET_H_
