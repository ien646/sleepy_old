#pragma once

#define _CPUFW_SLEEPYTEST_INIT_VARS()	System sys;\
										sys.Initialize();\
										auto& instMap = sys.CPU.Firmware.InstructionMap;\
										auto& regs = sys.CPU.Registers;\
										auto& mem = sys.Memory;\
										memset(mem.data(), 0, (0xFFFF * sizeof(BYTE)));\
										regs.ZeroRegisters(true);\
										const Registers::FLAG FLAG_SUB = Registers::FLAG::SUB;\
										const Registers::FLAG FLAG_ZERO = Registers::FLAG::ZERO;\
										const Registers::FLAG FLAG_HCARRY = Registers::FLAG::HALF_CARRY;\
										const Registers::FLAG FLAG_CARRY = Registers::FLAG::CARRY

#define _CPUFW_SLEEPYTEST_INIT_NOWARN() UNREFERENCED_PARAMETER(instMap);\
										UNREFERENCED_PARAMETER(regs);\
										UNREFERENCED_PARAMETER(mem);\
										UNREFERENCED_PARAMETER(sys)

/* Initialize common cpu firmware unit test variables [sys,regs,mem,instMap] */
#define CPUFW_SLEEPY_TESTINIT() _CPUFW_SLEEPYTEST_INIT_VARS();_CPUFW_SLEEPYTEST_INIT_NOWARN()