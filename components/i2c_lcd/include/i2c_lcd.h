/**
 * @file
 * @brief Interface definitions for the ESP32-compatible I2C LCD component.
 *
 * This component provides structures and functions that are useful for communicating with the device.
 *
 * Technically, the LCD device is an I2C not SMBus device, however some SMBus protocols can be used
 * to communicate with the device, so it makes sense to use an SMBus interface to manage communication.
 */

#ifndef I2C_LCD_H
#define I2C_LCD_H

#include <stdbool.h>
#include "smbus.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Structure containing information related to the I2C-LCD device.
 */
typedef struct
{
    bool init;                                          ///< True if struct has been initialised, otherwise false
    smbus_info_t * smbus_info;                          ///< Pointer to associated SMBus info
    uint8_t backlight_flag;                             ///< Non-zero if backlight is to be enabled, otherwise zero
    uint8_t num_rows;                                   ///< Number of configured columns
    uint8_t num_columns;                                ///< Number of configured columns, including offscreen columns
    uint8_t num_visible_columns;                        ///< Number of visible columns
    uint8_t display_control_flags;                      ///< Currently active display control flags
    uint8_t entry_mode_flags;                           ///< Currently active entry mode flags
} i2c_lcd_info_t;


// Special characters for ROM Code A00

// Use the second set (0bxxxx1xxx) to avoid placing the null character within a string
#define I2C_LCD_CHARACTER_CUSTOM_0     0b00001000   ///< User-defined custom symbol in index 0
#define I2C_LCD_CHARACTER_CUSTOM_1     0b00001001   ///< User-defined custom symbol in index 1
#define I2C_LCD_CHARACTER_CUSTOM_2     0b00001010   ///< User-defined custom symbol in index 2
#define I2C_LCD_CHARACTER_CUSTOM_3     0b00001011   ///< User-defined custom symbol in index 3
#define I2C_LCD_CHARACTER_CUSTOM_4     0b00001100   ///< User-defined custom symbol in index 4
#define I2C_LCD_CHARACTER_CUSTOM_5     0b00001101   ///< User-defined custom symbol in index 5
#define I2C_LCD_CHARACTER_CUSTOM_6     0b00001110   ///< User-defined custom symbol in index 6
#define I2C_LCD_CHARACTER_CUSTOM_7     0b00001111   ///< User-defined custom symbol in index 7

#define I2C_LCD_CHARACTER_ALPHA        0b11100000   ///< Lower-case alpha symbol
#define I2C_LCD_CHARACTER_BETA         0b11100010   ///< Lower-case beta symbol
#define I2C_LCD_CHARACTER_THETA        0b11110010   ///< Lower-case theta symbol
#define I2C_LCD_CHARACTER_PI           0b11110111   ///< Lower-case pi symbol
#define I2C_LCD_CHARACTER_OMEGA        0b11110100   ///< Upper-case omega symbol
#define I2C_LCD_CHARACTER_SIGMA        0b11110110   ///< Upper-case sigma symbol
#define I2C_LCD_CHARACTER_INFINITY     0b11110011   ///< Infinity symbol
#define I2C_LCD_CHARACTER_DEGREE       0b11011111   ///< Degree symbol
#define I2C_LCD_CHARACTER_ARROW_RIGHT  0b01111110   ///< Arrow pointing right symbol
#define I2C_LCD_CHARACTER_ARROW_LEFT   0b01111111   ///< Arrow pointing left symbol
#define I2C_LCD_CHARACTER_SQUARE       0b11011011   ///< Square outline symbol
#define I2C_LCD_CHARACTER_DOT          0b10100101   ///< Centred dot symbol
#define I2C_LCD_CHARACTER_DIVIDE       0b11111101   ///< Division sign symbol
#define I2C_LCD_CHARACTER_BLOCK        0b11111111   ///< 5x8 filled block

/**
 * @brief Enum of valid indexes for definitions of user-defined characters.
 */
typedef enum
{
    I2C_LCD_INDEX_CUSTOM_0 = 0,                     ///< Index of first user-defined custom symbol
    I2C_LCD_INDEX_CUSTOM_1,                         ///< Index of second user-defined custom symbol
    I2C_LCD_INDEX_CUSTOM_2,                         ///< Index of third user-defined custom symbol
    I2C_LCD_INDEX_CUSTOM_3,                         ///< Index of fourth user-defined custom symbol
    I2C_LCD_INDEX_CUSTOM_4,                         ///< Index of fifth user-defined custom symbol
    I2C_LCD_INDEX_CUSTOM_5,                         ///< Index of sixth user-defined custom symbol
    I2C_LCD_INDEX_CUSTOM_6,                         ///< Index of seventh user-defined custom symbol
    I2C_LCD_INDEX_CUSTOM_7,                         ///< Index of eighth user-defined custom symbol
} i2c_lcd_custom_index_t;

#define I2C_LCD_ERROR_CHECK(x) do {                                     \
        esp_err_t rc = (x);                                                 \
        if (rc != ESP_OK) {                                                 \
            ESP_LOGW(TAG, "I2C error %d at %s:%d", rc, __FILE__, __LINE__); \
        }                                                                   \
    } while(0);

/**
 * @brief Construct a new I2C-LCD info instance.
 *        New instance should be initialised before calling other functions.
 *
 * @return Pointer to new device info instance, or NULL if it cannot be created.
 */
i2c_lcd_info_t * i2c_lcd_malloc(void);

/**
 * @brief Delete an existing I2C-LCD info instance.
 *
 * @param[in,out] tsl2561_info Pointer to I2C-LCD info instance that will be freed and set to NULL.
 */
void i2c_lcd_free(i2c_lcd_info_t ** tsl2561_info);

/**
 * @brief Initialise a I2C-LCD info instance with the specified SMBus information.
 *
 * @param[in] i2c_lcd_info Pointer to I2C-LCD info instance.
 * @param[in] smbus_info Pointer to SMBus info instance.
 * @param[in] backlight Initial backlight state.
 * @param[in] num_rows Maximum number of supported rows for this device. Typical values include 2 (1602) or 4 (2004).
 * @param[in] num_columns Maximum number of supported columns for this device. Typical values include 40 (1602, 2004).
 * @param[in] num_visible_columns Number of columns visible at any one time. Typical values include 16 (1602) or 20 (2004).
 * @return ESP_OK if successful, otherwise an error constant.
 */
esp_err_t i2c_lcd_init(i2c_lcd_info_t * i2c_lcd_info, smbus_info_t * smbus_info,
                           bool backlight, uint8_t num_rows, uint8_t num_columns, uint8_t num_visible_columns);

/**
 * @brief Reset the display. Custom characters will be cleared.
 *
 * @param[in] i2c_lcd_info Pointer to I2C-LCD info instance.
 * @return ESP_OK if successful, otherwise an error constant.
 */
esp_err_t i2c_lcd_reset(const i2c_lcd_info_t * i2c_lcd_info);

/**
 * @brief Clears entire display (clears DDRAM) and returns cursor to home position.
 *        DDRAM content is cleared, CGRAM content is not changed.
 *
 * @param[in] i2c_lcd_info Pointer to initialised I2C-LCD info instance.
 * @return ESP_OK if successful, otherwise an error constant.
 */
esp_err_t i2c_lcd_clear(const i2c_lcd_info_t * i2c_lcd_info);

/**
 * @brief Move cursor to home position. Also resets any display shift that may have occurred.
 *        DDRAM content is not changed. CGRAM content is not changed.
 *
 * @param[in] i2c_lcd_info Pointer to initialised I2C-LCD info instance.
 * @return ESP_OK if successful, otherwise an error constant.
 */
esp_err_t i2c_lcd_home(const i2c_lcd_info_t * i2c_lcd_info);

/**
 * @brief Move cursor to specified column and row position. This is where a new character will appear.
 *
 * @param[in] i2c_lcd_info Pointer to initialised I2C-LCD info instance.
 * @param[in] col Zero-based horizontal index of intended cursor position. Column 0 is the left column.
 * @param[in] row Zero-based vertical index of intended cursor position. Row 0 is the top row.
 * @return ESP_OK if successful, otherwise an error constant.
 */
esp_err_t i2c_lcd_move_cursor(const i2c_lcd_info_t * i2c_lcd_info, uint8_t col, uint8_t row);

/**
 * @brief Enable or disable the LED backlight.
 *
 * @param[in] i2c_lcd_info Pointer to initialised I2C-LCD info instance.
 * @param[in] enable True to enable, false to disable.
 * @return ESP_OK if successful, otherwise an error constant.
 */
esp_err_t i2c_lcd_set_backlight(i2c_lcd_info_t * i2c_lcd_info, bool enable);

/**
 * @brief Enable or disable the display. When disabled, the backlight is not affected, but any
 *        contents of the DDRAM is not displayed, nor is the cursor. The display is "blank".
 *        Re-enabling the display does not affect the contents of DDRAM or the state or position of the cursor.
 *
 * @param[in] i2c_lcd_info Pointer to initialised I2C-LCD info instance.
 * @param[in] enable True to enable, false to disable.
 * @return ESP_OK if successful, otherwise an error constant.
 */
esp_err_t i2c_lcd_set_display(i2c_lcd_info_t * i2c_lcd_info, bool enable);

/**
 * @brief Enable or disable display of the underline cursor.
 *        If enabled, this visually indicates where the next character written to the display will appear.
 *        It may be enabled alongside the blinking cursor, however the visual result is inelegant.
 *
 * @param[in] i2c_lcd_info Pointer to initialised I2C-LCD info instance.
 * @param[in] enable True to enable, false to disable.
 * @return ESP_OK if successful, otherwise an error constant.
 */
esp_err_t i2c_lcd_set_cursor(i2c_lcd_info_t * i2c_lcd_info, bool enable);

/**
 * @brief Enable or disable display of the blinking block cursor.
 *        If enabled, this visually indicates where the next character written to the display will appear.
 *        It may be enabled alongside the underline cursor, however the visual result is inelegant.
 *
 * @param[in] i2c_lcd_info Pointer to initialised I2C-LCD info instance.
 * @param[in] enable True to enable, false to disable.
 * @return ESP_OK if successful, otherwise an error constant.
 */
esp_err_t i2c_lcd_set_blink(i2c_lcd_info_t * i2c_lcd_info, bool enable);

/**
 * @brief Set cursor movement direction following each character write to produce left-to-right text.
 *
 * @param[in] i2c_lcd_info Pointer to initialised I2C-LCD info instance.
 * @return ESP_OK if successful, otherwise an error constant.
 */
esp_err_t i2c_lcd_set_left_to_right(i2c_lcd_info_t * i2c_lcd_info);

/**
 * @brief Set cursor movement direction following each character write to produce right-to-left text.
 *
 * @param[in] i2c_lcd_info Pointer to initialised I2C-LCD info instance.
 * @return ESP_OK if successful, otherwise an error constant.
 */
esp_err_t i2c_lcd_set_right_to_left(i2c_lcd_info_t * i2c_lcd_info);

/**
 * @brief Enable or disable auto-scroll of display.
 *        When enabled, the display will scroll as characters are written to maintain the cursor position on-screen.
 *        Left-to-right text will appear to be right-justified from the cursor position.
 *        When disabled, the display will not scroll and the cursor will move on-screen.
 *        Left-to-right text will appear to be left-justified from the cursor position.
 *
 * @param[in] i2c_lcd_info Pointer to initialised I2C-LCD info instance.
 * @param[in] enable True to enable, false to disable.
 * @return ESP_OK if successful, otherwise an error constant.
 */
esp_err_t i2c_lcd_set_auto_scroll(i2c_lcd_info_t * i2c_lcd_info, bool enable);

/**
 * @brief Scroll the display one position to the left. On-screen text will appear to move to the right.
 *
 * @param[in] i2c_lcd_info Pointer to initialised I2C-LCD info instance.
 * @return ESP_OK if successful, otherwise an error constant.
 */
esp_err_t i2c_lcd_scroll_display_left(const i2c_lcd_info_t * i2c_lcd_info);

/**
 * @brief Scroll the display one position to the right. On-screen text will appear to move to the left.
 * @param[in] i2c_lcd_info Pointer to initialised I2C-LCD info instance.
 * @return ESP_OK if successful, otherwise an error constant.
 */
esp_err_t i2c_lcd_scroll_display_right(const i2c_lcd_info_t * i2c_lcd_info);

/**
 * @brief Move the cursor one position to the left, even if it is invisible.
 *        This affects where the next character written to the display will appear.
 *
 * @param[in] i2c_lcd_info Pointer to initialised I2C-LCD info instance.
 * @return ESP_OK if successful, otherwise an error constant.
 */
esp_err_t i2c_lcd_move_cursor_left(const i2c_lcd_info_t * i2c_lcd_info);

/**
 * @brief Move the cursor one position to the right, even if it is invisible.
 *        This affects where the next character written to the display will appear.
 *
 * @param[in] i2c_lcd_info Pointer to initialised I2C-LCD info instance.
 * @return ESP_OK if successful, otherwise an error constant.
 */
esp_err_t i2c_lcd_move_cursor_right(const i2c_lcd_info_t * i2c_lcd_info);

/**
 * @brief Define a custom character from an array of pixel data.
 *
 *        There are eight possible custom characters, and the zero-based index is used
 *        to select a character to define. Any existing character definition at that index will be lost.
 *        Characters are 5 pixels wide and 8 pixels tall.
 *        The pixelmap array consists of up to eight bytes, each byte representing the pixel states per row.
 *        The first byte represents the top row. The eighth byte is often left as zero (to leave space for the underline cursor).
 *        For each row, the lowest five bits represent pixels that are to be illuminated. The least significant bit represents
 *        the right-most pixel. Empty rows will be zero.
 *
 *        NOTE: After calling this function, the DDRAM will not be selected and the cursor position will be undefined. Therefore it
 *        is important that the DDRAM address is set following this function, if text is to be written to the display.
 *        This can be performed with a call to i2c_lcd_home() or i2c_lcd_move_cursor().
 *
 *        Custom characters are written using the I2C_LCD_CHARACTER_CUSTOM_X definitions.
 *
 * @param[in] i2c_lcd_info Pointer to initialised I2C-LCD info instance.
 * @param[in] index Zero-based index of the character to define. Only values 0-7 are valid.
 * @param[in] pixelmap An 8-byte array defining the pixel map for the new character definition.
 * @return ESP_OK if successful, otherwise an error constant.
 */
esp_err_t i2c_lcd_define_char(const i2c_lcd_info_t * i2c_lcd_info, i2c_lcd_custom_index_t index, const uint8_t pixelmap[]);

/**
 * @brief Write a single character to the display at the current position of the cursor.
 *        Depending on the active mode, the cursor may move left or right, or the display may shift left or right.
 *        Custom characters can be written using the I2C_LCD_CHARACTER_CUSTOM_X definitions.
 *
 *        The display is I2C_LCD_NUM_COLUMNS wide, and upon encountering the end of the first line, the cursor
 *        will automatically move to the beginning of the second line.
 *
 * @param[in] i2c_lcd_info Pointer to initialised I2C-LCD info instance.
 * @return ESP_OK if successful, otherwise an error constant.
 */
esp_err_t i2c_lcd_write_char(const i2c_lcd_info_t * i2c_lcd_info, uint8_t chr);

/**
 * @brief Write a string of characters to the display, starting at the current position of the cursor.
 *        Depending on the active mode, the cursor may move left or right, or the display may shift left or right,
 *        after each character is written.
 *
 *        The display is I2C_LCD_NUM_COLUMNS wide, and upon encountering the end of the first line, the cursor
 *        will automatically move to the beginning of the second line.
 *
 * @param[in] i2c_lcd_info Pointer to initialised I2C-LCD info instance.
 * @return ESP_OK if successful, otherwise an error constant.
 */
esp_err_t i2c_lcd_write_string(const i2c_lcd_info_t * i2c_lcd_info, const char * string);

#ifdef __cplusplus
}
#endif

#endif // I2C_LCD_H
