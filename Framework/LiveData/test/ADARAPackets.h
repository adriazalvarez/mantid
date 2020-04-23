// Mantid Repository : https://github.com/mantidproject/mantid
//
// Copyright &copy; 2018 ISIS Rutherford Appleton Laboratory UKRI,
//   NScD Oak Ridge National Laboratory, European Spallation Source,
//   Institut Laue - Langevin & CSNS, Institute of High Energy Physics, CAS
// SPDX - License - Identifier: GPL - 3.0 +
#pragma once

// This file includes sample packets for the AdaraPacketTest unit test. It's
// intended to be included by ADARAPacketTest.h (but outside of the class
// definition for AdaraPacketTest).
// This code is in a separate file to keep it from cluttering up the
// ADARAPacketTest.h file.

// Type:        "Banked Event Data" (version 0)
// Pulse ID:    728504567.761741666
// Packet Time: Jan 31, 2013 - 13:22:47.761
const unsigned char bankedEventPacket[96] = {
    0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0xf7, 0x18, 0x6c, 0x2b,
    0x62, 0x41, 0x67, 0x2d, 0x87, 0xa5, 0x17, 0x00, 0xe4, 0x8d, 0xe8, 0x37,
    0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0xb0, 0x3c, 0x15,
    0x06, 0x8b, 0x02, 0x00, 0x88, 0xf6, 0x00, 0x80, 0x02, 0x00, 0x00, 0x00,
    0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xd9, 0x3b, 0x02, 0x00,
    0x3c, 0x04, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x3a, 0x3f, 0x02, 0x00, 0xe2, 0x49, 0x00, 0x00, 0xc0, 0xdc, 0x3c, 0x15,
    0x06, 0x8b, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

// Type:        "Beam Monitor Event Data" (version 0)
// Pulse ID:    728504567.761741666
// Packet Time: Jan 31, 2013 - 13:22:47.761
const unsigned char beamMonitorPacket[32] = {
    0x10, 0x00, 0x00, 0x00, 0x00, 0x01, 0x40, 0x00, 0xf7, 0x18, 0x6c,
    0x2b, 0x62, 0x41, 0x67, 0x2d, 0x87, 0xa5, 0x17, 0x00, 0xe4, 0x8d,
    0xe8, 0x37, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

// Type:        "Real Time Data Link Info" (version 0)
// Pulse ID:    728504567.761741666
// Packet Time: Jan 31, 2013 - 13:22:47.761
const unsigned char rtdlPacket[136] = {
    0x78, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0xf7, 0x18, 0x6c, 0x2b,
    0x62, 0x41, 0x67, 0x2d, 0x87, 0xa5, 0x17, 0x01, 0x3c, 0x10, 0x80, 0x07,
    0x06, 0x8b, 0x02, 0x00, 0x88, 0xf6, 0x00, 0x80, 0x7b, 0x93, 0x0e, 0x04,
    0x24, 0x49, 0xdb, 0x05, 0x74, 0x6f, 0x72, 0x06, 0xf3, 0x02, 0x00, 0x07,
    0xc0, 0x27, 0x09, 0x08, 0x00, 0x00, 0x00, 0x0f, 0x01, 0x00, 0x00, 0x11,
    0x04, 0x00, 0x00, 0x18, 0x3c, 0x00, 0x00, 0x19, 0x3c, 0x00, 0x00, 0x1a,
    0x00, 0x00, 0x0c, 0x1c, 0x32, 0x00, 0x00, 0x1d, 0xbf, 0x42, 0x01, 0x1e,
    0x97, 0x0b, 0x00, 0x1f, 0x5a, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x21,
    0x00, 0x00, 0x00, 0x22, 0x87, 0xa5, 0x17, 0x23, 0x07, 0x10, 0x00, 0x24,
    0x59, 0xb0, 0x03, 0x25, 0x06, 0x10, 0x04, 0x26, 0x00, 0x00, 0x00, 0x27,
    0xfe, 0xff, 0x00, 0x28, 0x02, 0x00, 0x00, 0x29, 0x18, 0x6c, 0x2b, 0x01,
    0xf7, 0x1e, 0x62, 0x02};

// Type:        "Run Status" (version 0)
// Pulse ID:    728504568.5625794
// Packet Time: Jan 31, 2013 - 13:22:48.005
const unsigned char runStatusPacket[28] = {
    0x0c, 0x00, 0x00, 0x00, 0x00, 0x03, 0x40, 0x00, 0xf8, 0x18,
    0x6c, 0x2b, 0xc2, 0xd7, 0x55, 0x00, 0xbf, 0x33, 0x00, 0x00,
    0x01, 0x14, 0x6c, 0x2b, 0x00, 0x00, 0x00, 0x05};

// Type:        "Synchronization (File)" (version 0)
// Pulse ID:    728504568.5617153
// Packet Time: Jan 31, 2013 - 13:22:48.005
const unsigned char syncPacket[44] = {
    0x1c, 0x00, 0x00, 0x00, 0x00, 0x08, 0x40, 0x00, 0xf8, 0x18, 0x6c,
    0x2b, 0x01, 0xb6, 0x55, 0x00, 0x53, 0x4e, 0x53, 0x41, 0x44, 0x41,
    0x52, 0x41, 0x4f, 0x52, 0x4e, 0x4c, 0x00, 0x00, 0xf0, 0x7f, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

// Type:        "Variable Value (double)" (version 0)
// Pulse ID:    728281149.0
// Packet Time: Jan 28, 2013 - 23:19:09.000
const unsigned char variableDoublePacket[36] = {
    0x14, 0x00, 0x00, 0x00, 0x00, 0x02, 0x80, 0x00, 0x3d, 0xb0, 0x68, 0x2b,
    0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xa8, 0xc6, 0x4b, 0x37, 0x89, 0x01, 0x14, 0x40};

// Type:        "Variable Value (u32)" (version 0)
// Pulse ID:    728281149.0
// Packet Time: Jan 28, 2013 - 23:19:09.000
const unsigned char variableU32Packet[32] = {
    0x10, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x3d, 0xb0, 0x68,
    0x2b, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00};

// Type:        "Device Descriptor" (version 0)
// Pulse ID:    726785379.0
// Packet Time: Jan 11, 2013 - 15:49:39.000
const unsigned char devDesPacket[2600] = {
    0x18, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x63, 0xdd, 0x51, 0x2b,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0e, 0x0a, 0x00, 0x00,
    0x3c, 0x3f, 0x78, 0x6d, 0x6c, 0x20, 0x76, 0x65, 0x72, 0x73, 0x69, 0x6f,
    0x6e, 0x3d, 0x22, 0x31, 0x2e, 0x30, 0x22, 0x20, 0x65, 0x6e, 0x63, 0x6f,
    0x64, 0x69, 0x6e, 0x67, 0x3d, 0x22, 0x55, 0x54, 0x46, 0x2d, 0x38, 0x22,
    0x3f, 0x3e, 0x0a, 0x20, 0x20, 0x3c, 0x64, 0x65, 0x76, 0x69, 0x63, 0x65,
    0x20, 0x78, 0x6d, 0x6c, 0x6e, 0x73, 0x3d, 0x22, 0x68, 0x74, 0x74, 0x70,
    0x3a, 0x2f, 0x2f, 0x70, 0x75, 0x62, 0x6c, 0x69, 0x63, 0x2e, 0x73, 0x6e,
    0x73, 0x2e, 0x67, 0x6f, 0x76, 0x2f, 0x73, 0x63, 0x68, 0x65, 0x6d, 0x61,
    0x2f, 0x64, 0x65, 0x76, 0x69, 0x63, 0x65, 0x2e, 0x78, 0x73, 0x64, 0x22,
    0x0a, 0x20, 0x20, 0x78, 0x6d, 0x6c, 0x6e, 0x73, 0x3a, 0x78, 0x73, 0x69,
    0x3d, 0x22, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x77, 0x77, 0x77,
    0x2e, 0x77, 0x33, 0x2e, 0x6f, 0x72, 0x67, 0x2f, 0x32, 0x30, 0x30, 0x31,
    0x2f, 0x58, 0x4d, 0x4c, 0x53, 0x63, 0x68, 0x65, 0x6d, 0x61, 0x2d, 0x69,
    0x6e, 0x73, 0x74, 0x61, 0x6e, 0x63, 0x65, 0x22, 0x0a, 0x20, 0x20, 0x78,
    0x73, 0x69, 0x3a, 0x73, 0x63, 0x68, 0x65, 0x6d, 0x61, 0x4c, 0x6f, 0x63,
    0x61, 0x74, 0x69, 0x6f, 0x6e, 0x3d, 0x22, 0x68, 0x74, 0x74, 0x70, 0x3a,
    0x2f, 0x2f, 0x70, 0x75, 0x62, 0x6c, 0x69, 0x63, 0x2e, 0x73, 0x6e, 0x73,
    0x2e, 0x67, 0x6f, 0x76, 0x2f, 0x73, 0x63, 0x68, 0x65, 0x6d, 0x61, 0x2f,
    0x64, 0x65, 0x76, 0x69, 0x63, 0x65, 0x2e, 0x78, 0x73, 0x64, 0x20, 0x68,
    0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x70, 0x75, 0x62, 0x6c, 0x69, 0x63,
    0x2e, 0x73, 0x6e, 0x73, 0x2e, 0x67, 0x6f, 0x76, 0x2f, 0x73, 0x63, 0x68,
    0x65, 0x6d, 0x61, 0x2f, 0x64, 0x65, 0x76, 0x69, 0x63, 0x65, 0x2e, 0x78,
    0x73, 0x64, 0x22, 0x3e, 0x0a, 0x20, 0x20, 0x3c, 0x64, 0x65, 0x76, 0x69,
    0x63, 0x65, 0x5f, 0x6e, 0x61, 0x6d, 0x65, 0x3e, 0x6c, 0x61, 0x6b, 0x65,
    0x73, 0x68, 0x6f, 0x72, 0x65, 0x5f, 0x33, 0x33, 0x36, 0x3c, 0x2f, 0x64,
    0x65, 0x76, 0x69, 0x63, 0x65, 0x5f, 0x6e, 0x61, 0x6d, 0x65, 0x3e, 0x0a,
    0x20, 0x20, 0x3c, 0x65, 0x6e, 0x75, 0x6d, 0x65, 0x72, 0x61, 0x74, 0x69,
    0x6f, 0x6e, 0x73, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x65, 0x6e,
    0x75, 0x6d, 0x65, 0x72, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x3e, 0x0a, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x65, 0x6e, 0x75, 0x6d, 0x5f, 0x6e,
    0x61, 0x6d, 0x65, 0x3e, 0x65, 0x6e, 0x75, 0x6d, 0x5f, 0x30, 0x31, 0x3c,
    0x2f, 0x65, 0x6e, 0x75, 0x6d, 0x5f, 0x6e, 0x61, 0x6d, 0x65, 0x3e, 0x0a,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x65, 0x6e, 0x75,
    0x6d, 0x5f, 0x65, 0x6c, 0x65, 0x6d, 0x65, 0x6e, 0x74, 0x3e, 0x0a, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x65, 0x6e,
    0x75, 0x6d, 0x5f, 0x65, 0x6c, 0x65, 0x6d, 0x65, 0x6e, 0x74, 0x5f, 0x6e,
    0x61, 0x6d, 0x65, 0x3e, 0x55, 0x6e, 0x64, 0x65, 0x66, 0x69, 0x6e, 0x65,
    0x64, 0x3c, 0x2f, 0x65, 0x6e, 0x75, 0x6d, 0x5f, 0x65, 0x6c, 0x65, 0x6d,
    0x65, 0x6e, 0x74, 0x5f, 0x6e, 0x61, 0x6d, 0x65, 0x3e, 0x0a, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x65, 0x6e, 0x75,
    0x6d, 0x5f, 0x65, 0x6c, 0x65, 0x6d, 0x65, 0x6e, 0x74, 0x5f, 0x76, 0x61,
    0x6c, 0x75, 0x65, 0x3e, 0x30, 0x3c, 0x2f, 0x65, 0x6e, 0x75, 0x6d, 0x5f,
    0x65, 0x6c, 0x65, 0x6d, 0x65, 0x6e, 0x74, 0x5f, 0x76, 0x61, 0x6c, 0x75,
    0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c,
    0x2f, 0x65, 0x6e, 0x75, 0x6d, 0x5f, 0x65, 0x6c, 0x65, 0x6d, 0x65, 0x6e,
    0x74, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c,
    0x65, 0x6e, 0x75, 0x6d, 0x5f, 0x65, 0x6c, 0x65, 0x6d, 0x65, 0x6e, 0x74,
    0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x3c, 0x65, 0x6e, 0x75, 0x6d, 0x5f, 0x65, 0x6c, 0x65, 0x6d, 0x65, 0x6e,
    0x74, 0x5f, 0x6e, 0x61, 0x6d, 0x65, 0x3e, 0x41, 0x74, 0x5f, 0x54, 0x65,
    0x6d, 0x70, 0x3c, 0x2f, 0x65, 0x6e, 0x75, 0x6d, 0x5f, 0x65, 0x6c, 0x65,
    0x6d, 0x65, 0x6e, 0x74, 0x5f, 0x6e, 0x61, 0x6d, 0x65, 0x3e, 0x0a, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x65, 0x6e,
    0x75, 0x6d, 0x5f, 0x65, 0x6c, 0x65, 0x6d, 0x65, 0x6e, 0x74, 0x5f, 0x76,
    0x61, 0x6c, 0x75, 0x65, 0x3e, 0x31, 0x3c, 0x2f, 0x65, 0x6e, 0x75, 0x6d,
    0x5f, 0x65, 0x6c, 0x65, 0x6d, 0x65, 0x6e, 0x74, 0x5f, 0x76, 0x61, 0x6c,
    0x75, 0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x3c, 0x2f, 0x65, 0x6e, 0x75, 0x6d, 0x5f, 0x65, 0x6c, 0x65, 0x6d, 0x65,
    0x6e, 0x74, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x3c, 0x65, 0x6e, 0x75, 0x6d, 0x5f, 0x65, 0x6c, 0x65, 0x6d, 0x65, 0x6e,
    0x74, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x3c, 0x65, 0x6e, 0x75, 0x6d, 0x5f, 0x65, 0x6c, 0x65, 0x6d, 0x65,
    0x6e, 0x74, 0x5f, 0x6e, 0x61, 0x6d, 0x65, 0x3e, 0x4f, 0x75, 0x74, 0x5f,
    0x6f, 0x66, 0x5f, 0x74, 0x65, 0x6d, 0x70, 0x3c, 0x2f, 0x65, 0x6e, 0x75,
    0x6d, 0x5f, 0x65, 0x6c, 0x65, 0x6d, 0x65, 0x6e, 0x74, 0x5f, 0x6e, 0x61,
    0x6d, 0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x3c, 0x65, 0x6e, 0x75, 0x6d, 0x5f, 0x65, 0x6c, 0x65, 0x6d,
    0x65, 0x6e, 0x74, 0x5f, 0x76, 0x61, 0x6c, 0x75, 0x65, 0x3e, 0x32, 0x3c,
    0x2f, 0x65, 0x6e, 0x75, 0x6d, 0x5f, 0x65, 0x6c, 0x65, 0x6d, 0x65, 0x6e,
    0x74, 0x5f, 0x76, 0x61, 0x6c, 0x75, 0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x2f, 0x65, 0x6e, 0x75, 0x6d, 0x5f,
    0x65, 0x6c, 0x65, 0x6d, 0x65, 0x6e, 0x74, 0x3e, 0x0a, 0x20, 0x20, 0x20,
    0x20, 0x3c, 0x2f, 0x65, 0x6e, 0x75, 0x6d, 0x65, 0x72, 0x61, 0x74, 0x69,
    0x6f, 0x6e, 0x3e, 0x0a, 0x20, 0x20, 0x3c, 0x2f, 0x65, 0x6e, 0x75, 0x6d,
    0x65, 0x72, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x73, 0x3e, 0x0a, 0x20, 0x20,
    0x3c, 0x70, 0x72, 0x6f, 0x63, 0x65, 0x73, 0x73, 0x5f, 0x76, 0x61, 0x72,
    0x69, 0x61, 0x62, 0x6c, 0x65, 0x73, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20,
    0x3c, 0x70, 0x72, 0x6f, 0x63, 0x65, 0x73, 0x73, 0x5f, 0x76, 0x61, 0x72,
    0x69, 0x61, 0x62, 0x6c, 0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x3c, 0x70, 0x76, 0x5f, 0x6e, 0x61, 0x6d, 0x65, 0x3e, 0x53, 0x65,
    0x6e, 0x73, 0x6f, 0x72, 0x41, 0x3c, 0x2f, 0x70, 0x76, 0x5f, 0x6e, 0x61,
    0x6d, 0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x70,
    0x76, 0x5f, 0x69, 0x64, 0x3e, 0x31, 0x3c, 0x2f, 0x70, 0x76, 0x5f, 0x69,
    0x64, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x70, 0x76,
    0x5f, 0x74, 0x79, 0x70, 0x65, 0x3e, 0x64, 0x6f, 0x75, 0x62, 0x6c, 0x65,
    0x3c, 0x2f, 0x70, 0x76, 0x5f, 0x74, 0x79, 0x70, 0x65, 0x3e, 0x0a, 0x20,
    0x20, 0x20, 0x20, 0x3c, 0x2f, 0x70, 0x72, 0x6f, 0x63, 0x65, 0x73, 0x73,
    0x5f, 0x76, 0x61, 0x72, 0x69, 0x61, 0x62, 0x6c, 0x65, 0x3e, 0x0a, 0x20,
    0x20, 0x20, 0x20, 0x3c, 0x70, 0x72, 0x6f, 0x63, 0x65, 0x73, 0x73, 0x5f,
    0x76, 0x61, 0x72, 0x69, 0x61, 0x62, 0x6c, 0x65, 0x3e, 0x0a, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x3c, 0x70, 0x76, 0x5f, 0x6e, 0x61, 0x6d, 0x65,
    0x3e, 0x53, 0x65, 0x6e, 0x73, 0x6f, 0x72, 0x42, 0x3c, 0x2f, 0x70, 0x76,
    0x5f, 0x6e, 0x61, 0x6d, 0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x3c, 0x70, 0x76, 0x5f, 0x69, 0x64, 0x3e, 0x32, 0x3c, 0x2f, 0x70,
    0x76, 0x5f, 0x69, 0x64, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x3c, 0x70, 0x76, 0x5f, 0x74, 0x79, 0x70, 0x65, 0x3e, 0x64, 0x6f, 0x75,
    0x62, 0x6c, 0x65, 0x3c, 0x2f, 0x70, 0x76, 0x5f, 0x74, 0x79, 0x70, 0x65,
    0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x2f, 0x70, 0x72, 0x6f, 0x63,
    0x65, 0x73, 0x73, 0x5f, 0x76, 0x61, 0x72, 0x69, 0x61, 0x62, 0x6c, 0x65,
    0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x70, 0x72, 0x6f, 0x63, 0x65,
    0x73, 0x73, 0x5f, 0x76, 0x61, 0x72, 0x69, 0x61, 0x62, 0x6c, 0x65, 0x3e,
    0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x70, 0x76, 0x5f, 0x6e,
    0x61, 0x6d, 0x65, 0x3e, 0x53, 0x65, 0x6e, 0x73, 0x6f, 0x72, 0x43, 0x3c,
    0x2f, 0x70, 0x76, 0x5f, 0x6e, 0x61, 0x6d, 0x65, 0x3e, 0x0a, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x3c, 0x70, 0x76, 0x5f, 0x69, 0x64, 0x3e, 0x33,
    0x3c, 0x2f, 0x70, 0x76, 0x5f, 0x69, 0x64, 0x3e, 0x0a, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x3c, 0x70, 0x76, 0x5f, 0x74, 0x79, 0x70, 0x65, 0x3e,
    0x64, 0x6f, 0x75, 0x62, 0x6c, 0x65, 0x3c, 0x2f, 0x70, 0x76, 0x5f, 0x74,
    0x79, 0x70, 0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x2f, 0x70,
    0x72, 0x6f, 0x63, 0x65, 0x73, 0x73, 0x5f, 0x76, 0x61, 0x72, 0x69, 0x61,
    0x62, 0x6c, 0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x70, 0x72,
    0x6f, 0x63, 0x65, 0x73, 0x73, 0x5f, 0x76, 0x61, 0x72, 0x69, 0x61, 0x62,
    0x6c, 0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x70,
    0x76, 0x5f, 0x6e, 0x61, 0x6d, 0x65, 0x3e, 0x53, 0x65, 0x6e, 0x73, 0x6f,
    0x72, 0x44, 0x3c, 0x2f, 0x70, 0x76, 0x5f, 0x6e, 0x61, 0x6d, 0x65, 0x3e,
    0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x70, 0x76, 0x5f, 0x69,
    0x64, 0x3e, 0x34, 0x3c, 0x2f, 0x70, 0x76, 0x5f, 0x69, 0x64, 0x3e, 0x0a,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x70, 0x76, 0x5f, 0x74, 0x79,
    0x70, 0x65, 0x3e, 0x64, 0x6f, 0x75, 0x62, 0x6c, 0x65, 0x3c, 0x2f, 0x70,
    0x76, 0x5f, 0x74, 0x79, 0x70, 0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20,
    0x3c, 0x2f, 0x70, 0x72, 0x6f, 0x63, 0x65, 0x73, 0x73, 0x5f, 0x76, 0x61,
    0x72, 0x69, 0x61, 0x62, 0x6c, 0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20,
    0x3c, 0x70, 0x72, 0x6f, 0x63, 0x65, 0x73, 0x73, 0x5f, 0x76, 0x61, 0x72,
    0x69, 0x61, 0x62, 0x6c, 0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x3c, 0x70, 0x76, 0x5f, 0x6e, 0x61, 0x6d, 0x65, 0x3e, 0x53, 0x50,
    0x31, 0x3c, 0x2f, 0x70, 0x76, 0x5f, 0x6e, 0x61, 0x6d, 0x65, 0x3e, 0x0a,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x70, 0x76, 0x5f, 0x69, 0x64,
    0x3e, 0x35, 0x3c, 0x2f, 0x70, 0x76, 0x5f, 0x69, 0x64, 0x3e, 0x0a, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x70, 0x76, 0x5f, 0x74, 0x79, 0x70,
    0x65, 0x3e, 0x64, 0x6f, 0x75, 0x62, 0x6c, 0x65, 0x3c, 0x2f, 0x70, 0x76,
    0x5f, 0x74, 0x79, 0x70, 0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x3c,
    0x2f, 0x70, 0x72, 0x6f, 0x63, 0x65, 0x73, 0x73, 0x5f, 0x76, 0x61, 0x72,
    0x69, 0x61, 0x62, 0x6c, 0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x3c,
    0x70, 0x72, 0x6f, 0x63, 0x65, 0x73, 0x73, 0x5f, 0x76, 0x61, 0x72, 0x69,
    0x61, 0x62, 0x6c, 0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x3c, 0x70, 0x76, 0x5f, 0x6e, 0x61, 0x6d, 0x65, 0x3e, 0x53, 0x50, 0x32,
    0x3c, 0x2f, 0x70, 0x76, 0x5f, 0x6e, 0x61, 0x6d, 0x65, 0x3e, 0x0a, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x70, 0x76, 0x5f, 0x69, 0x64, 0x3e,
    0x36, 0x3c, 0x2f, 0x70, 0x76, 0x5f, 0x69, 0x64, 0x3e, 0x0a, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x3c, 0x70, 0x76, 0x5f, 0x74, 0x79, 0x70, 0x65,
    0x3e, 0x64, 0x6f, 0x75, 0x62, 0x6c, 0x65, 0x3c, 0x2f, 0x70, 0x76, 0x5f,
    0x74, 0x79, 0x70, 0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x2f,
    0x70, 0x72, 0x6f, 0x63, 0x65, 0x73, 0x73, 0x5f, 0x76, 0x61, 0x72, 0x69,
    0x61, 0x62, 0x6c, 0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x70,
    0x72, 0x6f, 0x63, 0x65, 0x73, 0x73, 0x5f, 0x76, 0x61, 0x72, 0x69, 0x61,
    0x62, 0x6c, 0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c,
    0x70, 0x76, 0x5f, 0x6e, 0x61, 0x6d, 0x65, 0x3e, 0x53, 0x65, 0x74, 0x70,
    0x6f, 0x69, 0x6e, 0x74, 0x4c, 0x50, 0x31, 0x3c, 0x2f, 0x70, 0x76, 0x5f,
    0x6e, 0x61, 0x6d, 0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x3c, 0x70, 0x76, 0x5f, 0x69, 0x64, 0x3e, 0x37, 0x3c, 0x2f, 0x70, 0x76,
    0x5f, 0x69, 0x64, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c,
    0x70, 0x76, 0x5f, 0x74, 0x79, 0x70, 0x65, 0x3e, 0x64, 0x6f, 0x75, 0x62,
    0x6c, 0x65, 0x3c, 0x2f, 0x70, 0x76, 0x5f, 0x74, 0x79, 0x70, 0x65, 0x3e,
    0x0a, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x2f, 0x70, 0x72, 0x6f, 0x63, 0x65,
    0x73, 0x73, 0x5f, 0x76, 0x61, 0x72, 0x69, 0x61, 0x62, 0x6c, 0x65, 0x3e,
    0x0a, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x70, 0x72, 0x6f, 0x63, 0x65, 0x73,
    0x73, 0x5f, 0x76, 0x61, 0x72, 0x69, 0x61, 0x62, 0x6c, 0x65, 0x3e, 0x0a,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x70, 0x76, 0x5f, 0x6e, 0x61,
    0x6d, 0x65, 0x3e, 0x53, 0x65, 0x74, 0x70, 0x6f, 0x69, 0x6e, 0x74, 0x4c,
    0x50, 0x32, 0x3c, 0x2f, 0x70, 0x76, 0x5f, 0x6e, 0x61, 0x6d, 0x65, 0x3e,
    0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x70, 0x76, 0x5f, 0x69,
    0x64, 0x3e, 0x38, 0x3c, 0x2f, 0x70, 0x76, 0x5f, 0x69, 0x64, 0x3e, 0x0a,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x70, 0x76, 0x5f, 0x74, 0x79,
    0x70, 0x65, 0x3e, 0x64, 0x6f, 0x75, 0x62, 0x6c, 0x65, 0x3c, 0x2f, 0x70,
    0x76, 0x5f, 0x74, 0x79, 0x70, 0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20,
    0x3c, 0x2f, 0x70, 0x72, 0x6f, 0x63, 0x65, 0x73, 0x73, 0x5f, 0x76, 0x61,
    0x72, 0x69, 0x61, 0x62, 0x6c, 0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20,
    0x3c, 0x70, 0x72, 0x6f, 0x63, 0x65, 0x73, 0x73, 0x5f, 0x76, 0x61, 0x72,
    0x69, 0x61, 0x62, 0x6c, 0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x3c, 0x70, 0x76, 0x5f, 0x6e, 0x61, 0x6d, 0x65, 0x3e, 0x54, 0x6f,
    0x6c, 0x4c, 0x50, 0x31, 0x3c, 0x2f, 0x70, 0x76, 0x5f, 0x6e, 0x61, 0x6d,
    0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x70, 0x76,
    0x5f, 0x69, 0x64, 0x3e, 0x39, 0x3c, 0x2f, 0x70, 0x76, 0x5f, 0x69, 0x64,
    0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x70, 0x76, 0x5f,
    0x74, 0x79, 0x70, 0x65, 0x3e, 0x64, 0x6f, 0x75, 0x62, 0x6c, 0x65, 0x3c,
    0x2f, 0x70, 0x76, 0x5f, 0x74, 0x79, 0x70, 0x65, 0x3e, 0x0a, 0x20, 0x20,
    0x20, 0x20, 0x3c, 0x2f, 0x70, 0x72, 0x6f, 0x63, 0x65, 0x73, 0x73, 0x5f,
    0x76, 0x61, 0x72, 0x69, 0x61, 0x62, 0x6c, 0x65, 0x3e, 0x0a, 0x20, 0x20,
    0x20, 0x20, 0x3c, 0x70, 0x72, 0x6f, 0x63, 0x65, 0x73, 0x73, 0x5f, 0x76,
    0x61, 0x72, 0x69, 0x61, 0x62, 0x6c, 0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x3c, 0x70, 0x76, 0x5f, 0x6e, 0x61, 0x6d, 0x65, 0x3e,
    0x54, 0x6f, 0x6c, 0x4c, 0x50, 0x32, 0x3c, 0x2f, 0x70, 0x76, 0x5f, 0x6e,
    0x61, 0x6d, 0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c,
    0x70, 0x76, 0x5f, 0x69, 0x64, 0x3e, 0x31, 0x30, 0x3c, 0x2f, 0x70, 0x76,
    0x5f, 0x69, 0x64, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c,
    0x70, 0x76, 0x5f, 0x74, 0x79, 0x70, 0x65, 0x3e, 0x64, 0x6f, 0x75, 0x62,
    0x6c, 0x65, 0x3c, 0x2f, 0x70, 0x76, 0x5f, 0x74, 0x79, 0x70, 0x65, 0x3e,
    0x0a, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x2f, 0x70, 0x72, 0x6f, 0x63, 0x65,
    0x73, 0x73, 0x5f, 0x76, 0x61, 0x72, 0x69, 0x61, 0x62, 0x6c, 0x65, 0x3e,
    0x0a, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x70, 0x72, 0x6f, 0x63, 0x65, 0x73,
    0x73, 0x5f, 0x76, 0x61, 0x72, 0x69, 0x61, 0x62, 0x6c, 0x65, 0x3e, 0x0a,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x70, 0x76, 0x5f, 0x6e, 0x61,
    0x6d, 0x65, 0x3e, 0x4c, 0x6f, 0x6f, 0x70, 0x31, 0x5f, 0x53, 0x74, 0x61,
    0x74, 0x75, 0x73, 0x3c, 0x2f, 0x70, 0x76, 0x5f, 0x6e, 0x61, 0x6d, 0x65,
    0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x70, 0x76, 0x5f,
    0x69, 0x64, 0x3e, 0x31, 0x31, 0x3c, 0x2f, 0x70, 0x76, 0x5f, 0x69, 0x64,
    0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x70, 0x76, 0x5f,
    0x74, 0x79, 0x70, 0x65, 0x3e, 0x65, 0x6e, 0x75, 0x6d, 0x5f, 0x30, 0x31,
    0x3c, 0x2f, 0x70, 0x76, 0x5f, 0x74, 0x79, 0x70, 0x65, 0x3e, 0x0a, 0x20,
    0x20, 0x20, 0x20, 0x3c, 0x2f, 0x70, 0x72, 0x6f, 0x63, 0x65, 0x73, 0x73,
    0x5f, 0x76, 0x61, 0x72, 0x69, 0x61, 0x62, 0x6c, 0x65, 0x3e, 0x0a, 0x20,
    0x20, 0x20, 0x20, 0x3c, 0x70, 0x72, 0x6f, 0x63, 0x65, 0x73, 0x73, 0x5f,
    0x76, 0x61, 0x72, 0x69, 0x61, 0x62, 0x6c, 0x65, 0x3e, 0x0a, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x3c, 0x70, 0x76, 0x5f, 0x6e, 0x61, 0x6d, 0x65,
    0x3e, 0x4c, 0x6f, 0x6f, 0x70, 0x32, 0x5f, 0x53, 0x74, 0x61, 0x74, 0x75,
    0x73, 0x3c, 0x2f, 0x70, 0x76, 0x5f, 0x6e, 0x61, 0x6d, 0x65, 0x3e, 0x0a,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x70, 0x76, 0x5f, 0x69, 0x64,
    0x3e, 0x31, 0x32, 0x3c, 0x2f, 0x70, 0x76, 0x5f, 0x69, 0x64, 0x3e, 0x0a,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x70, 0x76, 0x5f, 0x74, 0x79,
    0x70, 0x65, 0x3e, 0x65, 0x6e, 0x75, 0x6d, 0x5f, 0x30, 0x31, 0x3c, 0x2f,
    0x70, 0x76, 0x5f, 0x74, 0x79, 0x70, 0x65, 0x3e, 0x0a, 0x20, 0x20, 0x20,
    0x20, 0x3c, 0x2f, 0x70, 0x72, 0x6f, 0x63, 0x65, 0x73, 0x73, 0x5f, 0x76,
    0x61, 0x72, 0x69, 0x61, 0x62, 0x6c, 0x65, 0x3e, 0x0a, 0x20, 0x20, 0x3c,
    0x2f, 0x70, 0x72, 0x6f, 0x63, 0x65, 0x73, 0x73, 0x5f, 0x76, 0x61, 0x72,
    0x69, 0x61, 0x62, 0x6c, 0x65, 0x73, 0x3e, 0x0a, 0x3c, 0x2f, 0x64, 0x65,
    0x76, 0x69, 0x63, 0x65, 0x3e, 0x0a, 0x00, 0x00};
