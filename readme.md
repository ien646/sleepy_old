# To do

  - **Extended (prefix 0xCB) opcodes**
  
  - **Non-Extended opcodes**:
  
    ``[0x18] JR r8``
    
    ``[0x28] JR Z, r8``
    
    ``[0x38] JR C, r8``
    
    ``[0xC0] RET NZ``
    
    ``[0xC1] POP BC``
    
    ``[0xC2] JP NZ, a16``
    
    ``[0xC3] JP a16``
    
    ``[0xC4] CALL NZ, a16``
    
    ``[0xC5] PUSH BC``
    
    ``[0xD0] RET NC ``
    
    ``[0xD1] POP DE``
    
    ``[0xD2] JP NC, a16``
    
    ``[0xD4] CALL NC, a16``
    
    ``[0xD5] PUSH DE``
    
    ``[0xE1] POP HL``
    
    ``[0xE5] PUSH HL``
    
    ``[0xF1] POP AF {Z,N,H,C}``
    
    ``[0xF5] PUSH AF``
    
    ``[0xC8] RET Z``
    
    ``[0xC9] RET``
    
    ``[0xCA] JP Z, a16``
    
    ``[0xCB] ##PREFIX CB##``
    
    ``[0xCC] CALL Z, a16``
    
    ``[0xCD] CALL a16``
    
    ``[0xD8] RET C``
    
    ``[0xD9] RETI``
    
    ``[0xDA] JP C, a16``
    
    ``[0xDC] CALL C, a16``
    
    ``[0xE9] JP (HL)``
