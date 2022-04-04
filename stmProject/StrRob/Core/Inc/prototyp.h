







//RESET Operations
#define RESET_ENABLE                    0x66 //RESET ENABLE
#define RESET_MEMORY                    0x99 //RESET MEMORY


//IDENTIFICATION Operations
#define READ_ID                              //READ ID
#define MULTIPLE_I_OR_O_READ_ID         0xAF //MULTIPLE I/O READ ID
#define RD_SRL_FLSH_DISC_PARAM          0xA5 //READ SERIAL FLASH DISCOVERY PARAMETER


//READ Operations
#define READ                            0x03 //READ
#define FAST_READ                       0x0B //FAST READ
#define DUAL_OUTPUT_FAST_READ           0x3B //DUAL OUTPUT FAST READ
#define DUAL_INPUT_OR_OUTPUT_FAST_READ  0x0B //DUAL INPUT/OUTPUT FAST READ


//WRITE Operations
#define WRITE_ENABLE                    0x06 
#define WRITE_DISABLE                   0x04


//REGISTER Operations
#define READ_STATUS_REG                 0x05
#define WRITE_STATUS_REG                0x01
#define READ_LOCK_REG                   0xE8
#define WRITE_LOCK_REG                  0xE5
#define READ_FLAG_STAT_REG              0x70
#define CLEAR_FLAG_STAT_REG             0x50
#define READ_NONVOLATILE_CONF_REG       0xB5
#define WRITE_NONVOLATILE_CONF_REG      0xB1
#define READ_VOLATILE_CONF_REG          0x85
#define WRITE_VOLATILE_CONF_REG         0x81
#define READ_ENHANCED_VOL_CONF_REG      0x65
#define WRITE_ENHANCED_VOL_CONF_REG     0x61


//PROGRAM Operations
#define PAGE_PROGRAM                    0x02
#define DUAL_INPUT_FAST_PROGRAM         0xA2
#define EXT_DUAL_INPUT_FAST_PROGRAM     
#define QUAD_INPUT_FAST_PROGRAM         0x32
#define EXT_QUAD_INPUT_FAST_PROGRAM


//ERASE Operations
#define SUBSECTOR_ERASE                 0x20
#define SECTOR_ERASE                    0xD8
#define BULK_ERASE                      0xC7
#define PROGRAM_OR_ERASE_RESUME         0X7A
#define PROGRAM_OR_ERASE_SUSPEND        0x75


//ONE-TIME PROGRAMMABLE (OTP) Operations
#define READ_OTP_ARRAY                  0x4B
#define PROGRAM_OTP_ARRAY               0x42
