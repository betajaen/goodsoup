/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef COMI_OPCODES_H
#define COMI_OPCODES_H

namespace comi
{
	enum Opcodes
	{
		OP_00 = 0x00,
		OP_01 = 0x01,
		OP_02 = 0x02,
		OP_03 = 0x03,
		OP_04 = 0x04,
		OP_05 = 0x05,
		OP_06 = 0x06,
		OP_07 = 0x07,
		OP_08 = 0x08,
		OP_09 = 0x09,
		OP_0a = 0x0a,
		OP_0b = 0x0b,
		OP_0c = 0x0c,
		OP_0d = 0x0d,
		OP_0e = 0x0e,
		OP_0f = 0x0f,
		OP_10 = 0x10,
		OP_11 = 0x11,
		OP_12 = 0x12,
		OP_13 = 0x13,
		OP_14 = 0x14,
		OP_15 = 0x15,
		OP_16 = 0x16,
		OP_17 = 0x17,
		OP_18 = 0x18,
		OP_19 = 0x19,
		OP_1a = 0x1a,
		OP_1b = 0x1b,
		OP_1c = 0x1c,
		OP_1d = 0x1d,
		OP_1e = 0x1e,
		OP_1f = 0x1f,
		OP_20 = 0x20,
		OP_21 = 0x21,
		OP_22 = 0x22,
		OP_23 = 0x23,
		OP_24 = 0x24,
		OP_25 = 0x25,
		OP_26 = 0x26,
		OP_27 = 0x27,
		OP_28 = 0x28,
		OP_29 = 0x29,
		OP_2a = 0x2a,
		OP_2b = 0x2b,
		OP_2c = 0x2c,
		OP_2d = 0x2d,
		OP_2e = 0x2e,
		OP_2f = 0x2f,
		OP_30 = 0x30,
		OP_31 = 0x31,
		OP_32 = 0x32,
		OP_33 = 0x33,
		OP_34 = 0x34,
		OP_35 = 0x35,
		OP_36 = 0x36,
		OP_37 = 0x37,
		OP_38 = 0x38,
		OP_39 = 0x39,
		OP_3a = 0x3a,
		OP_3b = 0x3b,
		OP_3c = 0x3c,
		OP_3d = 0x3d,
		OP_3e = 0x3e,
		OP_3f = 0x3f,
		OP_40 = 0x40,
		OP_41 = 0x41,
		OP_42 = 0x42,
		OP_43 = 0x43,
		OP_44 = 0x44,
		OP_45 = 0x45,
		OP_46 = 0x46,
		OP_47 = 0x47,
		OP_48 = 0x48,
		OP_49 = 0x49,
		OP_4a = 0x4a,
		OP_4b = 0x4b,
		OP_4c = 0x4c,
		OP_4d = 0x4d,
		OP_4e = 0x4e,
		OP_4f = 0x4f,
		OP_50 = 0x50,
		OP_51 = 0x51,
		OP_52 = 0x52,
		OP_53 = 0x53,
		OP_54 = 0x54,
		OP_55 = 0x55,
		OP_56 = 0x56,
		OP_57 = 0x57,
		OP_58 = 0x58,
		OP_59 = 0x59,
		OP_5a = 0x5a,
		OP_5b = 0x5b,
		OP_5c = 0x5c,
		OP_5d = 0x5d,
		OP_5e = 0x5e,
		OP_5f = 0x5f,
		OP_60 = 0x60,
		OP_61 = 0x61,
		OP_62 = 0x62,
		OP_63 = 0x63,
		OP_64 = 0x64,
		OP_65 = 0x65,
		OP_66 = 0x66,
		OP_67 = 0x67,
		OP_68 = 0x68,
		OP_69 = 0x69,
		OP_6a = 0x6a,
		OP_6b = 0x6b,
		OP_6c = 0x6c,
		OP_6d = 0x6d,
		OP_6e = 0x6e,
		OP_6f = 0x6f,
		OP_70 = 0x70,
		OP_71 = 0x71,
		OP_72 = 0x72,
		OP_73 = 0x73,
		OP_74 = 0x74,
		OP_75 = 0x75,
		OP_76 = 0x76,
		OP_77 = 0x77,
		OP_78 = 0x78,
		OP_79 = 0x79,
		OP_7a = 0x7a,
		OP_7b = 0x7b,
		OP_7c = 0x7c,
		OP_7d = 0x7d,
		OP_7e = 0x7e,
		OP_7f = 0x7f,
		OP_80 = 0x80,
		OP_81 = 0x81,
		OP_82 = 0x82,
		OP_83 = 0x83,
		OP_84 = 0x84,
		OP_85 = 0x85,
		OP_86 = 0x86,
		OP_87 = 0x87,
		OP_88 = 0x88,
		OP_89 = 0x89,
		OP_8a = 0x8a,
		OP_8b = 0x8b,
		OP_8c = 0x8c,
		OP_8d = 0x8d,
		OP_8e = 0x8e,
		OP_8f = 0x8f,
		OP_90 = 0x90,
		OP_91 = 0x91,
		OP_92 = 0x92,
		OP_93 = 0x93,
		OP_94 = 0x94,
		OP_95 = 0x95,
		OP_96 = 0x96,
		OP_97 = 0x97,
		OP_98 = 0x98,
		OP_99 = 0x99,
		OP_9a = 0x9a,
		OP_9b = 0x9b,
		OP_9c = 0x9c,
		OP_9d = 0x9d,
		OP_9e = 0x9e,
		OP_9f = 0x9f,
		OP_a0 = 0xa0,
		OP_a1 = 0xa1,
		OP_a2 = 0xa2,
		OP_a3 = 0xa3,
		OP_a4 = 0xa4,
		OP_a5 = 0xa5,
		OP_a6 = 0xa6,
		OP_a7 = 0xa7,
		OP_a8 = 0xa8,
		OP_a9 = 0xa9,
		OP_aa = 0xaa,
		OP_ab = 0xab,
		OP_ac = 0xac,
		OP_ad = 0xad,
		OP_ae = 0xae,
		OP_af = 0xaf,
		OP_b0 = 0xb0,
		OP_b1 = 0xb1,
		OP_b2 = 0xb2,
		OP_SysCall = 0xb3,
		OP_b4 = 0xb4,
		OP_b5 = 0xb5,
		OP_b6 = 0xb6,
		OP_b7 = 0xb7,
		OP_b8 = 0xb8,
		OP_b9 = 0xb9,
		OP_ba = 0xba,
		OP_bb = 0xbb,
		OP_bc = 0xbc,
		OP_bd = 0xbd,
		OP_be = 0xbe,
		OP_bf = 0xbf,
		OP_c0 = 0xc0,
		OP_c1 = 0xc1,
		OP_c2 = 0xc2,
		OP_c3 = 0xc3,
		OP_c4 = 0xc4,
		OP_c5 = 0xc5,
		OP_c6 = 0xc6,
		OP_c7 = 0xc7,
		OP_c8 = 0xc8,
		OP_c9 = 0xc9,
		OP_ca = 0xca,
		OP_cb = 0xcb,
		OP_cc = 0xcc,
		OP_cd = 0xcd,
		OP_ce = 0xce,
		OP_cf = 0xcf,
		OP_d0 = 0xd0,
		OP_d1 = 0xd1,
		OP_d2 = 0xd2,
		OP_d3 = 0xd3,
		OP_d4 = 0xd4,
		OP_d5 = 0xd5,
		OP_d6 = 0xd6,
		OP_d7 = 0xd7,
		OP_d8 = 0xd8,
		OP_d9 = 0xd9,
		OP_da = 0xda,
		OP_db = 0xdb,
		OP_dc = 0xdc,
		OP_dd = 0xdd,
		OP_de = 0xde,
		OP_df = 0xdf,
		OP_e0 = 0xe0,
		OP_e1 = 0xe1,
		OP_e2 = 0xe2,
		OP_e3 = 0xe3,
		OP_e4 = 0xe4,
		OP_e5 = 0xe5,
		OP_e6 = 0xe6,
		OP_e7 = 0xe7,
		OP_e8 = 0xe8,
		OP_e9 = 0xe9,
		OP_ea = 0xea,
		OP_eb = 0xeb,
		OP_ec = 0xec,
		OP_ed = 0xed,
		OP_ee = 0xee,
		OP_ef = 0xef,
		OP_f0 = 0xf0,
		OP_f1 = 0xf1,
		OP_f2 = 0xf2,
		OP_f3 = 0xf3,
		OP_f4 = 0xf4,
		OP_f5 = 0xf5,
		OP_f6 = 0xf6,
		OP_f7 = 0xf7,
		OP_f8 = 0xf8,
		OP_f9 = 0xf9,
		OP_fa = 0xfa,
		OP_fb = 0xfb,
		OP_fc = 0xfc,
		OP_fd = 0xfd,
		OP_fe = 0xfe,
		OP_ff = 0xff
	};

	enum OpSysCall
	{
		OpSyscall_Restart = 158,
		OpSyscall_Pause = 159,
		OpSyscall_Quit = 160
	};
}

#endif