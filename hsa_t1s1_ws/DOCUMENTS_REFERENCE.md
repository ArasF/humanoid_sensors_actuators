# ATmega32 / AVR Reference Notes

Local source PDFs are in:

`/home/ercankacmaz/Documents/lectures/humamoid_sensors_and_actuators/Documents`

Files:

- `atmega32.pdf` - main ATmega32/ATmega32L datasheet.
- `atmega32-pin-configs.pdf` - pinout/package reference.
- `atmega32-register-summary.pdf` - I/O register map and bit summaries.
- `atmega32-instr-set-summary.pdf` - AVR instruction set summary.
- `avr-gcc-abi.pdf` - AVR-GCC calling convention / ABI reference.

## ATmega32 Core Facts

- 8-bit AVR RISC microcontroller.
- 32 x 8 general-purpose CPU registers.
- Most instructions execute in one clock cycle.
- Up to 16 MIPS at 16 MHz.
- On-chip 2-cycle hardware multiplier.
- Program memory: 32 KiB self-programmable Flash.
- Data memory: 2 KiB internal SRAM.
- Nonvolatile data memory: 1024 bytes EEPROM.
- Endurance: about 10,000 Flash write/erase cycles and 100,000 EEPROM write/erase cycles.
- Retention: documented as 20 years at 85 C and 100 years at 25 C.
- ATmega32 operating voltage: 4.5 V to 5.5 V.
- ATmega32L operating voltage: 2.7 V to 5.5 V.
- ATmega32 speed grade: 0-16 MHz.
- ATmega32L speed grade: 0-8 MHz.
- Typical low-frequency ATmega32L power examples at 1 MHz, 3 V, 25 C: active about 1.1 mA, idle about 0.35 mA, power-down below 1 uA.

## Main Peripherals

- GPIO: 32 programmable I/O lines.
- Timers:
  - Timer/Counter0: 8-bit, prescaler, compare mode.
  - Timer/Counter1: 16-bit, prescaler, compare mode, input capture.
  - Timer/Counter2: 8-bit, prescaler, compare mode, can support real-time counter operation with separate oscillator.
- PWM: four PWM channels.
- ADC: 8-channel, 10-bit ADC.
- Analog comparator: on-chip comparator with related interrupt support.
- Serial:
  - USART.
  - SPI master/slave.
  - Byte-oriented Two-wire Serial Interface, compatible with I2C-style buses.
- Watchdog: programmable watchdog timer with separate oscillator.
- Reset/supervision: power-on reset and programmable brown-out detection.
- Sleep modes: Idle, ADC Noise Reduction, Power-save, Power-down, Standby, Extended Standby.
- Debug/programming:
  - JTAG IEEE 1149.1 boundary scan.
  - On-chip debug support.
  - Programming of Flash, EEPROM, fuses, and lock bits through JTAG.
  - Boot code section with independent lock bits and true read-while-write behavior.

## Package / Pin Reference

Packages listed in the datasheet:

- 40-pin PDIP.
- 44-lead TQFP.
- 44-pad QFN/MLF.

Important alternate pin functions:

- Port A:
  - PA0-PA7: ADC0-ADC7.
- Port B:
  - PB0: XCK/T0.
  - PB1: T1.
  - PB2: INT2/AIN0.
  - PB3: OC0/AIN1.
  - PB4: SS.
  - PB5: MOSI.
  - PB6: MISO.
  - PB7: SCK.
- Port C:
  - PC0: SCL.
  - PC1: SDA.
  - PC2: TCK.
  - PC3: TMS.
  - PC4: TDO.
  - PC5: TDI.
  - PC6: TOSC1.
  - PC7: TOSC2.
- Port D:
  - PD0: RXD.
  - PD1: TXD.
  - PD2: INT0.
  - PD3: INT1.
  - PD4: OC1B.
  - PD5: OC1A.
  - PD6: ICP1.
  - PD7: OC2.

Power/reference pins to watch:

- VCC and GND are digital supply pins.
- AVCC supplies the ADC/Port A analog side and should be connected even if ADC is unused.
- AREF is the ADC analog reference pin.
- XTAL1/XTAL2 are external oscillator pins.
- RESET is active-low reset.
- On QFN/MLF, the exposed bottom pad should be soldered to ground.

## Register Model

Common GPIO register pattern:

- `DDRx`: data direction, 1 = output, 0 = input.
- `PORTx`: output latch when output; pull-up enable when input.
- `PINx`: input readback; on AVR, writing 1 to a `PINx` bit can toggle the corresponding `PORTx` latch on many classic AVR devices.

Common system/control registers:

- `SREG`: status register; includes global interrupt enable bit `I` and ALU flags.
- `SPH` / `SPL`: stack pointer high/low.
- `MCUCR`, `MCUCSR`: MCU control/status, reset and interrupt-related configuration.
- `GICR`, `GIFR`: external interrupt control/flags.
- `TIMSK`, `TIFR`: timer interrupt mask/flags.

Peripheral register groups to expect:

- Timers: `TCCRn`, `TCNTn`, `OCRn`, `ICRn`, compare/capture interrupt flags and masks.
- ADC: `ADMUX`, `ADCSRA`, `ADCH`, `ADCL`, `SFIOR` trigger-related bits.
- USART: `UBRRH`, `UBRRL`, `UCSRA`, `UCSRB`, `UCSRC`, `UDR`.
- SPI: `SPCR`, `SPSR`, `SPDR`.
- TWI: `TWBR`, `TWSR`, `TWAR`, `TWDR`, `TWCR`.
- EEPROM: `EEARH`, `EEARL`, `EEDR`, `EECR`.
- Watchdog: `WDTCR`.
- Analog comparator: `ACSR`.

## AVR Instruction Set Summary

Instruction categories:

- Arithmetic and logic: `ADD`, `ADC`, `SUB`, `SBC`, `SUBI`, `SBCI`, `ADIW`, `SBIW`, `AND`, `ANDI`, `OR`, `ORI`, `EOR`, `COM`, `NEG`, `INC`, `DEC`, `MUL`.
- Bit and flag operations: `SBI`, `CBI`, `BST`, `BLD`, `BSET`, `BCLR`, `SEC`, `CLC`, `SEI`, `CLI`, and related flag set/clear aliases.
- Data transfer: `MOV`, `MOVW`, `LDI`, `LD`, `LDD`, `ST`, `STD`, `LDS`, `STS`, `IN`, `OUT`, `PUSH`, `POP`, `LPM`.
- Branch/control flow: `RJMP`, `IJMP`, `JMP`, `RCALL`, `ICALL`, `CALL`, `RET`, `RETI`, `CP`, `CPC`, `CPI`, `CPSE`, `SBRC`, `SBRS`, `SBIC`, `SBIS`, conditional branches such as `BREQ`, `BRNE`, `BRCS`, `BRCC`, `BRLT`, `BRGE`.
- Shifts/rotates/swaps: `LSL`, `LSR`, `ROL`, `ROR`, `ASR`, `SWAP`.
- MCU control: `NOP`, `SLEEP`, `WDR`, `BREAK`, `SPM`.

Practical assembly reminders:

- `r0` is commonly used as a temporary register by compiler-generated code.
- `r1` is expected to contain zero in AVR-GCC C/C++ code and must be restored to zero after code that changes it.
- I/O registers can often be accessed with `IN`/`OUT`; extended I/O and SRAM-mapped registers require data-memory access instructions.
- Branches and skip instructions have cycle counts that depend on whether the branch/skip is taken and, for skip, on the size of the skipped instruction.

## AVR-GCC ABI Notes

Data type layout commonly used by AVR-GCC / AVR-LibC:

- `char`: 8 bits.
- `short`: 16 bits.
- `int`: 16 bits.
- `long`: 32 bits.
- `long long`: 64 bits.
- `float`: 32 bits.
- `double`: often 32 bits on classic AVR toolchains, though newer configurations may support 64-bit `double` / `long double`.
- Data pointers: typically 16 bits on devices in this size class.
- Function pointers are word addresses so they can address program memory.

Register convention:

- Call-used / call-clobbered: `r18-r27`, `r30-r31`.
- Call-saved / callee-saved: `r2-r17`, `r28-r29`.
- Fixed:
  - `r0` / `__tmp_reg__`: temporary, may be clobbered.
  - `r1` / `__zero_reg__`: must be zero when returning to C/C++ ABI code.
- `r29:r28` is the Y pointer and is used as a frame pointer when needed.

Argument and return convention:

- Arguments are assigned left-to-right into registers, generally from `r25` downward, aligned to even register numbers.
- An 8-bit argument consumes an even register slot.
- If register space runs out, remaining arguments are passed on the stack.
- Return values are placed in registers:
  - 8-bit in `r24`.
  - 16-bit in `r25:r24`.
  - Wider scalar returns use additional lower registers according to ABI rules.

Assembly interoperability checklist:

- Preserve callee-saved registers if your assembly routine changes them.
- Restore `r1` to zero before returning to C/C++.
- Use `extern "C"` for C++ symbols that assembly should call by plain name.
- Prefer assembling `.S` files through `avr-gcc` so preprocessor symbols and `-mmcu` handling are consistent.

## Sources Used For These Notes

- Local PDFs listed above.
- Microchip ATmega32 product page.
- ATMEGA32 datasheet HTML mirror at AllDatasheet.
- AVR-LibC FAQ and toolchain documentation.
